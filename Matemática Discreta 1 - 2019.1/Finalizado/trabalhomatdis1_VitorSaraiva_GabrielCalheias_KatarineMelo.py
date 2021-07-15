# -*- coding: utf-8 -*-
"""
Created on Fri May 31 18:16:12 2019

@authors: Gabriel Calheias
          Katarine Melo
          Vitor Saraiva
"""
### Importações ###
from Tkinter import *
import sqlite3
import tkMessageBox

### Globais ###
conn = sqlite3.connect("cadastros.db")
cursor = conn.cursor()

def criarTabela():
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS cadastros (
            N INTEGER NOT NULL PRIMARY KEY,
            nome TEXT NOT NULL,
            valor REAL NOT NULL,
            parcelas INTEGER NOT NULL,
            juros REAL NOT NULL
        );
    """)

criarTabela()
r=2

#### Definições da Aplicação Principal ###
principal = Tk()
principal.title("Calculadora Financeira - Principal")
principal.resizable(FALSE, FALSE)
principal.configure(background='white')
principal['borderwidth'] = 10
principal['relief'] = 'solid'

#### Funções ###
def limpar():
    etN.delete(0, 'end')   
    etNome.delete(0, 'end')
    etValor.delete(0, 'end')
    etParcelas.delete(0, 'end')
    etJuros.delete(0, 'end')
    
def adicionar_cadastro():
    N = etN.get()
    nome = etNome.get()
    valor = etValor.get()
    parcelas = etParcelas.get()
    juros = etJuros.get()
    cursor.execute("""
        INSERT INTO cadastros (N,nome ,valor, parcelas,
        juros) VALUES (?, ?, ?, ?, ?)""",
        (N, nome, valor, parcelas, juros))
    conn.commit()
    lstCadastros.insert(END, (N, nome, valor, parcelas, juros))
           
def carregarvalores():   
    etNome.delete(0, 'end')
    etValor.delete(0, 'end')
    etParcelas.delete(0, 'end')
    etJuros.delete(0, 'end')
    N_cadastro = etN.get()
    for row in cursor.execute("""SELECT * FROM cadastros WHERE N=?""",
    (N_cadastro,)):
        etNome.insert(10, row[1])
        etValor.insert(10, row[2])
        etParcelas.insert(10, row[3])
        etJuros.insert(10, row[4])
            
def deletecadastro():
    newwin = Toplevel(principal)
    newwin.resizable(FALSE, FALSE)
    newwin.configure(background='white')
    newwin.title("Calculadora Financeira - Deletar")
    newwin['borderwidth'] = 10
    newwin['relief'] = 'solid'
    ### Widgets - Deletar Cadastro ###
    lblDeletarCadastro = Label(newwin, text="Deletar Simulação",
                               font="Arial 12 bold",background='white')
    lblNDeletar = Label(newwin, text="Nº da Simulação: ",font="Arial 10 bold",
                        background='white')
    etNDeletar = Entry(newwin, width=30,fg='blue',background='lightgrey')    
    def deletar_cadastro():
        N_cadastro = etNDeletar.get()
        cursor.execute("""
            DELETE FROM cadastros WHERE N=?""", (N_cadastro,))
        conn.commit()
        lstCadastros.delete(0, END)
        lista = cursor.execute("""
            SELECT * FROM cadastros;
            """)
        for i in lista:
            lstCadastros.insert(END, i)
    btnDel = Button(newwin, text="Deletar",font="Arial 10 bold",
                    command=deletar_cadastro)
    ### Posicionamento de Widgets - Deletar Cadastro ###
    lblDeletarCadastro.grid(row=0, column=0,columnspan=2)
    lblNDeletar.grid(row=1, column=0)
    etNDeletar.grid(row=1, column=1)
    btnDel.grid(row=2, column=1)

def alterarvalores():
    newwin = Toplevel(principal)
    newwin.resizable(FALSE, FALSE)
    newwin.configure(background='white')
    newwin.title("Calculadora Financeira - Alterar")
    newwin['borderwidth'] = 10
    newwin['relief'] = 'solid'
    ### Widgets - Alterar Valores ###
    lblMudarValores = Label(newwin, text="Alterar Simulação",
                            font="Arial 12 bold",background='white')
    lblNMudar = Label(newwin, text="Nº da Simulação: ",font="Arial 10 bold",
                      background='white')
    lblNovoNome = Label(newwin, text="Novo Nome:",font="Arial 10 bold",
                        background='white')
    lblNovaValor = Label(newwin, text="Novo Valor: ",font="Arial 10 bold",
                         background='white')
    lblNovaParcela = Label(newwin, text="Novo Nº de Parcelas: ",
                           font="Arial 10 bold",background='white')
    lblNovoJuros = Label(newwin, text="Novo Juros(% a.m.):",
                         font="Arial 10 bold",background='white')
    etNMudar = Entry(newwin,fg='blue',background='lightgrey',width = 30)
    etNovoNome = Entry(newwin,fg='blue',background='lightgrey',width = 30)
    etNovoValor = Entry(newwin,fg='blue',background='lightgrey',width = 30)
    etNovaParcela = Entry(newwin,fg='blue',background='lightgrey',width = 30)
    etNovoJuros = Entry(newwin,fg='blue',background='lightgrey',width = 30)   
    def mudar_valores():
        N_cadastro = etNMudar.get()
        novo_nome = etNovoNome.get()
        novo_valor = etNovoValor.get()
        nova_parcela = etNovaParcela.get()
        novo_juros = etNovoJuros.get()
        if (novo_valor=="" or nova_parcela=="" or novo_juros=="" or novo_nome==""):
            tkMessageBox.showerror("Erro!", "Algum Espaço Não Foi Preenchido")
        else:
            cursor.execute("""
                UPDATE cadastros SET nome = ? WHERE N = ?""",
                (novo_nome, N_cadastro))
            cursor.execute("""
                UPDATE cadastros SET valor = ? WHERE N = ?""",
                (novo_valor, N_cadastro))
            cursor.execute("""
                UPDATE cadastros SET parcelas = ? WHERE N = ?""",
                (nova_parcela, N_cadastro))
            cursor.execute("""
                UPDATE cadastros SET juros = ? WHERE N = ?""",
                (novo_juros, N_cadastro))
            conn.commit()
            lstCadastros.delete(0, END)
            lista = cursor.execute("""
                SELECT * FROM cadastros;
                """)
            for i in lista:
                lstCadastros.insert(END, i)
    btnMudarValor = Button(newwin, text="Alterar Simulação",
                           command=mudar_valores,font="Arial 10 bold")
    ### Posicionamento de Widgets - Alterar Valores ###
    lblMudarValores.grid(row=0, column=0,columnspan=2)
    lblNMudar.grid(row=1, column=0)
    etNMudar.grid(row=1, column=1)
    lblNovoNome.grid(row=2, column=0)
    etNovoNome.grid(row=2, column=1)
    lblNovaValor.grid(row=3, column=0)
    etNovoValor.grid(row=3, column=1)
    lblNovaParcela.grid(row=4, column=0)
    etNovaParcela.grid(row=4, column=1)
    lblNovoJuros.grid(row=5, column=0)
    etNovoJuros.grid(row=5, column=1)
    btnMudarValor.grid(row=6, column=1)

### Método SAC ###
def chamarsac(): 
    import Tkinter as tk
    def sac(frame):
        global widgets
        widgets={}
        v = float(etValor.get().replace(',', '.'))
        i = float(etJuros.get().replace(',', '.'))
        n = int(etParcelas.get())
        nome = etNome.get()
        tk.Label(frame, text = "Olá "+ nome +",\nAqui está a sua tabela de parcelamento SAC:",background='white',font ="Arial 12 bold").grid(row=0,columnspan=5)
        tk.Label(frame,text="Parâmetros ==> "+"Valor: R$"+str(round(v,r))+"  Parcelas: "+str(n)+"  Juros: "+str(i)+"% a.m.",
        background='darkgrey',borderwidth="1",relief="solid",font ="Arial 12").grid(row=1,columnspan=5)
        tk.Label(frame, text='Parcela',background='white',font ="Arial 12",fg="blue").grid(row=2, column=0,padx=10,pady=5)
        tk.Label(frame, text='Valor da Prestação',background='white',font ="Arial 12",fg="blue").grid(row=2, column=1,padx=10,pady=5)
        tk.Label(frame, text='Amortização',background='white',font ="Arial 12",fg="blue").grid(row=2, column=2,padx=10,pady=5)
        tk.Label(frame, text='Juros',background='white',font ="Arial 12",fg="blue").grid(row=2, column=3,padx=10,pady=5)
        tk.Label(frame, text='Saldo Devedor',background='white',font ="Arial 12",fg="blue").grid(row=2, column=4,padx=10,pady=5)
        tk.Label(frame,text="R$ "+str(round(v,r)),font ="Arial 10",fg="red",borderwidth="1",relief="solid").grid(row=3,column=4)
        tk.Label(frame,text="0",font="Arial 10 bold",fg="blue",background='darkgrey',borderwidth="1",relief="solid").grid(row=3,column=0)
        i = i/100
        sd=v
        a=v/n
        sj=0
        sp=0
        sa=0
        for c in range(0, n):
            j=i*sd
            pmt=a+j
            sd=sd-a  
            if sd<=0:
                sd=0
            tk.Label(frame,text=str(c+1),font="Arial 10 bold",fg="blue",
                     background='darkgrey',borderwidth="1",relief="solid").grid(row=c+4,column=0)
            tk.Label(frame,text="R$ "+str(round(pmt,r)),font="Arial 10",
                     fg="darkgreen",borderwidth="1",relief="solid").grid(row=c+4,column=1)
            tk.Label(frame,text="R$ "+str(round(a,r)),font="Arial 10",
                     fg="darkgreen",borderwidth="1",relief="solid").grid(row=c+4,column=2)
            tk.Label(frame,text="R$ "+str(round(j,r)),font="Arial 10",
                     fg="darkgreen",borderwidth="1",relief="solid").grid(row=c+4,column=3)
            tk.Label(frame,text="R$ "+str(round(sd,r)),font="Arial 10",
                     fg="red",borderwidth="1",relief="solid").grid(row=c+4,column=4)
            sj=round(sj+j,r)
            sp=round(sp+pmt,r)
            sa=round(sa+a,r)
            if sa>v or sa<v:
                sa=v
        tk.Label(frame,text="Totais",font="Arial 12 bold",fg="blue",background='darkgrey',borderwidth="1",relief="solid").grid(row=n+5,column=0)
        tk.Label(frame,text="R$ "+str(sj),font="Arial 10",fg="blue",borderwidth="1",relief="solid").grid(row=n+5,column=3)
        tk.Label(frame,text="R$ "+str(sa),font="Arial 10",fg="blue",borderwidth="1",relief="solid").grid(row=n+5,column=2)
        tk.Label(frame,text="R$ "+str(sp),font="Arial 10",fg="blue",borderwidth="1",relief="solid").grid(row=n+5,column=1)
    
    def onFrameConfigure(canvas):
        '''Reset the scroll region to encompass the inner frame'''
        canvas.configure(scrollregion=canvas.bbox("all"))       
    
    table_root = tk.Tk()
    canvas = tk.Canvas(table_root, borderwidth=0, background="#ffffff")
    frame = tk.Frame(canvas, background="#ffffff")
    vsb = tk.Scrollbar(table_root, orient="vertical", command=canvas.yview)
    canvas.configure(yscrollcommand=vsb.set)
    
    table_root.title("Calculadora Financeira - SAC")
    table_root.geometry('600x450')
    table_root.resizable(FALSE,TRUE)
    table_root.configure(background='white')
    table_root['borderwidth'] = 10
    table_root['relief'] = 'solid'
    
    vsb.pack(side="right", fill="y")
    canvas.pack(side="left", fill="both", expand=True)
    canvas.create_window((4,4), window=frame, anchor="nw")
    
    frame.bind("<Configure>", lambda event, canvas=canvas: onFrameConfigure(canvas))

    sac(frame)
            
### Método Price ###
def chamarprice():
    import Tkinter as tk
    def price(frame):
        global widgets
        widgets={}
        v = float(etValor.get().replace(',', '.'))
        i = float(etJuros.get().replace(',', '.'))
        n = int(etParcelas.get())
        nome = etNome.get()
        '''Put in some fake data'''
        tk.Label(frame, text = "Olá "+ nome +",\nAqui está a sua tabela de parcelamento Price:",background='white',font ="Arial 12 bold").grid(row=0,columnspan=5)
        tk.Label(frame,text="Parâmetros ==> "+"Valor: R$"+str(round(v,r))+"  Parcelas: "+str(n)+"  Juros: "+str(i)+"% a.m.",
        background='darkgrey',borderwidth="1",relief="solid",font ="Arial 12").grid(row=1,columnspan=5)
        tk.Label(frame, text='Parcela',background='white',font ="Arial 12",fg="blue").grid(row=2, column=0,padx=10,pady=5)
        tk.Label(frame, text='Valor da Prestação',background='white',font ="Arial 12",fg="blue").grid(row=2, column=1,padx=10,pady=5)
        tk.Label(frame, text='Amortização',background='white',font ="Arial 12",fg="blue").grid(row=2, column=2,padx=10,pady=5)
        tk.Label(frame, text='Juros',background='white',font ="Arial 12",fg="blue").grid(row=2, column=3,padx=10,pady=5)
        tk.Label(frame, text='Saldo Devedor',background='white',font ="Arial 12",fg="blue").grid(row=2, column=4,padx=10,pady=5)
        tk.Label(frame,text="R$ "+str(round(v,r)),font ="Arial 10",fg="red",borderwidth="1",relief="solid").grid(row=3,column=4)
        tk.Label(frame,text="0",font="Arial 10 bold",fg="blue",background='darkgrey',borderwidth="1",relief="solid").grid(row=3,column=0)
        i = i/100
        f = ((((1+i)**n)*i)/(((1+i)**n)-1))
        pmt = round(v*f,r)
        sd=v 
        sj=0 
        sp=0 
        sa=0
        for c in range(0, n):
            j=i*sd
            a=pmt-j
            sd=sd-a  
            if sd<=0:
                sd=0
            tk.Label(frame,text=str(c+1),font="Arial 10 bold",fg="blue",background='darkgrey',borderwidth="1",relief="solid").grid(row=c+4,column=0)
            tk.Label(frame,text="R$ "+str(round(pmt,r)),font="Arial 10",fg="darkgreen",borderwidth="1",relief="solid").grid(row=c+4,column=1)
            tk.Label(frame,text="R$ "+str(round(a,r)),font="Arial 10",fg="darkgreen",borderwidth="1",relief="solid").grid(row=c+4,column=2)
            tk.Label(frame,text="R$ "+str(round(j,r)),font="Arial 10",fg="darkgreen",borderwidth="1",relief="solid").grid(row=c+4,column=3)
            tk.Label(frame,text="R$ "+str(round(sd,r)),font="Arial 10",fg="red",borderwidth="1",relief="solid").grid(row=c+4,column=4)
            sj=round(sj+j,r)
            sa=round(sa+a,r)
        if sa>v or sa<v:
            sa=round(v,r)
        sp=round(sj+sa,r)
        tk.Label(frame,text="Totais",font="Arial 12 bold",fg="blue",background='darkgrey',borderwidth="1",relief="solid").grid(row=n+5,column=0)
        tk.Label(frame,text="R$ "+str(sj),font="Arial 10",fg="blue",borderwidth="1",relief="solid").grid(row=n+5,column=3)
        tk.Label(frame,text="R$ "+str(sa),font="Arial 10",fg="blue",borderwidth="1",relief="solid").grid(row=n+5,column=2)
        tk.Label(frame,text="R$ "+str(sp),font="Arial 10",fg="blue",borderwidth="1",relief="solid").grid(row=n+5,column=1)
        
    def onFrameConfigure(canvas):
        '''Reset the scroll region to encompass the inner frame'''
        canvas.configure(scrollregion=canvas.bbox("all"))
    table_root = tk.Tk()
    canvas = tk.Canvas(table_root, borderwidth=0, background="#ffffff")
    frame = tk.Frame(canvas, background="#ffffff")
    vsb = tk.Scrollbar(table_root, orient="vertical", command=canvas.yview)
    canvas.configure(yscrollcommand=vsb.set)
    
    table_root.title("Calculadora Financeira - Price")
    table_root.geometry('600x450')
    table_root.resizable(FALSE,TRUE)
    table_root.configure(background='white')
    table_root['borderwidth'] = 10
    table_root['relief'] = 'solid'
    
    vsb.pack(side="right", fill="y")
    canvas.pack(side="left", fill="both", expand=True)
    canvas.create_window((4,4), window=frame, anchor="nw")
    
    frame.bind("<Configure>", lambda event, canvas=canvas: onFrameConfigure(canvas))
    
    price(frame)
        
## Widgets - Principal ###
lblTitulo = Label(principal, text="Simulações Salvas:",font="Arial 12 bold",background='white')
lblNomeValor = Label(principal, text="Nº / Nome / Valor / Parcelas / Juros",font="Arial 10 bold",background='white')

### Widgets - Adicionar Cadastro ###
lblAdicionarCadastro = Label(principal, text="Nova Simulação",font="Arial 12 bold",background='white')
lblN = Label(principal, text="Nº da Simulação: ",font="Arial 10 bold",background='white')
lblNome = Label(principal, text="Nome: ",font="Arial 10 bold",background='white')
lblValor = Label(principal, text="Valor: ",font="Arial 10 bold",background='white')
lblParcelas = Label(principal, text="Nº de Parcelas: ",font="Arial 10 bold",background='white')
lblJuros = Label(principal, text="Juros(% a.m.): ",font="Arial 10 bold",background='white')
etN = Entry(principal,width = 30,fg='blue',background='lightgrey')
etNome = Entry(principal,width = 30,fg='blue',background='lightgrey')
etValor = Entry(principal,width = 30,fg='blue',background='lightgrey')
etParcelas = Entry(principal,width = 30,fg='blue',background='lightgrey')
etJuros = Entry(principal,width = 30,fg='blue',background='lightgrey')
btnAdd = Button(principal, text="Salvar Simulação",width = 20, command=adicionar_cadastro,font="Arial 10 bold")
btnsac = Button(principal, text="Gerar Tabela SAC",width = 20, command=chamarsac,font="Arial 10 bold")
btnprice = Button(principal, text="Gerar Tabela Price",width = 20, command=chamarprice,font="Arial 10 bold")
btnDelete = Button(principal, text="Deletar Simulação",width = 20, command=deletecadastro,font="Arial 10 bold")
btnAlterar = Button(principal, text="Alterar Simulação",width = 20, command=alterarvalores,font="Arial 10 bold")
btnCarregar = Button(principal, text="Carregar Simulação",width = 20, command=carregarvalores,font="Arial 10 bold")
btnLimpar = Button(principal, text="Limpar Campos",width = 20, command=limpar,font="Arial 10 bold")

### Widgets - Listar Cadastros ###
scrollbar = Scrollbar(principal)
lstCadastros = Listbox(principal, width=35, height=16,background='lightgrey')
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

### Posicionamento de Widgets - Listar Cadastros ###
lstCadastros.grid(rowspan=7, column=2)
scrollbar.grid(row=2,rowspan=7,column=3)

### Posicionamento de Widgets - Adicionar Cadastro###
lblAdicionarCadastro.grid(row=0,rowspan=2, column=0, columnspan=2)
lblN.grid(row=2, column=0)
etN.grid(row=2, column=1)
lblNome.grid(row=3, column=0)
etNome.grid(row=3, column=1)
lblValor.grid(row=4, column=0)
etValor.grid(row=4, column=1)
lblParcelas.grid(row=5,column=0)
etParcelas.grid(row=5,column=1)
lblJuros.grid(row=6,column=0)
etJuros.grid(row=6,column=1)
btnAdd.grid(row=9, column=0)
btnDelete.grid(row=10,column=2)
btnAlterar.grid(row=9,column=2)
btnsac.grid(row=7,column=0)
btnprice.grid(row=7,column=1)
btnLimpar.grid(row=8,column=0,columnspan=2)
btnCarregar.grid(row=9,column=1)

### Main ###
principal.mainloop()