#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstdio>

#define NUM_ATRIBUTOS 34
#define NUM_ENTRADAS 351

const double EulerConstant = exp(1.0);

using namespace std;

// Instancia
struct t_Entrada {
	double valores[NUM_ATRIBUTOS]; //Valores dos atributos
	double classificacao; //Classificação, se é good ou bad
};


// Inicializa pesoss com valores aleatorios
void inicializaPesos(double *peso) {
	for(int i=0; i<NUM_ATRIBUTOS; i++) // Para cada peso, faz o calculo			
		peso[i] = ((rand()%10000)*1.0 )/((rand()%10000 + 10000)*1.0); // Gera valor aleatorio
}

// Funcao de ativacao da Regressão
double logistica(double *peso, t_Entrada entrada) {
	double somatorio = 0;
	
	for(int i=0; i<NUM_ATRIBUTOS; i++) // Faz o somatorio de cada atributo multiplicado pelo peso
		somatorio += entrada.valores[i]*peso[i];
	

	return 1.0 / (1.0 + pow(EulerConstant, -somatorio))*1.0; //Retorna valor de H_theta(x)
}

//Avalia se é "good" ou "bad"
int classificaLogistica(double *peso, t_Entrada entrada) {
	if(logistica(peso, entrada) >= 0.5)
		return 1;
	
	return 0;
}

void treinaLogistica(t_Entrada *entrada, double *peso, double alpha) {
	double somatorio;
	double aux[NUM_ENTRADAS];
	
	for(int i=75; i<NUM_ENTRADAS; i++)
		aux[i] = logistica(peso, entrada[i]) - entrada[i].classificacao;
	
	for(int i=0; i<NUM_ATRIBUTOS; i++) {
		somatorio = 0;
		for(int j=75; j<NUM_ENTRADAS; j++)
			somatorio += aux[j]*entrada[j].valores[i];
		peso[i] -= alpha * (1.0/NUM_ENTRADAS) * somatorio;
	}
}


// Faz leitura do arquivo de entrada
bool leEntrada(t_Entrada *entrada) {
	FILE *arq;
	
	arq = fopen("entrada.txt", "r");
	if (arq == NULL) {
		printf("Um erro ocorreu ao tentar abrir o arquivo `entrada.txt'.\n");
		return false;
	}
	
	char aux;
	
	for(int i=0; i<NUM_ENTRADAS; i++) {
		for(int j=0; j<NUM_ATRIBUTOS; j++)
			fscanf(arq, "%lf,", &entrada[i].valores[j]);
		fscanf(arq, "%c\n", &aux);
		
		if(aux == 'g')
			entrada[i].classificacao = 1.0;
		else	
			entrada[i].classificacao = 0;
	}
	
	fclose(arq);
}

int main() {
	double peso_logistica[NUM_ATRIBUTOS]; // Vetor de pesos da Regressão
	t_Entrada entrada[NUM_ENTRADAS]; // Instacia da entrada
	
	srand(time(NULL)); // Semente para rand
	
	leEntrada(entrada); // Faz leitura da entrada
	
	inicializaPesos(peso_logistica); // Inicializa pesos com valores aleatorios de -1 a 1
	
	for(int i=0; i<=10000; i++)
		treinaLogistica(entrada, peso_logistica, 0.01); // Treina a Regressão

	// Testa Regressão
	int acertou = 0;
	int i=0;
	for(int j=0; j<75; j++, i++) 
		if(classificaLogistica(peso_logistica, entrada[j]) == entrada[j].classificacao)
			acertou++;
		
	printf("%d - %d\n",i , acertou);
	
	return 0;
}