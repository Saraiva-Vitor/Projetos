#include<iostream>
#include<math.h>
using namespace std;

float funcR(float R){
    return (exp(-((R/(2*5))*0.05))*(cos(sqrt((1/(5*0.0001)-((pow((R/(2*5)),2)))))*0.05))+(((R/(2*5))*(1/sqrt(1/(5*0.0001)-((pow((R/(2*5)),2)))))*exp(-((R/(2*5))*0.05))*(sin(sqrt((1/(5*0.0001)-((pow((R/(2*5)),2)))))*0.05))))-0.01);
}

float funcL(float L){
    return (exp(-((R/(2*L))*t))*(cos(sqrt((1/(L*C)-((pow((R/(2*L)),2)))))*t))+(((R/(2*L))*(1/sqrt(1/(L*C)-((pow((R/(2*L)),2)))))*exp(-((R/(2*L))*t))*(sin(sqrt((1/(L*C)-((pow((R/(2*L)),2)))))*t))))-q);

void print_data(func(), vector<double>parametros, int k, double x, double inter_a, double inter_b, double mod_ab){
	cout<<"Iterações = "<<k<<endl;
	cout<<"A = "<<inter_a<<endl;
	cout<<"X = "<<x<<endl;
	cout<<"B = "<<inter_b<<endl;
	cout<<"F(A) = "<<func(inter_a, parametros)<<endl;
	cout<<"F(X) = "<<func(x, parametros)<<endl;
	cout<<"F(B) = "<<func(inter_b, parametros)<<endl;
	cout<<" |B-A = "<<mod_ab<<endl;
	cout<<"--------------------------------------------------------"<<endl;
 }

float bissecaoR() {
    int a,b; float e;
    (exp(-((R/(2*L))*t))*(cos(sqrt((1/(L*C)-((pow((R/(2*L)),2)))))*t))+(((R/(2*L))*(1/sqrt(1/(L*C)-((pow((R/(2*L)),2)))))*exp(-((R/(2*L))*t))*(sin(sqrt((1/(L*C)-((pow((R/(2*L)),2)))))*t))))-q);
    cout << "\n Digite os valores a do intervalo:"; cin >> a;
    cout << "\n Digite os valores b do intervalo:"; cin >> b;
    cout << "\n Digite o Erro:"; cin >> e;
    R = ((a + b) / 2);
    while(fabs(a-b) > e){
		if((func(R,L,C,t,q)*func(a,L,C,t,q)) > 0){
			a = R;
		}else if((func(R,L,C,t,q)*func(b,L,C,t,q)) > 0){
			b = R;
		}
		R = ((a + b) / 2);
	}
return R;
}

int main() {
    int op;
    float raiz;
    cout << "Escolha o valor a ser calculado:";
    cout << "\n1- Resistencia";
    cout << "\n2- Indutancia\n";
    cin >> op;
    if (op==1) {
        float L,t,q,C,R=0;
        cout << "\n\nDigite o Valor do Capacitor(C):"; cin >> C;
        cout << "\nDigite o Valor do Tempo(t):"; cin >> t;
        cout << "\nDigite o Valor do Indutor(L):"; cin >> L;
        cout << "\nDigite a razao da Carga(q):"; cin >> q;
        raiz = bissecaoR(R,L,C,t,q);
    }
    if (op==2) {
        float L=0,t,q,C,R;
        cout << "\n\nDigite o Valor do Capacitor(C):"; cin >> C;
        cout << "\nDigite o Valor do Tempo(t):"; cin >> t;
        cout << "\nDigite o Valor do Resistor(R):"; cin >> R;
        cout << "\nDigite a razao da Carga(q):"; cin >> q;
    }
    cout << raiz;
}

