clear;
clc;

function y = f(x)
    y = (x(1)-x(2)^3)^2 + (3*(x(1)-x(2))^4)
endfunction

function y1 = Derivada_Primeira(x, x1) 
    h = 0.00001
    y1 = (f(x1) - f(x))/h
endfunction

function y2 = Derivada_Segunda(x, x1, x2) 
    h = 0.00001
    y2 = (f(x1) - 2*f(x) + f(x2))/(h^2)
endfunction

function ponto = add_Lambda(x, Lambda, Direção)
    ponto = [x(1) + Lambda*Direção(1), x(2) + Lambda*Direção(2)]
endfunction

function [x1, x2, x3] = vetores_x(x, Lambda, d)
    h = 0.00001
    x1 = add_Lambda(x, Lambda, Direção)
    x2 = add_Lambda(x, Lambda + h, Direção)
    x3 = add_Lambda(x, Lambda - h, Direção)
endfunction

function direcao = calc_direcao(x)
    fxk = [(2*(x(1)-x(2)^3)+12*(x(1)-x(2))^3) , ((6*x(2)^2)*(x(1)-x(2)^3)+12*(x(1)-x(2))^3)]
    mod = sqrt(fxk(1)^2 + fxk(2)^2)
    direcao = (-1)*fxk
endfunction

function n = Newton(x, d)
    E = 0.0001
    k = 1
    N = 100
    tol = E + 1
    Lambda1 = 0
    
    while ((tol > E) && (k <= N))
        [x1, x2, x3] = vetores_x(x, Lambda1, d)
        Lambda2 = Lambda1 - (Derivada_Primeira(x1, x2)/Derivada_Segunda(x1, x2, x3))

        tol = abs(Lambda2 - Lambda1)
        Lambda1 = Lambda2
        k = k + 1
    end
    n = Lambda1
endfunction

function Solucao = Gradiente_Descendente(N, ponto_inicial)
    k = 1
    ponto = ponto_inicial
    Gradiente = [(2*(ponto_inicial(1)-ponto_inicial(2)^3)+12*(ponto_inicial(1)-ponto_inicial(2))^3) , ((6*ponto_inicial(2)^2)*(ponto_inicial(1)-ponto_inicial(2)^3)+12*(ponto_inicial(1)-ponto_inicial(2))^3)]
    Módulo_Gradiente = sqrt(Gradiente(1)^2 + Gradiente(2)^2)
    mprintf("k   \tXk                \tGradiente                \tMódulo         \tDireção                  \tLambda   \tXk+1\n")
    
    while ((k <= N))
        Direção = calc_direcao(ponto)
   
        Lambda = Newton(ponto, Direção)
        ponto = add_Lambda(ponto, Lambda, Direção)
        Gradiente = [(2*(ponto_inicial(1)-ponto_inicial(2)^3)+12*(ponto_inicial(1)-ponto_inicial(2))^3) , ((6*ponto_inicial(2)^2)*(ponto_inicial(1)-ponto_inicial(2)^3)+12*(ponto_inicial(1)-ponto_inicial(2))^3)]
        Módulo_Gradiente = sqrt(Gradiente(1)^2 + Gradiente(2)^2)
        
        mprintf("%g   \t(%4.4g , %4.4g)   \t(%8.4g , %8.4g)   \t%5.4g   \t(%8.4g , %8.4g)   \t%3.4g   \t(%3.4g , %3.4g)\n", k, ponto_inicial,Gradiente, Módulo_Gradiente ,Direção, Lambda, ponto)
        
        ponto_inicial = ponto
        k = k + 1
    end
    Solucao = ponto
endfunction


function main()
    N = 200
    x1 = [2, 1]
    
    Solucao = Gradiente_Descendente(N, x1)
    mprintf("\nSolução: (%g , %g)",Solucao);
endfunction

main()
