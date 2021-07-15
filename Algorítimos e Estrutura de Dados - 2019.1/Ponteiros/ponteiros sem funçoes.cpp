#include<iostream>
using namespace std;
int main()
{
	int x=4, y=7;
	cout << "\n &x= " << &x << "\t x=" << x;
	cout << "\n &y= " << &y << "\t y=" << y;
	int *px, *py;
	px = &x;
	py = &y;
	//Ponteiros para variáveis
	//Atribui um endereco ao ponteiro
	cout << "\n px= " << px << "\t *px=" << *px;
	cout << "\n py= " << py << "\t *py=" << *py;
}
