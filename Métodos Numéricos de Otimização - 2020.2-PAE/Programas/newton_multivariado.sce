clear
clc

function y = fx(x)
    y = x(1)^3 + 6*x(1)^4 - 3*x(2)^2 + 2*x(2)^6
endfunction

function grad = gradiente(x)
    grad =[24*x(1)^3 + 3*x(1)^2, -6*x(2) + 12*x(2)^5]
endfunction

function H = hessiana(x)
    H = [6*x(1) + 72*x(1)^2, 0; 0, -6 + 60*x(2)^4]
endfunction

function inversa = inversa_H(H)
    detH = (H(1,1) * H(2,2)) - (H(1,2) * H(2, 1))
    inversa = [H(2,2), (-1)*H(1,2); (-1)*H(2,1), H(1,1)]
    inversa = (1/detH)*inversa
endfunction

function sol = newton_multivariado(E, N, x0)
    tol = E + 1
    k = 1
    
    while ((tol > E) & (k <= N))
        H = inversa_H(hessiana(x0))
        grad = gradiente(x0)
        mult = [H(1,1)*grad(1) + H(1,2)*grad(2), H(2,1)*grad(1) + H(2,2)*grad(2)]
        x = [x0(1) - mult(1), x0(2) - mult(2)]
        
        printf("Iteração: %g\n", k)
        disp(x0, "Ponto de início: ")
        disp(H, "Hessiana Inversa: ")
        disp(grad, "Gradiente: ")
        disp(x, "Ponto Otimizado: ")
        printf("\n")
        
        diferenca = [x(1) - x0(1), x(2) - x0(2)]
        tol = sqrt(diferenca(1)^2 + diferenca(2)^2)
        
        x0 = x
        k = k + 1
        
    end
    sol = x
endfunction

function main()
    E = 0.001
    N = 100
    x0 = [1, 2]
    
    sol = newton_multivariado(E, N, x0)
    disp(sol)
endfunction

main()
