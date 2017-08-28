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

    long long int raio[15] = {3,3,5,10,10,50,100,500,500,1001,1001,7000,7000,11000,11000}, qtPontos[15] = {3,1000,5,10,10000,50,100,500,100,1001,2000,7000,1000,10000,100000}, X, Y, cont;
    double distancia;


	srand(time(NULL));
	for(int i=0; i<15; i++) {
		cont = 0;
		for (int j=0; j<qtPontos[i]; j++) {
			X = (rand()%(raio[i]+raio[i]+1))-raio[i];
			Y = (rand()%(raio[i]+raio[i]+1))-raio[i];

			distancia = X*X+Y*Y;

			if(distancia <= raio[i]*raio[i])
				cont++;
		}
		cout << "Raio: " << setw(5) << raio[i] << " e Quantidade de pontos: " << setw(6) << qtPontos[i] << " => PI = " << 4.0*(1.0*cont/qtPontos[i]) << endl;
	}

		cout << endl << "Este metodo nao eh preciso, pois se trata de um sorteio, logo os resultados \nvariam, e sao pouco precisos.\nMesmo usando altos valores, este metodo eh ineficaz." << endl << endl;

    return 0;
}
