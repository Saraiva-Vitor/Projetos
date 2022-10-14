clear
clc

n = 100

//A = rand(2,2,'normal')
//A = [1,2;2,1] //Matriz Definida
//A = [-0.6834217,0.8145127;-0.7209534,0.3240162] //Primeira Matriz Aleatória
A = [-0.2343923,1.4027612;-0.1821937,2.0320067] //Segunda Matriz Aleatória

function y = semicirculopositivo(x)
    y = sqrt(1-x**2)
endfunction

function y = semicirculonegativo(x)
    y = -sqrt(1-x**2)
endfunction

x = linspace (-1,1,n);
xinv = linspace (1,-1,n);

Pts = zeros(n*2,2);

for i=1:n
    Pts(i,1) = x(i);
    Pts(i+n,1) = xinv(i);
    Pts(i,2) = semicirculopositivo(x(i));
    Pts(i+n,2) = semicirculonegativo(xinv(i));
end    

mprintf("     X \t \t      Y\n");
for i=1:n*2
    mprintf('%8.4g \t %8.4g\n', Pts(i,1),Pts(i,2))
end

disp("A",A)

M = Pts*A

plot(x,semicirculopositivo(x),'k');
plot(x,semicirculonegativo(x),'r');
//legend(['Semi-Círculo Unitário Positivo';'Semi-Círculo Unitário Positivo'],4);
//plot(M(:,1),M(:,2),'--')
//legend(['Semi-Círculo Unitário Positivo';'Semi-Círculo Unitário Positivo';'Circulo Unitário transformado pela Matriz A'],4);

[u,s,v]=svd(A);
MU= u*Pts';
MS= s*Pts';
MV= v*Pts';
disp("U",u);
disp("S",s);
disp("V",v);

//plot(MU(1,:), MU(2,:), '--c');
//legend(['Semi-Círculo Unitário Positivo';'Semi-Círculo Unitário Positivo';'Circulo Unitário transformado pela Matriz U'],4);

plot(MS(1,:), MS(2,:), '--g');
legend(['Semi-Círculo Unitário Positivo';'Semi-Círculo Unitário Positivo';'Circulo Unitário transformado pela Matriz S'],4);

//plot(MV(1,:), MV(2,:), '--m');
//legend(['Semi-Círculo Unitário Positivo';'Semi-Círculo Unitário Positivo';'Circulo Unitário transformado pela Matriz V'],4);
