#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
using namespace std;
double funcao1(double x, vector<double> coeficientes){
	double instante0 = (1/(x*coeficientes[1])) - pow((coeficientes[0]/(2*x)), 2);
	double instante = sqrt(instante0);
	double instante1 = -((((coeficientes[0])/(2*x)))*coeficientes[2]);
	double instante2 = (instante*coeficientes[2]);
	double instante3 = ((coeficientes[0])/ (2*x*instante));
	//cout<<(((exp(instante1))*(cos(instante2))) - (coeficientes[3]))<<endl;
	return (((exp(instante1))*(cos(instante2))) - (coeficientes[3]));
}
double funcao2(double x, vector<double> coeficientes){
	double instante0 = (1/(x*coeficientes[1])) - pow((coeficientes[0]/(2*x)), 2);
	double instante = sqrt(instante0);
	double instante1 = -((((coeficientes[0])/(2*x)))*coeficientes[2]);
	double instante2 = (instante*coeficientes[2]);
	double instante3 = ((coeficientes[0])/ (2*x*instante));
	//cout<<(((exp(instante1))*(cos(instante2))) + ((instante3)*(exp(instante1))*(sin(instante2))) - (coeficientes[3]))<<endl;
	return (((exp(instante1))*(cos(instante2))) + ((instante3)*(exp(instante1))*(sin(instante2))) - (coeficientes[3]));
}
double funcao3(double x, vector<double> coeficientes){
	double instante0 = (1/(coeficientes[0]*coeficientes[1])) - pow((x/(2*coeficientes[0])), 2);
	double instante = sqrt(instante0);
	double instante1 = -((((x)/(2*coeficientes[0])))*coeficientes[2]);
	double instante2 = (instante*coeficientes[2]);
	double instante3 = ((x)/ (2*coeficientes[0]*instante));
	//cout<<(((exp(instante1))*(cos(instante2))) - (coeficientes[3]))<<endl;
	return (((exp(instante1))*(cos(instante2))) - (coeficientes[3]));

}
double funcao4(double x, vector<double> coeficientes){
	double instante0 = (1/(coeficientes[0]*coeficientes[1])) - pow((x/(2*coeficientes[0])), 2);
	double instante = sqrt(instante0);
	double instante1 = -((((x)/(2*coeficientes[0])))*coeficientes[2]);
	double instante2 = (instante*coeficientes[2]);
	double instante3 = ((x)/ (2*coeficientes[0]*instante));
	//cout<<(((exp(instante1))*(cos(instante2))) + ((instante3)*(exp(instante1))*(sin(instante2))) - (coeficientes[3]))<<endl;
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
return x;
}
}
int main(){
    int o;
    cout<<"Menu de opcoes, escolha o componente a ser calculado:"<<endl;
	cout<<"1 - Indutor(e^at)*Cos(bt)."<<endl;
	cout<<"2 - Indutor(e^at)*Cos(bt)+ K*(e^at)*Sin(bt)."<<endl;
	cout<<"3 - Resistor(e^at)*Cos(bt)."<<endl;
	cout<<"4 - Resistor(e^at)*Cos(bt)+ K*(e^at)*Sin(bt)."<<endl;
    while (o!=1 && o!=2 && o!=3 && o!=4) {
		   cin>>o;
			 if(o!=1 && o!=2 && o!=3 && o!=4){
				 cout<<"Escolha incorreta, faca novamente, por favor."<<endl;
			 }
			}
    if (o==1) {
        vector<double> parametros;
        double R,C,t,q,a,b,erro;
        cout << "Digite o Valor do Resistor(R):"; cin >> R;
        cout << "Digite o Valor do Capacitor(C):"; cin >> C;
        cout << "Digite o tempo(t):"; cin >> t;
        cout << "Digite a Razao da Carga(q/q0):"; cin >> q;
        cout << "Digite o Valor de a do intervalo [a,b]:"; cin >> a;
        cout << "Digite o Valor de b do intervalo [a,b]:"; cin >> b;
        cout << "Digite o Erro:"; cin >> erro;
        parametros.push_back(R);
        parametros.push_back(C);
        parametros.push_back(t);
        parametros.push_back(q);
        double func = bisseccao(funcao1, parametros, a, b, erro);
        cout.precision(10);
        cout<<func<<endl;
    }
    if (o==2) {
        vector<double> parametros;
        double R,C,t,q,a,b,erro;
        cout << "Digite o Valor do Resistor(R):"; cin >> R;
        cout << "Digite o Valor do Capacitor(C):"; cin >> C;
        cout << "Digite o tempo(t):"; cin >> t;
        cout << "Digite a Razao da Carga(q/q0):"; cin >> q;
        cout << "Digite o Valor de a do intervalo [a,b]:"; cin >> a;
        cout << "Digite o Valor de b do intervalo [a,b]:"; cin >> b;
        cout << "Digite o Erro:"; cin >> erro;
        parametros.push_back(R);
        parametros.push_back(C);
        parametros.push_back(t);
        parametros.push_back(q);
        double func = bisseccao(funcao2, parametros, a, b, erro);
        cout.precision(10);
        cout<<func<<endl;
    }
    if (o==3) {
        vector<double> parametros;
        double L,C,t,q,a,b,erro;
        cout << "Digite o Valor do Indutor(L):"; cin >> L;
        cout << "Digite o Valor do Capacitor(C):"; cin >> C;
        cout << "Digite o tempo(t):"; cin >> t;
        cout << "Digite a Razao da Carga(q/q0):"; cin >> q;
        cout << "Digite o Valor de a do intervalo [a,b]:"; cin >> a;
        cout << "Digite o Valor de b do intervalo [a,b]:"; cin >> b;
        cout << "Digite o Erro:"; cin >> erro;
        parametros.push_back(L);
        parametros.push_back(C);
        parametros.push_back(t);
        parametros.push_back(q);
        double func = bisseccao(funcao3, parametros, a, b, erro);
        cout.precision(10);
        cout<<func<<endl;
    }
    if (o==4) {
        vector<double> parametros;
        double L,C,t,q,a,b,erro;
        cout << "Digite o Valor do Indutor(L):"; cin >> L;
        cout << "Digite o Valor do Capacitor(C):"; cin >> C;
        cout << "Digite o tempo(t):"; cin >> t;
        cout << "Digite a Razao da Carga(q/q0):"; cin >> q;
        cout << "Digite o Valor de a do intervalo [a,b]:"; cin >> a;
        cout << "Digite o Valor de b do intervalo [a,b]:"; cin >> b;
        cout << "Digite o Erro:"; cin >> erro;
        parametros.push_back(L);
        parametros.push_back(C);
        parametros.push_back(t);
        parametros.push_back(q);
        double func = bisseccao(funcao4, parametros, a, b, erro);
        cout.precision(10);
        cout<<func<<endl;
    }
}
