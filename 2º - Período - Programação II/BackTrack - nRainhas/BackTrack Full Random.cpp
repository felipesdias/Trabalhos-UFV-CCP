#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>

using namespace std;

void alocaMatriz();
void desalocaMatriz();
void leMatriz();
void escreveMatriz();
void backtrack(int);
void reset(int, int, int);
void enumeraCandidatos(int *, int &, int, int);
void baguncaCandidatos(int *, int);
bool quadrante(int, int, int);
bool coluna(int, int, int);
bool linha(int, int, int);
void preenchePosicao();
void baguncaPosicao();

struct posicao {
	int lin;
	int col;
};

/*===================================================
================= Variaveis Globais =================
===================================================*/
int **matriz;
bool **matrizAux;
posicao *pos;
int n;
bool acabou = false;

/*===================================================
================= Funções principal =================
===================================================*/
int main () {
	int i, j;
	srand((unsigned)time(NULL));
	scanf("%i",&n);

	alocaMatriz();
	leMatriz();
	
	preenchePosicao();
	baguncaPosicao();
	
	backtrack(0);
	
	escreveMatriz();
    printf("\n");

	desalocaMatriz();

	return 0;
}

/*===================================================
=============== Função de BackTrack =================
===================================================*/
void backtrack(int cadeia) {
	int *candidatos = new int [n];
	int nCandidatos;
	int lin = pos[cadeia].lin;
	int col = pos[cadeia].col;
	if(cadeia == n*n) {
		acabou = true;
	} else if(matrizAux[lin][col]) {
		enumeraCandidatos(candidatos, nCandidatos, lin, col);
		for(int i=0; i<nCandidatos; i++) {
			matriz[lin][col] = candidatos[i];
			backtrack(cadeia+1);
			if(acabou) {
				delete [] candidatos;
				return;
			}
		}
		matriz[lin][col] = 0;
	} else
		backtrack(cadeia+1);
			
	delete []candidatos;
}

void preenchePosicao() {
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++) {
			pos[i*n+j].lin = i;
			pos[i*n+j].col = j;
		}
}

void baguncaPosicao() {
	int aux = n*n;
	posicao auxPos;
	int a;
	for(int i=0; i<aux; i++) {
		a = rand()%aux;
		auxPos = pos[i];
		pos[i] = pos[a];
		pos[a] = auxPos;
		
	}
}

void enumeraCandidatos(int *candidatos, int &nCandidatos, int lin, int col) {
	nCandidatos = 0;
	for(int i=1; i<=n; i++)
		if(linha(i, lin, col) && coluna(i, col, lin) && quadrante(i, lin, col)) {
			candidatos[nCandidatos] = i;
			nCandidatos++;
		}
	if(nCandidatos)
		baguncaCandidatos(candidatos, nCandidatos);
}

void baguncaCandidatos(int *candidatos, int nCandidatos) {
	int a, aux;	
	for(int i=0; i<nCandidatos; i++) {
		a = rand()%nCandidatos;
		aux = candidatos[i];
		candidatos[i] = candidatos[a];
		candidatos[a] = aux;
	}
}
bool linha(int num, int lin, int col) {
	for(int i=0; i<n; i++)
		if(matriz[lin][i] == num)
			return false;
	return true;
}

bool coluna(int num, int col, int lin) {
	for(int i=0; i<n; i++)
		if(matriz[i][col] == num)
			return false;
	return true;
}

bool quadrante(int num, int lin, int col) {

	int aux = (int)sqrt(n);
	int aux2 = (lin/aux)*aux+aux;
	int aux3 = (col/aux)*aux+aux;
	for(int i=(lin/aux)*aux; i<aux2; i++)
		for(int j=(col/aux)*aux; j<aux3; j++)
			if(matriz[i][j] == num)
				return false;
	return true;
}

/*===================================================
==== Funções de leitura e impressão de matriz =======
===================================================*/
void leMatriz() {
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++) {
			scanf("%i",&matriz[i][j]);
			if(matriz[i][j] == 0)
				matrizAux[i][j] = true;
			else
				matrizAux[i][j] = false;
		}
}

void escreveMatriz() {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++)
            printf("%2i ",matriz[i][j]);
		printf("\n");
	}
}

/*===================================================
==== Funções de alocação e desalocação de matriz ====
===================================================*/
void alocaMatriz() {
	pos = new posicao [n*n];
	matriz = new int *[n];
	matrizAux = new bool *[n];
	for(int i=0;i<n;i++) {
		matriz[i] = new int[n];
		matrizAux[i] = new bool[n];
		
	}
}

void desalocaMatriz() {
	for(int i=0;i<n;i++) {
		delete [] matriz[i];
		delete [] matrizAux[i];
	}
	delete [] pos;
	delete [] matriz;
	delete [] matrizAux;
}
//=================================================//
