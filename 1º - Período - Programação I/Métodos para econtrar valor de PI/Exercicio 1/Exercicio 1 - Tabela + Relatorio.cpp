#include <iomanip>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main() {
    int tabela, n;
    double pi, denominador, numerador, variacao;
    int teste[15] = {6,7,9,10,11,50,51,100,111,500,501,1000,100001,500000,1000001};

	do {
	system("cls");
		cout << "===================================" << endl;
		cout << "=== Aluno: Felipe de Souza Dias ===" << endl;
		cout << "======= Matricula: 81841 ==========" << endl;
		cout << "===================================" << endl << endl;

        cout << "Fechar Programa = 0" <<
        endl << "Brouncker = 1" <<
        endl << "Leibniz = 2" <<
        endl << "Wallis = 3" <<
        endl << "Euler = 4" <<
		endl << "Geral = 5" << endl <<
        endl << "Escolha qual metodo usar para gerar a tabela: ";

        cin >> tabela;
        cout << endl;


        while (tabela < 0 || tabela > 5) {
            cout << "Numero invalido, digite novamente: ";
            cin >> tabela;
            cout << endl;
        }


        if (tabela == 0) {

        }
        //Brouncker
        else if (tabela == 1) {
            cout << "========================" << endl;
            cout << "=== Metodo Brouncker ===" << endl;
            cout << "========================" << endl << endl;
            for (int i=0; i < 15; i++) {
                n = teste[i];
                    pi = pow(n*2-1,2.0);
                for (int j=n-1; j > 1; j -= 1)
                    pi = 2+(pow(j*2-1,2.0)/pi);
                pi = 1+1/pi;
                cout << fixed << setprecision(15) << "Metodo Brouncker - " << setw(7) << teste[i] << ": " << 4/pi << endl;
            }
			cout << endl << "Quanto mais termos usados, mais proximo vai ficando de PI, quando numero de\ntermos usados eh par ele se aproxima pela direita e quando impar pela esquerda.\nA quantidade de termos nescesasrio para obter uma boa precisao de PI eh por\nvolta de 50000." << endl;
			cin.get();
			cin.get();
		}
        //Leibniz
        else if (tabela == 2) {
            cout << "======================" << endl;
            cout << "=== Metodo Leibniz ===" << endl;
            cout << "======================" << endl << endl;
            for (int i=0; i < 15; i++) {
                n = teste[i];
                pi = 0;
                for (int j=1; j<=n; j++) {  
                    if (j%2 == 1)    
                        pi += 1.0/(j*2-1);
                    else
                        pi -= 1.0/(j*2-1);
                }
                cout << fixed << setprecision(15) << "Metodo Leibniz - " << setw(7) << teste[i] << ": " << 4*pi << endl;
            }
			cout << endl << "Quanto mais termos usados, mais proximo vai ficando de PI, quando numero de\ntermos usados eh par ele se aproxima pela esquerda e quando impar pela direita.\nA quantidade de termos nescesasrio para obter uma boa precisao de PI eh por\nvolta de 50000 " << endl;
			cin.get();
			cin.get();
        }
        //Wallis
        else if (tabela == 3) {
            cout << "======================" << endl;
            cout << "=== Metodo Wallis ===" << endl;
            cout << "======================" << endl << endl;
            for (int i=0; i < 15; i++) {
                n = teste[i];
                pi = 1;
                for (int j=1; j<=n; j++) {
                    if (j%2 == 1)              // Alternando entre somar "0" e 2 no numerador e no denominador alternando entre somar 2 e repetir
                        pi *= (j+1)/(j*1.0);
                    else
                        pi *= (j*1.0)/(j+1.0);
                }
                cout << fixed << setprecision(15) << "Metodo Wallis - " << setw(7) << teste[i] << ": " << 2*pi << endl; // Imprime o valor de PI
            }
			cout << endl << "Quanto mais termos usados, mais proximo vai ficando de PI, quando numero de\ntermos usados eh par ele se aproxima pela esquerda e quando impar pela direita.\nA quantidade de termos nescesasrio para obter uma boa precisao de PI eh por\nvolta de 15000."  << endl;
			cin.get();
			cin.get();
		}
        //Euler
        else if (tabela == 4) {
            cout << "======================" << endl;
            cout << "=== Metodo Euler ===" << endl;
            cout << "======================" << endl << endl;
            for (int i=0; i < 15; i++) {
                n = teste[i];
                pi = 0;
                for (int j=1; j<=n; j++) {
                    pi += 1.0/pow(j,2.0);
                }
                cout << fixed << setprecision(15) << "Metodo Euler - " << setw(7) << teste[i] << ": " << sqrt(6*pi) << endl; // Imprime o valor de PI
            }
			cout << endl << "Quanto mais termos usados, mais proximo vai ficando de PI, diferentemente dos\noutros metodos, o Euler se aproxima apenas pela esquerda.\nA quantidade de termosnescesasrio para obter uma boa precisao de PI eh porvolta de 15000." << endl;
			cin.get();
			cin.get();
		}
		
		//Geral
		else if (tabela == 5) {
	
            cout << "=======================" << endl;
            cout << "=== Relatorio Geral ===" << endl;
            cout << "=======================" << endl << endl;
	
			cout << endl << endl << "A maioria dos metodos se aproxima pela esquerda quando o numero de termos eh pare pela direita quando impar, com excecão do Euler que se aproxima apenas pela\nesquerda e Brouncker que é o oposto.\nApesar de todos os metodos convergirem com velocidades parecidas, no metodo do \nEuler eh um pouco mais rapido que os demais." << endl << endl << "Aperte um tecla para continuar";
			cin.get();
			cin.get();
		}
    } while(tabela != 0);

    return 0;
}
