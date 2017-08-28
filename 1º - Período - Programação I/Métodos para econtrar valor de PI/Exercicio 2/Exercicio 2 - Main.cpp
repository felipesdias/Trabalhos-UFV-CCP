#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main() {
	system("cls");
	cout << "===================================" << endl;
	cout << "=== Aluno: Felipe de Souza Dias ===" << endl;
	cout << "======= Matricula: 81841 ==========" << endl;
	cout << "===================================" << endl << endl;

    long long int raio, qtPontos, X, Y, cont=0;
    double distancia;

    cout << "Digite o raio: ";
    cin >> raio; // Le o valor do raio
	cout << "Digite quantos pontos devera ser sorteado: ";
	cin >> qtPontos; // Le quantos pontos deverão ser sortedos
	cout << endl;


	srand(time(NULL)); // Inicia modo aleatorio
    for (int i=0; i<qtPontos; i++) { //Sorteia numero de pontos pedidos
		X = (rand()%(raio+raio+1))-raio; // Sorteia uma cordenada X de -raio até raio
		Y = (rand()%(raio+raio+1))-raio; // Sorteia uma cordenada Y de -raio até raio

        distancia = X*X+Y*Y; // Formula da distancia ( pitagoras ), H² = x² + y² (Não usei sqrt pois é uma função lenta)

        if(distancia <= raio*raio) // Se distancia for menor que o raio*raio ( compensar, quando não tirei a raiz da distancia ), logo o ponto esta dentro do circulo
            cont++; // Conta quantos pontos estão dentro do circulo
    }

    cout << "PI = " << 4.0*(1.0*cont/qtPontos) << endl; // Imprime valor final de PI

    return 0;
}
