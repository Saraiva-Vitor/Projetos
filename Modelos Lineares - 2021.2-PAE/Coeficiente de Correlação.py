import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import math

x = [0.86, 0.61, 0.55, 0.24, -0.27, -0.75, -1.46, 0.37, -0.40, -1.21]
y = []

for i in range(0,10):
  y.append(x[i]**3)

print(x)
print("\n",y)

medX = np.mean(x)
medY = np.mean(y)

num, denx, deny=0, 0, 0

for i in range(0,10):
  
  num = num + (x[i] - medX) * (y[i] - medY) 
  denx = denx + ((x[i] - medX) ** 2)
  deny = deny + ((y[i] - medY) ** 2)

  
den = math.sqrt(denx * deny)

result = num / den
print("\n",num)
print("\n",den)
print("\n",result)
