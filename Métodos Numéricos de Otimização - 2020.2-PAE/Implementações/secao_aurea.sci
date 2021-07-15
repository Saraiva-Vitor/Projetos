clc
clear
razao=0.618
function y = funcao(x)
    y=x^3 - 3*x - 3;
endfunction

function resultado = razao_aurea(a,b)
    iteracoes = 100;
    i=1;
    Lambda = a;
    Mi = b;
    i = 1;
    while(i <= iteracoes)
        printf('\n\nIteração %d',i);
        Lambda = b-(razao*(b-a));
        Mi = a+(razao*(b-a));
        printf("\nLambda = %.2f", Lambda);
        printf("  Mi = %.2f", Mi);
        printf("\nf(Lambda) = %.2f", funcao(Lambda));
        printf("  f(Mi) = %.2f", funcao(Mi));
        if(funcao(Mi)>funcao(Lambda))
            b = Mi;
            printf("\nNovo b = %.2f", b);
        else
            a = Lambda;
            printf("\nNovo a = %.2f", a);
        end
        printf("\na= %.2f  b= %.2f",a,b);
        i=i+1;
    end
    resultado = (Lambda+Mi)/2;
endfunction

function main()
    a = 0;
    b = 3;
    r = razao_aurea(a,b);
    printf("\n\n o valor final é: %.2f",r);
endfunction

main()
