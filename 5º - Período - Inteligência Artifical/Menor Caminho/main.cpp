/*------------------------------------------------
|    •	Felipe de Souza Dias – 81841			 |
|    •	Marcelo de Matos Menezes – 75254		 |
|    •	Hevellin Ferreira Aguiar Ferraz – 81826  |
|    •	Renê Victor Milagres - 79789 			 |
------------------------------------------------*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
#include <algorithm>
#include <ctime>

#define INF 1000000
#define DIM 258

using namespace std;

// Estrutura para representar pontos no mapa
struct Ponto {
    int linha, coluna, paiLinha, paiColuna;
    int distancia;         // Distância até o ponto inicial
	int heuristica;	  // Valor da heuristica
    int expandido;     // Contole se o ponto foi expandido ou não;
    char bloco;       // Tipo de terreno

    bool operator<(const Ponto &a) const {     // Sobrecarga do operador de comparação "<" para que a fila de prioridade ordene de forma crescente
        return this->distancia+this->heuristica > a.distancia + a.heuristica;
    }
};


//---------------------------------- CABEÇALHO DAS FUNÇÕES --------------------------------------//

char* leMapa(Ponto mapa[DIM][DIM]);                                    // Função para leitura do mapa
void escreveMapa(Ponto mapa[DIM][DIM], char* nome_mapa, int fator, int distancia);    // Função para impressão do mapa
void geraCaminho(Ponto mapa[DIM][DIM], int x, int y);                  // Função para escrever o caminho mínimo no mapa
bool podeMover(Ponto mapa[DIM][DIM], Ponto aux, int i, int j);         // Retorna se o movimento é possível
int distanciaMovimento(int i, int j);                                  // Retorna a distância de um movimento
void dijkstra(Ponto mapa[DIM][DIM], int x1, int y1, int x2, int y2, int w);   // Função Dijkstra
void copiaMapa(Ponto mapa[DIM][DIM], Ponto mapa2[DIM][DIM]);		   // Copia o mapa2 em mapa


//------------------------------------ FUNÇÃO PRINCIPAL -----------------------------------------//

Ponto mapa[DIM][DIM];         // Matriz de pontos que representa o mapa
Ponto mapa_resolvido[DIM][DIM];         // Matriz de pontos que representa o mapa

int nosExpandidos;
double tempo;


int main() {
	clock_t tick;
    int x1, y1, x2, y2;           // Coordenadas dos pontos inicial e final
    char nome_mapa[50];           // Nome do mapa
	nome_mapa[0] = '\0';

	strcat(nome_mapa, leMapa(mapa)); //Le o mapa e recebe o nome do mapa

	printf("Digite as coordenadas dos pontos inicial e final: ");

	do {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		if(x1 < 1 || x1 > 256 || y1 < 1 || y1 > 256 || x2 < 1 || x2 > 256 || y2 < 1 || y2 > 256 || mapa[x1][y1].bloco == '@' || mapa[x2][y2].bloco == '@')
			printf("Coordenadas invalidas. Digite novamente: ");

	} while(mapa[x1][y1].bloco == '@' || mapa[x2][y2].bloco == '@');


//Dijkstra
	copiaMapa(mapa_resolvido, mapa);
	tick = clock(); //Inicia contagem de clocks
	dijkstra(mapa_resolvido, x1, y1, x2, y2, 0);
	tempo = (clock()-tick)*1000 / (double)CLOCKS_PER_SEC; //Termina contagem e transforma em milisegundos
	geraCaminho(mapa_resolvido, x2, y2);
	escreveMapa(mapa_resolvido, nome_mapa, 0, mapa_resolvido[x2][y2].distancia);
	printf("=====\nSolucao Dijkstra gerada com sucesso.\n\n");
	printf("   Distancia: %.1f\n   Nos Expandidos: %i\n   Tempo gasto(Milisegundos): %.2f\n=====\n\n", ((double)mapa_resolvido[x2][y2].distancia)/10, nosExpandidos, tempo);

//A*
	copiaMapa(mapa_resolvido, mapa);
	tick = clock();
	dijkstra(mapa_resolvido, x1, y1, x2, y2, 1);
	tempo = (clock()-tick)*1000 / (double)CLOCKS_PER_SEC;
	geraCaminho(mapa_resolvido, x2, y2);
	escreveMapa(mapa_resolvido, nome_mapa, 1, mapa_resolvido[x2][y2].distancia);
	printf("=====\nSolucao A* gerada com sucesso.\n\n");
	printf("   Distancia: %.1f\n   Nos Expandidos: %i\n   Tempo gasto(Milisegundos): %.2f\n=====\n\n", ((double)mapa_resolvido[x2][y2].distancia)/10, nosExpandidos, tempo);


//WA* - 2 - 3 - 4 - 5 - 10
	copiaMapa(mapa_resolvido, mapa);
	tick = clock();
	dijkstra(mapa_resolvido, x1, y1, x2, y2, 2);
	tempo = (clock()-tick)*1000 / (double)CLOCKS_PER_SEC;
	geraCaminho(mapa_resolvido, x2, y2);
	escreveMapa(mapa_resolvido, nome_mapa, 2, mapa_resolvido[x2][y2].distancia);
	printf("=====\nSolucao WA*-2 gerada com sucesso.\n\n");
	printf("   Distancia: %.1f\n   Nos Expandidos: %i\n   Tempo gasto(Milisegundos): %.2f\n=====\n\n", ((double)mapa_resolvido[x2][y2].distancia)/10, nosExpandidos, tempo);

	copiaMapa(mapa_resolvido, mapa);
	tick = clock();
	dijkstra(mapa_resolvido, x1, y1, x2, y2, 3);
	tempo = (clock()-tick)*1000 / (double)CLOCKS_PER_SEC;
	geraCaminho(mapa_resolvido, x2, y2);
	escreveMapa(mapa_resolvido, nome_mapa, 3, mapa_resolvido[x2][y2].distancia);
	printf("=====\nSolucao WA*-3 gerada com sucesso.\n\n");
	printf("   Distancia: %.1f\n   Nos Expandidos: %i\n   Tempo gasto(Milisegundos): %.2f\n=====\n\n", ((double)mapa_resolvido[x2][y2].distancia)/10, nosExpandidos, tempo);

	copiaMapa(mapa_resolvido, mapa);
	tick = clock();
	dijkstra(mapa_resolvido, x1, y1, x2, y2, 4);
	tempo = (clock()-tick)*1000 / (double)CLOCKS_PER_SEC;
	geraCaminho(mapa_resolvido, x2, y2);
	escreveMapa(mapa_resolvido, nome_mapa, 4, mapa_resolvido[x2][y2].distancia);
	printf("=====\nSolucao WA*-4 gerada com sucesso.\n\n");
	printf("   Distancia: %.1f\n   Nos Expandidos: %i\n   Tempo gasto(Milisegundos): %.2f\n=====\n\n", ((double)mapa_resolvido[x2][y2].distancia)/10, nosExpandidos, tempo);

	copiaMapa(mapa_resolvido, mapa);
	tick = clock();
	dijkstra(mapa_resolvido, x1, y1, x2, y2, 5);
	tempo = (clock()-tick)*1000 / (double)CLOCKS_PER_SEC;
	geraCaminho(mapa_resolvido, x2, y2);
	escreveMapa(mapa_resolvido, nome_mapa, 5, mapa_resolvido[x2][y2].distancia);
	printf("=====\nSolucao WA*-5 gerada com sucesso.\n\n");
	printf("   Distancia: %.1f\n   Nos Expandidos: %i\n   Tempo gasto(Milisegundos): %.2f\n=====\n\n", ((double)mapa_resolvido[x2][y2].distancia)/10, nosExpandidos, tempo);

	copiaMapa(mapa_resolvido, mapa);
	tick = clock();
	dijkstra(mapa_resolvido, x1, y1, x2, y2, 10);
	tempo = (clock()-tick)*1000 / (double)CLOCKS_PER_SEC;
	geraCaminho(mapa_resolvido, x2, y2);
	escreveMapa(mapa_resolvido, nome_mapa, 10, mapa_resolvido[x2][y2].distancia);
	printf("=====\n Solucao WA*-10 gerada com sucesso.\n\n");
	printf("   Distancia: %.1f\n   Nos Expandidos: %i\n   Tempo gasto(Milisegundos): %.2f\n=====\n\n", ((double)mapa_resolvido[x2][y2].distancia)/10, nosExpandidos, tempo);
//

    return 0;
}

//-------------------------------- IMPLEMENTAÇÃO DAS FUNÇÕES ------------------------------------//

void copiaMapa(Ponto mapa[DIM][DIM], Ponto mapa2[DIM][DIM]) {
	for(int i=0; i<DIM; i++)
		for(int j=0; j<DIM; j++)
			mapa[i][j] = mapa2[i][j];
}

char* leMapa(Ponto mapa[DIM][DIM]) {
    // Laço para cercar as bordas do mapa a fim de evitar o acesso inválido das posições
    for(int i=0; i<DIM; i++) {
        mapa[i][0].bloco = mapa[0][i].bloco = '@';
        mapa[i][DIM-1].bloco = mapa[DIM-1][i].bloco = '@';
        mapa[i][0].distancia = mapa[0][i].distancia = INF;
        mapa[i][DIM-1].distancia = mapa[DIM-1][i].distancia = INF;
    }

    char nome[50];
    FILE* arq_mapa;

    printf("Digite o nome do mapa que deseja abrir (nome.map): ");
    do {
        scanf("%s", &nome);

        arq_mapa = fopen(nome, "r");

        if(arq_mapa==NULL)
            printf("Nome inválido. Digite novamente: ");

    } while(arq_mapa==NULL);

    // Laço para transferir os dados do arquivo para a matriz e inicializar os valores padrões
    for(int i=1; i<DIM-1; i++)
        for(int j=1; j<DIM-1; j++) {
            fscanf(arq_mapa, " %c", &mapa[i][j].bloco);
            mapa[i][j].distancia = INF;
            mapa[i][j].expandido = false;
			mapa[i][j].heuristica = 0;
            mapa[i][j].linha = i;
            mapa[i][j].coluna = j;
        }

    fclose(arq_mapa);

	return nome;
}

// Salva o mapa num arquivo .txt
void escreveMapa(Ponto mapa[DIM][DIM], char* nome_mapa, int fator, int distancia) {
    FILE* arq_mapa;

	char nome[50];
	nome[0] = '\0';

    strcat(nome, nome_mapa);
	nome[strlen(nome_mapa)-4] = '\0'; //Retira a extenção do nome

	// Insere ao final do nome do arquivo o tipo de algoritimo utiizado
	if(fator == 0)
		strcat(nome, "-DI.txt");
	if(fator == 1)
		strcat(nome, "-ST.txt");
	if(fator == 2)
		strcat(nome, "-WA2.txt");
	if(fator == 3)
		strcat(nome, "-WA3.txt");
	if(fator == 4)
		strcat(nome, "-WA4.txt");
	if(fator == 5)
		strcat(nome, "-WA5.txt");
	if(fator == 10)
		strcat(nome, "-WA10.txt");

    arq_mapa = fopen(nome, "w");

	fprintf(arq_mapa, "Distancia: %.1f\nNós Expandidos: %i\nTempo gasto(Milisegundos): %.2f\n", ((double)distancia)/10, nosExpandidos, tempo);

    for(int i=1; i<DIM-1; i++) {
        for(int j=1; j<DIM-1; j++)
            fprintf(arq_mapa, "%c", mapa[i][j].bloco);
        fprintf(arq_mapa, "\n");
    }
}

// Função recebe as coordenadas do ponto final e gera o caminho mínimo de acordo com o nó pai
void geraCaminho(Ponto mapa[DIM][DIM], int x, int y) {
    int aux;

    while(x!=-1 && y!=-1) {
        mapa[x][y].bloco = 'X';
        aux = x;
        x = mapa[x][y].paiLinha;
        y = mapa[aux][y].paiColuna;
    }
}

// Função que recebe o ponto atual (Ponto aux) e o movimento  (int i, int j) e retorna se é possível ou não mover
bool podeMover(Ponto mapa[DIM][DIM], Ponto aux, int i, int j) {
    if(mapa[aux.linha+i][aux.coluna+j].bloco == '@')    // Se for parede
        return false;

    if(i==0 && j==0)    // Se for a posição atual
        return false;

    if(i==-1 && j!=0 && mapa[aux.linha+i][aux.coluna].bloco == '@')    // Se diagonal para cima e tem parede em cima
        return false;
    if(i==1 && j!=0 && mapa[aux.linha+i][aux.coluna].bloco == '@')     // Se diagonal para baixo e tem parede em baixo
        return false;
    if(i!=0 && j==-1 && mapa[aux.linha][aux.coluna+j].bloco == '@')    // Se diagonal para esquerda e tem parede à esquerda
        return false;
    if(i!=0 && j==1 && mapa[aux.linha][aux.coluna+j].bloco == '@')    // Se diagonal para direita e tem parede à direita
        return false;

    return true;
}

// Função que recebe o movimento (int i, int j). Caso a soma seja -2, 0 ou 2 a posição destino está na diagonal, portanto sua distância é maior
int distanciaMovimento(int i, int j) {
    if(i+j==-2 || i+j==0 || i+j==2)
        return 15;

    return 10;
}

void dijkstra(Ponto mapa[DIM][DIM], int x1, int y1, int x2, int y2, int w) {
	nosExpandidos = 0; //Zera o numero de nós expandidos
    // Inicialização dos valores do ponto inicial
    mapa[x1][y1].distancia = 0;
    mapa[x1][y1].paiColuna = -1;
    mapa[x1][y1].paiLinha = -1;

    Ponto aux, proximo;
    priority_queue<Ponto> aberto;     // Fila de prioridade que representa a estrutura ABERTO

    aberto.push(mapa[x1][y1]);    // Insere o ponto inicial em ABERTO

    while(!aberto.empty()) {
		while(mapa[aberto.top().linha][aberto.top().coluna].expandido) //Se ponto já foi expandido, não precisa expandi-lo novamente (Fila de prioridade garante que "melhor opção (parcial)" seja aberta primeiro) 
			aberto.pop();
		
        aux = aberto.top();
		aberto.pop();
		
		//Atualiza os dados do no que está sendo aberto
		mapa[aux.linha][aux.coluna].paiLinha = aux.paiLinha;
		mapa[aux.linha][aux.coluna].paiColuna = aux.paiColuna;
		mapa[aux.linha][aux.coluna].distancia = aux.distancia;

        if(aux.linha == x2 && aux.coluna == y2)   // Destino encontrado
            return;

        // Laço para testar todos os movimentos possíveis
        for(int i=-1; i<=1; i++) {
            for(int j=-1; j<=1; j++) {
                if(podeMover(mapa, aux, i, j)) { //Verifica se pode realizar o movimento (i,j)
					proximo = mapa[aux.linha+i][aux.coluna+j]; //Proximo recebe o ponto de destino
					if(!mapa[proximo.linha][proximo.coluna].expandido) { //Se proximo já foi expandido, não faz nada
						proximo.distancia = aux.distancia+distanciaMovimento(i ,j);	//Proximo recebe a distancia dele até o inicio
						
						int x = abs(proximo.linha-x2);
						int y = abs(proximo.coluna-y2);
						proximo.heuristica = (max(x, y)*10 + min(x, y)*5) * w; //Calcula Heuristica, w = 0 -> Dijkstra, w = 1 -> A*, w > 1 -> WA*
						
						//Proximo recebe seu pai
						proximo.paiLinha = aux.linha;  
						proximo.paiColuna = aux.coluna;
                        aberto.push(proximo); //Insere proximo na fila
					}
				}
			}
		}

		nosExpandidos++;
		mapa[aux.linha][aux.coluna].bloco = ' ';    // Marca os nós expandidos no mapa
		mapa[aux.linha][aux.coluna].expandido = true;    // Marca ponto como expandido
    }
}

