clear ;
clc ;
disp ("Example 6 . 1 ") ;
// Depth F i r s t S e a r c h T r a v e r s a l
funcprot (0)
function []= Dfs(adj,n) ;
    i =1;
    j =1;
    colour =[];
    for i =1: n
        for j =1: n
            colour =[colour(:,:)0];
        end
    end
    disp("The DFS t r a v e r s a l i s ") ;
    dfs(adj,colour,1,n);
endfunction

function []= dfs(adj,colour,r,n)
    colour(r) =1;
    disp(r ," ") ;
    for i =1: n
        if(adj((r-1)*n+i)&(colour(i)==0) )
        dfs(adj,colour,i,n) ;
        end
    end
    colour(r)=2;
endfunction

// C a l l i n g Ro u ti n e :
n =4;
adj =[0 1 1 0 1 0 0 1 1 0 0 1 0 1 1 0];
Dfs(adj,n);
