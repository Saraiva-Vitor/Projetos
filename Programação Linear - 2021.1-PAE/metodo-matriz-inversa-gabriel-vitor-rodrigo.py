import numpy as np
import itertools

#Definir Matriz e Vetor de Resultados do Sistema de Equações Lineares como Abaixo: 
#A = [[A11, A12, A13], [A21, A22, A23], [A31, A32, A33]] - Matriz Quadrada 3x3
#b = [R1, R2, R3] - Resultados das Equações

#Exemplo Matriz Retangular
A = np.array([[1, -2, 5, 3, -4], [2, -4, 5, 6, 2], [2, -5, 7, 7, 3]])
b = np.array([2, -6, -7])

#Exemplo Matriz Quadrada
#A = [[2, 2, 4], [1, 1, 3], [1, 3, 4]]
#b = [10, 9, 17]

#Matrizes Retangulares
def matrizret(A, b):
    count = 0

    linhas = len(A)
    colunas = len(A[0])

    #Combinação (Possibilidades)
    k = np.array(range(colunas))
    C = itertools.combinations(k, linhas)
    P = []
    for L in range(0, colunas+1):
      for subset in C:
        P.append(subset)

    p = len(P)
    print("Matriz Retangular ", linhas, " x ", colunas)
    print(p,"Possíveis Soluções Básicas")
    print("\nMatriz A:\n", A, "\n")
    print("----------------------------------------------------------------------\n")

    B = np.eye(linhas,linhas)
    i = 0
    j = 0
    #print(P)
    for i in range(p):
      print("Possibilidade :", P[i], "\n")
      for j in range(linhas):
        B[:, j] =  A[:,P[i][j]]
        #print(P[i][j])
      if(np.linalg.det(B) == 0):
          print("A Matriz Inversa Não Existe Para a Possibilidade: ", P[i], "\n")
          print("----------------------------------------------------------------------\n")
          continue
      

      #B = np.array(A[0:linhas, 0:linhas])
      #N = np.array(A[0:linhas, linhas:colunas])
      #print("\n",N)

      #Inverte Matriz
      print("Matriz B:\n", B, "\n")

      Bi = np.linalg.inv(B)
      print("Matriz Inversa de B:\n", Bi, "\n")

      #Inversa * Matriz A
      I = np.matmul(Bi, A)
      print("Matriz Identidade do Problema:\n", np.rint(I), "\n")

      #Inversa * b(vetor resultados)
      bi = np.matmul(Bi, b)
      #print("\n", bi)

      #Solução
      #R = np.rint(np.matmul(Bi, N))
      #print(R)
      print("\nSoluções Básicas:")
      count = 0
      while count < linhas:
        print("X",P[i][count]," = ",bi[count])
        count = count + 1
      print("\nPara as Outras", abs(colunas-linhas), "Variáveis Iguais a Zero")
      print("---------------------------------------------------------------------\n")

      

#Matrizes Quadradas
def matrizquad(A,b):
  linhas = len(A)
  colunas = len(A[0])
  print("Matriz Quadrada ", linhas, " x ", colunas)

  #Inversa de A
  Ai = np.linalg.inv(A)
  print("\nMatriz Inversa:\n",Ai, "\n")
  
  #Matriz Identidade
  I = np.matmul(Ai, A)
  print("Matriz Identidade:\n",I, "\n")
  
  #Vetor Solução
  S = np.matmul(Ai, b)
  print("Vetor Solução:", S, "\n")

  count = 0
  while count<linhas:
    print("X", count + 1, " = ", S[count])
    count = count + 1

if (len(A) != len(A[0])):
  matrizret(A, b)
else:
  matrizquad(A,b)