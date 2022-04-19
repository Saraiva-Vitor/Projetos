import scipy as sp
import matplotlib.pyplot as plt
import numpy as np
import random

x = random.uniform(0, 50)
b0, b1 = -10, 2
y, erroE = [], []
mu, sigma = 0, 2

for i in range(0,50):
  erro = np.random.normal(0, 2, 1)
  erroE.append(erro)
  erroE.append(-erro)
  y.append(b0 + b1*x + erro)
  y.append(b0 + b1*x - erro)

plt.scatter(erroE, y)
plt.show
