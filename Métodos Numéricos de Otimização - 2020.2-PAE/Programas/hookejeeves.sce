clc;
clear;
clearglobal;

global d;
d = [1, 0; 0, 1];
global p;
p = [0, 3];
global lambdas;
lambdas = [0,0];

function a = f(p)
    a = (p(1)-2)^4 + (p(1) - 2*p(2))^2;
endfunction

function z = fLambda(a, j)
    global d;
    z = f([p(1) + (a*d(j, 1)), p(2) + (a*d(j, 2))]);
endfunction

function y=derivada(j)
    global lambdas;
    h=0.00001;
    y=(fLambda(lambdas(j)+h, j)-fLambda(lambdas(j), j))/h;
endfunction

function y=derivada2(j)
    global lambdas;
    h=0.0001;
    y = (fLambda(lambdas(j)+h, j)-2*fLambda(lambdas(j), j)+fLambda(lambdas(j)-h, j))/h^2;
endfunction

function newton(j)
    global lambdas;
    for (i = 1:10)                  //faz 10 iteracoes
        lambdas(j) = lambdas(j) - (derivada(j)/derivada2(j)); 
    end
endfunction

function minimo=hookejeeves()
    global p;
    global d;
    global lambdas;
    for(k = 1:100)
        for (j = 1:2)
            newton(j);
            p(1) = (p(1) + lambdas(j) * d(j,1));
            p(2) = (p(2) + lambdas(j) * d(j,2));
        end
    end
    minimo = p;
endfunction

disp('a resposta e ', hookejeeves());
