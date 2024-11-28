import tkinter as tk
import random
from collections import deque
from tkinter import messagebox

# Função para contabilizar as inversões
def contar_inversoes(lista):
  inversoes = 0
  for i in range(len(lista)):
    for j in range(i + 1, len(lista)):
      if lista[i] != 0 and lista[j] != 0 and lista[i] > lista[j]:
        inversoes += 1
  return inversoes

# Função para verificar se o tabuleiro inicial é solucionável
def eh_solucionavel(initial_state, goal_state):
  # conta o número de inversões em ambos
  inversoes_inicial = contar_inversoes(initial_state)
  inversoes_objetivo = contar_inversoes(goal_state)

  # se o número de inversões for par em ambos ou ímpar em ambos, é solucionável
  return (inversoes_inicial % 2) == (inversoes_objetivo % 2)

def randomize_initial_state(initial_state, goal_state):
    random.shuffle(initial_state)
    while(not eh_solucionavel(initial_state, goal_state)):
        random.shuffle(initial_state)
    return initial_state

# Função para encontrar a posição do zero (posição vazia)
def find_zero(state):
    return state.index(0)

# Função para gerar novos estados a partir de movimentos válidos
def generate_new_states(state):
    zero_pos = find_zero(state)
    new_states = []
    
    # Definindo os movimentos (cima, baixo, esquerda, direita)
    moves = {'up': -3, 'down': 3, 'left': -1, 'right': 1}
    
    for move, pos_change in moves.items():
        new_pos = zero_pos + pos_change
        
        # Verifica se o movimento é válido
        if move == 'up' and zero_pos >= 3 or \
           move == 'down' and zero_pos <= 5 or \
           move == 'left' and zero_pos % 3 != 0 or \
           move == 'right' and zero_pos % 3 != 2:
            new_state = state[:]
            new_state[zero_pos], new_state[new_pos] = new_state[new_pos], new_state[zero_pos]
            new_states.append(new_state)
    
    return new_states

# Implementação do BFS com contagem de estados gerados
def bfs(initial_state, goal_state):
    queue = deque([(initial_state, [])])  # Armazena (estado atual, caminho)
    visited = set()
    
    while queue:
        current_state, path = queue.popleft()
        visited.add(tuple(current_state))
        
        if current_state == goal_state:
            return path + [current_state]
        
        for new_state in generate_new_states(current_state):
            if tuple(new_state) not in visited:
                queue.append((new_state, path + [new_state]))
                visited.add(tuple(new_state))
    
    return None  # Se não encontrar solução

# Função para atualizar a interface gráfica
def update_board(board, state):
    for i in range(9):
        row = i // 3
        col = i % 3
        board[row][col].config(text=str(state[i]) if state[i] != 0 else "")

# Função para mostrar a solução passo a passo
def show_solution():
    solution = bfs(initial_state, goal_state)
    if solution:
        for state in solution:
            update_board(board, state)
            root.update()
            root.after(2000)
    else:
        print("Nenhuma solução encontrada.")

# Estado inicial aleatório
def restart_randomized():
    randomize_initial_state(initial_state, goal_state)
    update_board(board, initial_state)

# Configuração da interface gráfica
root = tk.Tk()
root.title("Jogo dos 8")

main_screen = tk.Frame(root)
main_screen.grid(row=0, column=0, padx=20)
board = [[None for _ in range(3)] for _ in range(3)]
for row in range(3):
    for col in range(3):
        label = tk.Label(main_screen, text="", font=("Helvetica", 32), width=2, height=1, borderwidth=2, relief="groove")
        label.grid(row=row, column=col, padx=5, pady=5)
        board[row][col] = label

# Representação do estado como uma lista de 9 elementos
initial_state = [1, 2, 3, 4, 5, 6, 7, 8, 0] # Exemplo de estado inicial
goal_state = [1, 2, 3, 8, 0, 4, 7, 6, 5]    # Estado objetivo
randomize_initial_state(initial_state, goal_state) # Aleatoriza e verifica se a solução é possível



# botao reset
# botao gerar solucao
# botao proximo passo (depois de clicar na solucao)
# botao passo anterior


buttons_frame = tk.Frame(root)
buttons_frame.grid(row=1)

def proximo_passo():
    if solution == []:
        messagebox.showwarning(message="Clique no botão 'solucionar'")
    if indice_passos < len(solution)-1:
        passo_atual = solution[indice_passos]
        update_board(board, passo_atual)
        indice_passos += 1

def passo_anterior():
    if solution == []:
        messagebox.showwarning(message="Clique no botão 'solucionar'")
    if indice_passos > 0:
        passo_atual = solution[indice_passos]
        update_board(board, passo_atual)
        indice_passos += 1

def resetar():
    solution = []
    passo_atual = initial_state
    indice_passos = 0

def solucionar():
    solution = bfs(initial_state, goal_state)

indice_passos = 0
solution = []

# Botão para o proximo passo
gerar_solucao_button = tk.Button(buttons_frame, text="Solucionar com BFS", command=solucionar)
gerar_solucao_button.grid(row=0, column=0)

# Botão para reorganizar aleatoriamente o início do jogo
resetar_button = tk.Button(buttons_frame, text="Resetar", command=resetar)
resetar_button.grid(row=0, column=1)

# Botão para o proximo passo
prox_passo_button = tk.Button(buttons_frame, text="Próximo passo", command=proximo_passo)
prox_passo_button.grid(row=1, column=1)

# Botão para reorganizar aleatoriamente o início do jogo
prev_button = tk.Button(buttons_frame, text="Passo Anterior", command=restart_randomized)
prev_button.grid(row=1, column=0)

update_board(board, initial_state)  # Mostrar o estado inicial
root.mainloop()
