from automata.tm.dtm import DTM
from fastapi import FastAPI, Request, Depends
from fastapi_mail import ConnectionConfig, MessageSchema, MessageType, FastMail
from sqlalchemy.orm import Session

from sql_app import crud, models, schemas
from sql_app.database import engine, SessionLocal
from util.email_body import EmailSchema

from prometheus_fastapi_instrumentator import Instrumentator

import pika
import json
from contextlib import contextmanager
from typing import List
from pydantic import BaseModel

# Variável global para lidar com as mensagens que serão enviadas por email
resultadosPorEmail = []

# Função para se conectar ao RabbitMQ
@contextmanager
def create_channel():
    try:
        # Conectar ao RabbitMQ
        connection = pika.BlockingConnection(pika.ConnectionParameters(host='rabbitMQ'))
        # Criar canal
        channel = connection.channel()
        # Criar fila
        channel.queue_declare(queue='filaFoda')

        yield channel
    except pika.exceptions.AMQPConnectionError as e:
        print("Error connecting to RabbitMQ:", repr(e))
    finally:
        connection.close()

# Função para consumir mensagens do RabbitMQ
async def consume_messages():
    with create_channel() as channel:
        queue_name = 'filaFoda'

        # Verifica se há mensagens pendentes na fila antes de iniciar o consumo
        method, properties, body = channel.basic_get(queue=queue_name)
        if not method:
            print("A fila '{queue_name}' está vazia. Nenhuma mensagem para consumir.")
            return
        
        # Definir o callback para tratar as mensagens recebidas
        channel.basic_consume(queue=queue_name, on_message_callback=callback, auto_ack=True)
        
        print('Processando mensagens . . . ')
        channel.start_consuming()

        # O loop de consumo termina aqui quando não houver mais mensagens na fila
        print('Todas as mensagens foram consumidas. Fechando o canal. Enviando emails')
        await send_emails()

models.Base.metadata.create_all(bind=engine)

conf = ConnectionConfig(
    MAIL_USERNAME="8f8c124614d170",
    MAIL_PASSWORD="f59a1e941b65ae",
    MAIL_FROM="from@example.com",
    MAIL_PORT=587,
    MAIL_SERVER="sandbox.smtp.mailtrap.io",
    MAIL_STARTTLS=False,
    MAIL_SSL_TLS=False,
    USE_CREDENTIALS=True,
    VALIDATE_CERTS=True
)

app = FastAPI()

Instrumentator().instrument(app).expose(app)

# Patter Singleton
# Dependency
def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()


@app.get("/get_history/{id}")
async def get_history(id: int, db: Session = Depends(get_db)):
    history = crud.get_history(db=db, id=id)
    if history is None:
        return {
            "code": "404",
            "msg": "not found"
        }
    return history


@app.get("/get_all_history")
async def get_all_history(db: Session = Depends(get_db)):
    history = crud.get_all_history(db=db)
    return history

# Função para lidar com os objetos JSON de um post
class InfoItem(BaseModel):
    states: List[str]
    input_symbols: List[str]
    tape_symbols: List[str]
    initial_state: str
    blank_symbol: str
    final_states: List[str]
    transitions: dict
    input: str

@app.post("/dtm")
async def dtm(info: List[InfoItem]):

    results = []

    # Recebendo os dados
    for item in info:
        states = set(item.states)
        input_symbols = set(item.input_symbols)
        tape_symbols = set(item.tape_symbols)
        initial_state = item.initial_state
        blank_symbol = item.blank_symbol
        final_states = set(item.final_states)
        transitions = item.transitions
        input = item.input

        # Validando os dados
        if len(states) == 0:
            return {
                "code": "400",
                "msg": "states cannot be empty"
            }
        
        if len(input_symbols) == 0:
            return {
                "code": "400",
                "msg": "input_symbols cannot be empty"
            }
        
        if len(tape_symbols) == 0:
            return {
                "code": "400",
                "msg": "tape_symbols cannot be empty"
            }
        
        if initial_state == "":
            return {
                "code": "400",
                "msg": "initial_state cannot be empty"
            }
        
        if blank_symbol == "":
            return {
                "code": "400",
                "msg": "blank_symbol cannot be empty"
            }
        
        if len(final_states) == 0:
            return {
                "code": "400",
                "msg": "final_states cannot be empty"
            }
        
        if len(transitions) == 0:
            return {
                "code": "400",
                "msg": "transitions cannot be empty"
            }
        
        if input == "":
            return {
                "code": "400",
                "msg": "input cannot be empty"
            }
        
        dtm = DTM(
            states=states,
            input_symbols=input_symbols,
            tape_symbols=tape_symbols,
            transitions=transitions,
            initial_state=initial_state,
            blank_symbol=blank_symbol,
            final_states=final_states,
        )

        if dtm.accepts_input(item.input):
            print('accepted')
            dtm_message = {
                "code": "200",
                "msg": "accepted",
                "info": {
                    "states": list(states),
                    "input_symbols": list(input_symbols),
                    "tape_symbols": list(tape_symbols),
                    "initial_state": initial_state,
                    "blank_symbol": blank_symbol,
                    "final_states": list(final_states),
                    "transitions": transitions,
                    "input": input
                }
            }
        else:
            print('rejected')
            dtm_message = {
                "code": "400",
                "msg": "rejected",
                "info": {
                    "states": list(states),
                    "input_symbols": list(input_symbols),
                    "tape_symbols": list(tape_symbols),
                    "initial_state": initial_state,
                    "blank_symbol": blank_symbol,
                    "final_states": list(final_states),
                    "transitions": transitions,
                    "input": input
                }
            }

        await data_send(dtm_message)

        results.append(dtm_message)

    await consume_messages()

    return results

# Função para enviar uma mensagem ao RabbitMQ
async def data_send(data):
    with create_channel() as channel:
        channel.basic_publish(exchange='', routing_key='filaFoda', body=json.dumps(data))

# Função para processar a mensagem recebida do RabbitMQ
def callback(channel, method, properties, body):
    print("Mensagem recebida:", body.decode())

    resultadosPorEmail.append(body)

# Função para enviar os emails
async def send_emails(db: Session = Depends(get_db)):

    for item in resultadosPorEmail:
        history = schemas.History(query=str(item["info"]), result=item["msg"])
        crud.create_history(db=db, history=history)

        email_shema = EmailSchema(email=["to@example.com"])

        await simple_send(email_shema, result=item["msg"], configuration=str(item["info"]))

    resultadosPorEmail.clear()

async def simple_send(email: EmailSchema, result: str, configuration: str):
    html = """
    <p>Thanks for using Fastapi-mail</p>
    <p> The result is: """ + result + """</p>
    <p> We have used this configuration: """ + configuration + """</p>
    """
    message = MessageSchema(
        subject="Fastapi-Mail module",
        recipients=email.dict().get("email"),
        body=html,
        subtype=MessageType.html)

    fm = FastMail(conf)
    await fm.send_message(message)
    return "OK"