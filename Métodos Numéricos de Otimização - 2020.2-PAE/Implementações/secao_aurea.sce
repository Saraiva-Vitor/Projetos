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
        printf("\nLambda = %f", Lambda);
        printf("  Mi = %f", Mi);
        printf("\nf(Lambda) = %f", funcao(Lambda));
        printf("  f(Mi) = %f", funcao(Mi));
        if(funcao(Mi)>funcao(Lambda))
            b = Mi;
            printf("\nNovo b = %f", b);
        else
            a = Lambda;
            printf("\nNovo a = %f", a);
        end
        printf("\na= %f  b= %f",a,b);
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
