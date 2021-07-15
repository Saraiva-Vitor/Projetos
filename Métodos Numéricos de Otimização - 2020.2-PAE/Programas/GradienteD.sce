clear 
clc

function y = f(x)
    y = (x(1)-x(2)^3)^2 + (3*(x(1)-x(2))^4)
endfunction

function y1 = f1(x, x1) //x1 > lb + h x > lb
    h = 10e-5
    y1 = (f(x1) - f(x))/h
endfunction

function y2 = f2(x, x1, x2) //x1 > lb + h, x2 > lb - h, x > lb
    h = 10e-5
    y2 = (f(x1) - 2*f(x) + f(x2))/(h^2)
endfunction

function ponto = add_lb(x, lb, d1)
    ponto = [x(1) + lb*d1(1), x(2) + lb*d1(2)]
endfunction

function [x1, x2, x3] = vetores_x(x, lb, d)
    h = 10e-5
    x1 = add_lb(x, lb, d1)
    x2 = add_lb(x, lb + h, d1)
    x3 = add_lb(x, lb - h, d1)
endfunction

function direcao = calc_direcao(x)
    fxk = [(2*(x(1)-x(2)^3)+12*(x(1)-x(2))^3) , ((6*x(2)^2)*(x(1)-x(2)^3)+12*(x(1)-x(2))^3)]
    mod = sqrt(fxk(1)^2 + fxk(2)^2)
    direcao = (-1)*fxk
endfunction

function n = newton(x, d)
    E = 0.0001
    k = 1
    N = 2
    tol = E + 1
    lb1 = 0
    
    while ((tol > E) & (k <= N))
        [x1, x2, x3] = vetores_x(x, lb1, d)
        lb2 = lb1 - (f1(x1, x2)/f2(x1, x2, x3))

        tol = abs(lb2 - lb1)
        lb1 = lb2
        k = k + 1
    end
    n = lb1
endfunction

function sol = gradiente_d(E, N, ponto_inicial)
    tol = E + 1
    k = 1
    ponto = ponto_inicial
    
    mprintf("Iteração k          \tXk                          \t d1                   \tlambda                \tXk+1\n")
    
    while ((tol > E) & (k <= N))
        d1 = calc_direcao(ponto)
   
        lb = newton(ponto, d1)
        ponto = add_lb(ponto, lb, d1)
        
        mprintf("\t%g          \t(%.4g,%.4g)         \t(%.4g,%.4g)        \t %.4g           \t(%.4g,%.4g)\n", k, ponto_inicial(1), ponto_inicial(2), d1(1), d1(2), lb, ponto(1), ponto(2))
        
        diferenca(1) = abs(ponto(1) - ponto_inicial(1))
        diferenca(2) = abs(ponto(2) - ponto_inicial(2))

        tol = sqrt(diferenca(1)^2 + diferenca(2)^2)
        ponto_inicial = ponto
        k = k + 1
    end
    sol = ponto
endfunction


function main()
    E = 0.01
    N = 200
    x1 = [2, 1]
    
    sol = gradiente_d(E, N, x1)
    disp(sol)
endfunction

main()

