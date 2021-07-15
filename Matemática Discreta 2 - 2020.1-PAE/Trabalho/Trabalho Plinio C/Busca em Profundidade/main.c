#include <stdio.h>
#include <stdlib.h>

#define qtdNos 5

typedef struct no{
        int valor;
        struct no* prox;
}NO;

//NO lista[qtdNos];

void inserirArco(NO *lista, int a, int b){
    NO *aux;
    NO *tmp;

    aux = (NO*) malloc((int)sizeof(NO));    //retorno de um ponteiro genérico.
    aux->valor = b;
    aux->prox = NULL;

    lista[a].valor++;
    if(lista[a].prox == NULL) // Caso a lista estiver vazia - Insere.
        lista[a].prox = aux;
    else{
        tmp = lista[a].prox;
        if (tmp->valor > b){ //insere como primeiro da lista
            aux->prox = tmp;
            lista[a].prox = aux;
        } 		          //insere os vértices ordenados
        else if (tmp->prox == NULL){
            aux->prox = tmp->prox;
            tmp->prox = aux;
        }
        else{
            while((tmp->prox != NULL) &&(tmp->prox->valor < b))
                tmp = tmp->prox;
            aux->prox = tmp->prox;
            tmp->prox = aux;
    }
  }
}

void Imprimir(NO *lista){
  int i;
  NO * tmp;
  for(i=0; i < qtdNos; i++) {
    tmp = lista[i].prox;
    printf("%2d: (%d) ==>", i, lista[i].valor);
    while (tmp != NULL) {
      printf("%d  ", tmp->valor);
      tmp = tmp->prox;
    }
    printf("\n");
  }
}

void buscaProfundidade(NO *lista, int vetorProfundidade[], int iteracao){
    NO *aux = lista;
    if(iteracao == 0){
        aux = aux->prox;
    }
    int i;
    //NO *tmp;
    printf("valor %d ",aux->valor);
    if(vetorProfundidade[(aux->valor)-1] == 0){
        vetorProfundidade[(aux->valor)-1] = iteracao + 1;
        while(aux->prox != NULL){
            aux = aux->prox;
            buscaProfundidade(aux, vetorProfundidade, iteracao+1);
                    //printf("%d ",iteracao);

        }
    }
    else
        return;
}

/*void buscaProfundidade(NO lista, int vetorProfundidade[], int iteracao){
    NO aux = lista;
    //NO tmp = lista->prox;
    printf("valor %d ",aux.valor);
    if(vetorProfundidade[(aux.valor)-1] == 0){
        vetorProfundidade[(aux.valor)-1] = iteracao + 1;
        while(aux.prox != NULL){
            aux = aux.prox;
            buscaProfundidade(aux, vetorProfundidade, iteracao+1);
                    //printf("%d ",iteracao);

        }
    }
    else
        return;
}*/

int main()
{
    NO lista[qtdNos];
    int matriz[qtdNos][qtdNos] = {{0,1,1,0,2},{1,0,0,0,1},{1,0,0,1,1},{0,0,1,2,0},{2,1,1,0,1}};
    int vetorProfundidade[qtdNos] = {0};
    int i,j,k;

    for(i = 0; i <= qtdNos; i++){
        lista[i].valor = 0;
        lista[i].prox = NULL;
    }
    //NO *aux = lista->prox;

    for(i = 0; i < qtdNos; i++){
        for(j = 0; j < qtdNos; j++){
            if(matriz[i][j] != 0){
                for(k = matriz[i][j]; k > 0; k--){
                    inserirArco(lista,i,j);
                }
            }
        }
    }
    Imprimir(lista);
    //for(i = 0; i < qtdNos; i++){
        buscaProfundidade(lista,vetorProfundidade,0);
    //}

    printf("%d %d %d %d %d",vetorProfundidade[0],vetorProfundidade[1],vetorProfundidade[2],vetorProfundidade[3],vetorProfundidade[4]);

    return 0;
}
