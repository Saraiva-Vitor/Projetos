clear;
clc;
//A = read('C:\Users\Vitor\Documents\Scilab\matrizadj',4,4);//pega a matriz de um arquivo salvo no TMPDIR
//C:\Users\Vitor\AppData\Local\Temp\SCI_TMP_5460_25627 (TMPDIR)
G = [2,3,%inf,4;
     3,0,5,%inf;
     %inf,5,0,2;
     4,%inf,2,0]; 
     //ou ler a matriz pelo programa separando colunas com vírgulas e linha com ponto e vírgula 
A=G; //Matriz G sem os %inf(infinitos)
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
 
//Matriz Adjacência
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

//Vetor de Arestas
a=zeros(1,vertices);
for i=1:x 
    for j=1:y
        if At(i,j)==1 then
            a(1,j)=(a(1,j))+1;
        end
    end
end

//Algorítmo de Busca Profundidade
function buscap(vertice)
    global visitado
    global caminho
    if vertice==j then 
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
    else // node!=j
        visitado(1,vertice)=1;
        if caminho(1,1)==0 then
            caminho(1,1)=vertice
        else
            caminho=[caminho,vertice]
        end
    for nr=1:vertices
        if At(vertice,nr)==1 then //node and nr are neighbours
            if visitado(1,nr)==0 then
                buscap(nr)
            end
        end
    end //for nr
end
 //visited(1,nr)=0
visitado(1,vertice)=0
caminho(:,$)=[] //remove last element from path
endfunction

random = grand(2, "prm", 1:vertices);
    inicio=random(1,1);
    fim=random(2,1);
    custo=dijkstra(G,inicio,fim);


random = grand(2, "prm", 1:vertices);
i=random(1,1);
j=random(2,1);
global visited
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

//Lista Adjacência
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
/*B=zeros(vertices+sum(a),4)
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
for i=1:vertices
    aux(1,i)=B(i,4)
    for ind=vertices+1:vertices+sum(a)
            for l=1:vertices
                if At(i,l)<>0 then
                    B(ind,2)=l
                    B(ind,3)=A(i,l)
                    B(ind,4)=0
                else
                    B(ind,2)=l
                    B(ind,3)=A(i,l)
                    B(ind,4)=ind+1
                end
            end
    end
end
*/

//printf("\nLista Adjacência:");
//printf("\n   #    Nó  Peso  Aponta")
//disp(B)

printf("\n\nAlgorítmo de Dijkstra:");
printf("\nPeso mínimo de %d --> %d: ",inicio,fim);
printf("%d \n",custo(fim,1));
printf("\nBusca Profundidade:");
printf("\nDe %d --> %d\n",i,j);
buscap(i);
