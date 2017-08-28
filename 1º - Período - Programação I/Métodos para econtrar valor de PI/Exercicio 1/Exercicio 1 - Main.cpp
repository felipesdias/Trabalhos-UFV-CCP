#include <iomanip>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Função recursiva para o metodo de brouncker (EXTRA)
double brouncker(double denominador, unsigned long long int n) {
    if (n*2 <= denominador-1)
        return pow(denominador,2.0); // retorna apenas o denominador quando chegar ao ultimo termo pedido
    else
        return 2+(pow(denominador,2.0)/brouncker(denominador+2,n)); // retorna o denominador/denominador recursivo
}



int main() {
	system("cls");
	cout << "===================================" << endl;
	cout << "=== Aluno: Felipe de Souza Dias ===" << endl;
	cout << "======= Matricula: 81841 ==========" << endl;
	cout << "===================================" << endl << endl;

    double pi, denominador;
    unsigned long long int n;
	cout << "Informe quantos termos, deverão ser usados: ";
    cin >> n; // Le o numero de termos, que ira ser usado nas series
    cout << endl;

/*
    //Brouncker Recursivo ( EXTRA )
    denominador = 1;
    pi = 1 + 1/brouncker(denominador+2,n);
    cout << fixed << setprecision(15) << "Metodo Brouncker: " << 4/pi << endl;
*/

    //Brouncker
    pi = pow(n*2-1,2.0); //Começa pelo ultimo termo da serie
    for (unsigned long long int i=n-1; i > 1; i--) // Serie é calculada de traz pra frente, repetindo N-2 vezes
        pi = 2+(pow(i*2-1,2.0)/pi); // Calcula a serie, até o segundo termo
    pi = 1+1/pi; // esta parte ficou separada pois, a primeiro tormado é somado de 1 ao invez de 2
        cout << fixed << setprecision(15) << "Metodo Brouncker: " << 4/pi << endl; // Imprime o valor final de PI

    //Leibniz
    pi = 0; // Por ser uma serie de soma, o valor inicial é 0 ( neutro )
    for (unsigned long long int i=1; i<=n; i++) { // Repete N vezes
        if (i%2 == 1) // alternasoma e subtração
            pi += 1.0/(i*2-1); // faz a soma da serie
        else
            pi -= 1.0/(i*2-1); // faz a subtração da serie
    }
    cout << fixed << setprecision(15) << "Metodo Leibniz:   " << 4*pi << endl; // Imprime o valor final de PI


    //Wallis
    pi = 1; // Por ser uma serie de multiplicação o valor inicial é 1 ( neutro )
    for (unsigned long long int i=1; i<=n; i++) { // Repete N vezes
        if (i%2 == 1) // Alternando aumentar o numerador e denominador, de acordo ao termo da serie
            pi *= (i+1)/(i*1.0); // aumenta o numerador 1
        else
            pi *= (i*1.0)/(i+1.0); // aumenta o denominador em 1
    }
    cout << fixed << setprecision(15) << "Metodo Wallis:    " << 2*pi << endl; // Imprime o valor final de PI


    //Euler
    pi = 0; // Por ser uma serie de soma, o valor inicial é 0 ( neutro )
    for (unsigned long long int i=1; i<=n; i++) // Repete N vezes
        pi += 1.0/pow(i,2.0); // Soma os termos da serie
    cout << fixed << setprecision(15) << "Metodo Euler:     " << sqrt(6*pi) << endl; // Imprime o valor final de PI

    return 0;
}
