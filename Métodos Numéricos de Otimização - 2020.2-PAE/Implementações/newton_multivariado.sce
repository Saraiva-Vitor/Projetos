clear
clc

function y = fx(x)
    //y = x(1)^3 + 6*x(1)^4 - 3*x(2)^2 + 2*x(2)^6
    //y = ((x(1)-2)^4) + ((x(1)-2*x(2))^2)
    y = (12*x(1)^2)+(4*x(2)^2)+(2*x(1))-(12*x(1)*x(2))
endfunction

function grad = Gradiente(x)
    //grad =[24*x(1)^3 + 3*x(1)^2, -6*x(2) + 12*x(2)^5]
    grad = [(24*x(1)+2-12*x(2)), (8*x(2)-12*x(1))]
endfunction

function H = Hessiana(x)
    //H = [6*x(1) + 72*x(1)^2, 0; 0, -6 + 60*x(2)^4]
    H = [24, -12;
          -12, 8]
endfunction

function inversa = Hessiana_Inversa(H)
    detH = (H(1,1) * H(2,2)) - (H(1,2) * H(2, 1))
    inversa = [H(2,2), (-1)*H(1,2); (-1)*H(2,1), H(1,1)]
    inversa = (1/detH)*inversa
endfunction

function sol = Método_Newton_Multivariado(E, N, x0)
    tol = E + 1
    k = 1
    printf("k   \tXk                    \tGradiente         \tHessiana        \tHessiana Inversa   \tXk+1\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n")
    while ((tol > E) & (k <= N))
        H = Hessiana(x0)
        IH = Hessiana_Inversa(H)
        grad = Gradiente(x0)
        mult = [IH(1,1)*grad(1) + IH(1,2)*grad(2), IH(2,1)*grad(1) + IH(2,2)*grad(2)]
        x = [x0(1) - mult(1), x0(2) - mult(2)]
        
        //printf("\nIteração: %g\n", k)
        //disp("Ponto de início: ",x0)
        //disp("Hessiana",Hessiana(x0))
        //disp("Hessiana Inversa: ",H)
        //disp("Gradiente: ",grad)
        //disp("Ponto Otimizado: ",x)
        printf("%g \t(%7.4g , %7.4g) \t(%7.4g , %7.4g) \t|%7.4g , %7.4g| \t|%7.4g , %7.4g| \t(%7.4g , %7.4g)\n",k,x0,grad,H(1),H(2),IH(1),IH(2),x);
        printf("                                                \t|%7.4g , %7.4g| \t|%7.4g , %7.4g|\n",H(3),H(4),IH(3),IH(4));
        printf("-----------------------------------------------------------------------------------------------------------------------------\n")
        //printf("\n")
        
        diferenca = [x(1) - x0(1), x(2) - x0(2)]
        tol = sqrt(diferenca(1)^2 + diferenca(2)^2)
        
        x0 = x
        k = k + 1
        
    end
    sol = x
endfunction

E = 0.001
N = 100
x0 = [1, 2]
Solução = Método_Newton_Multivariado(E, N, x0)
printf("\n\nSolução: (%g , %g)",Solução);
