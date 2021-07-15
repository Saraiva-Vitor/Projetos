# -*- coding: utf-8 -*-
"""
Created on Fri May 31 18:16:12 2019

@authors: Gabriel Calheias
          Katarine Melo
          Vitor Saraiva
"""

import Tkinter as tk
from reportlab.pdfgen import canvas

v=0
i=0
n=0

def sac(frame):
    global widgets
    widgets={}
    r=2
    v=9000.0
    i=2.0
    n=12
    nome = "Vitor"
    i = i/100
    f = ((((1+i)**n)*i)/(((1+i)**n)-1))
    pmt = round(v*f,r)
    sd=v 
    sj=0 
    sp=0 
    sa=0
    '''Put in some fake data'''
    tk.Label(frame, text = "Olá "+ nome +"\nAqui está a sua tabela de parcelamento SAC:",background='white').grid(row=0,columnspan=5)
    tk.Label(frame,text="Parâmetros ==> "+"Valor: R$"+str(round(v,r))+"  Parcelas: "+str(n)+"  Juros: "+str(i)+"% a.m.",background='darkgrey').grid(row=1,columnspan=5)
    tk.Label(frame, text='Parcela',background='white').grid(row=2, column=0,padx=10,pady=5)
    tk.Label(frame, text='Valor da Prestação',background='white').grid(row=2, column=1,padx=10,pady=5)
    tk.Label(frame, text='Amortização',background='white').grid(row=2, column=2,padx=10,pady=5)
    tk.Label(frame, text='Juros',background='white').grid(row=2, column=3,padx=10,pady=5)
    tk.Label(frame, text='Saldo Devedor',background='white').grid(row=2, column=4,padx=10,pady=5)
    tk.Label(frame,text="R$ "+str(round(v,r)),font ="Arial 10",fg="red",borderwidth="1",relief="solid").grid(row=3,column=4)
    tk.Label(frame,text="0",font="Arial 10 bold",fg="blue",background='darkgrey',borderwidth="1",relief="solid").grid(row=3,column=0)
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
command = sac
cnv = canvas.Canvas("alomundo.pdf")
cnv.drawString(150,450,command)

def onFrameConfigure(canva):
    '''Reset the scroll region to encompass the inner frame'''
    canvas.configure(scrollregion=canvas.bbox("all"))

table_root = tk.Tk()
canva = tk.Canvas(table_root, borderwidth=0, background="#ffffff")
frame = tk.Frame(canva, background="#ffffff")
vsb = tk.Scrollbar(table_root, orient="vertical", command=canvas.yview)
canvas.configure(yscrollcommand=vsb.set)

table_root.title("Calculadora Financeira - Principal")
table_root.configure(background='white')
table_root['borderwidth'] = 10
table_root['relief'] = 'solid'

vsb.pack(side="right", fill="y")
canvas.pack(side="left", fill="both", expand=True)
canvas.create_window((4,4), window=frame, anchor="nw")

frame.bind("<Configure>", lambda event, canva=canva: onFrameConfigure(canva))

sac(frame) 
 
cnv.save()
 
if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))

table_root.mainloop()