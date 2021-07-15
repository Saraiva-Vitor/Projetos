#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
using namespace std;

// Fução que recebe informações.
void get_info(double *intervalo_a, double *intervalo_b, double *erro, int *funcao){
	cout<<"Menu de opções, escolha o componente a ser calculado:"<<endl;
	cout<<"1 - Resistor(t=0,05s, L=5H, C=0,0001F, Q=1%% de Qo)."<<endl;
	cout<<"2 - Indutor(t=0,05s, R=280 Ohms, C=0,0001F, Q=1%% de Qo)."<<endl;

	while (*funcao!=1 && *funcao!=2) {
		   cin>>*funcao;
			 if(*funcao!=1 && *funcao!=2){
				 cout<<"Escolha incorreta, faça novamente, por favor."<<endl;
			 }
			}
			cout<<"Digite o valor dos intervalos a e b:"<<endl;
			cin>>*intervalo_a>>*intervalo_b;

			cout<<"Digite o valor do erro:"<<endl;
			cin>>*erro;


}

// Calcula Resitencia
double resistor(double x, vector<double>param){
	return (exp(-(0.005*x))*(cos(sqrt(2000-(0.01*(pow(x,2))))*0.05))+(((x/10)*(1/sqrt(2000-(0.01*(pow(x,2))))))*exp(-(0.005*x))*(sin(sqrt(2000-(0.01*(pow(x,2))))*0.05)))-0.01);

}
// Calcula Indutancia
double indutor(double x, vector<double> param){
	return (exp(-(7/x))*(cos(sqrt((10000/x)-(19600/(pow(x,2))))*0.05))+(((280/2*x)*(1/sqrt((10000/x)-(19600/(pow(x,2))))))*exp(-(7/x))*(sin(sqrt((10000/x)-(19600/(pow(x,2))))*0.05)))-0.01);
}

void print_data(double (*func)(double, vector<double>), vector<double>parametros, int k, double x, double inter_a, double inter_b, double mod_ab){
	cout<<"IteraÃ§Ãµes = "<<k<<endl;
	cout<<"A = "<<inter_a<<endl;
	cout<<"X = "<<x<<endl;
	cout<<"B = "<<inter_b<<endl;
	cout<<"F(A) = "<<func(inter_a, parametros)<<endl;
	cout<<"F(X) = "<<func(x, parametros)<<endl;
	cout<<"F(B) = "<<func(inter_b, parametros)<<endl;
	cout<<" |B-A| = "<<mod_ab<<endl;
	cout<<"--------------------------------------------------------"<<endl;
 }

int iterations(double intervalo_a, double intervalo_b, double erro){
	int iteration;
	double iteracoes = 0;
	double aux = (intervalo_b-intervalo_a);
	iteracoes = ((log10(aux) - log10(erro))/log10(2));
	iteration = (int)ceil(iteracoes);
	return iteration;

}



double bisseccao(double (*func)(double, vector<double>), vector<double> parametros, double intervalo_a, double intervalo_b, double erro){
	cout<<"Este é A = "<<intervalo_a<<"|| Este é B = "<<intervalo_b<<endl;
	if((func(intervalo_a, parametros))*(func(intervalo_b, parametros)) > 0){
		cout<<"Tente novamente com outro intervalo ou outra função."<<endl;
	}else{
		double x = 0;
		int k = 0;
		int i = 0;
		x = ((intervalo_a + intervalo_b) / 2);
		while(fabs(intervalo_a-intervalo_b) > erro){
cout<<"Este é k = "<<k<<" Este é i = "<<i<<endl;

		if((func(intervalo_a, parametros))*(func(x, parametros)) > 0){
			intervalo_a = x;
		}else if((func(intervalo_b, parametros))*(func(x, parametros)) > 0){
			intervalo_b = x;
		}
		x = ((intervalo_a + intervalo_b) / 2);
		k++;
		 print_data(indutor, parametros, k, x, intervalo_a, intervalo_b, fabs(intervalo_b - intervalo_a));
	}
return x; // retorna o valor aproximado da raiz.
}
}


int main (){
  setlocale(LC_ALL, "Portuguese");
	int i, n_func;
	vector<double>vec_parametros;
	double aux, intervalo_a, intervalo_b, erro;
	double raiz = 0;

	get_info(&intervalo_a, &intervalo_b, &erro, &n_func);


	cout<<"Digite os parametros:"<<endl;
	if(n_func == 1){
		vec_parametros.reserve(2);
		for(i = 0; i < 2; i++){
			cin>> aux;
			vec_parametros.push_back(aux);
			aux = 0;
		}
		raiz = bisseccao(resistor, vec_parametros, intervalo_a, intervalo_b, erro);
		cout.precision(10);
		cout<<"A raiz aproximada da função é: "<<raiz<<endl;
	}else if(n_func == 2){
		vec_parametros.reserve(2);
			for(i = 0; i < 2; i++){
				cin>> aux;
				vec_parametros.push_back(aux);
				aux = 0;
			}
			raiz = bisseccao(indutor, vec_parametros, intervalo_a, intervalo_b, erro);
			cout.precision(10);
			cout<<"A raiz aproximada da função é: "<<raiz<<endl;

		}
}
