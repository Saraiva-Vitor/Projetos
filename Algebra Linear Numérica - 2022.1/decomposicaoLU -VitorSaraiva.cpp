#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define n 3

void print_matriz(float (*mat)[n]){
    int i,j;
    for(i=0;i<n;i++){
        printf("|");
        for(j=0;j<n;j++){
            printf(" %.2f\t",mat[i][j]);
        }
        printf(" |\n");
    }
}

void matrizA(float (*mat)[n]){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("Digite o valor da posicao A[%d][%d]=",i+1,j+1);
            scanf("%f",&mat[i][j]);
        }
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

}

int main(){
    
    float A[n][n];
    float M[n][n];
    matrizA(A);
//    time_t inicio, fim;
//    int t;
//    inicio = time(NULL);
//    int count = 0;
//while(count < 100){
    /*A[0][0]=16;
    A[0][1]=-4;
    A[0][2]=12;
    A[0][3]=-4;
    A[1][0]=-4;
    A[1][1]=2;
    A[1][2]=-1;
    A[1][3]=1;
    A[2][0]=12;
    A[2][1]=-1;
    A[2][2]=14;
    A[2][3]=-2;
    A[3][0]=-4;
    A[3][1]=1;
    A[3][2]=-2;
    A[3][3]=83;
    
    A[0][0]=1;
    A[0][1]=2;
    A[0][2]=0;
    A[1][0]=0;
    A[1][1]=4;
    A[1][2]=2;
    A[2][0]=1;
    A[2][1]=3;
    A[2][2]=2;*/

    //printf("Matriz A:\n");
    //print_matriz(A);

    decomposicaolu(A);
    //count++;
//}
    //fim = time(NULL); //Isto deve ficar no final
    //fprintf(stdout, "O tempo de execucao em segundos é %.8f\n", difftime(fim, inicio)/100);

    return 0;
}
