/*++++++++++++++++++++++++++++++++++++++++++++++++
|	Nome						Matricula        |
|	Felipe de Souza Dias		81841            |
|	Marcelo Matos				75254            |
++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

void alocaMatriz();
void desalocaMatriz();
void leMatriz();
void escreveMatriz();
void backtrack(int, int); //linha, coluna
void enumeraCandidatos(int *, int &, int, int); //vetor candidatos, numero candidatos, linha, coluna
bool quadrante(int, int, int); //numero testado, linha, coluna
bool coluna(int, int, int); //numero testado, linha, coluna
bool linha(int, int, int); //numero testado, linha, coluna

/*===================================================
================= Variaveis Globais =================
===================================================*/
int **matriz; //Vetor do tabuleiro
bool **matrizAux; //Vetor que armaze se o numero eh fixo ou nao
int n; //tamanho do vetor
bool acabou = false; //booleano que armazena quando encontra uma resposta

/*===================================================
================= Função principal =================
===================================================*/
int main () {
	int i, j;

	scanf("%i",&n); // le o tamanho da matriz

	alocaMatriz(); //chama a funcao para alocar a matriz
	leMatriz(); //faz a leitura dos valores da matriz

	backtrack(0, 0); //chama backtraco, com lin=0 e col=0
	
	escreveMatriz(); //escreve a matriz apos o backTrack
    printf("\n");

	desalocaMatriz(); //desaloca a matriz

	return 0;
}

/*===================================================
=============== Função de BackTrack =================
===================================================*/
void backtrack(int lin, int col) {
	int *candidatos = new int [n]; // cria vetor que armazena os candidatos possiveis para essa posicao
	int nCandidatos; // guaradara o numero de candidatos possiveis para essa posicao
	if(lin == n) { // verifica se chegou ao final da matriz
		acabou = true;
	} else if(matrizAux[lin][col]) { // verifica se essa posicao nao eh fixa
		enumeraCandidatos(candidatos, nCandidatos, lin, col); // armazena os candidatos possiveis para essa posicao
		for(int i=0; i<nCandidatos; i++) {	// testa todos os candidatos	
			matriz[lin][col] = candidatos[i]; // coloca o candidato na matriz principal

			if(col == n-1) // Verifica posicao atual para chamar a proxima posicao da matriz por backTrack
				backtrack(lin+1, 0);
			else
				backtrack(lin, col+1);
			
			if(acabou) { // Verifica se ja encontrou uma solucao
				delete []candidatos; // deleta o vetor de candidatos
				return;
			}
		}
		matriz[lin][col] = 0; // Apos testar os candidos, e nenhum dar certo ele zera a posicao antes de voltar recursivamente
	} else {
		if(col == n-1) // Verifica posicao atual para chamar a proxima posicao da matriz por backTrack
			backtrack(lin+1, 0);
		else
			backtrack(lin, col+1);	
	}
	delete []candidatos; // deleta o vetor de candidatos
}

/*===============================================================
=== Função que enumera os candidatos possiveis para a posicao ===
===============================================================*/
void enumeraCandidatos(int *candidatos, int &nCandidatos, int lin, int col) {
	nCandidatos = 0;
	for(int i=1; i<=n; i++) { // testa todos os valores de 1 ate n
		if(linha(i, lin, col) && coluna(i, col, lin) && quadrante(i, lin, col)) { // verifica se esse valor pode ser um candidato
			candidatos[nCandidatos] = i; // guarda esse valor dentro do vetor de candidatos
			nCandidatos++; // incrementa o numero de candidatos
		}
	}
}

/*================================================================
=== Funções que verifica se um numero pode estar nessa posicao ===
================================================================*/
bool linha(int num, int lin, int col) {
	for(int i=0; i<n; i++) //passa por todos as posicoes da linha
		if(matriz[lin][i] == num) // verifica se o numero ja se encontra em alguma posicao
			return false;
	return true;
}

bool coluna(int num, int col, int lin) {
	for(int i=0; i<n; i++) // igual o de cima
		if(matriz[i][col] == num) // igual o de cima
			return false;
	return true;
}

bool quadrante(int num, int lin, int col) {

	int aux = (int)sqrt(n); // recebe o tamanho do quadrante
	int aux2 = (lin/aux)*aux+aux; // recebe a ultima posicao da linha do quadrante
	int aux3 = (col/aux)*aux+aux; // recebe a ultima posicao da coluna do quadrante
	for(int i=(lin/aux)*aux; i<aux2; i++) // passa por todas as posicoes do quadrante
		for(int j=(col/aux)*aux; j<aux3; j++)
			if(matriz[i][j] == num) // verifica se o numero se encontra em alguma posicao do quadrante
				return false;
	return true;
}

/*===================================================
==== Funções de leitura e impressão de matriz =======
===================================================*/
// esse c ja manja
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
// esse tmb
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
// esse aqui tmb
void alocaMatriz() {
	matriz = new int *[n];
	matrizAux = new bool *[n];
	for(int i=0;i<n;i++) {
		matriz[i] = new int[n];
		matrizAux[i] = new bool[n];
		
	}
}
// esse otro tmb
void desalocaMatriz() {
	for(int i=0;i<n;i++) {
		delete [] matriz[i];
		delete [] matrizAux[i];
	}
	delete [] matriz;
	delete [] matrizAux;
}
//=================================================//
