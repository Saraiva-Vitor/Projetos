clc;
clear;

function y=f(x)
    //y=(7*x)-(log(x));
    y=(((2-14*x)-(1-18*x)^3)^2) + (3*((2-14*x)-(1-18*x))^4)
endfunction

function y=derivada(x)
    h=0.00001;
    y=(f(x+h) - f(x))/h;
endfunction

function y=derivada2(x)
    h=0.00001;
    y = (f(x+h) - 2*f(x) +f(x-h))/h^2;
endfunction

function y=newton(x0,e)
    //x = x0 + 2*e;
    N=2;
    i=1;
    x=x0;
    while(abs(x-x0)>=e || i<=N)
        if(derivada2(x)<>0)
            x0=x;
            printf("x%d = %.4f\n",i-1,x);
            printf("Derivada Primeira = %.4f\nDerivada Segunda = %.4f\n",derivada(x),derivada2(x));
            x = x0 - (derivada(x)/derivada2(x));
            printf("x%d = %.4f - (%.4f/%.4f)\n",i,x0,derivada(x),derivada2(x));
            printf("x%d = %.4f\n\n",i,x);
            i = i+1;
        end
    end
    y=x;
    
endfunction

x0=0;
e=1;
printf("a resposta é = %.4f", newton(x0,e));
