clc;
clear;
clearglobal;

p = [2,3];
q = [3,2];
r = [1,4];

global c;
global b;
global g;
global w;
c = [0,0];
b = p;
g = q;
w = r;

function y=f(p)
  y = (p(1) - 2)^4 + (p(1) - 2 * p(2))^2;
endfunction

function ordena(p,q,r)
    global b;
    global g;
    global w;
    
    if ((f(p) < f(q)) & f(p) < f(r)) then
        if (f(q) < f(r)) then
            b = p;
            g = q;
            w = r;
        else
            b = p;
            g = r;
            w = q;
        end
    elseif ((f(q) < f(p)) & f(q) < f(r)) then
        if (f(p) < f(r)) then
            b = q;
            g = p;
            w = r;
        else
            b = q;
            g = r;
            w = p;
        end
    elseif ((f(r) < f(p)) & f(r) < f(q)) then
        if (f(p) < f(q)) then
            b = r;
            g = p;
            w = q;
        else
            b = r;
            g = q;
            w = p;
        end
    //mprintf('Xb = %g \n', b);
    //mprintf('Xl = %g \n', g);
    //mprintf('Xw = %g \n', w);
    end
endfunction

function centroide(p,q)
    global c;
    c(1) = (p(1)+q(1))/2;
    c(2) = (p(2)+q(2))/2;
endfunction

function r=reflexao()
    global c;
    global b;
    global g;
    global w;
    
    centroide(b,g);
    
    r = c+(c-w);
endfunction

function e=expansao()
    global c;
    global b;
    global g;
    global w;
    
    centroide(b,g);
    
    e=c+2*(c-w);
endfunction

function con=contracao()
    global c;
    global b;
    global g;
    global w;
    
    centroide(b,g);
    
    con=c+0.5*(c-w);
endfunction

function encolher()
    global c;
    global b;
    global g;
    global w;
    
    centroide(b,g);
    g = b + 0.5*c;

    centroide(b,w);
    w = b + 0.5*c;
endfunction

function simplex()
    global c;
    global b;
    global g;
    global w;

    n = 100;
    i=1;
    while (i<=n)
        printf('\nIteração %d\n', i);
        ordena(b,g,w);
        reflete = reflexao();
        if( f(reflete) <= f(w) ) then
            printf('Xr melhor que Xw , \nExpanção\n');
            expande = expansao();
            if ( f(expande) < f(reflete) ) then
                w = expande;
            else
                w = reflete;
            end
        else
            printf('Xr pior que Xw,\nContração\n');
            contrai = contracao();
            if ( f(contrai) < f(w) ) then
                w = contrai;
            else
                encolher();
            end
        end
        i = i + 1;
        printf('Xb = ( %8.4g , %8.4g )\n', b(1),b(2));
        printf('Xl = ( %8.4g , %8.4g )\n', g(1),g(2));
        printf('Xw = ( %8.4g , %8.4g )\n', w(1),w(2));
    end
    ordena(b,g,w);
endfunction
simplex();
printf('\nX minimizado = ( %g , %g ) ', b(1), b(2));
