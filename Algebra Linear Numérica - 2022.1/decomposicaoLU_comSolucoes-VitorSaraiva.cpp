#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <random>
#define n 10

float eqsol[n][n];
float sol[n];
float b[n];

std::random_device seeder;
std::mt19937 engine(seeder());
std::uniform_int_distribution<int> dist(-100, 100);

using namespace std;

/*
void print_matriz(float (*mat)[n]){
    int i,j;
    for(i=0;i<n;i++){
        printf("|");
        for(j=0;j<n;j++){
            printf(" %.1f\t",mat[i][j]);
        }
        printf(" |\n");
    }
}

void print_vetor(float (*vet)){
    int i;
    for(i=0;i<n;i++){
        printf("|");
        printf(" %.1f\t",vet[i]);
        printf(" |\n");
        }
    }
*/

void gera_A_b(float (*mat)[n], float (*vet)){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            //printf("Digite o valor da posicao A[%d][%d]=",i+1,j+1);
            //scanf("%f",&mat[i][j]);
            mat[i][j] = dist(engine);
            vet[i] = dist(engine);
        }
    }
}

void mult(float (*mat1)[n], float (*mat2)[n], float (*vet)){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            eqsol[i][j] += mat1[i][j]*mat2[i][j];
            sol[i] += eqsol[i][j]*vet[i];
        }
        //printf("%.1f\n",eqsol[i]);
    }
}

void decomposicaolu(float(*mat)[n]){
    int i,j;
    float M[n][n],aux[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            M[i][j]=0;
            aux[i][j]=mat[i][j]; 
        }
    }
    //printf("Matriz antes:\n");
    //print_matriz(aux);
    for(j=0;j<n;j++){
        //printf("\nMultiplicadores de Gauss da %d coluna\n",j+1);
        for(i=j+1;i<n;i++){
            if(aux[i][j]==0)
            {
                //printf("Sem necessidade de cálculo nesse termo\n");
            }else
             {
                M[i][j]=aux[i][j]/aux[j][j];
                //printf("M[%d][%d]=%.2f\n",i+1,j+1,M[i][j]);
            
                int c=0;

                for(c=j;c<n;c++){
                    //printf("\nMultiplicando a %dx%d por %.2f\n",j+1,c+1,-1*M[i][j]);
                    //print_matriz(aux);
                    //printf("\n%.2f * %.2f = %.2f\n",aux[j][c],-1*M[i][j],aux[j][c]*(-1*(M[i][j])));
                    //printf("%.2f + %.2f = %.2f --> POS[%d][%d]\n",aux[j][c]*(-1*(M[i][j])),aux[i][c],aux[i][c]+aux[j][c]*(-1*(M[i][j])),i+1,c+1);
                    aux[i][c]=aux[i][c]+aux[j][c]*(-1*(M[i][j]));

                    //printf("\nMatriz depois\n");
                    //print_matriz(aux);
                }
            }
            //printf("\n");
        }

    }
    //printf("\n\nDECOMPOSIÇÃO LU\n");
    for(i=0;i<n;i++) M[i][i]=1;
    //printf("\nMatriz L:\n");
    //print_matriz(M);

    //printf("\nMatriz U:\n");
    //print_matriz(aux);

    mult(M,aux,b);
}

int main(){
    
    //auto start = chrono::steady_clock::now();

    float A[n][n];
    float M[n][n];
    gera_A_b(A,b);

    int count = 0;
//while(count < 100){

    //printf("Matriz A:\n");
    //print_matriz(A);
    //printf("Vetor B:\n");
    //print_vetor(b);

    decomposicaolu(A);
    
    //print_matriz(eqsol);
    //print_vetor(sol);
    
    //count++;
//}
//auto end = chrono::steady_clock::now();
//        cout << "Elapsed time in microseconds: "
//        << (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/100
//        << " ns" << endl;

    return 0;
}
