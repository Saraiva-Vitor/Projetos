import matplotlib.pyplot as plt
import numpy
import math

fCa = []
fCb = []
fCc = []
tempo = []

# Por volta de uma dezena
alfa = 11
beta = 12
gamma = 13

# Por volta de algumas dezenas
A = 90
B = 0
C = 90

t = 0

# Por volta de algumas unidades
tf = 2

# Passo de Tempo
# Max Calculado = 0.0014 ----- 0.0015 os valores de concentração se tornam Nan
Δt = 0.001


def dca(ca, cb, cc): return -alfa*ca*cc + cb
def dcb(ca, cb, cc): return beta*ca*cc - cb
def dcc(ca, cb, cc): return -gamma*ca*cc + cb - 2*cc


def RungeKutta(A, B, C, t, tf, Δt):
    fa = A
    fb = B
    fc = C
    while (t < tf):
        print("\nt = " + str(t))

        ka1 = dca(fa, fb, fc)
        kb1 = dcb(fa, fb, fc)
        kc1 = dcc(fa, fb, fc)
        
        ka2 = dca(fa + (ka1*(Δt/2)), fb + (kb1*(Δt/2)), fc + (kc1*(Δt/2)))
        kb2 = dcb(fa + (ka1*(Δt/2)), fb + (kb1*(Δt/2)), fc + (kc1*(Δt/2)))
        kc2 = dcc(fa + (ka1*(Δt/2)), fb + (kb1*(Δt/2)), fc + (kc1*(Δt/2)))

        ka3 = dca(fa - (ka1*Δt) + (2*ka2*Δt), fb - (kb1*Δt) + (2*kb2*Δt), fc - (kc1*Δt) + (2*kc2*Δt))
        kb3 = dcb(fa - (ka1*Δt) + (2*ka2*Δt), fb - (kb1*Δt) + (2*kb2*Δt), fc - (kc1*Δt) + (2*kc2*Δt))
        kc3 = dcc(fa - (ka1*Δt) + (2*ka2*Δt), fb - (kb1*Δt) + (2*kb2*Δt), fc - (kc1*Δt) + (2*kc2*Δt))
        
        ka = (Δt*(ka1+(4*ka2)+ka3))/6
        kb = (Δt*(kb1+(4*kb2)+kb3))/6
        kc = (Δt*(kc1+(4*kc2)+kc3))/6

        fa = fa + ka
        fb = fb + kb
        fc = fc + kc

        print("RK3 dCa = " + str(fa))
        print("RK3 dCb = " + str(fb))
        print("RK3 dCc = " + str(fc))

        fCa.append(fa)
        fCb.append(fb)
        fCc.append(fc)
        tempo.append(t)

        t = t + Δt


print("Alpha = " + str(alfa))
print("Beta = " + str(beta))
print("Gamma = " + str(gamma))
print("\nA = " + str(A))
print("B = " + str(B))
print("C = " + str(C))
print("Δt = " + str(Δt))
RungeKutta(A, B, C, t, tf, Δt)

plt.plot(tempo, fCa, color = 'red', marker = 'o', label='dCa/dt = -αCaCc + Cb')
plt.plot(tempo, fCb, color = 'green', marker = 'D', label='dCb/dt =  βCaCc - Cb')
plt.plot(tempo, fCc, color = 'blue', marker = '^', label='dCc/dt = -γCaCc + Cb - 2Cc')
plt.xlabel('t')
plt.ylabel('f(t)')
plt.grid(True)
plt.title('Δt = ' + str(Δt))
plt.legend()