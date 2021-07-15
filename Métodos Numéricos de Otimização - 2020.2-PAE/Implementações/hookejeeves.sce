clc;
clear;
clearglobal;

N = 5;
erro=0.05;
global d;
d = [1, 0; 0, 1];
global x;
global y;
x = [0, 3];
global Lambda;
Lambda = [0,0];

function a = f(x)
    a = (x(1)-2)^4 + (x(1) - 2*x(2))^2;
endfunction

function z = fLambda(a, j)
    global d;
    z = f([x(1) + (a*d(j, 1)), x(2) + (a*d(j, 2))]);
endfunction

function y=Derivada_Primeira(j)
    global Lambda;
    h=0.00001;
    y=(fLambda(Lambda(j)+h, j)-fLambda(Lambda(j), j))/h;
endfunction

function y=Derivada_Segunda(j)
    global Lambda;
    h=0.00001;
    y = (fLambda(Lambda(j)+h, j)-2*fLambda(Lambda(j), j)+fLambda(Lambda(j)-h, j))/h^2;
endfunction

function Metodo_Newton(j,erro)
    global Lambda;
    for (i = 1:5)                  //faz 10 iteracoes
        Lambda(j) = Lambda(j) - (Derivada_Primeira(j)/Derivada_Segunda(j)); 
        //printf("\n%.2f",Lambda(j));
    end
 //           printf("\n%.2f",Lambda(j));
endfunction

function minimo=Metodo_Hooke_Jeeves()
    global x;
    global d;
    global Lambda;
    i=1
    while (i < 8) 
        for (j = 1:2)
            Metodo_Newton(j,erro);            
            x(1) = (x(1) + Lambda(j) * d(j,1));
            x(2) = (x(2) + Lambda(j) * d(j,2));
            //printf("(%.2f,%.2f)\n",x(1),x(2));
            //disp(Lambda(j))
        end
        i=i+1;
    end
    minimo = x;
endfunction

printf("A resposta é: (%.2f,%.2f)",Metodo_Hooke_Jeeves());
