# -*- coding: utf-8 -*-
"""
Created on Fri Apr 23 15:53:42 2021

@author: Sir Viktor
"""

import numpy as np
import math
def f_x(y_k, lambda_k, d, j):
    list_y = []
    list_y.append(y_k[0] + d.item(j)*lambda_k)
    list_y.append(y_k[1] + d.item(j+2)*lambda_k)
    
    return ((list_y[0] - 2)**4) + ((list_y[0] - 2*list_y[1])**2)

def derivada_primeira(y_k, lambda_k, d, j):
    delta_lambda = 0.00001
    deri = (f_x(y_k, lambda_k + delta_lambda, d, j) - f_x(y_k, lambda_k, d, j)) / delta_lambda
    return deri

def derivada_segunda(y_k, lambda_k, d, j):
    delta_lambda = 0.00001
    deri = (f_x(y_k, lambda_k + delta_lambda, d, j) - 2*f_x(y_k, lambda_k, d, j) + f_x(y_k, lambda_k - delta_lambda, d, j)) / (delta_lambda**2)
    return deri 


def Newton(y_k, d, j):
    erro = 0.05
    lambda_k = 0
    lambda_k_1 = lambda_k - (derivada_primeira(y_k, lambda_k, d, j) / derivada_segunda(y_k, lambda_k, d, j))
    i = 0
    while (abs(lambda_k_1 - lambda_k) > erro):
    #while (i < 3):
        lambda_k = lambda_k_1
        lambda_k_1 = lambda_k - (derivada_primeira(y_k, lambda_k, d, j) / derivada_segunda(y_k, lambda_k, d, j))
        i = i + 1
    return lambda_k_1
    
def HookeJeeves(x_0, erro):
    d = np.eye(2,2)
    y_1, y_2, y_3 = np.array([]), np.array([]),np.array([])
    y_1 = x_0
    i = 0
    d_1 = np.array([1.0, 0.0])
    d_2 = np.array([0.0, 1.0])
    aux = np.array([])
    aux1 = 2*erro
    while  (aux1 > erro):
    #while (i < 1):
        j = 0
        y_2 = y_1 + Newton(y_1, d, j)*d_1
        j = 1
        y_3 = y_2 + Newton(y_2, d, j)*d_2
        aux = abs(y_3 - y_1)
        aux1 = math.sqrt(aux[0]**2 + aux[1]**2)
        y_1 = y_3
        print(np.around(y_3,2))
        i = i + 1
    

x_0 = np.array([0,3])
erro = 0.05

HookeJeeves(x_0, erro)
