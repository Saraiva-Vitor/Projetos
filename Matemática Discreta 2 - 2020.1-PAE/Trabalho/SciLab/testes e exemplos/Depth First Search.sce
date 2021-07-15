clc
clear
function dfs(node)
 global visited
 global path

 if node==j then 
  if path(1,1)==0 then
   path(1,1)=node
  else
   path=[path,node]
  end
  [nrRows,nrCols]=size(path)
  for counter=1:nrCols
   printf('%d ',path(1,counter))
  end
  printf('\n')

 else // node!=j

  visited(1,node)=1;
  if path(1,1)==0 then
   path(1,1)=node
  else
   path=[path,node]
  end

  for nr=1:n
   if v(node,nr)==1 then //node and nr are neighbours
    if visited(1,nr)==0 then
     dfs(nr)
    end
   end
  end //for nr
 end

 //visited(1,nr)=0
 visited(1,node)=0
 path(:,$)=[] //remove last element from path
endfunction

n=4;
v=[ 0 1 1 0;
1 0 1 0;
1 1 0 1;
0 0 1 0];

i=1; //startnode
j=3; //endnode

global visited
visited=zeros(1,n);
global path
path=zeros(1,1);

//o1 = mopen('pathsBetweenTwoNodes.txt', 'w');
dfs(i);
