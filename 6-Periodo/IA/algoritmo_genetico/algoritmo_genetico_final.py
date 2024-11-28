import random
import tkinter as tk
from matplotlib.figure import Figure # type: ignore
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg # type: ignore
import numpy as np # type: ignore

class Interface():
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Algoritmo Genético - f(x): x² - 3x + 4")

        self.iterator = 0

        self.largura_janela = 750
        self.altura_janela = 500
        self.centralizar_janela(self.largura_janela, self.altura_janela)

        # Parâmetros Variáveis
        self.parametros = {
            'x_min': -10,
            'x_max': 10,
            'tamanho_cromossomo': 5,
            'tamanho_populacao': 4,
            'taxa_mutacao': 0.01,
            'taxa_cruzamento': 0.7,
            'geracoes': 5
        }

        self.criar_widgets()
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

    def criar_widgets(self):
        self.container = tk.Frame(self.root)
        self.container.pack(expand=True)

        self.titulo = tk.Label(self.container, text='Preencha Novos Parâmetros (Se Desejar)', font=('Helvetica', 24))
        self.titulo.grid(row=0, column=0, columnspan=3, pady=(20, 20))

        self.entries = []

        entry_x_min = tk.Entry(self.container, font=('Helvetica', 20), width=4, justify='center')
        entry_x_min.grid(row=1, column=1, padx=5, pady=5)
        self.entries.append(entry_x_min)

        entry_x_max = tk.Entry(self.container, font=('Helvetica', 20), width=4, justify='center')
        entry_x_max.grid(row=1, column=2, padx=5, pady=5)
        self.entries.append(entry_x_max)

        self.entries.extend(self.criar_entry(i) for i in range(5))
        self.criar_labels_entries()

        self.btn_resolver = tk.Button(self.container, text="Resolver", width=8, height=2, command=self.resolver)
        self.btn_resolver.grid(row=7, column=0, columnspan=3, pady=20)

    def criar_entry(self, index):
        entry = tk.Entry(self.container, font=('Helvetica', 20), width=4, justify='center')
        entry.grid(row=index+2, column=1, padx=5, pady=5)
        return entry

    def criar_labels_entries(self):
        labels = [
            ('Intervalo [min, max]:', 'x_min', 'x_max'),
            ('Tamanho cromossomo (# bits):', 'tamanho_cromossomo', None),
            ('Tamanho população:', 'tamanho_populacao', None),
            ('Taxa de mutação:', 'taxa_mutacao', None),
            ('Taxa de cruzamento:', 'taxa_cruzamento', None),
            ('Gerações:', 'geracoes', None)
        ]

        for i, (texto, param1, param2) in enumerate(labels):
            tk.Label(self.container, text=texto, font=('Helvetica', 18)).grid(row=i+1, column=0, padx=5, pady=5)
            if param2 is not None:
                self.entries[i * 2].insert(0, str(self.parametros[param1]))
                self.entries[i * 2 + 1].insert(0, str(self.parametros[param2]))
            else:
                self.entries[i + 1].insert(0, str(self.parametros[param1]))

    def aptidao(self, x):
        return x**2 - 3*x + 4

    def criar_individuo(self):
        return [random.randint(0, 1) for _ in range(self.parametros['tamanho_cromossomo'])]

    def decodificar_cromossomo(self, cromossomo):
        # binário para decimal
        decimal = int(''.join(map(str, cromossomo)), 2)
        max_decimal = 2 ** len(cromossomo) - 1
        # decodificando o valor decimal para o intervalo [x_min, x_max] de x
        x = self.parametros['x_min'] + (self.parametros['x_max'] - self.parametros['x_min']) * (decimal / max_decimal)
        return x

    def selecao_torneio(self, populacao, comparacoes = 2):
        selecionados = random.sample(populacao, comparacoes)
        return min(selecionados, key=lambda cromossomo: self.aptidao(self.decodificar_cromossomo(cromossomo)))

    def cruzamento(self, pai1, pai2):
        if random.random() < self.parametros['taxa_cruzamento']:
            ponto = random.randint(1, len(pai1) - 1)
            return pai1[:ponto] + pai2[ponto:], pai2[:ponto] + pai1[ponto:]
        else:
            return pai1, pai2

    def mutacao(self, individuo):
        ocorreu = False
        for i in range(len(individuo)):
            if random.random() < self.parametros['taxa_mutacao']:
                individuo[i] = 1 - individuo[i]
                ocorreu = True
        return ocorreu

    def exibir_grafico(self, canvas, ax, geracoes):
        populacao_atual = geracoes[self.iterator]

        ax.cla()

        # Gerar valores de x
        x = np.linspace(self.parametros['x_min'], self.parametros['x_max'])
        # Calcular os valores de y usando a função definida
        y = self.aptidao(x)

        # Plotar a função na figura
        ax.plot(x, y)
        ax.set_title('Geração ' + self.iterator.__str__())
        ax.set_xlabel('x')
        ax.set_ylabel('y = x² - 3x + 4')
        
        melhor_individuo = min(populacao_atual, key=lambda cromossomo: self.aptidao(self.decodificar_cromossomo(cromossomo)))
        melhor_individuo = self.decodificar_cromossomo(melhor_individuo)

        for cromossomo in populacao_atual:
            ponto_x = self.decodificar_cromossomo(cromossomo)
            ponto_y = self.aptidao(ponto_x)
            cor = 'green' if melhor_individuo == ponto_x else 'red'
            ax.scatter(ponto_x, ponto_y, color=cor)  # Adicionar ponto em vermelho
        
        canvas.draw()
    
    def proxima_geracao(self, canvas, ax, geracoes):
        if self.iterator < len(geracoes)-1:
            self.iterator += 1
            self.exibir_grafico(canvas, ax, geracoes)
    
    def geracao_anterior(self, canvas, ax, geracoes):
        if self.iterator > 0:
            self.iterator -= 1
            self.exibir_grafico(canvas, ax, geracoes)


    def gerar_janela_grafico(self, geracoes):
        self.iterator = 0
        # Criar uma nova janela
        new_window = tk.Toplevel(self.root)
        new_window.title("Gráfico da Função f(x): x² - 3x + 4")

        # Criar uma figura do matplotlib
        fig = Figure(figsize=(6, 4), dpi=100)
        ax = fig.add_subplot(111)

        # Criar um canvas do tkinter que conterá a figura do matplotlib
        canvas = FigureCanvasTkAgg(fig, master=new_window)
        canvas.draw()
        canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)

        # Criar um frame para os botões
        button_frame = tk.Frame(new_window)
        button_frame.pack(side=tk.BOTTOM, pady=10)

        # Adicionar os botões ao frame
        prev_button = tk.Button(button_frame, text="Geração Anterior", command=lambda: self.geracao_anterior(canvas, ax, geracoes))
        prev_button.pack(side=tk.LEFT, padx=5)

        next_button = tk.Button(button_frame, text="Próxima Geração", command=lambda: self.proxima_geracao(canvas, ax, geracoes))
        next_button.pack(side=tk.LEFT, padx=5)

        self.exibir_grafico(canvas, ax, geracoes)
        

    def resolver(self):
        self.parametros['x_min'] = float(self.entries[0].get())
        self.parametros['x_max'] = float(self.entries[1].get())
        self.parametros['tamanho_cromossomo'] = int(self.entries[2].get())
        self.parametros['tamanho_populacao'] = int(self.entries[3].get())
        self.parametros['taxa_mutacao'] = float(self.entries[4].get())
        self.parametros['taxa_cruzamento'] = float(self.entries[5].get())
        self.parametros['geracoes'] = int(self.entries[6].get())

        populacao = [self.criar_individuo() for _ in range(self.parametros['tamanho_populacao'])]

        geracoes = [populacao.copy()]

        for geracao in range(self.parametros['geracoes']):
            print(f'Geração {geracao + 1}')
            print(f'População atual: ')
            for idx, cromossomo in enumerate(populacao):
                print(f'\tCromossomo {idx + 1}: {cromossomo}')

            pai1 = self.selecao_torneio(populacao)
            pai2 = self.selecao_torneio(populacao)
            while pai2 == pai1:
                pai2 = self.selecao_torneio(populacao)
            print(f'Pai 1: {pai1}, Aptidão: {self.aptidao(self.decodificar_cromossomo(pai1))}')
            print(f'Pai 2: {pai2}, Aptidão: {self.aptidao(self.decodificar_cromossomo(pai2))}')

            filho1, filho2 = self.cruzamento(pai1, pai2)
            print(f'Filho 1: {filho1}, Aptidão: {self.aptidao(self.decodificar_cromossomo(filho1))}')
            if self.mutacao(filho1):
                print(f'Filho 1 pós mutação: {filho1}, Aptidão: {self.aptidao(self.decodificar_cromossomo(filho1))}')
            print(f'Filho 2: {filho2}, Aptidão: {self.aptidao(self.decodificar_cromossomo(filho2))}')
            if self.mutacao(filho2):
                print(f'Filho 2 pós mutação: {filho2}, Aptidão: {self.aptidao(self.decodificar_cromossomo(filho2))}')

            populacao.remove(pai1)
            populacao.remove(pai2)
            populacao.extend([filho1, filho2])
            print()
            geracoes.append(populacao.copy())

        melhor_individuo = min(populacao, key=lambda cromossomo: self.aptidao(self.decodificar_cromossomo(cromossomo)))
        melhor_x = self.decodificar_cromossomo(melhor_individuo)
        melhor_aptidao = self.aptidao(melhor_x)

        print(f"Melhor x: {melhor_x}")
        print(f"Valor mínimo da função: {melhor_aptidao}")

        self.gerar_janela_grafico(geracoes)

Interface()