clear
clc
A = [2,3,0,4;
     3,0,5,0;
     0,5,0,2;
     4,0,2,0]; 
vertices=max(size(A));

//Matriz Adjacência
At=A
for i=1:vertices 
    for j=1:vertices
        if At(i,j)==0|At(i,j)==%inf then
            At(i,j)=0;
        else
            At(i,j)=1;
        end
    end
end

//Vetor de Arestas
a=sum(At,'r');

B=zeros(vertices+sum(a),4)
for i=1:vertices+sum(a)
    if i==1 then 
        B(1,1)=1;
    else
        B(i,1)=1+B(i-1,1)
    end
end
B(1,4)=vertices+1
for ind=1:vertices
    B(ind,2)=-1
    B(ind,3)=0
    if ind>1 then
        B(ind,4)=B(ind-1,4)+a(1,ind-1)
    end
end
ind=vertices+1
aux=zeros(1,vertices)
aux(1)=B(1,4)+a(2)
for i=2:vertices
    aux(i)=aux(i-1)+a(i)
end
for i=1:vertices
            for l=1:vertices
                if A(i,l)<>0 then
                    B(ind,2)=l
                    B(ind,3)=A(i,l)
                    B(ind,4)=ind+1
                else
                    continue;
                end
                ind=ind+1
            end
            B(aux(i),4)
end


printf("\nMatriz Adjacência:");
disp(At)
printf("\nVetor de Arestas:");
disp(a)
printf("\nLista Adjacência:");
printf("\n   #    Nó  Peso  Aponta")
disp(B)
