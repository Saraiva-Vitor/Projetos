clear;
clc;

B_=[-1.   0.   5.; 
  -1.   0.   8. ;
  -1.   0.   10.;
  -1.   0.   12.;
   1.   2.   6. ;
   2.   3.   7. ;
   4.   4.   0. ;
   1.   3.   9. ;
   3.   5.   0. ;
   2.   5.   11.;
   4.   2.   0. ;
   1.   4.   13.;
   3.   2.   0. ;]

G = [2,3,%inf,4;
     3,0,5,%inf;
     %inf,5,0,2;
     4,%inf,2,0]; 
     
A=G; //Matriz G sem os %inf(infinitos)
     //%inf representam nós que não estao conectados por arestas
x=size(G,1);
y=size(G,2);
vertices=max(size(G));
if x<>y then
    printf("Grafo Inválido!\n");
end
    
    //Algorítmo de Dijkstra
    function custo = dijkstra(G,inicio,fim)
        custo(1:vertices) = %inf;
        visitados(1:vertices) = 0;
        custo(inicio) = 0;
        while sum(visitados) < vertices;
            candidatos(1:vertices) = %inf;
            for index=1:vertices
                if visitados(index) == 0 then
                    candidatos(index) = custo(index);
                end    
            end
            [custoatual, verticeatual] = min(candidatos);
            for index=1:vertices
                novocusto = custoatual + G(verticeatual, index);
                if novocusto < custo(index) then
                    custo(index)=novocusto;
                end
            end
            visitados(verticeatual) = 1;    
        end
    endfunction
 
//Matriz Adjacência da Matriz A
At=G
for i=1:x 
    for j=1:y
        if At(i,j)==0|At(i,j)==%inf then
            At(i,j)=0;
        else
            At(i,j)=1;
        end
    end
end

//Vetor de Arestas da Matriz A
a=sum(At,'r');

//Algorítmo de Busca Profundidade
function buscap(vertice)
    global visitado
    global caminho
    if vertice==fimb then 
        if caminho(1,1)==0 then
            caminho(1,1)=vertice
        else
            caminho=[caminho,vertice]
        end
    [nrRows,nrCols]=size(caminho)
    for counter=1:nrCols
        printf('%d ',caminho(1,counter))
    end
    printf('\n')
    else 
        visitado(1,vertice)=1;
        if caminho(1,1)==0 then
            caminho(1,1)=vertice
        else
            caminho=[caminho,vertice]
        end
    for nr=1:vertices
        if At(vertice,nr)==1 then 
            if visitado(1,nr)==0 then
                buscap(nr)
            end
        end
    end 
end
visitado(1,vertice)=0
caminho(:,$)=[] 
endfunction

random1 = grand(2, "prm", 1:vertices);//Números Aleatórios
    iniciod=random1(1,1);
    fimd=random1(2,1);
    custo=dijkstra(G,iniciod,fimd);

random2 = grand(2, "prm", 1:vertices);//Números Aleatórios
iniciob=random2(1,1);
fimb=random2(1,2);
global visitado
visitado=zeros(1,vertices);
global caminho
caminho=zeros(1,1);

Arestas=sum(a);
    printf("\n%d Vértices\n",vertices);
    printf("%d Arestas\n",Arestas);

printf("\nMatriz Adjacência:");
disp(At)
printf("\nVetor de Arestas:");
disp(a)

//Lista Adjacência da Matriz A
    printf("\nLista Adjacência:");
    for i=1:x
        printf("\n%d --> ",i); 
        for j=1:y
            if A(i,j)==%inf then A(i,j)=0; end
            if A(i,j)<>0 then 
                //if i<>j then A(j,i)=0; end 
                printf("%d ",j); 
            end
        end
    end
    
//Transforma a Matriz A na Matriz B 
function AparaB(A)   
B=zeros(vertices+sum(a),3)
B(1,3)=vertices+1
for ind=1:vertices
    B(ind,1)=-1
    B(ind,2)=0
    if ind>1 then
        B(ind,3)=B(ind-1,3)+a(1,ind-1)
    end
end
ind=vertices+1
aux=zeros(1,vertices)
aux(1)=B(1,3)+a(2)
for i=2:vertices
    aux(i)=aux(i-1)+a(i)
end
for i=1:vertices
            for l=1:vertices
                if A(i,l)<>0 then
                    B(ind,1)=l
                    B(ind,2)=A(i,l)
                    B(ind,3)=ind+1
                else
                    continue;
                end
                ind=ind+1
            end
            B(aux(i),3)=0
end
printf("\n\nMatriz B convertida da matriz A:");
printf("\n  Nó  Peso  Aponta")
disp(B);
endfunction
  
//Transforma a Matriz B na Matriz A  
function BparaA(B_)
v=1
while B_(v,1)==-1
    v=v+1
end
linhasB = size(B_,1)
nós=v-1
a_=zeros(1,nós)
for i=1:nós
    if i < nós then
        a_(1,i) = B_(i+1,3) - B_(i,3)
    else
        a_(1,i) = linhasB - (nós + sum(a_));
    end
end
A_=zeros(nós,nós)
cont = nós;
for k=1:nós
    for i=1:a_(k)
        A_(k,B_(cont+i,1))=B_(cont+i,2);
    end   
    cont = cont+a_(k);
end
printf("\nMatriz A convertida da matriz B:")
disp(A_);
endfunction


//Saídas
AparaB(A);
BparaA(B_);
printf("\nAlgorítmo de Dijkstra:");
printf("\nPeso mínimo de %d --> %d: ",iniciod,fimd);
printf("%d \n",custo(fimd,1));
printf("\nBusca Profundidade:");
printf("\nDe %d --> %d\n",iniciob,fimb);
buscap(iniciob);
