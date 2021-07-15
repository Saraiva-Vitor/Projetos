# -*- coding: utf-8 -*-
"""
Created on Fri Jun 14 10:46:37 2019

@author: Sir Viktor
"""
from Tkinter import *
import sqlite3
import io

conn = sqlite3.connect('clientes.db')

with io.open('clientes_dump.sql', 'w') as f:
    for linha in conn.iterdump():
        f.write('%s\n' % linha)

print('Backup realizado com sucesso.')
print('Salvo como clientes_dump.sql')

conn.close()