clc
clear

function ylinha = primderivada(x)
    
    ylinha = 2*x - 6;
    
endfunction

function segundaderivada = segderivada(x)
    
    segundaderivada = 2;
    
endfunction

function resultado = newton(x1)

    x2 = x1 -(primderivada(x1)/segderivada(x1));
    while(abs(x1-x2)>0.001)
        x2 = x1 -(primderivada(x1)/segderivada(x1));

        x1 = x2;

        resultado = x2;
    end

endfunction

function main()
    x1 = 6;
    
    a = newton(x1);
    
    disp(a,"o valor de a eh: ");
    
endfunction

main()
