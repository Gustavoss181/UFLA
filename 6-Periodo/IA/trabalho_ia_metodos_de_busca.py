from collections import deque
import tkinter as tk
from random import shuffle
import heapq
from tkinter import messagebox
from time import monotonic

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
def eh_solucionavel_lista(tabuleiro, objetivo):
  # conta o número de inversões em ambos
  inversoes_inicial = contar_inversoes(tabuleiro)
  inversoes_objetivo = contar_inversoes(objetivo)

  # se o número de inversões for par em ambos ou ímpar em ambos, é solucionável
  return (inversoes_inicial % 2) == (inversoes_objetivo % 2)

# Função para verificar se o tabuleiro inicial é solucionável
def eh_solucionavel(tabuleiro, objetivo):
  # converte o tabuleiro e o objetivo para listas unidimensionais
  lista_inicial = [num for linha in tabuleiro for num in linha]
  lista_objetivo = [num for linha in objetivo for num in linha]

  return eh_solucionavel_lista(lista_inicial, lista_objetivo)

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
      return caminho

    explorados.add(tuple(map(tuple, estado_atual)))  # adiciona o estado atual no conjunto dos explorados

    sucessores = {}
    for sucessor, acao in gerar_sucessores(estado_atual):
      sucessor_tupla = tuple(map(tuple, sucessor))
      if sucessor_tupla not in explorados:
        novo_custo = custo + 1
        heapq.heappush(fronteira, (novo_custo + calcular_distancia_manhattan(sucessor), novo_custo, sucessor, caminho + [acao]))
        sucessores[acao] = sucessor

  return None

# Função para encontrar a posição do zero (posição vazia)
def find_zero(state):
    return state.index(0)

# Função para gerar novos estados a partir de movimentos válidos
def generate_new_states(state):
    zero_pos = find_zero(state)
    new_states = []
    
    # Definindo os movimentos (cima, baixo, esquerda, direita)
    moves = {'Baixo': -3, 'Cima': 3, 'Direita': -1, 'Esquerda': 1}
    
    for move, pos_change in moves.items():
        new_pos = zero_pos + pos_change
        
        # Verifica se o movimento é válido
        if move == 'Baixo' and zero_pos >= 3 or \
           move == 'Cima' and zero_pos <= 5 or \
           move == 'Direita' and zero_pos % 3 != 0 or \
           move == 'Esquerda' and zero_pos % 3 != 2:
            new_state = state[:]
            new_state[zero_pos], new_state[new_pos] = new_state[new_pos], new_state[zero_pos]
            new_states.append((new_state, move))
    
    return new_states

# Implementação do BFS com contagem de estados gerados
def bfs(initial_state, goal_state):
    queue = deque([(initial_state, [])])  # Armazena (estado atual, caminho)
    visited = set()
    
    while queue:
        current_state, path = queue.popleft()
        visited.add(tuple(current_state))
        
        if current_state == goal_state:
            return path
        
        for new_state, move in generate_new_states(current_state):
            if tuple(new_state) not in visited:
                queue.append((new_state, path + [move]))
                visited.add(tuple(new_state))
    
    return None  # Se não encontrar solução

# Função para imprimir o estado do tabuleiro
def imprimir_estado(tabuleiro):
  for linha in tabuleiro:
    print(linha)
  print()

# Função que monta o caminho completo, a fim de facilitar a demonstração na interface
def obter_caminho_completo(tabuleiro_inicial, resultado):
  caminho_completo = []

  estado_atual = tabuleiro_inicial
  for acao_correta in resultado:
    caminho_completo.append({
      'estado_atual': estado_atual,
      'acoes_possiveis': [acao for _, acao in gerar_sucessores(estado_atual)],
      'acao_correta': acao_correta,
      'tabuleiros_sucessores': [sucessor for sucessor, _ in gerar_sucessores(estado_atual)]
    })
    for sucessor, acao_possivel in gerar_sucessores(estado_atual):
      if acao_possivel == acao_correta:
        estado_atual = sucessor
        break

  caminho_completo.append({
    'estado_atual': estado_atual,
    'acoes_possiveis': [],
    'acao_correta': acao_correta,
    'tabuleiros_sucessores': []
  })

  return caminho_completo

class JogoOitoInterface:
    def __init__(self, caminho_completo):
        self.caminho_completo = caminho_completo
        self.passo_atual = 0
        self.passo_final = len(self.caminho_completo) - 1

        self.root = tk.Tk()
        self.root.title(f"Jogo dos Oito - Tabuleiro Resolvido em {len(self.caminho_completo)} Passos!")

        self.largura_janela = 1000
        self.altura_janela = 700
        self.centralizar_janela(self.largura_janela, self.altura_janela)

        self.container = tk.Frame(self.root)
        self.container.pack(expand=True)

        self.titulo = tk.Label(self.container, text='', font=('Helvetica', 24))
        self.titulo.grid(row=0, column=0, columnspan=5, pady=(20, 20))

        self.labels = [[tk.Label(self.container, text='', font=('Helvetica', 32), width=2, height=1, relief="solid", borderwidth=1) for _ in range(3)] for _ in range(3)]
        for i in range(3):
            for j in range(3):
                self.labels[i][j].grid(row=i+1, column=j+1, padx=5, pady=10)

        self.sucessores_container = tk.Frame(self.root)
        self.sucessores_container.pack(expand=True, pady=5)

        botoes_container = tk.Frame(self.root)
        botoes_container.pack(pady=15)

        btn_primeiro = tk.Button(botoes_container, text="Ir para o primeiro passo", command=self.ir_para_primeiro)
        btn_primeiro.grid(row=0, column=0, padx=5)

        btn_voltar = tk.Button(botoes_container, text="Voltar passo", command=self.voltar_passo)
        btn_voltar.grid(row=0, column=1, padx=5)

        self.avanco_automatico = False
        self.btn_automatico = tk.Button(botoes_container, text="Automático", command=self.toggle_automatico)
        self.btn_automatico.grid(row=0, column=2, padx=5)

        btn_proximo = tk.Button(botoes_container, text="Próximo passo", command=self.proximo_passo)
        btn_proximo.grid(row=0, column=3, padx=5)

        btn_ultimo = tk.Button(botoes_container, text="Ir para o último passo", command=self.ir_para_ultimo)
        btn_ultimo.grid(row=0, column=4, padx=5)

        self.root.iconify()
        self.root.after(100, self.root.deiconify)
        self.root.focus_set()

        self.ir_para_primeiro()

        self.root.mainloop()

    def centralizar_janela(self, largura, altura):
        largura_tela = self.root.winfo_screenwidth()
        altura_tela = self.root.winfo_screenheight()
        x = (largura_tela / 2) - (largura / 2)
        y = (altura_tela / 2) - (altura / 2)
        self.root.geometry(f'{largura}x{altura}+{int(x)}+{int(y)}')

    def atualizar_tabuleiro(self):
        for widget in self.sucessores_container.winfo_children():
            widget.destroy()

        estado = self.caminho_completo[self.passo_atual]
        cor_fundo_final= self.root.cget('bg')
        if self.passo_atual == 0:
            self.titulo.config(text="Tabuleiro Inicial")
        elif self.passo_atual == self.passo_final:
            self.titulo.config(text="Tabuleiro Final")
            cor_fundo_final = 'green'
            if self.avanco_automatico:
                self.toggle_automatico()
        else:
            self.titulo.config(text=f"Passo Atual: {self.passo_atual + 1}º")
        for i in range(3):
            for j in range(3):
                self.labels[i][j].config(text=str(estado['estado_atual'][i][j]) if estado['estado_atual'][i][j] != 0 else '', bg=cor_fundo_final)

        if self.passo_atual != self.passo_final:
            self.sucessores_titulo = tk.Label(self.sucessores_container, text="Opções de Jogadas", font=('Helvetica', 20))
            self.sucessores_titulo.grid(row=0, column=0, columnspan=16, pady=(10, 20))

            quantidade_sucessores = len(estado['tabuleiros_sucessores'])
            acao_correta = estado['acao_correta']

            for idx, (acao, sucessor) in enumerate(zip(estado['acoes_possiveis'], estado['tabuleiros_sucessores'])):
                if acao == acao_correta:
                    cor_fundo = 'green'
                else:
                    cor_fundo = 'red'
                tk.Label(self.sucessores_container, text=f"Mover: {acao}", font=('Helvetica', 16)).grid(row=1, column=idx*4, columnspan=3, padx=(10, 0), pady=(10, 0))
                for i in range(3):
                    for j in range(3):
                        label = tk.Label(self.sucessores_container, text=str(sucessor[i][j]) if sucessor[i][j] != 0 else '', font=('Helvetica', 24), width=2, height=1, relief="solid", borderwidth=1)
                        label.grid(row=i+2, column=idx*4+j, padx=10, pady=10)
                        label.configure(bg=cor_fundo)
                if idx != quantidade_sucessores - 1:
                    phantom_label = tk.Label(self.sucessores_container, text='', width=2, height=1)
                    phantom_label.grid(row=3, column=idx*4+3, padx=10)

    def ir_para_primeiro(self):
        if self.avanco_automatico:
            self.toggle_automatico()
        self.passo_atual = 0
        self.atualizar_tabuleiro()

    def voltar_passo(self):
        if self.avanco_automatico:
            self.toggle_automatico()
        if self.passo_atual > 0:
            self.passo_atual -= 1
            self.atualizar_tabuleiro()

    def proximo_passo(self):
        if self.avanco_automatico:
            self.toggle_automatico()
        if self.passo_atual < self.passo_final:
            self.passo_atual += 1
            self.atualizar_tabuleiro()

    def toggle_automatico(self):
        if hasattr(self, 'after_id'):
            self.root.after_cancel(self.after_id)

        self.avanco_automatico = not self.avanco_automatico

        if self.avanco_automatico:
            self.btn_automatico.configure(bg='green')
            self.proximo_passo_automatico()
        else:
            self.btn_automatico.configure(bg=self.root.cget('bg'))


    def proximo_passo_automatico(self):
        if self.passo_atual < self.passo_final:
            self.passo_atual += 1
            self.atualizar_tabuleiro()
            self.after_id = self.root.after(500, self.proximo_passo_automatico)

    def ir_para_ultimo(self):
        if self.avanco_automatico:
            self.toggle_automatico()
        self.passo_atual = self.passo_final
        self.atualizar_tabuleiro()

class Interface:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Jogo dos Oito - Preencha o Tabuleiro")

        self.largura_janela = 400
        self.altura_janela = 400
        self.centralizar_janela(self.largura_janela, self.altura_janela)

        self.container = tk.Frame(self.root)
        self.container.pack(expand=True)

        self.titulo = tk.Label(self.container, text='Preencha o Tabuleiro', font=('Helvetica', 24))
        self.titulo.grid(row=0, column=0, columnspan=5, pady=(20, 20))

        self.entries = [[tk.Entry(self.container, font=('Helvetica', 32), width=2, justify='center') for _ in range(3)] for _ in range(3)]
        for i in range(3):
            for j in range(3):
                self.entries[i][j].grid(row=i+1, column=j+1, padx=5, pady=5)

        self.btn_aleatorio = tk.Button(self.container, text="Tabuleiro Aleatório", command=self.tabuleiro_aleatorio)
        self.btn_aleatorio.grid(row=4, column=0, columnspan=2, pady=10)

        self.btn_buscar = tk.Button(self.container, text="Buscar Solução por BFS", command=lambda: self.buscar_solucao('BFS'))
        self.btn_buscar.grid(row=4, column=3, columnspan=2, pady=10)

        self.btn_buscar = tk.Button(self.container, text="Buscar Solução por A*", command=lambda: self.buscar_solucao('A*'))
        self.btn_buscar.grid(row=5, column=3, columnspan=2, pady=10)

        self.root.iconify()
        self.root.after(100, self.root.deiconify)
        self.root.focus_set()
        self.root.mainloop()

    def centralizar_janela(self, largura, altura):
        largura_tela = self.root.winfo_screenwidth()
        altura_tela = self.root.winfo_screenheight()
        x = (largura_tela / 2) - (largura / 2)
        y = (altura_tela / 2) - (altura / 2)
        self.root.geometry(f'{largura}x{altura}+{int(x)}+{int(y)}')

    def tabuleiro_aleatorio(self):
        numeros = list(range(9))
        while not eh_solucionavel_lista(numeros, [1, 2, 3, 8, 0, 4, 7, 6, 5]):
            shuffle(numeros)
        for i in range(3):
            for j in range(3):
                self.entries[i][j].delete(0, tk.END)
                self.entries[i][j].insert(0, str(numeros.pop()))

    def buscar_solucao(self, metodo_de_busca):
        tabuleiro = self.obter_tabuleiro_atual()
        if tabuleiro != None:
            if self.validar_tabuleiro(tabuleiro):
                self.objetivo = [[1, 2, 3], [8, 0, 4], [7, 6, 5]]
                if(metodo_de_busca == 'BFS'):
                    tabuleiro_inline = [num for linha in tabuleiro for num in linha]
                    objetivo_inline = [num for linha in self.objetivo for num in linha]
                    inicio_tempo = monotonic()
                    resultado = bfs(tabuleiro_inline, objetivo_inline)
                    fim_tempo = monotonic()
                else:
                    inicio_tempo = monotonic()
                    resultado = busca_A_estrela(tabuleiro, self.objetivo)
                    fim_tempo = monotonic()
                print(resultado)
                if resultado is not None:
                    messagebox.showinfo("Tempo de Execução", "Solução encontrada em %.4fms" % ((fim_tempo - inicio_tempo)*1000))
                    caminho_completo = obter_caminho_completo(tabuleiro, resultado)
                    self.exibir_solucao(caminho_completo)
                else:
                    messagebox.showinfo("Sem Solução", "O tabuleiro informado não tem solução.")
            else:
                messagebox.showerror("Tabuleiro Inválido", "O tabuleiro informado não é válido. Certifique-se de preencher todos os números de 0 a 8 exatamente uma vez.")
        else:
            messagebox.showerror("Tabuleiro Inválido", "O tabuleiro informado não é válido. Certifique-se de preencher todas as células.")

    def obter_tabuleiro_atual(self):
        tabuleiro = []
        for i in range(3):
            linha = []
            for j in range(3):
                texto = self.entries[i][j].get()
                if texto == '':
                    return None
                valor = int(texto)
                linha.append(valor)
            tabuleiro.append(linha)
        return tabuleiro

    def validar_tabuleiro(self, tabuleiro):
        numeros = set(range(9))
        numeros_tabuleiro = set()
        for linha in tabuleiro:
            numeros_tabuleiro.update(linha)
        return numeros == numeros_tabuleiro

    def exibir_solucao(self, caminho_completo):
        self.root.destroy()
        JogoOitoInterface(caminho_completo)

Interface()
