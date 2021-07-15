clear;
clc;

load('dados.txt');

s = size(A)
n = s(1)

for i=1:n
    for j=1:n
        if A(i,j)==1 then
            plot([x(i) x(j)],[y(i) y(j)],'.-r')
        end
    end    
end

for i=1:n
    t=string(i);
    xstring(x(i),y(i),t)
end
