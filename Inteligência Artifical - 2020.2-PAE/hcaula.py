#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Apr 14 10:25:35 2021

@author: roberto
"""
import random

    
import matplotlib.pyplot as plt
 
import  numpy as np
import string

def solucaoAleatoria(tsp):
    cidades = list(range(len(tsp)))
    solucao = []

    for i in range(len(tsp)):
        cidadeAleatoria = cidades[random.randint(0, len(cidades) - 1)]
        solucao.append(cidadeAleatoria)
        cidades.remove(cidadeAleatoria)

    return solucao

def comprimentoRota(tsp, solucao):
    comprimentoRota = 0
    for i in range(len(solucao)):
        comprimentoRota += tsp[solucao[i - 1]][solucao[i]]
    return comprimentoRota

def pegaVizinhos(solucao):
    vizinhos = []
    for i in range(len(solucao)):
        for j in range(i + 1, len(solucao)):
            vizinho = solucao.copy()
            vizinho[i] = solucao[j]
            vizinho[j] = solucao[i]
            vizinhos.append(vizinho)
    return vizinhos

def pegaMelhorVizinho(tsp, vizinhos):
    melhorComprimentoRota = comprimentoRota(tsp, vizinhos[0])
    melhorVizinho = vizinhos[0]
    for viz in vizinhos:
        comprimentoRotaAtual = comprimentoRota(tsp, viz)
        if comprimentoRotaAtual < melhorComprimentoRota:
            melhorComprimentoRota = comprimentoRotaAtual
            melhorVizinho = viz
    return melhorVizinho, melhorComprimentoRota

def hillClimbing(tsp):
    solucaoAtual = solucaoAleatoria(tsp)
    comprimentoRotaAtual = comprimentoRota(tsp, solucaoAtual)
    vizinhos = pegaVizinhos(solucaoAtual)
    melhorVizinho, melhorVizinhoComprimentoRota = pegaMelhorVizinho(tsp, vizinhos)

    while melhorVizinhoComprimentoRota < comprimentoRotaAtual:
        solucaoAtual = melhorVizinho
        comprimentoRotaAtual = melhorVizinhoComprimentoRota
        vizinhos = pegaVizinhos(solucaoAtual)
        melhorVizinho, melhorVizinhoComprimentoRota = pegaMelhorVizinho(tsp, vizinhos)

    return solucaoAtual, comprimentoRotaAtual

def GeradorDeProblema(nCidades):
    tsp = []
    for i in range(nCidades):
        distancias = []
        for j in range(nCidades):
            if j == i:
                distancias.append(0)
            elif j < i:
                distancias.append(tsp[j][i])
            else:
                distancias.append(random.randint(10, 1000))
        tsp.append(distancias)
    return tsp

def main():
    tsp = [
        [0, 400, 500, 300],
        [400, 0, 300, 500],
        [500, 300, 0, 400],
        [300, 500, 400, 0]
    ]

    print(hillClimbing(tsp))
    newtsc = np.loadtxt("C:\Users\Vitor\Documents\Vitor\IPRJ-UERJ (Engenharia da Computação)\6º Período - 2020.2 - PAE\Inteligência Artificial - Eletiva\Semana 6\cinco.txt", dtype='i', delimiter=" ")
    print(newtsc) 
    print(hillClimbing(newtsc))




if __name__ == "__main__":
    main()