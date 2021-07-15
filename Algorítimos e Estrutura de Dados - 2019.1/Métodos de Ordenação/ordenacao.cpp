#include<iostream>
using namespace std;
void selection_sort (int vetor[],int max) {
    int i, j, min, aux;
    for (i = 0; i < (max - 1); i++) {
        min = i;
        for (j = i+1; j < max; j++) {
            if (vetor[j] < vetor[min]) {
            min = j;
            }
        }
        if (i != min) {
            aux = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = aux;
        }
    }
    cout << "\nOrdenado com Selection Sort: ";
    for(int c=0;c<max;c++){
        cout << vetor[c] << " ";
    }
}
void insertion_sort(int vetor[], int n) {
    int i, j, tmp;
    for (i = 1; i < n; i++) {
        j = i;
        while (j > 0 && vetor[j - 1] > vetor[j]) {
            tmp = vetor[j];
            vetor[j] = vetor[j - 1];
            vetor[j - 1] = tmp;
            j--;
        }
    }
    cout << "\nOrdenado com Insertion Sort: ";
    for(int c=0;c<n;c++){
        cout << vetor[c] << " ";
    }
}
void bubble_sort(int vetor[], int n) {
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
    cout << "\nOrdenado com Bubble Sort: ";
    for(int c=0;c<n;c++){
        cout << vetor[c] << " ";
    }
}
int main() {
    int n;
    cout << "Entre com o número de termos: "; cin >> n;
    int vetor[n];
    cout << "Entre com os números: ";
    for(int c=0;c<n;c++){
        cin >> vetor[c];
    }
    selection_sort(vetor,n);
    insertion_sort(vetor,n);
    bubble_sort(vetor,n);
}
