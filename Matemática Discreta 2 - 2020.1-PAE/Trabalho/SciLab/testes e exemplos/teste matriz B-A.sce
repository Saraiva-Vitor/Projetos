//Transforma a Matriz B na Matriz A  
v=1
while B(v,1)==-1
    v=v+1
end
linhasB = size(B,1)
nós=v-1
a_=zeros(1,nós)
for i=1:nós
    if i < nós then
        a_(1,i) = B(i+1,3) - B(i,3)
    else
        a_(1,i) = linhasB - (nós + sum(a_));
    end
end
A_=zeros(nós,nós)
cont = nós;
for k=1:nós
    for i=1:a_(k)
        A_(k,B(cont+i,1))=B(cont+i,2);
    end   
    cont = cont+a_(k);
end
