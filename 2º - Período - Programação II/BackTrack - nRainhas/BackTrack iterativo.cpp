#include <cstdio>
#include <cmath>
#include <cstdlib>

void alocaMatriz();
void desalocaMatriz();
void leMatriz();
void escreveMatriz();
void backtrack();
void reset(int, int);
void enumeraCandidatos(int, int);
bool quadrante(int, int, int);
bool coluna(int, int, int);
bool linha(int, int, int);

/*===================================================
================= Variaveis Globais =================
===================================================*/
int ***matriz;
int n;
bool acabou = false;
bool voltando = false;

/*===================================================
================= Funções principal =================
===================================================*/
int main () {
	int i, j;

	scanf("%i",&n);

	alocaMatriz();
	leMatriz();
	
	backtrack();
	
	escreveMatriz();
    printf("\n");

	desalocaMatriz();

	return 0;
}

/*===================================================
=============== Função de BackTrack =================
===================================================*/
void backtrack() {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(matriz[i][j][n+2]) {
				if(!voltando)
					enumeraCandidatos(i, j);
				if(matriz[i][j][n+1] == 0) {
					voltando=true;
					reset(i, j);
				} else {
					matriz[i][j][0] = matriz[i][j][matriz[i][j][n+1]];
					matriz[i][j][n+1]--;
					voltando = false;
				}
			}
			if(voltando) {
				if(j == 0) {
					i--;
					j=n-2;
				} else
					j-=2;
			}
		}
	}
}

void reset(int lin, int col) {
	int cont=0;
	for(int i=lin; i<n; i++)
		for(int j=col; j<n; j++)
			if(matriz[i][j][n+2]) {
				matriz[i][j][0] = 0;
				cont++;
				if(cont == 2)
					return;
			}
}

void enumeraCandidatos(int lin, int col) {
	matriz[lin][col][n+1] = 0;
	for(int i=n; i>=1; i--) {
		if(linha(i, lin, col) && coluna(i, col, lin) && quadrante(i, lin, col)) {
			matriz[lin][col][n+1]++;
			matriz[lin][col][matriz[lin][col][n+1]] = i;
		}
	}
}

bool linha(int num, int lin, int col) {
	for(int i=0; i<n; i++)
		if(matriz[lin][i][0] == num)
			return false;
	return true;
}

bool coluna(int num, int col, int lin) {
	for(int i=0; i<n; i++)
		if(matriz[i][col][0] == num)
			return false;
	return true;
}

bool quadrante(int num, int lin, int col) {
	int aux = (int)sqrt(n);
	int aux2 = (lin/aux)*aux+aux;
	int aux3 = (col/aux)*aux+aux;
	for(int i=(lin/aux)*aux; i<aux2; i++)
		for(int j=(col/aux)*aux; j<aux3; j++)
			if(matriz[i][j][0] == num)
				return false;
	return true;
}

/*===================================================
==== Funções de leitura e impressão de matriz =======
===================================================*/
void leMatriz() {
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++) {
			scanf("%i",&matriz[i][j][0]);
			if(matriz[i][j][0] == 0)
				matriz[i][j][n+2] = 1;
			else
				matriz[i][j][n+2] = 0;
		}
}

void escreveMatriz() {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++)
            printf("%2i ",matriz[i][j][0]);
		printf("\n");
	}
}

/*===================================================
==== Funções de alocação e desalocação de matriz ====
===================================================*/
void alocaMatriz() {
	matriz = new int **[n];
	for(int i=0; i<n; i++) {
		matriz[i] = new int *[n];
		for(int j=0;j<n;j++) {
			matriz[i][j] = new int [n+3];
		}
	}
}

void desalocaMatriz() {
	for(int i=0; i<n; i++) {
		for(int j=0;j<n;j++) {
			delete []matriz[i][j];
		}
		delete []matriz[i];
	}
	delete []matriz;
}
//=================================================//
