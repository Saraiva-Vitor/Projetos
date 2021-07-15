#include<iostream>
using namespace std;
void bubble_sort (int vetor[], int n) {
    int k, j, aux;
    for (k = 0; k < n+1; k++) {
        for (j = 0; j < n +1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}
int main() {
    int i;
    cout << "Entre com a quantidade de termos: "; cin >> i;
    cout << "\nEntre com os termos: " ;
    int vetor[i];
    for(int c=0;c<i;c++){
        cin >> vetor[c];
    }
    bubble_sort(vetor,i);
    cout << "\nTermos Ordenados: ";
    for(int c=0;c<5;c++){
        printf("%d ",vetor[c]);
    }
}
