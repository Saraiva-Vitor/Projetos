clc;
clear;

function y=f(x)
    y=(7*x)-(log(x));
endfunction

function y=derivada(x)
    h=0.00001;
    y=(f(x+h) - f(x))/h;
endfunction

function y=derivada2(x)
    h=0.0001;
    y = (f(x+h) - 2*f(x) +f(x-h))/h^2;
endfunction

function y=newton(x0,e)
    x = x0 + 2*e;
    while(abs(x-x0)>=e)
        if(derivada2(x)<>0)
            x0 = x;
            x = x0 - (derivada(x)/derivada2(x));
        end
    end
    y=x;
    
endfunction

disp('a resposta e ', newton(0.1,0.01));
