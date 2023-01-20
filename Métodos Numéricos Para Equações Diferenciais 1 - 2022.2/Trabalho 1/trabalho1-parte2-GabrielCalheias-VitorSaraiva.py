import matplotlib.pyplot as plt
import numpy as np
import math
import scipy
import pandas as pd

Lmax = 20
i = 30
Δx = Lmax/i
nofinal = i-1
print(i)

L = []
count = 0
while(count < Lmax):
  L.append(count)
  count += Δx

#print(L)

C = [0]*(i+1)
A = np.zeros((i-2,i-2),dtype=np.float64)
b = np.zeros((i,1),dtype=np.float64)

C[1] = 0.1
C[i] = 0

alpha = 7
D = alpha*10**-6

beta = 5*alpha
k = beta*10**-6

def criterio_linhas(A):
    swap = np.copy(A)
    b = np.diag(A)
    A = A - np.diagflat(b)
    x = np.ones(b.size)
    permutation = b.size**2
    acc = True
    
    while(acc and permutation > 0):
        for i in range(b.size):
            x[i] = np.sum(A[i])/b[i]
        
        if(np.amax(x) < 1): acc = False
        else:
            permutation = permutation-1
            swap = np.random.permutation(swap)
            A = np.copy(swap)
            b = np.diag(A)
            A = A - np.diagflat(b)
    
    return np.amax(x)

#Matriz A, Matriz b dos termos independentes e N o número de iterações e o erro
def jacobi(A, b, N, chute, erro = 0.001):
    if(criterio_linhas(A) > 1):
        print("O sistema não converge para o método de Jacobi")
        return
    
    x = np.diag(A) #recebe um vetor contendo a diagonal principal
    A = A - np.diagflat(x) #Zera a diagonal principal de A
    
    #Para dividir todos os valores da matriz A pelos termos independentes
    for i in range(x.size):
        A[i] = A[i]/x[i]
        b[i] = b[i]/x[i]

    x = np.copy(chute)
    swap = np.zeros(x.size)
    
    A = A*-1
    
    for stop in range(N):
        for i in range(x.size):
            swap[i] = np.sum((A[i]*x))+(b[i])
        #Cálculo da tolerância ou erro
        data_df_jacobi = pd.DataFrame(swap)
        #print(f"Iteração {stop}: {swap}")
        print("\nIteração ",stop)
        print(data_df_jacobi)
        if((np.linalg.norm(swap) - np.linalg.norm(x)) < erro): 
          print("\nFinalizou por Erro\n")
          return swap
        x = np.copy(swap)

    return x

def F(Ci): 
  j = count-2
  if(Ci == 2):
    #print("i = 2")
    A[Ci-2,j] = ((2*D)+((Δx**2)*k))
    A[Ci-2,j+1] = -D
    b[Ci-2,0] = D*C[1]
    #print(A[0,:])
  if(Ci == nofinal):
    #print("i = L")
    A[Ci-2,j-1] = -D
    A[Ci-2,j] = ((2*D)+((Δx**2)*k))
    b[Ci-2,0] = D*C[i]
    #print(A[nofinal-2,:])
  if((Ci > 2) & (Ci < nofinal)):
    #print("2 < i < L")
    A[Ci-2,j-1] = -D
    A[Ci-2,j] = ((2*D)+((Δx**2)*k))
    A[Ci-2,j+1] = -D
    b[Ci-2,0] = 0
    #print(A[Ci-2,:])

count = 2
while count <= nofinal:
  F(count)
  count += 1


data_df_A = pd.DataFrame(A)
data_df_b = pd.DataFrame(b)
print("\nMatriz A:\n",data_df_A)
print("\nVetor b:\n",data_df_b,"\n")

'''print("\nMatriz A:\n",A)
print("\nVetor b:\n",b,"\n")'''

x = np.zeros(i-2)

print("Jacobi:")
r = jacobi(A, b, 100, x)
data_df_r = pd.DataFrame(r)
print("\nSolução:\n",data_df_r,"\n")

'''count = 2
while count <= nofinal:
  print("C" + str(count) + " = " + str(r[count-2]))
  count += 1'''

r_list = []
r_list.append(0.1)
count = 0
while(count < i-2):
  r_list.append(r[count])
  count += 1
r_list.append(0)


plt.plot(L, r_list, marker = 'o')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True)
plt.title('Δx = ' + str(Δx))