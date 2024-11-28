import heapq
from time import monotonic
import tkinter as tk
import random
from tkinter import messagebox

# Função para encontrar a posição do espaço vazio no tabuleiro
def encontrar_vazio(tabuleiro):
  for i in range(3):
    for j in range(3):
      if tabuleiro[i][j] == 0:
        return i, j

# A distância Manhattan consiste em determinar o montante das distância entre a posição atual de cada valor no tabuleiro com a posição desejada
def calcular_distancia_manhattan(tabuleiro):
  manhattan = 0
  for i in range(3):
    for j in range(3):
      if tabuleiro[i][j] != 0:  # ignora o espaço vazio
        valor = tabuleiro[i][j]
        if valor == 1:
            linha, coluna = 0, 0
        elif valor == 2:
            linha, coluna = 0, 1
        elif valor == 3:
            linha, coluna = 0, 2
        elif valor == 8:
            linha, coluna = 1, 0
        elif valor == 4:
            linha, coluna = 1, 2
        elif valor == 7:
            linha, coluna = 2, 0
        elif valor == 6:
            linha, coluna = 2, 1
        elif valor == 5:
            linha, coluna = 2, 2

        manhattan += abs(i - linha) + abs(j - coluna)

  return manhattan

# Função para gerar os estados sucessores válidos
def gerar_sucessores(tabuleiro):
  sucessores = []
  linha_vazia, coluna_vazia = encontrar_vazio(tabuleiro)

  for variacao_linha, variacao_coluna, acao in [(1, 0, 'Cima'), (-1, 0, 'Baixo'), (0, 1, 'Esquerda'), (0, -1, 'Direita')]:
    nova_linha, nova_coluna = linha_vazia + variacao_linha, coluna_vazia + variacao_coluna
    if 0 <= nova_linha < 3 and 0 <= nova_coluna < 3:
      novo_tabuleiro = [linha[:] for linha in tabuleiro]  # copia o tabuleiro atual
      # troca o espaço vazio com o espaço valorado específico
      novo_tabuleiro[linha_vazia][coluna_vazia], novo_tabuleiro[nova_linha][nova_coluna] = novo_tabuleiro[nova_linha][nova_coluna], novo_tabuleiro[linha_vazia][coluna_vazia]
      sucessores.append((novo_tabuleiro, acao))

  return sucessores

# Função para verificar se um estado é o estado objetivo
def eh_o_objetivo(tabuleiro, objetivo):
    return tabuleiro == objetivo

# Função para contabilizar as inversões
def contar_inversoes(lista):
  inversoes = 0
  for i in range(len(lista)):
    for j in range(i + 1, len(lista)):
      if lista[i] != 0 and lista[j] != 0 and lista[i] > lista[j]:
        inversoes += 1
  return inversoes

# Função para verificar se o tabuleiro inicial é solucionável
def eh_solucionavel(tabuleiro, objetivo):
  # converte o tabuleiro e o objetivo para listas unidimensionais
  lista_inicial = [num for linha in tabuleiro for num in linha]
  lista_objetivo = [num for linha in objetivo for num in linha]

  # conta o número de inversões em ambos
  inversoes_inicial = contar_inversoes(lista_inicial)
  inversoes_objetivo = contar_inversoes(lista_objetivo)

  # se o número de inversões for par em ambos ou ímpar em ambos, é solucionável
  return (inversoes_inicial % 2) == (inversoes_objetivo % 2)

# Função de busca A*
def busca_A_estrela(tabuleiro_inicial, objetivo):
  if not eh_solucionavel(tabuleiro_inicial, objetivo):
    return None

  fronteira = []
  heapq.heappush(fronteira, (calcular_distancia_manhattan(tabuleiro_inicial), 0, tabuleiro_inicial, []))  # Fila de prioridade com a tupla (heurística, custo, estado, caminho)
  explorados = set()  # conjunto dos estados já explorados

  while fronteira:
    _, custo, estado_atual, caminho = heapq.heappop(fronteira)

    if eh_o_objetivo(estado_atual, objetivo):
      return caminho + [estado_atual]

    explorados.add(tuple(map(tuple, estado_atual)))  # adiciona o estado atual no conjunto dos explorados

    sucessores = {}
    for sucessor, acao in gerar_sucessores(estado_atual):
      sucessor_tupla = tuple(map(tuple, sucessor))
      if sucessor_tupla not in explorados:
        novo_custo = custo + 1
        heapq.heappush(fronteira, (novo_custo + calcular_distancia_manhattan(sucessor), novo_custo, sucessor, caminho + [estado_atual]))
        sucessores[acao] = sucessor

  return None

# Função para imprimir o estado do tabuleiro
def imprimir_estado(tabuleiro):
  for linha in tabuleiro:
    print(linha)
  print()

# Função que monta o caminho completo, a fim de facilitar a demonstração na interface
def obter_caminho_completo(tabuleiro_inicial, resultado):
  caminho_completo = []

  estado_atual = tabuleiro_inicial
  caminho_completo.append({
      'estado_atual': estado_atual,
      'acoes_possiveis': [acao for _, acao in gerar_sucessores(estado_atual)],
      'acao_correta': resultado[0],
      'tabuleiros_sucessores': [sucessor for sucessor, _ in gerar_sucessores(estado_atual)],
      'passo': 0
  })

  for idx, acao_correta in enumerate(resultado):
    for sucessor, acao_possivel in gerar_sucessores(estado_atual):
      if acao_possivel == acao_correta:
        estado_atual = sucessor
        break

    caminho_completo.append({
        'estado_atual': estado_atual,
        'acoes_possiveis': [acao for _, acao in gerar_sucessores(estado_atual)],
        'acao_correta': acao_correta,
        'tabuleiros_sucessores': [sucessor for sucessor, _ in gerar_sucessores(estado_atual)],
        'passo': idx + 1
    })

  return caminho_completo

def randomize_initial_state(initial_state, goal_state):
    random.shuffle(initial_state)
    while(not eh_solucionavel(initial_state, goal_state)):
        random.shuffle(initial_state)
    return initial_state

estado_inicial = [[7, 0, 8], [3, 1, 2], [4, 6, 5]]  # exemplo qualquer
objetivo = [[1, 2, 3], [8, 0, 4], [7, 6, 5]]
# inicio = monotonic()
# resultado = busca_A_estrela(estado_inicial, objetivo)
# fim = monotonic()

# if resultado is not None:
#   print(f"Tabuleiro resolvido em {len(resultado)} passos!\n")
#   print(f"Caminho: {resultado}\n")

#   caminho_completo = obter_caminho_completo(estado_inicial, resultado)

#   for estado in caminho_completo:
#     if estado['passo'] == 0:
#       print("Estado Inicial:")
#     elif estado['passo'] == len(resultado):
#       print(f"Passo {estado['passo']}: Mover {estado['acao_correta']}")
#       print("Estado Final:")
#     else:
#       print(f"Passo {estado['passo']}: Mover {estado['acao_correta']}")
#       print("Estado Atual:")
#     imprimir_estado(estado['estado_atual'])
#     if estado['passo'] != len(resultado):
#       print("Tabuleiros Sucessores:")
#       for acao, sucessor in zip(estado['acoes_possiveis'], estado['tabuleiros_sucessores']):
#         print(f"Ação: Mover {acao}")
#         imprimir_estado(sucessor)

# print("Tempo total para a busca A*: " + str((fim - inicio) * 1000) + " milissegundo(s)")
# else:
#   print("Tabuleiro insolucionável.")




  # Função para atualizar a interface gráfica
def update_board(board, state):
    for i in range(9):
        row = i // 3
        col = i % 3
        board[row][col].config(text=str(state[row][col]) if state[row][col] != 0 else "")

# Função para mostrar a solução passo a passo
def show_solution():
    inicio = monotonic()
    solution = busca_A_estrela(estado_inicial, objetivo)
    fim = monotonic()
    messagebox.showinfo("Tempo", "Tempo total para a busca A*: " + ("%.2f" % ((fim - inicio) * 1000)) + " milissegundo(s)")
    if solution:
        for state in solution:
            update_board(board, state)
            root.update()
            root.after(500)
    else:
        print("Nenhuma solução encontrada.")

def restart_randomized():
    randomize_initial_state(estado_inicial, objetivo)
    update_board(board, estado_inicial)

# Configuração da interface gráfica
root = tk.Tk()
root.title("Jogo dos 8")

board = [[None for _ in range(3)] for _ in range(3)]
for row in range(3):
    for col in range(3):
        label = tk.Label(root, text="", font=("Helvetica", 32), width=2, height=1, borderwidth=2, relief="groove")
        label.grid(row=row, column=col, padx=5, pady=5)
        board[row][col] = label

# Botão para iniciar a demonstração
button = tk.Button(root, text="Mostrar Solução", command=show_solution)
button.grid(row=3, column=0, columnspan=3)

button2 = tk.Button(root, text="Aleatorizar Início", command=restart_randomized)
button2.grid(row=4, column=0, columnspan=3)

update_board(board, estado_inicial)  # Mostrar o estado inicial
root.mainloop()