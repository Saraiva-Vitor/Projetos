import numpy as np
import math
def f_x(y_k, lambda_k, d, j):
    list_y = []
    list_y.append(y_k[0] + d.item(j)*lambda_k)
    list_y.append(y_k[1] + d.item(j+2)*lambda_k)
    
    return (1**list_y[0]) + (list_y[0]*list_y[1]) + (list_y[1]**2) + (list_y[0]**2)

def first_derivate(y_k, lambda_k, d, j):
    delta_lambda = 0.00001
    deri = (f_x(y_k, lambda_k + delta_lambda, d, j) - f_x(y_k, lambda_k, d, j)) / delta_lambda
    #print("-------------------------------")
    #print("Derivada Primeira = ", deri)
    return deri

def second_derivate(y_k, lambda_k, d, j):
    delta_lambda = 0.00001
    deri = (f_x(y_k, lambda_k + delta_lambda, d, j) - 2*f_x(y_k, lambda_k, d, j) + f_x(y_k, lambda_k - delta_lambda, d, j)) / (delta_lambda**2)
    #print("Derivada Segunda = ", deri)
    return deri 


def newton(y_k, d, j):
    erro = 0.000001
    lambda_k = 0
    lambda_k_1 = lambda_k - (first_derivate(y_k, lambda_k, d, j) / second_derivate(y_k, lambda_k, d, j))
    i = 0
    #while (abs(lambda_k_1 - lambda_k) > erro):
    while (i < 3):
        lambda_k = lambda_k_1
        lambda_k_1 = lambda_k - (first_derivate(y_k, lambda_k, d, j) / second_derivate(y_k, lambda_k, d, j))
        i = i + 1
    #print("O valor do lambda ótimo é =", lambda_k_1)
    return lambda_k_1
    
def HJ(x_0, erro):
    d = np.eye(2,2)
    y_1, y_2, y_3 = np.array([]), np.array([]),np.array([])
    y_1 = x_0
    i = 0
    d_1 = np.array([1.0, 0.0])
    d_2 = np.array([0.0, 1.0])
    #print(y_1 + newton(y_1, d, 0)*d_1)
    aux = np.array([])
    aux1 = 2*erro
    #print(aux1 > erro)
    #while  (aux1 > erro):
    while (i < 1):
        print("oi")
        j = 0
        
        y_2 = y_1 + newton(y_1, d, j)*d_1
        #print("y_2 = ", y_2)
        j = 1
        y_3 = y_2 + newton(y_2, d, j)*d_2
        
        #print("y_3 = ", y_3)
        aux = abs(y_3 - y_1)
        #print(aux)
        aux1 = math.sqrt(aux[0]**2 + aux[1]**2)
        #print(aux1)
        y_1 = y_3
        print(y_3)
        i = i + 1
    

x_0 = np.array([1,2])
erro = 0.1

HJ(x_0, erro)
