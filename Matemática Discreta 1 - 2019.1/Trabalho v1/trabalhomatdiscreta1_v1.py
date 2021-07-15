# -*- coding: utf-8 -*-
"""
Created on Wen May 29 16:38:21 2019

@author: Vitor Saraiva
"""
from Tkinter import *
import sqlite3

class Application:
    def __init__(self, master=None):
        #Janela Principal        
        frame = Frame(root)
        frame.configure(background='white')
        root.iconbitmap('C:\Users\Vitor\Desktop\Trabalho Matemática Discreta 1\Trabalho v1\icon.ico')
        frame.pack(side=TOP)
        Label(frame,text="  ",background='white').grid(rowspan=9,column=0)
        Label(frame,text="  ",background='white').grid(rowspan=9,column=3)
        Label(frame,text=" ",background='white').grid(row=0,columnspan=4) 
        titulo = Label(frame, text="Entre com os dados:",font = "Arial 12 bold",background='white')
        nomeLabel = Label(frame,text="Nome:", font="Arial 10 bold",background='white')
        self.nomeinput = Entry(frame,width = 30,font = "Arial 10",fg="blue",background='grey')
        valorLabel = Label(frame,text="Valor:", font="Arial 10 bold",background='white')
        self.valorinput = Entry(frame,width = 30,font = "Arial 10",fg="blue",background='grey')
        parcelasLabel = Label(frame, text="Parcelas:", font="Arial 10 bold",background='white')
        self.parcelasinput = Entry(frame,width = 30,font= "Arial 10",fg="blue",background='grey')
        jurosLabel = Label(frame, text="Juros(% a.m.):", font="Arial 10 bold",background='white')
        self.jurosinput = Entry(frame,width = 30,font = "Arial 10",fg="blue",background='grey')
        titulo2 = Label(frame, text="Metodo de parcelamento:",font ="Arial 12 bold",background='white')
        SAC = Button(frame,text = "SAC",font = "Arial 10 bold",command = self.sac, width= 12)
        Price = Button(frame,text="Price",font = "Arial 10 bold",width = 12,command = self.price)
        Label(frame,text=" ",background='white').grid(row=8,columnspan=4)
            
        #Packing
        titulo.grid(row=1,columnspan=4)
        nomeLabel.grid(row=2,column=1)
        self.nomeinput.grid(row=2,column=2)
        valorLabel.grid(row=3,column=1)
        self.valorinput.grid(row=3,column=2)
        parcelasLabel.grid(row=4,column=1)
        self.parcelasinput.grid(row=4,column=2)
        jurosLabel.grid(row=5,column=1)
        self.jurosinput.grid(row=5,column=2)
        titulo2.grid(row=6,columnspan=4)
        SAC.grid(row=7,column=1)
        Price.grid(row=7,column=2)
   
   #Método SAC
    def sac(self):
        nome = self.nomeinput.get()
        v = float(self.valorinput.get().replace(',', '.'))
        i = float(self.jurosinput.get().replace(',', '.'))
        n = int(self.parcelasinput.get())
        newwin = Toplevel(root)
        newwin.iconbitmap('icon.ico')
        display = Label(newwin, text="Olá "+nome+", \nAqui está a sua tabela de parcelamento SAC:",font="Arial 12 bold",fg="black")
        Label(newwin,text="Parâmetros ==> "+"Valor: R$"+str(round(v,r))+"  Parcelas: "+str(n)+"  Juros: "+str(i)+"% a.m.",relief=RIDGE,font="Arial 10",fg="black",background='white').grid(row=1,columnspan=5)
        lb = Label(newwin, text="Parcela  ",font ="Arial 10 bold",fg="blue",background='darkgrey',relief=RIDGE)
        lb1 = Label(newwin, text="Valor da Prestação  ",font ="Arial 10 bold",fg="blue",background='darkgrey',relief=RIDGE)
        lb2 = Label(newwin, text="Amortização  ",font ="Arial 10 bold",fg="blue",background='darkgrey',relief=RIDGE)
        lb3 = Label(newwin, text="Juros  ",font ="Arial 10 bold",fg="blue",background='darkgrey',relief=RIDGE)
        lb4 = Label(newwin, text="Saldo Devedor  ",font ="Arial 10 bold",fg="blue",background='darkgrey',relief=RIDGE)
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
            Label(newwin,text=str(c+1),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=c+3,column=0)
            Label(newwin,text="R$ "+str(round(pmt,r)),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=c+3,column=1)
            Label(newwin,text="R$ "+str(round(a,r)),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=c+3,column=2)
            Label(newwin,text="R$ "+str(round(j,r)),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=c+3,column=3)
            Label(newwin,text="R$ "+str(round(sd,r)),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=c+3,column=4)
            sj=round(sj+j,r)
            sp=round(sp+pmt,r)
            sa=round(sa+a,r)
            if sa>v or sa<v:
                sa=v
        Label(newwin,text=" ",font="bold",fg="blue").grid(row=n+5,columnspan=5)
        Label(newwin,text="<== Totais",font="Arial 12 bold",fg="blue",background='darkgrey',relief=RIDGE).grid(row=n+6,column=4)
        Label(newwin,text="R$ "+str(sj),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=n+6,column=3)
        Label(newwin,text="R$ "+str(sa),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=n+6,column=2)
        Label(newwin,text="R$ "+str(sp),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=n+6,column=1)
        # Packing:
        display.grid(row=0,columnspan=5)
        lb.grid(row=2,column=0)
        lb1.grid(row=2,column=1)
        lb2.grid(row=2,column=2)
        lb3.grid(row=2,column=3)
        lb4.grid(row=2,column=4)
        
    #Método Price
    def price(self):
        nome = self.nomeinput.get()
        v = float(self.valorinput.get().replace(',', '.'))
        i = float(self.jurosinput.get().replace(',', '.'))
        n = int(self.parcelasinput.get())
        newwin = Toplevel(root)
        newwin.iconbitmap('icon.ico')
        display = Label(newwin, text="Olá "+nome+", \nAqui está a sua tabela de parcelamento Price:",font="Arial 12 bold")
        Label(newwin,text="Parâmetros ==> "+"Valor: R$"+str(round(v,r))+"  Parcelas: "+str(n)+"  Juros: "+str(i)+"% a.m.",relief=RIDGE,font="Arial 10",background='white').grid(row=1,columnspan=5)
        lb = Label(newwin, text="Parcela  ",font ="Arial 10 bold",fg="blue",background='darkgrey',relief=RIDGE)
        lb1 = Label(newwin, text="Valor da Prestação  ",font ="Arial 10 bold",fg="blue",background='darkgrey',relief=RIDGE)
        lb2 = Label(newwin, text="Amortização  ",font ="Arial 10 bold",fg="blue",background='darkgrey',relief=RIDGE)
        lb3 = Label(newwin, text="Juros  ",font ="Arial 10 bold",fg="blue",background='darkgrey',relief=RIDGE)
        lb4 = Label(newwin, text="Saldo Devedor  ",font ="Arial 10 bold",fg="blue",background='darkgrey',relief=RIDGE)
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
            Label(newwin,text=str(c+1),font="Arial 10",relief=RIDGE,fg="red").grid(row=c+3,column=0)
            Label(newwin,text="R$ "+str(round(pmt,r)),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=c+3,column=1)
            Label(newwin,text="R$ "+str(round(a,r)),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=c+3,column=2)
            Label(newwin,text="R$ "+str(round(j,r)),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=c+3,column=3)
            Label(newwin,text="R$ "+str(round(sd,r)),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=c+3,column=4)
            sj=round(sj+j,r)
            sa=round(sa+a,r)
            if sa>v or sa<v:
                sa=round(v,r)
        sp=round(sj+sa,r)
        Label(newwin,text=" ",font="bold",fg="blue").grid(row=n+5,columnspan=5)
        Label(newwin,text="<== Totais",font="Arial 12 bold",fg="blue",background='darkgrey',relief=RIDGE).grid(row=n+6,column=4)
        Label(newwin,text="R$ "+str(sj),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=n+6,column=3)
        Label(newwin,text="R$ "+str(sa),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=n+6,column=2)
        Label(newwin,text="R$ "+str(sp),font="Arial 10",relief=RIDGE,fg="red",background='white').grid(row=n+6,column=1)
        # Packing:
        display.grid(row=0,columnspan=5)
        lb.grid(row=2,column=0)
        lb1.grid(row=2,column=1)
        lb2.grid(row=2,column=2)
        lb3.grid(row=2,column=3)
        lb4.grid(row=2,column=4)
  
r=2
root = Tk()
root.title("Calculadora Financeira")
Application(root)
root.mainloop()