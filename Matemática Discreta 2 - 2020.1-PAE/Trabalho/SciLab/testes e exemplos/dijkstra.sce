G = [2,3,%inf,4;
     3,0,5,%inf;
     %inf,5,0,2;
     4,%inf,2,0];
function custo = dijkstra(G,inicio)
    N = max(size(G));
    custo(1:N) = %inf;
    visitados(1:N) = 0;
    custo(inicio) = 0;
    while sum(visitados) < N;
        candidatos(1:N) = %inf;
        for index=1:N
            if visitados(index) == 0 then
                candidatos(index) = custo(index);
            end    
        end
        [custoatual, verticeatual] = min(candidatos);
        for index=1:N
            novocusto = custoatual + G(verticeatual, index);
            if novocusto < custo(index) then
                custo(index)=novocusto;
            end
        end
        visitados(verticeatual) = 1;    
    end
endfunction
custo=dijkstra(G,1);
