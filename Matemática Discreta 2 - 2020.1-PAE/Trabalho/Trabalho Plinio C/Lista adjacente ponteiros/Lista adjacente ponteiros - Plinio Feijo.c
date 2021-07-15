#include <stdio.h>

typedef struct item{
	int campo;
	struct item* prox;
}ITEM;

ITEM lista[6]; //Numero de pontos + 1

void Imprimir(ITEM *lista);
void InserirNaLista(ITEM *lista, int x, int y);

int main(int argc, char *argv[]){
  int i,j;

  //a matriz tera na primeira linha os nomes dos pontos, na primeira coluna o grau dos respectivos pontos e no meio a qtd de ligacoes com cada ponto
  int matriz[6][6] = {{0, 1, 2, 3, 4, 5},{3, 0, 1, 1, 0, 1},{3, 1, 0, 1, 1, 0},{3, 1, 1, 0, 0, 1},{1, 0, 1, 0, 0, 0},{2, 1, 0, 1, 0, 0}};

  // Inicialização da lista.
  for(i=1; i<=5; i++){ //i vai ate a qtd de pontos
    lista[i].campo = matriz[i][0];
    lista[i].prox = NULL;
  }

  for(i=1; i<6; i++){
    for(j=1; j<6; j++){
        if(matriz[i][j] != 0)
            InserirNaLista(lista,i,j);
    }
  }

  Imprimir(lista);
  return 0;
}


void Imprimir(ITEM *lista){
  int i;
  ITEM * tmp;
  for(i=1; i<=5; i++) {
    tmp = lista[i].prox;
    printf("%2d: ==>", i);
    while (tmp != NULL) {
      printf("%d  ", tmp->campo);
      tmp = tmp->prox;
    }
    printf("\n");
  }
}

void InserirNaLista(ITEM *lista, int x, int y){//int a, int b){
  ITEM *aux;
  ITEM *tmp;

  aux = (ITEM*) malloc((int)sizeof(ITEM));    //retorno de um ponteiro genérico.
  aux->campo = y;
  aux->prox = NULL;

  lista[x].campo++;
  if(lista[x].prox == NULL) // Caso a lista estiver vazia - Insere.
    lista[x].prox = aux;
  else	{
    tmp = lista[x].prox;
    if (tmp->campo > y) { //insere como primeiro da lista
      aux->prox = tmp;
      lista[x].prox = aux;
    } 		          //insere os vértices ordenados
    else if (tmp->prox == NULL) {
      aux->prox = tmp->prox;
      tmp->prox = aux;
    }
    else {
      while((tmp->prox != NULL) &&(tmp->prox->campo < y))
	tmp = tmp->prox;
      aux->prox = tmp->prox;
      tmp->prox = aux;
    }
  }
}
