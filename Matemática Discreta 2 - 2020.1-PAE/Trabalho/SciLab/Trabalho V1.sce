clear;
clc;
//A = read('C:\Users\Vitor\Documents\Scilab\matrizadj',4,4);//pega a matriz de um arquivo salvo no TMPDIR
//C:\Users\Vitor\AppData\Local\Temp\SCI_TMP_5460_25627 (TMPDIR)
V=[];
G = [2,3,0,4;
     3,0,5,0;
     0,5,0,2;
     4,0,2,0]; //ou ler a matriz pelo programa separando colunas com vírgulas e linha com ponto e vírgula 
A=G;
Arestas=ceil(nnz(G)/2);
x=size(G,1);
y=size(G,2);
if x<>y then
    printf("Grafo Inválido!\n");
else
    printf("Grafo com:\n");
    printf("%d Vértices\n",x)
    printf("%d Arestas\n",Arestas);
    for i=1:x
        for j=1:y
            if A(i,j)<>0 then 
                if i<>j then A(j,i)=0; end
                    printf("%d --> %d com custo %d\n",i,j,A(i,j)); 
            end
        end
    end
    c=1;
   for i=1:x
        for j=1:y
            if A(i,j)<>0 then 
                V(1,c)=A(i,j);
                c=c+1;
            end
        end
    end
end
visitados = [1 0 0 0 1];
candidatos = [ %inf 3 5 2 %inf];
[minvaluethingie, positionthingie] = min(candidatos);
