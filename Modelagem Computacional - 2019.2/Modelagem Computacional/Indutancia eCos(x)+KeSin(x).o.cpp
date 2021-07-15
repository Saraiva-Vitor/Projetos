#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
using namespace std;
// Calcula o L.
double funcao(double x, vector<double> coeficientes){
	double instante0 = (1/(x*coeficientes[1])) - pow((coeficientes[0]/(2*x)), 2);
	double instante = sqrt(instante0);
	double instante1 = -((((coeficientes[0])/(2*x)))*coeficientes[2]);
	double instante2 = (instante*coeficientes[2]);
	double instante3 = ((coeficientes[0])/ (2*x*instante));
	cout<<(((exp(instante1))*(cos(instante2))) + ((instante3)*(exp(instante1))*(sin(instante2))) - (coeficientes[3]))<<endl;
	return (((exp(instante1))*(cos(instante2))) + ((instante3)*(exp(instante1))*(sin(instante2))) - (coeficientes[3]));

}
double bisseccao(double (*func)(double, vector<double>), vector<double> parametros,
                double intervalo_a, double intervalo_b, double erro){
	if((func(intervalo_a, parametros))*(func(intervalo_b, parametros)) > 0){
		cout<<"Tente novamente com outro intervalo ou outra funcao."<<endl;
	}else{
		double x = 0;
		x = ((intervalo_a + intervalo_b) / 2);
		while(fabs(intervalo_a-intervalo_b) > erro){
		if((func(intervalo_a, parametros))*(func(x, parametros)) > 0){
			intervalo_a = x;
		}else if((func(intervalo_b, parametros))*(func(x, parametros)) > 0){
			intervalo_b = x;
		}
		x = ((intervalo_a + intervalo_b) / 2);
	}
return x; // retorna o valor aproximado da raiz.
}
}
int main(){
	vector<double> parametros;
	double R,C,t,q,a,b,erro;
	cout << "Digite o Valor do Resistor(R):"; cin >> R;
	cout << "Digite o Valor do Capacitor(C):"; cin >> C;
	cout << "Digite o tempo(t):"; cin >> t;
	cout << "Digite a Razao da Carga(q/q0):"; cin >> q;
	cout << "Digite o Valor de a do intervalo [a,b]:"; cin >> a;
	cout << "Digite o Valor de b do intervalo [a,b]:"; cin >> b;
	cout << "Digite o Erro:"; cin >> erro;
	parametros.push_back(R); //R
	parametros.push_back(C); //C
	parametros.push_back(t); //t
	parametros.push_back(q); //q/q0
	double func = bisseccao(funcao, parametros, a, b, erro);
	cout.precision(10);
	cout<<func<<endl;
}
