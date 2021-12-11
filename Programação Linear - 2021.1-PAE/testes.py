import numpy as np
import itertools

#Definir Matriz e Vetor de Resultados do Sistema de Equações Lineares como Abaixo Já na Forma Canônica: 
#A = [[A11, A12, A13],
#    [A21, A22, A23],
#    [A31, A32, A33]]
#    Matriz Quadrada 3x3
#b = [R1, R2, R3] - Resultados das Equações
#c = [C1, C2, C3] - Coeficientes da Equação

#Exemplo Matriz Retangular Para Resolução do Simplex
#A = np.array([[1, 2, 1, 0, 0],
#              [1, 0, 0, 1, 0],
#              [0, 1, 0, 0, 1]])
#b = np.array([9, 3, 4])
#c = np.array([5, 2, 0, 0, 0])

#Exemplo Matriz Retangular Para Resolução do Simplex
A = np.array([[1, 2, 3, 1, 0, 0],
              [2, 1, -1, 0, 1, 0],
              [-1, 3, 0, 0, 0, 1]])
b = np.array([12, 6, 9])
c = np.array([1 , -2, 1, 0, 0, 0])

#Matrizes Retangulares
def matrizret(A, b, c):
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
    print("Matriz Retangular:", linhas, "x", colunas)
    print(p,"Possíveis Soluções Básicas")
    print("\nMatriz A:\n", A, "\n")
    print("----------------------------------------------------------------------\n")
    teste = np.arange(colunas)
    xb = teste[0:linhas]
    xn = teste[linhas:colunas]
    n = np.array([[0] * colunas for i in range(linhas)])
    c = np.array(c).T
    B = A[:,0:linhas]
    #print(P)
    #while(all(s <= 0 for s in gamma)): Novo Laço de Repetição
    for i in range(0,1):
      print("Possibilidade :", P[i], "\n")
      #for j in range(0,linhas):
      #  B[:, j] =  A[:,P[i][j]]
        #print(P[i][j])
      if(np.linalg.det(B) == 0):
          print("A Matriz Inversa Não Existe Para Esta Possibilidade\n")
          print("----------------------------------------------------------------------\n")
          continue
      

      #B = np.array(A[0:linhas, 0:linhas])
      #print("\n",N)

      print("Matriz B:\n", B, "\n")

      #Matriz N
      for cont1 in range(0,colunas-linhas-1):
        for elemento in teste:
          if elemento not in P[i]:
            n[:,elemento] = A[:,elemento]
      N = n[:,linhas:colunas]
      print("Matriz N:\n", N, "\n")    
      
      #Inverte Matriz
      Bi = np.linalg.inv(B)
      print("Matriz Inversa de B:\n", Bi, "\n")

      #Inversa * b(vetor resultados)
      bi = np.matmul(Bi, b)
      #print("\n", bi)

      #Matriz R
      R = np.matmul(Bi, N)
      print("Matriz R:\n", R, "\n")

      #Transposta de N e da Inversa de B
      Nt = np.array(N).T
      Bit = np.array(Bi).T

      #Gamma e Vetor de Coeficientes
      cn = c[linhas:colunas]
      cb = c[0:linhas]
      print("Coeficientes de N: ",cn, "\n")
      print("Coeficientes de B: ",cb, "\n")
      gamma = np.subtract(cn,np.matmul(np.matmul(Nt,Bit),cb))
      print("Gamma: ", gamma, "\n")

      #Solução
      print("\nSoluções Básicas:")
      count = 0
      while count < linhas:
        print("X",P[i][count]," = ",bi[count])
        count = count + 1
      print("\nPara as Outras", abs(colunas-linhas), "Variáveis Iguais a Zero")
      
      if all(s <= 0 for s in gamma):
        print("\nÉ UMA SOLUÇÃO ÓTIMA\n")
      else:
        print("\nNÃO É UMA SOLUÇÃO ÓTIMA\n")

      #Maior Valor em Gamma
      print(max(gamma))
      #Variável Não Básica a Entrar na Base
      vnb = np.where(gamma == max(gamma))
      
      aux1 = B[:,0]
      aux2 = B[:,1]
      aux3 = B[:,2]
      #Variável Básica a Sair da Base 
      ''''
      aux = np.zeros(linhas)
      menor = np.zeros(linhas)
      for coluna in range(0,linhas):
        print("Coluna:",coluna)
        print(aux)
        print(menor, "\n")
        if(aux1[coluna] == 0 or aux2[coluna] == 0 or aux3[coluna] == 0):
          continue
        aux[coluna] = b[coluna]/aux1[coluna]
        if(len(aux)==0 and menor[coluna] > 0):
          menor[coluna] ==  np.copy(aux[coluna])
          continue
        elif(aux[coluna] < menor[coluna] and aux[coluna] > 0):
          menor[coluna] ==  np.copy(aux[coluna])
        else:
          continue
      '''

      
      menor = [float(i) / B for i in b]
      #print(aux)
      print(menor[0][0], "\n")
      print(menor[1][1], "\n")
      print(menor[2][2], "\n")
      
      aux = np.array(N[vnb]).T

      print(aux)
      print(np.matmul(Bi,aux))

      #vb = np.where(menor == min(menor))
      #print(b)
      #print(vnb)
      #print(vb)
      #print(xb)
      #print(xn)
      #print(xn[vnb])

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
  matrizret(A, b, c)
else:
  matrizquad(A,b)