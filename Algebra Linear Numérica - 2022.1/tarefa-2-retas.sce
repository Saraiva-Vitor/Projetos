clear;
clc;

x = linspace(-10,10)
y = 3*x - 1;

//plot2d(x,y,[5]);

for i = 1:5
    disturb = [rand(1,length(x))*i;rand(1,length(y))*i];
    xd = x + disturb(1,:);
    yd = y + disturb(2,:);
    xnew = linspace(min(xd),max(xd),100);
    
    plot2d(xd,yd,[-10]);
    legend('Pontos da Reta 3x-1 Perturbados');
    
    A=[3*xd-1;xd;ones(x)];
    B=[yd];
    A = A';
    B = B';
    X=A\B;
    
    ynew = X(3,:) + 3*xnew*X(1,:) - 1;
    plot2d(xnew,ynew,[6]);
    legend('Pontos da Reta 2x+1 Perturbados', 'Reta Aproximada dos Pontos');
    show_window(i);
end
