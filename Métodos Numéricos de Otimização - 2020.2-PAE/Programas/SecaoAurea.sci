clc;
clear;

function y=f(x)
    y=x^2 - 6*x +15;
endfunction


function minimo=func(xh,xl,tolerancia)
    fi=0.618
    x1=xl
    x2=xh
    while(abs(x2-x1)>tolerancia)
        x1=xh - fi*(xh-xl) 
        x2=xl + fi*(xh-xl)
        if(f(x1)>f(x2))
            xh=x2
        else
            xl=x1
        end
    end
    minimo = (x1+x2)/2
endfunction


