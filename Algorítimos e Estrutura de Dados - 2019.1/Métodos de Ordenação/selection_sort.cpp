#include <stdio.h>
#include<iostream>
using namespace std;

void selection_sort (int vetor[],int max) {
  int i, j, min, aux;

  for (i = 0; i < (max - 1); i++) {
    /* O minimo é o primeiro número não ordenado ainda */
    min = i;
    for (j = i+1; j < max; j++) {
      /* Caso tenha algum numero menor ele faz a troca do minimo*/
      if (vetor[j] < vetor[min]) {
   min = j;
      }
    }
    /* Se o minimo for diferente do primeiro numero não ordenado ele faz a troca para ordena-los*/
    if (i != min) {
      aux = vetor[i];
      vetor[i] = vetor[min];
      vetor[min] = aux;
    }
  }
  cout << "Termos Ordenados: ";
  for (i = 0; i < max; i++) {
    printf ("%d ",vetor[i]);
  }
  printf ("\n");
}

int main () {
  int max, i;
  cout << "Digite a quantidade de termos: \n";
  scanf ("%d",&max);

  int  vetor[max];
  cout << "Digite os termos a serem ordenados: \n";
  for (i = 0; i < max; i++) {
    scanf ("%d",&vetor[i]);
  }

  selection_sort (vetor, max);

}
