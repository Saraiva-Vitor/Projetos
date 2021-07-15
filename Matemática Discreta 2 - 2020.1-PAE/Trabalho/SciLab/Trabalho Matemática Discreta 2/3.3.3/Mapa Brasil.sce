clear;
clc;

load('dados brasil.txt');

imagem = imread('Brasil.jpg')

s = size(A)
n = s(1)
razao=27.5

subplot(2,2,1)
imshow(imagem);

subplot(2,2,2)
for i=1:n
    for j=1:n
        if A(i,j)==1 then
            plot([x(i) x(j)],[y(i) y(j)],'.-b')
        end
    end    
end

for i=1:n
    t=string(i);
    xstring(x(i),y(i),t)
end

subplot(2,2,3)
for i=1:n
    for j=1:n
        if A(i,j)==1 then
            plot([x(i) x(j)],[y(i) y(j)],'.-b')
        end
    end    
end

for i=1:n
    t=r(i);
    xstring(x(i),y(i),t)
end

subplot(2,2,4)
imshow(imagem);
imagem1 = rgb2gray(imagem)
imshow(imagem1);
x2=x*razao
y2=y*razao
for i=1:n
    for j=1:n
        if A(i,j)==1 then
            plot([x2(i) x2(j)],[y2(i) y2(j)],'.-b')
        end
    end    
end
for i=1:n
    t=string(i);
    xstring(x2(i),y2(i),t)
end 
