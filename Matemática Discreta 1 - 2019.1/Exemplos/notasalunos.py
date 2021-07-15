# -*- coding: utf-8 -*-
"""
Created on Fri May 31 18:16:12 2019

@author: Sir Viktor
"""

### Importações ###
from Tkinter import *
import sqlite3

### Globais ###
conn = sqlite3.connect("cadastros.db")
cursor = conn.cursor()

def criarTabela():
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS cadastros (
            cpf INTEGER NOT NULL PRIMARY KEY,
            nome TEXT NOT NULL,
            valor REAL NOT NULL,
            parcelas INTEGER NOT NULL,
            juros REAL NOT NULL
        );
    """)

criarTabela()

#### Definições da Aplicaçao Principal ###
principal = Tk()
principal.title("Calculadora Financeira - Principal")
principal.resizable(FALSE, FALSE)

#### Funções ###
def adicionar_cadastro():
    cpf = etCPF.get()
    nome = etNome.get()
    valor = etValor.get()
    parcelas = etParcelas.get()
    juros = etJuros.get()
    cursor.execute("""
        INSERT INTO alunos (cpf, nome, valor, parcelas, juros) VALUES (?, ?, ?, ?, ?)""", (cpf, nome, valor, parcelas, juros))
    conn.commit()
    lstCadastros.insert(END, (cpf, nome, valor, parcelas, juros))

def deletar_cadastro():
    cpf_cadastro = etcpfDeletar.get()
    cursor.execute("""
        DELETE FROM alunos WHERE matricula=?""", (cpf_cadastro,))
    conn.commit()
    lstCadastros.delete(0, END)
    lista = cursor.execute("""
        SELECT * FROM cadastros;
        """)
    for i in lista:
        lstCadastros.insert(END, i)

def mudar_valores():
    cpf_cadastro = etcpfMudar.get()
    novo_valor = etNovoValor.get()
    nova_parcela = etNovaParcela.get()
    novo_juros = etNovoJuros.get()
    cursor.execute("""
        UPDATE cadastros SET valor = ? WHERE cpf = ?""", (novo_valor, cpf_cadastro))
    cursor.execute("""
        UPDATE cadastros SET parcelas = ? WHERE cpf = ?""", (nova_parcela, cpf_cadastro))
    cursor.execute("""
        UPDATE cadastros SET juros = ? WHERE cpf = ?""", (novo_juros, cpf_cadastro))
    conn.commit()
    lstCadastros.delete(0, END)
    lista = cursor.execute("""
        SELECT * FROM cadastros;
        """)
    for i in lista:
        lstCadastros.insert(END, i)

### Widgets - Principal ###
lblTitulo = Label(principal, text="Cadastros:")
lblNomeValor = Label(principal, text="CPF / Nome / Valor / Parcelas / Juros")

### Widgets - Adicionar Aluno ###
lblAdicionarCadastro = Label(principal, text="Novo Cadastro")
lblCPF = Label(principal, text="CPF: ")
lblNome = Label(principal, text="Nome: ")
lblValor = Label(principal, text="Valor: ")
lblParcelas = Label(principal, text="Parcelas: ")
lblJuros = Label(principal, text="Juros: ")
etCPF = Entry(principal)
etNome = Entry(principal)
etValor = Entry(principal)
etParcelas = Entry(principal)
etJuros = Entry(principal)
btnAdd = Button(principal, text="Salvar Dados", command=adicionar_cadastro)

### Widgets - Deletar Aluno ###
lblDeletarCadastro = Label(principal, text="Deletar Cadastro")
lblCPFDeletar = Label(principal, text="CPF: ")
etcpfDeletar = Entry(principal, width=10)
btnDel = Button(principal, text="Deletar", command=deletar_cadastro)

### Widgets - Mudar Nota ###
lblMudarValores = Label(principal, text="Mudar Valores")
lblCPFMudar = Label(principal, text="CPF: ")
lblNovoValor = Label(principal, text="Novo Valor: ")
lblNovaParcela = Label(principal, text="Nova Parcela: ")
lblNovoJuros = Label(principal, text="Novo Juros: ")
etCPFMudar = Entry(principal)
etNovoValor = Entry(principal)
etNovaParcela = Entry(principal)
etNovoJuros = Entry(principal)
btnMudarValor = Button(principal, text="Mudar Valores", command=mudar_valores)

### Widgets - Listar Alunos ###
scrollbar = Scrollbar(principal)
lstCadastros = Listbox(principal, width=35, height=16)
lstCadastros.config(yscrollcommand=scrollbar.set)
scrollbar.config(command=lstCadastros.yview)
lista = cursor.execute("""
    SELECT * FROM cadastros;
    """)
for i in lista:
    lstCadastros.insert(END, i)

### Posicionamento de Widgets - Principal ###
lblTitulo.grid(row=0,column=2)
lblNomeValor.grid(row=1, column=2)

### Posicionamento de Widgets - Listar Alunos ####
lstCadastros.grid(row=0,rowspan=15, column=2)
scrollbar.grid(row=3,column=3)

### Posicionamento de Widgets - Adicionar Aluno ###
lblAdicionarCadastro.grid(row=1, column=0, columnspan=2)
lblCPF.grid(row=2, column=0)
etCPF.grid(row=2, column=1)
lblNome.grid(row=3, column=0)
etNome.grid(row=3, column=1)
lblValor.grid(row=4, column=0)
etValor.grid(row=4, column=1)
lblParcelas.grid(row=5, column=0)
etParcelas.grid(row=5, column=1)
lblJuros.grid(row=6, column=0)
etJuros.grid(row=6, column=1)
btnAdd.grid(row=7, column=1)

### Posicionamento de Widgets - Deletar Aluno ###
lblDeletarCadastro.grid(row=8, column=0,columnspan=2)
lblCPFDeletar.grid(row=9, column=0)
etcpfDeletar.grid(row=10, column=1)
btnDel.grid(row=11, column=1)

### Posicionamento de Widgets - Mudar Nota ###
lblMudarValores.grid(row=12, column=0,columnspan=2)
lblCPFMudar.grid(row=13, column=0)
etCPFMudar.grid(row=13, column=1)
lblNovoValor.grid(row=14, column=0)
etNovoValor.grid(row=14, column=1)
lblNovaParcela.grid(row=15, column=0)
etNovaParcela.grid(row=15, column=1)
lblNovoJuros.grid(row=16, column=0)
etNovoJuros.grid(row=16, column=1)
btnMudarValor.grid(row=17, column=1)

principal.mainloop()