clc;
clear;
clearglobal;

global d;
d = [1, 0; 0, 1];
global x;
x = [0, 3];
global Lambda;
erro = 0.05;
Lambda = [0,0];

function a = f(x)
    global d;
    a = (x(1)-2)^4 + (x(1) - 2*x(2))^2;
endfunction

function z = fLambda(a, j)
    global d;
    z = f([x(1) + (a*d(j, 1)), x(2) + (a*d(j, 2))]);
endfunction

function y=Derivada_Primeira(j)
    global Lambda;
    global d;
    h=0.00001;
    y=(fLambda(Lambda(j)+h, j)-fLambda(Lambda(j), j))/h;
endfunction

function y=Derivada_Segunda(j)
    global d;
    global Lambda;
    h=0.0001;
    y = (fLambda(Lambda(j)+h, j)-2*fLambda(Lambda(j), j)+fLambda(Lambda(j)-h, j))/h^2;
endfunction

function Metodo_Newton(j,erro)
    global Lambda;
    global d;
    it=1;
    while(abs(Lambda(j)-Lambda(j))>=erro || it<=10)
        Lambda(j)=Lambda(j);
        Lambda(j) = Lambda(j) - (Derivada_Primeira(j)/Derivada_Segunda(j)); 
        it=it+1;
    end
    //printf("%.2f\n",Lambda(j))
endfunction

function Gram_Schmidt(k)
    global x;
    global d;    
    global Lambda;    
    a = [0,0];
    b = [0,0];
    //GRAM SCHIMIDT
    for (j=1:2)
                //achando a 
                if(Lambda(j)== 1) then
                    a(1) = d(j,1);
                    a(2) = d(j,2);
                else
                    for (i=j:2)
                        a(1) = a(1) + Lambda(i)*d(i,1);
                        a(2) = a(2) + Lambda(i)*d(i,2);
                    end
                end
                //achando b
                if(j==2) then
                    b = a;
                else
                    b(1) = a(1) - ( a(1)*d(1,1) )*d(1,1);
                    b(2) = a(2) - ( a(2)*d(1,2) )*d(1,2); 
                end
                //calculando a direção
                moduloB = (b(1)^2 + b(2)^2)^0.5;
                d(j,1) = (1/moduloB)*b(1);
                d(j,2) = (1/moduloB)*b(2);
                Metodo_Newton(j);
                x(1) = (x(1) + Lambda(j) * d(j,1));
                x(2) = (x(2) + Lambda(j) * d(j,2));
                //printf("\nd1 = (%.2f,%.2f)",d(1,1),d(2,1));
                //printf("\nd2 = (%.2f,%.2f)\n",d(1,2),d(2,2));                
            end
endfunction

function minimo=Metodo_Rosenbrock()
    global x;
    global d;
    global Lambda;
    for(k = 1:100)
        if(k>1) then 
            Gram_Schmidt(k);
        else
            for (j = 1:2)
                Metodo_Newton(j,erro);
                x(1) = (x(1) + Lambda(j) * d(j,1));
                x(2) = (x(2) + Lambda(j) * d(j,2));
            end
        end
        printf("Iteração %d --> ",k);
        printf("(%f,%f)\n",x(1),x(2));                
    end
    minimo = x;
endfunction

printf("a resposta e: (%.2f,%.2f)", Metodo_Rosenbrock());

