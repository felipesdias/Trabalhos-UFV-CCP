////////////////////////////////////////////
///// Felipe de Souza Dias - 81841 /////////
///// Marcelo Matos de Menezes - 75254 /////
////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

#define INF 2000000000
#define TAM 28 //Numero de cidades

string mensagemDeDespedida[10] = {"Comece o trabalho assim que puder, pois a data de entrega nunca estara tao longe quanto agora!",
						   "Eh hora de dar tchau",
						   "Nao vai, ta cedo ainda",
						   "Mas jah ta saindo ??",
						   "Eu sei que vc ta rindo, pode parar",
						   "Ala, riu de novo!!!",
						   "Ta bom!!!, pode ir",
						   "Pera so um poquinho, rapidao",
						   "So queria falar uma coisa:",
						   "Comece o trabalho assim que puder, pois a data de entrega nunca estara tao longe quanto agora!  \n  Vlws Flws"};

int gAereo[TAM][TAM]; //Grafo contendo distancia aerea
int gRodovia[TAM][TAM]; //Grafo contendo distancia rodoviaria
string Cidades[28] = {"Aracaju","Belem","Belo Horizonte","Boa Vista","Brasilia","Campo Grande",
/* Nome das Cidades*/ "Cuiaba","Curitiba","Florianopolis","Fortaleza","Goiania","Joao Pessoa",
					  "Macapa","Maceio","Manaus","Natal","Palmas","Porto Alegre","Porto Velho",
					  "Recife","Rio Branco","R. Janeiro","Salvador","Sao Luis","Sao Paulo",
					  "Teresina","Vitoria","Vicosa"};

					  
void leGrafos(); //Função que faz a leitura dos 2 tipos de grafo
void menu(); //Função que exibe o menu de opções
void limpaTela(); //Função que limpa tela
int prim(int g[][TAM]); //Função de Prim (Arvore geradora minima)
void buscaProfundidade(int g[][TAM], bool visitado[], int v); //Função que realiza busca em profundidade
int contaComponentes(int L); //Função que conta o numero de componentes do grafo
int kahXimiro(int g[][TAM], int solucao[], int v); //Função resolve caminho hamiltoniano pela euristica da aresta mais proxima
int kahXimiro(int opcao); //Função que chama a função para resolver caminho hamiltoniano dependendo do tipo de grafo escolhido



int main()
{
    leGrafos();
	menu();
}

void menu()
{
	int aux; //Variaveis auxiliares
    int opcao; //Opção selecionada do menu
    do {
        limpaTela();
		
        cout << "===========================================\n";
        cout << " 1 - Arvore Geradora Minima   \n";
        cout << " 2 - Fibra Otica, limite entre as cidades  \n";
        cout << " 3 - Caminho Hamiltoniano - kahXimiro mode \n";
        cout << "-1 - Sair\n";
        cout << "===========================================\n\n";
        cout << "Escolha uma opcao: ";
		
        cin >> opcao;
		cout << endl;
		
        switch(opcao) {
            case 1:
				cout << endl << "Total: " << prim(gAereo) << endl; //Informa custo total
                system("pause");
                break;
				
            case 2:
				cout << "Informe o tamaho L (0 para sair): ";
				cin >> aux; //Le o tamanho de L
				
				while(aux) { //Repete enquanto L != -1
					
					aux = contaComponentes(aux);
					
					cout << "Numero de sub-redes: " << aux << endl << endl; //Informa numero de componentes
					
					cout << "Informe o tamaho L (0 para sair): ";
					cin >> aux; //Faz a leitura do novo L
				}
                system("pause");
                break;
				
			case 3:
				cout << "    1 - Modo Aereo\n";
				cout << "    2 - Modo Rodoviario\n";
				cout << "OUTRO - Sair\n\n";
				cout << "Escolha uma opcao: ";
				cin >> aux; //Le opção selecionada
				cout << endl;
				
				aux = kahXimiro(aux); //Chama função que seleciona se vai resolver com modo aereo ou rodoviario
				
				if(aux != -1)
					cout << endl << "Custo total: " << aux << endl; //Imprime custo total
				
				system("pause");
				break;
				
			case -1:
				aux = 0;
				while(aux <10) {
					limpaTela();
					cout << endl << endl << endl << endl << mensagemDeDespedida[aux] << endl << endl << endl << endl << endl << endl << endl;
					system("pause");
					aux++;
				}
				break;
				
            default:
                cout << "Opcao invalida\n";
                system("pause");
        }
    } while (opcao != -1);
}

void leGrafos()
{
    //Lê grafo Aereo
    for(int i=0; i<TAM; i++)
        for(int j=0; j<TAM; j++)
            cin >> gAereo[i][j];

    //Lê grafo rodovia
    for(int i=0; i<TAM; i++)
        for(int j=0; j<TAM; j++)
            cin >> gRodovia[i][j];
}

int contaComponentes(int L) 
{
	int aux[TAM][TAM]; //Grafo auxiliar, com a arestas maiores que L retiradas
	bool visitado[TAM];
	
	//Copia o grafo para aux retirando as arestas com peso maior que L
	for(int i=0; i<TAM; i++)
		for(int j=0; j<TAM; j++)
			if(gRodovia[i][j] <= L)
				aux[i][j] = gRodovia[i][j];
			else
				aux[i][j] = 0;
	
	
	//Marcando todas os vertices como não visitado
	for(int i=0; i<TAM; i++)
		visitado[i] = false; //Vetor de visitados
	
	int componentes = 0; //Numero de componentes
	
	for(int i=0; i<TAM; i++) { //Para cada vertice, faça:
		if(!visitado[i]) { //Se não foi visitado, então:
			buscaProfundidade(aux, visitado, i); //Chama BP para o vertice i
			componentes++; //Incrementa numero de componentes
		}
	}
	
	return componentes;
}

void buscaProfundidade(int g[][TAM], bool visitado[], int v)
{
	visitado[v] = true; //Marca vetor como visitado, para não repetir e entrar em loop infinito
	for(int i=0; i<TAM; i++)
		if(g[v][i]) //Para cada vertice adjacente a V
			if(!visitado[i]) //Se não tiver sido visitado, chama a busca para o vertice i
				buscaProfundidade(g, visitado, i);
}

void limpaTela()
{
    #ifdef LINUX || linux || Linux //Se for linux executa o comando clear
        system("clear");
    #elif defined WIN32 || win32 || Win32//Se não, e for windows executa cls
        system("cls");
    #else //Se não for nem e nem outro, é pq vc é rico e ta usando macBook
        #error Plataforma não suportada
    #endif
}

int prim(int g[][TAM])
{
	int pai[TAM];
    int distancia[TAM]; //Vetor de distancias
    bool visitado[TAM]; //Vetor de visitados
    int custo, v, menor; //Custo, e vertice auxiliar

    //Inicializando as variaveis
    for(int i=0; i<TAM; i++) {
        distancia[i] = INF;
        visitado[i] = false;
    }

    distancia[0] = 0;
	pai[0] = 0;


    for(int i=0; i<TAM-1; i++) { //O subGrafo vai ter: arestas = Numero de Vertices-1, ou seja, i<TAM-1
		menor = INF;
		
		for (int i=0; i<TAM; i++) //Para todas as posições do vetor de distancia
			if (!visitado[i] && distancia[i] < menor) { //Se já foi visitado e a distancia for menor que a menor, atualiza menor e guarda o vertice
				menor = distancia[i];
				v = i;
			}

		visitado[v] = true; //Marca vertice como visitado

		for(int j=0; j<TAM; j++) {
			if(g[v][j] && !visitado[j] && g[v][j] < distancia[j]) { //Se tem aresta de V->J e não foi visitado e sua distancia é menor que a atual, então faz:
				pai[j] = v; //Atualiza vetor de solução, já que encontrou uma aresta com menor custo
				distancia[j] = g[v][j]; //Atualiza o vetor de distancia, já que encontrou uma distancia menor
			}
		}
    }

	custo = 0;
	for(int i=0; i<TAM; i++) //Calcula o custo, somando o custo das arestas do subGrafo
        custo += g[pai[i]][i];
	
	//Informa de qual cidade vai para qual e seu custo
	for(int i=0; i<TAM; i++)
		if(g[pai[i]][i])
			cout << setw(14) << Cidades[pai[i]] << " -> " << setw(14) << Cidades[i] << ", custo: " << setw(4) << g[pai[i]][i] << endl;
	
    return custo; //Retorna custo
}

int kahXimiro(int opcao)
{
	int solucao[TAM]; //Vetor contendo a solução
	int aux[TAM][TAM]; //Grafo auxiliar com o grafo da opção escolhida
	int menor = INF;
	int custo = -1;
	int menorI;
	
	if(opcao == 1) { //Decide qual opção realizar
		for(int i=0; i<TAM; i++) //Copia Grafo aereo
			for(int j=0; j<TAM; j++)
				aux[i][j] = gAereo[i][j];
	} 
	else if(opcao == 2) {
		for(int i=0; i<TAM; i++) //Copia gravo rodoviario e substitui as rodovias inexistentes pelas distacias aereas
			for(int j=0; j<TAM; j++)
				if(gRodovia[i][j])
					aux[i][j] = gRodovia[i][j];
				else
					aux[i][j] = gAereo[i][j];
	} 
	else
		return -1;
	
	
	for(int i=0; i<TAM; i++) { //Chama função que calcula custo para todos os vertices
		custo = kahXimiro(aux, solucao, i); //Recebe custo do caminho hamiltoniano começando do vertice i
		if(custo < menor) {  //Guarda a melhor solução
			menor = custo;
			menorI = i;
		}
	}

	int v = menorI; //Vertice inicial da solução com menor custo
	
	custo = kahXimiro(aux, solucao, v); //Recebe custo da melhor solução
	
	for(int i=0; i<TAM-1; i++) {//Imprime o caminho com o custo de suas respectivas arestas
		cout << setw(14) << Cidades[v] << " -> " << setw(14) << Cidades[solucao[v]] << ", custo: " << setw(4) << aux[v][solucao[v]] << endl;
		v = solucao[v];
	}
	
	return custo; //Retorna custo
}

int kahXimiro(int g[][TAM], int solucao[], int v) 
{
    bool visitado[TAM]; //Vetor de visitados
	int menor;
	
    //Inicializando as variaveis
    for(int i=0; i<TAM; i++)
        visitado[i] = false;
	
	int v3, v2;
	v3 = v2 = v;
	
	visitado[v] = true; //Vertice V já visitado
	
	for(int i=0; i<TAM-1; i++) {
		menor = INF;
		for(int j=0; j<TAM; j++) //Procura vertice adjacente a V com menor custo e que ainda não foi visitado
			if(!visitado[j] && g[v3][j] && g[v3][j] < menor) {
				menor = g[v3][j];
				v2 = j;
			}
		
		solucao[v3] = v2; //Marca o destino do vertice V
		v3 = v2; //Atualiza V para o destino, para assim formar o cliclo
		visitado[v2] = true; //Marca o destino como visitado
	}
	
	int custo = 0;

	v2 = v;
	for(int i=0; i<TAM-1; i++) {//Imprime o ciclo com o custo de suas respectivas arestas
		custo += g[v2][solucao[v2]];
		v2 = solucao[v2];
	}

	return custo; //retorna custo
}