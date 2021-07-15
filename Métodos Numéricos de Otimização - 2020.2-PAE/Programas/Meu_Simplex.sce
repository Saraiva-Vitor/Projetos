clc
clear

global n;
n = 2;

global centro;
centro =[0,0];

global Xb;
global Xw;
global Xl;

//Simplex Inicial:

Xb = [2,3];
Xl = [3,2];
Xw = [1,4];

//função da equação:
function y = f(x)
    y = (x(2)^2)/4 + (x(1)^2)/9
endfunction

//função para troca de valores do Triangulo Simplex:
function variaveis(a,b,c)
    global Xb;
    global Xw;
    global Xl;
    
    if ((f(a) < f(b)) & f(a) < f(c)) then
        if (f(b) < f(c)) then
            Xb = a;
            Xl = b;
            Xw = c;
        else
            Xb = a;
            Xl = c;
            Xw = b;
        end
        
        elseif ((f(b) < f(a)) & f(b) < f(c)) then
        if (f(a) < f(c)) then
            Xb = b;
            Xl = a;
            Xw = c;
        else
            Xb = b;
            Xl = c;
            Xw = a;
        end
        
        elseif ((f(c) < f(a)) & f(c) < f(b)) then
        if (f(a) < f(b)) then
            Xb = c;
            Xl = a;
            Xw = b;
        else
            Xb = c;
            Xl = b;
            Xw = a;
        end
        mprintf('Xb = %f \n', Xb);
        mprintf('Xl = %f \n', Xl);
        mprintf('Xw = %f \n', Xw);
    end
endfunction

//funcao para calcular o novo centro do simplex
function centroide(a,b)
    global centro;
    c(1) = (a(1) + b(1))/2;
    c(2) = (a(2) + b(2))/2;
    
    //centro = [c1,c2]
endfunction

function xr=reflexao()
    global centro;
    global Xb;
    global Xl;
    global Xw;
    
    centroide(Xb,Xl);
    
    xr = centro + (centro - Xw);
endfunction

function xe=expansao()
    global centro;
    global Xb;
    global Xl;
    global Xw;
    
    centroide(Xb,Xl);
    
    xe= centro + 2*(centro - Xw);
    
endfunction

function xc=contracao()
    global centro;
    global Xb;
    global Xl;
    global Xw;
    
    centroide(Xb,Xl);
    
    xc = centro + 0.5 * (centro - Xw);
endfunction

function encolher()
    global centro;
    global Xb;
    global Xl;
    global Xw;
    
    centroide(Xb,Xl);
    Xl = Xb + 0.5 * centro;

    centroide(Xb,Xw);
    Xw = Xb + 0.5 * centro;
endfunction

//funcao do algoritimo simplex
function simplex()
    global centro;
    global Xb;
    global Xl;
    global Xw;
    
    i = 1;
    
    while(i <= n)
        printf('\nIteração %d\n', i);
        variaveis(Xb,Xl,Xw);
        Xr = reflexao();
        if(f(Xr) <= f(Xw) ) then
            printf('Xr melhor que Xw , portanto : Expandimos\n');
            Xe = expansao();
            
            if ( f(Xe) < f(Xr) ) then       // Verificando se Xe é melhor que Xr para substituirmos Xw.
                Xw = Xe;
            else
                Xw = Xr;
            end
            
        else
            printf('Xr pior que Xw, portanto : Contraimos\n');
            Xc = contracao();
            if ( f(Xc) < f(Xw) ) then
                Xw = Xc;
            else
                encolher();
            end
        end
        
        i = i + 1;
        printf('Xb = ( %f , %f )\n', Xb(1),Xb(2));
        printf('Xl = ( %f , %f )\n', Xl(1),Xl(2));
        printf('Xw = ( %f , %f )\n', Xw(1),Xw(2));
    end
    variaveis(Xb,Xl,Xw);
endfunction

simplex();
printf('X minimizado = ( %g , %g ) ', Xb(1), Xb(2));
