#include <cstdio>
#include <cmath>
#include <cstdlib>

void alocaMatriz();
void desalocaMatriz();
void leMatriz();
void escreveMatriz();
void backtrack(int, int);
void chamaBackTrack(int, int);
void reset(int, int);
void enumeraCandidatos(int *, int &, int, int);
bool quadrante(int, int, int);
bool coluna(int, int, int);
bool linha(int, int, int);

/*===================================================
================= Variaveis Globais =================
===================================================*/
int **matriz;
bool **matrizAux;
int n;
bool acabou = false;

/*===================================================
================= Funções principal =================
===================================================*/
int main () {
	int i, j;

	scanf("%i",&n);

	alocaMatriz();
	leMatriz();
	
	backtrack(0, 0);
	
	escreveMatriz();
    printf("\n");

	desalocaMatriz();

	return 0;
}

/*===================================================
=============== Função de BackTrack =================
===================================================*/
void backtrack(int lin, int col) {
	int *candidatos = new int [n];
	int nCandidatos;
	if(lin == n) {
		acabou = true;
	} else if(matrizAux[lin][col]) {
		enumeraCandidatos(candidatos, nCandidatos, lin, col);
		for(int i=0; i<nCandidatos; i++) {
			matriz[lin][col] = candidatos[i];
			chamaBackTrack(lin, col);
			if(acabou) {
				delete []candidatos;
				return;
			}
		}
	reset(lin, col);
	} else {
		chamaBackTrack(lin, col);	
	}
	delete []candidatos;
}

void chamaBackTrack(int lin, int col) {
	int aux = (int)sqrt(n);
	int aux2 = ((lin/aux)*aux+aux)-1;
	int aux3 = ((col/aux)*aux+aux)-1;
	if(lin == aux2 && col == aux3) {
		if(lin == aux2 && col == n-1)
			backtrack(lin+1, 0);
		else
			backtrack(lin-aux+1 ,col+1);
	} else {
		if(col<aux3)
			backtrack(lin, col+1);
		else
			backtrack(lin+1, col-aux+1);
	}
}

void reset(int lin, int col) {
	int cont=0;
	for(int i=lin; i<n; i++)
		for(int j=col; j<n; j++)
			if(matrizAux[i][j]) {
				matriz[i][j] = 0;
				cont++;
				if(cont == 2)
					return;
			}
}

void enumeraCandidatos(int *candidatos, int &nCandidatos, int lin, int col) {
	nCandidatos = 0;
	for(int i=1; i<=n; i++) {
		if(linha(i, lin, col) && coluna(i, col, lin) && quadrante(i, lin, col)) {
			candidatos[nCandidatos] = i;
			nCandidatos++;
		}
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
	delete [] matriz;
	delete [] matrizAux;
}
//=================================================//
