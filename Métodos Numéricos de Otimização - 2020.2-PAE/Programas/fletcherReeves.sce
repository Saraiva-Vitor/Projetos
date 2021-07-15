clear;
clc;

function f = fx(x)
    f = (x(1) - 2)^4 + (x(1) - 2*x(2))^2;
endfunction

function g = Gradiente(x)
    g = [4*(x(1) - 2)^3 + 2*(x(1) - 2*x(2)), -4*(x(1) - 2*x(2))];
endfunction

function fh = fhx(x, d, lam)
    x_p(1) = x(1) + lam*d(1);
    x_p(2) = x(2) + lam*d(2);
    fh = fx(x_p);
endfunction

function d1 = dp(x, d, lam)
    h = 1e-4;
    d1 = (fhx(x, d, lam + h) - fhx(x, d, lam))/h;
endfunction

function d2 = ds(x, d, lam)
    h = 1e-4;
    d2 = (fhx(x, d, lam + h) - 2*fhx(x, d, lam) + fhx(x, d, lam - h))/h^2;
endfunction

function n = Newton(x, d)
    lam1 = 0;
    E = 1e-4;
    erro = 2*E;
    while erro > E
        lam2 = lam1 - (dp(x, d, lam1)/ds(x, d, lam1));
        erro = abs(lam1 - lam2);
        lam1 = lam2;
    end
    n = lam2;
endfunction

function a = Alfa(g1, g2)
    a = abs(g2(1)^2 + g2(2)^2)/abs(g1(1)^2 + g1(2)^2);
endfunction

function dfr = Método_Fletcher_Reeves(x, E, N)
    y1 = x;
    i = 1;
    erro = 2*E;
    printf("k   \tXk                \tj     \tYj                          \tGradiente                \tMódulo    \tAlpha      \tDireção                  \tLambda   \tYk+1\n")
    while(erro > E && i < N)
        j=1
        g1 = Gradiente(y1);
        d1 = -1*g1;
        y2 = y1 + Newton(y1, d1)*d1;
        g2 = Gradiente(y2);
        dj = -1*g2 + Alfa(g1, g2)*d1;
        y3 = y2 + Newton(y2, dj)*dj;
        g = Gradiente(y1);
        Módulo_Gradiente=sqrt(g(1)^2 + g(2)^2)
        mprintf("%g   \t(%4.4g , %4.4g)   \t%d   \t(%8.4g , %8.4g)   \t(%8.4g , %8.4g)   \t%5.4g   ", i, y1,j,y1,g1, Módulo_Gradiente);
        mprintf("\t  --      \t(%8.4g , %8.4g)   \t%3.4g   \t(%3.4g , %3.4g)\n",d1,Newton(y1, d1), y2);
        g = Gradiente(y2);
        Módulo_Gradiente=sqrt(g(1)^2 + g(2)^2)
        mprintf("                          \t%d   \t(%8.4g , %8.4g)   \t(%8.4g , %8.4g)   \t%5.4g   ", j+1,y2,g2, Módulo_Gradiente);
        mprintf("\t%5.4g   \t(%8.4g , %8.4g)   \t%3.4g   \t(%3.4g , %3.4g)\n",Alfa(g1, g2) ,dj,Newton(y2, dj), y3);
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n")
        g1 = Gradiente(y2);
        y2 = y3;
        d1 = dj;
        g = Gradiente(y2);
        erro = sqrt(g(1)^2 + g(2)^2);
        y1 = y2;
        i=i+1;
    end
    dfr = y2;
endfunction

function main()
    x = [0, 3];
    E = 0.01;
    N = 5;
    mprintf("\nSolução: (%g , %g)",Método_Fletcher_Reeves(x, E, N));
endfunction

main();
