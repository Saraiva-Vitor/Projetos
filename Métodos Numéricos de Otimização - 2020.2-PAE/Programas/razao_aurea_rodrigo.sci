clc
clear
razao=0.618
function y = funcao(x)
    y=x^2 - 6*x +15;
endfunction

function resultado = razao_aurea(a,b)
    iteracoes = 5;
    i=1;
    x1 = a;
    x2 = b;
    i = 1;
    while(i <= iteracoes)
        printf('\n\n Iteração %d',i);
        x1 = b-(razao*(b-a));
        x2 = a+(razao*(b-a));
        printf("\nLambda = %.2f", x1);
        printf("  Mi = %.2f", x2);
        printf("\nf(Lambda) = %.2f", funcao(x1));
        printf("  f(Mi) = %.2f", funcao(x2));
        if(funcao(x2)>funcao(x1))
            b = x2;
            printf("\nNovo b = %.2f", b);
        else
            a = x1;
            printf("\nNovo a = %.2f", a);
        end
        printf("\na= %.2f  b= %.2f",a,b);
        i=i+1;
    end
    resultado = (x1+x2)/2;
endfunction

function main()
    b = 10;
    a = 0;
    r = razao_aurea(a,b);
    printf("\n\n o valor final é: %.2f",r);
endfunction

main()
