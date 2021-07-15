
clear 
clc

function y = f(x)
    y = (x(1)-2)^4 + (x(1)-2*x(2))^2
endfunction

function y1 = f1(x, x1) //x1 > lb + h x > lb
    h = 1e-6
    y1 = (f(x1) - f(x))/h
endfunction

function y2 = f2(x, x1, x2) //x1 > lb + h, x2 > lb - h, x > lb
    h = 1e-6
    y2 = (f(x1) - 2*f(x) + f(x2))/(h^2)
endfunction

function ponto = add_lb(x, lb, d1)
    ponto = [x(1) + lb*d1(1), x(2) + lb*d1(2)]
endfunction

function [x1, x2, x3] = vetores_x(x, lb, d)
    h = 1e-6
    x1 = add_lb(x, lb, d)
    x2 = add_lb(x, lb + h, d)
    x3 = add_lb(x, lb - h, d)
endfunction

function grad = gradiente(x)
    grad = [4*(x(1)-2)^3 + 2*(x(1) - 2*x(2)); -4*(x(1) - 2*x(2))]
endfunction

function direcao = calc_direcao(x1, j, D_anterior, x0)
    if j == 1 then
        D = D_anterior
    else
        termo1 = D_anterior
        Pj = x1 - x0
        qj = gradiente(x1) - gradiente(x0)
        
        D = D_anterior + ((Pj*Pj')/(Pj'*qj)) - ((D_anterior*qj*qj'*D_anterior)/(qj'*D_anterior*qj))   
        
    end
    direcao = (-1)*D*gradiente(x1)
endfunction

function n = newton(x, d)
    E = 1e-4
    k = 1
    N = 1000
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

function sol = dfp(E, N, x0)
    tol = E + 1
    k = 1
    x1 = x0
    lb(1) = 0
    lb(2) = 0
    D = eye(2,2)
   
    printf("Iteração k          Xk          d1           lambda           Xk+1          d2          lamda2          Xk+2\n")
    
    while ((tol > E) & (k <= N))
        j = 1
        d1 = calc_direcao(x1, j, D, x0)
        lb(1) = newton(x0', d1')
        x1 = add_lb(x1', lb(1), d1')
        x1 = x1'
        
        j = 2
        d2 = calc_direcao(x1, j, D, x0)
        lb(2) = newton(x1', d2')
        x2 = add_lb(x1', lb(2), d2')
        x2 = x2'
        
        printf("%g          (%g,%g)         (%g,%g)                     %g          (%g,%g)         (%g, %g)         %g           (%g,%g)\n", k, x0(1,1), x0(2,1), d1(1,1), d1(2,1), lb(1), x1(1,1), x2(2,1), d2(1,1), d2(2,1), lb(2), x2(1,1), x2(2,1))
        
        diferenca = gradiente(x2)
        tol = sqrt(diferenca(1,1)^2 + diferenca(2,1)^2)
        x0 = x2
        k = k + 1
    end
    sol = x2
endfunction


function main()
    E = 1e-6
    N = 100
    x1 = [0; 3]
    
    sol = dfp(E, N, x1)
    disp(sol)
endfunction

main()

