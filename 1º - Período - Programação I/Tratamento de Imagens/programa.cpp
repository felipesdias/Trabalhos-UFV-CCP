// INF110 - Trabalho pratico 3
//
// programa para ler, modificar e gravar uma imagem no formato PNM
//
//
//
// Autores/Matricula: Felipe de Souza Dias              - 81841
//                    Hevellin Ferreira Aguiar e Ferraz - 81826
//

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#define MAXALTURA 500
#define MAXLARGURA 500
#define MAXFILTRO 100

using namespace std;

// Funções imagens em tons de cinza
void escurecer(unsigned char imagem[][MAXLARGURA], int altura, int largura);
void clarear(unsigned char imagem[][MAXLARGURA], int altura, int largura);
void negativo(unsigned char imagem[][MAXLARGURA], int altura, int largura);
void espelhar(unsigned char imagem[][MAXLARGURA], int altura, int largura);
void colorir(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura, unsigned char imagem[][MAXLARGURA], char tipo[]);
void aplicaFiltro(unsigned char imagem[][MAXLARGURA], int altura, int largura, int filtro[][MAXFILTRO], int x, int y, int coeficiente);
// Funções imagens coloridas
void escurecer(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura);
void clarear(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura);
void negativo(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura);
void espelhar(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura);
void tonsCinza(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura, unsigned char imagem[][MAXLARGURA], char tipo[]);
void aplicaFiltro(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura, int filtro[][MAXFILTRO], int x, int y, int coeficiente);
//Funções de Filtros
int Sobel(int filtro[][MAXFILTRO], int &x, int &y);
int Laplace(int filtro[][MAXFILTRO], int &x, int &y);
int Sharpen(int filtro[][MAXFILTRO], int &x, int &y);
int MotionBlur(int filtro[][MAXFILTRO], int &x, int &y);
int RealcarImagem(int filtro[][MAXFILTRO], int &x, int &y);
int Desfocagem(int filtro[][MAXFILTRO], int &x, int &y);
int SemNome(int filtro[][MAXFILTRO], int &x, int &y);
int Emboss(int filtro[][MAXFILTRO], int &x, int &y);
int EdgeDetect(int filtro[][MAXFILTRO], int &x, int &y);
int Random(int filtro[][MAXFILTRO], int &x, int &y);
//Funções auxiliares
void geraArquivo(char nomeArquivo2[], char tipo[], int altura, int largura, unsigned char imagem[][MAXLARGURA], unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA]);


int i, j,valor, auxEspelho, fator, numeroFiltro=1; //auxiliares globais
string filtrosAplicados; //Variavel dos filtros que já foram aplicados

int main()
{
    unsigned char imagem[MAXALTURA][MAXLARGURA], auxImagem[MAXALTURA][MAXLARGURA];    //a imagem propriamente dita
    unsigned char R[MAXALTURA][MAXLARGURA];         //Parte vermelha da imagem colorida
    unsigned char G[MAXALTURA][MAXLARGURA];         //Parte verde da imagem colorida
    unsigned char B[MAXALTURA][MAXLARGURA];         //Parte azul da imagem colorida
    int filtro[MAXFILTRO][MAXFILTRO], x, y;
    int largura, altura;                            //dimensoes da imagem
    char tipo[4];                                   //tipo da imagem
    ifstream arqentrada;                            //arquivo que contem a imagem original
    char comentario[200], c;                        //auxiliares

//*** LEITURA DA IMAGEM ***//
//inicialmente nao sera necessario entender nem mudar nada nesta parte

    //*** Abertura do arquivo ***//
	char nomeArquivo[100];
	char nomeArquivo2[100];
	cout << "Qual o nome do arquivo que deseja abrir: ";
	cin >> nomeArquivo; //Recebe o nome do arquivo
	cout << "Qual o nome que deseja salvar a nova imagem: ";
	cin >> nomeArquivo2; //Recebe o nome do arquivo
    arqentrada.open(nomeArquivo,ios::in); //Abre arquivo para leitura
    //***************************//


    //*** Leitura do cabecalho ***//
    arqentrada >> tipo;  //Le o tipo de arquivo
    arqentrada.get();    //Le e descarta o \n do final da 1a. linha

    if (strcmp(tipo,"P3")==0) {
      cout << "Imagem colorida\n";
    }
    else if (strcmp(tipo,"P2")==0) {
      cout << "Imagem em tons de cinza\n";
    }
    else if (strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
      cout << "Imagem no formato RAW\n";
      cout << "Desculpe, mas nao trabalho com esse tipo de imagem.\n";
      arqentrada.close();
      return 0;
    }


    while((c = arqentrada.get()) == '#')   //Enquanto for comentario
       arqentrada.getline(comentario,200); //Le e descarta a linha "inteira"

    arqentrada.putback(c);  //Devolve o caractere lido para a entrada, pois como
                            //nao era comentario, era o primeiro digito da largura

    arqentrada >> largura >> altura;  //Le o numero de pixels da horizontal e vertical
    cout << "Tamanho: " << largura << " x " << altura << endl;

    arqentrada >> valor;    //Valor maximo do pixel (temos que ler, mas nao sera usado)
    //****************************//


    //*** Leitura dos pixels da imagem ***//
	if (strcmp(tipo,"P2")==0) { // Leitura Tons de Cinza
		for(i=0;i<altura;i++)
		 for(j=0;j<largura;j++) {
			arqentrada >> valor;
			imagem[i][j] = (unsigned char)valor;
		 }
	} else { // Leitura imagens coloridas
		for(i=0;i<altura;i++)
		 for(j=0;j<largura;j++) {
			arqentrada >> valor;
			R[i][j] = (unsigned char)valor;
			arqentrada >> valor;
			G[i][j] = (unsigned char)valor;
			arqentrada >> valor;
			B[i][j] = (unsigned char)valor;
		 }
	}
    //************************************//

    arqentrada.close();

//*** FIM DA LEITURA DA IMAGEM ***//




//*** MENU PROGRAMA ***//

    int resposta, opcao;

	do {
		opcao = 0;
		system("cls");
		cout << "=============================" << endl;
		cout << "===== Opcoes aplicadas ======" << endl;
		cout << "=============================" << endl;
		cout << filtrosAplicados << endl << endl;
		cout << "=============================" << endl;
		cout << "=== Operacoes disponiveis ===" << endl;
		cout << "=============================" << endl << endl;
		cout << fixed << setw(2) << ++opcao << " - Escurecer a Imagem    ";					//1
		cout << fixed << setw(2) << ++opcao << " - Clarear a Imagem      " << endl;			//2
		cout << fixed << setw(2) << ++opcao << " - Efeito Negativo       ";					//3
		cout << fixed << setw(2) << ++opcao << " - Espelhar a Imagem     " << endl;			//4

		if (strcmp(tipo,"P2")==0)
        cout << fixed << setw(2) << ++opcao << " - Colorir Imagem        ";					//5
        else
		cout << fixed << setw(2) << ++opcao << " - Efeito Tons de Cinza  ";	                //5

		cout << fixed << setw(2) << ++opcao << " - Sobel                 " << endl; 		//6
        cout << fixed << setw(2) << ++opcao << " - Sharpen               ";					//7
        cout << fixed << setw(2) << ++opcao << " - MotionBlur            " << endl; 		//8
        cout << fixed << setw(2) << ++opcao << " - Ralcar Imagem         ";					//9
        cout << fixed << setw(2) << ++opcao << " - Desfocagem Gaussiana  " << endl;			//10
        cout << fixed << setw(2) << ++opcao << " - Sem Nome              ";					//11
        cout << fixed << setw(2) << ++opcao << " - Emboss                " << endl;			//12
        cout << fixed << setw(2) << ++opcao << " - Edge-Detect           ";					//13
        cout << fixed << setw(2) << ++opcao << " - Laplace               " << endl;         //14
        cout << fixed << setw(2) << ++opcao << " - Random                ";			        //15
        cout << fixed << setw(2) << ++opcao << " - Random                " << endl;			//16
		cout << fixed << setw(2) << ++opcao << " - Salvar Imagem         ";					//17
		cout << fixed << setw(2) << ++opcao << " - Fechar Programa       " << endl << endl; //18

		cout << "Qual operacao deseja realizar ? : ";
		cin >> resposta; // recebe qual filtro deve ser aplicado

		while (!(resposta >= 0 && resposta <= opcao)) { // enquanto o usuario digitar um valor invalido, ele exige outra resposta
			cout << "Valor invalido, digite novamente: ";
			cin >> resposta;
		}

		if(resposta == opcao) { // Caso o usuario feche o programa, ele pergunta se deseja salvar a imagem
			cout << "\nA Tem certeza que deseja fechar o programa? (S/N): ";
			char resposta2;
			cin >> resposta2;
			cout << endl;
			if(resposta2 == 'S' || resposta2 == 's')
				return 0;
		}

		if (strcmp(tipo,"P2")==0) { //Menu Imagens em tons de cinza
			switch(resposta) {
				case 1: escurecer(imagem, altura, largura);break;
				case 2: clarear(imagem, altura, largura);break;
				case 3: negativo(imagem, altura, largura);break;
				case 4: espelhar(imagem, altura, largura);break;
				case 5: colorir(R, G, B, altura, largura, imagem, tipo);break;
				case 6: aplicaFiltro(imagem, altura, largura, filtro, x, y, Sobel(filtro, x, y));break; //Sobel
				case 7: aplicaFiltro(imagem, altura, largura, filtro, x, y, Sharpen(filtro, x, y));break; //Sharpen
				case 8: aplicaFiltro(imagem, altura, largura, filtro, x, y, MotionBlur(filtro, x, y));break;//Motion Blur
				case 9: aplicaFiltro(imagem, altura, largura, filtro, x, y, RealcarImagem(filtro, x, y));break; // Realçar Imagem
				case 10: aplicaFiltro(imagem, altura, largura, filtro, x, y, Desfocagem(filtro, x, y));break; // Desfocagem Gaussiana
				case 11: aplicaFiltro(imagem, altura, largura, filtro, x, y, SemNome(filtro, x, y));break; //Sem Nome
				case 12: aplicaFiltro(imagem, altura, largura, filtro, x, y, Emboss(filtro, x, y));break; //Emboss
				case 13: aplicaFiltro(imagem, altura, largura, filtro, x, y, EdgeDetect(filtro, x, y));break; //EdgeDetect
				case 14: aplicaFiltro(imagem, altura, largura, filtro, x, y, Laplace(filtro, x, y));break; //Laplace
				case 15: aplicaFiltro(imagem, altura, largura, filtro, x, y, Random(filtro, x, y));break; // Random
				case 16: aplicaFiltro(imagem, altura, largura, filtro, x, y, Random(filtro, x, y));break; // Random
				case 17: geraArquivo(nomeArquivo2, tipo, altura, largura, imagem, R, G, B); // Gera Arquivo
			}
		} else {
			switch(resposta) { //Escurece
				case 1: escurecer(R, G, B, altura, largura);break;
				case 2: clarear(R, G, B, altura, largura);break;
				case 3: negativo(R, G, B, altura, largura);break;
				case 4: espelhar(R, G, B, altura, largura);break;
				case 5: tonsCinza(R, G, B, altura, largura, imagem, tipo);break;
				case 6: aplicaFiltro(R, G, B, altura, largura, filtro, x, y, Sobel(filtro, x, y));break; //Sobel
				case 7: aplicaFiltro(R, G, B, altura, largura, filtro, x, y, Sharpen(filtro, x, y));break; //Sharpen
				case 8: aplicaFiltro(R, G, B, altura, largura, filtro, x, y, MotionBlur(filtro, x, y));break; //Motion Blur
				case 9: aplicaFiltro(R, G, B, altura, largura, filtro, x, y, RealcarImagem(filtro, x, y));break; // Realçar Imagem
				case 10: aplicaFiltro(R, G, B, altura, largura, filtro, x, y, Desfocagem(filtro, x, y));break; // Desfocagem Gaussiana
				case 11: aplicaFiltro(R, G, B, altura, largura, filtro, x, y, SemNome(filtro, x, y));break; //Sem Nome
				case 12: aplicaFiltro(R, G, B, altura, largura, filtro, x, y, Emboss(filtro, x, y));break; //Emboss
				case 13: aplicaFiltro(R, G, B, altura, largura, filtro, x, y, EdgeDetect(filtro, x, y));break; //EdgeDetect
				case 14: aplicaFiltro(R, G, B, altura, largura, filtro, x, y, Laplace(filtro, x, y));break; //Laplace
				case 15: aplicaFiltro(R, G, B, altura, largura, filtro, x, y, Random(filtro, x, y));break; // Random
				case 16: aplicaFiltro(R, G, B, altura, largura, filtro, x, y, Random(filtro, x, y));break; // Random
				case 17: geraArquivo(nomeArquivo2, tipo, altura, largura, imagem, R, G, B); // Gera Arquivo
			}
		}
		numeroFiltro++; //Acrescenta o indice dos filtros já aplicados
	} while (true);
    //*************************//
    return 0;
}

//*** GRAVACAO DA IMAGEM ***//
//inicialmente nao sera necessario entender nem mudar nada nesta parte

    //*** Grava a nova imagem ***//
void geraArquivo(char nomeArquivo2[], char tipo[], int altura, int largura, unsigned char imagem[][MAXLARGURA], unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA]) {
        ofstream arqsaida;                              //arquivo que contera a imagem gerada
	arqsaida.open(nomeArquivo2,ios::out);  //Abre arquivo para escrita

    arqsaida << tipo << endl;                            //tipo
    arqsaida << "# Criada pelo TP3 - INF110 - Felipe Dias e Hevellin Ferraz\n";  //comentario
    arqsaida << largura << " " << altura << endl;        //dimensoes
    arqsaida << 255 << endl;                             //maior valor
	if (strcmp(tipo,"P2")==0) { //Salvar imagem em Tons de Cinza
		for(i=0;i<altura;i++)
		 for(j=0;j<largura;j++)
         arqsaida << (int)imagem[i][j] << endl;           //pixels
	} else { // Salvar imagem colorida
		for(i=0;i<altura;i++)
		 for(j=0;j<largura;j++) {
			arqsaida << (int)R[i][j] << endl;
			arqsaida << (int)G[i][j] << endl;
			arqsaida << (int)B[i][j] << endl;
		 }
	}
    arqsaida.close();     //fecha o arquivo
	std::stringstream numFiltro;
	numFiltro << numeroFiltro;
	filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Salvar Imagem";
}
    //***************************//

//*** FIM DA GRAVACAO DA IMAGEM ***//


// Funções para imagens em tons de cinza
void escurecer(unsigned char imagem[][MAXLARGURA], int altura, int largura) {
	cout << "Qual o fator de escurecimento (1-255) ? ";
	cin >> fator;

	//*** Escurece a imagem ***//
	for(i=0;i<altura;i++)
	  for(j=0;j<largura;j++) {
		valor = (int)imagem[i][j];   //pega o valor do pixel
		valor -= fator;              //escurece o pixel
		if (valor<0)                 //se der negativo, deixa preto
		  valor = 0;
		imagem[i][j] = (unsigned char)valor;   //modifica o pixel
	  }
	 std::stringstream intensidade; // Cria uma string que pode receber um INT
	 std::stringstream numFiltro; // Cria uma string que pode receber um INT
	 numFiltro << numeroFiltro; // String recebe qual o indice do filtro aplicado
	 intensidade << fator; // String recebe qual o fator de clareamento/escurecimento usado no filtro
	 filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Escurecer ("+intensidade.str()+")"; // String que informa os filtros que foram aplicados
}

//Mesmos comentarios acima
void clarear(unsigned char imagem[][MAXLARGURA], int altura, int largura) {
	cout << "Qual o fator de clareamento (1-255) ? ";
	cin >> fator;

	//*** Clarear a imagem ***//
	for(i=0;i<altura;i++)
	  for(j=0;j<largura;j++) {
		valor = (int)imagem[i][j];   //pega o valor do pixel
		valor += fator;              //clareia o pixel
		if (valor>255)                 //se der mais que 255, deixa branco
		  valor = 255;
		imagem[i][j] = (unsigned char)valor;   //modifica o pixel
	}
	 std::stringstream intensidade;
	 std::stringstream numFiltro;
	 numFiltro << numeroFiltro;
	 intensidade << fator;
	 filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Clarear ("+intensidade.str()+")";
}

void negativo(unsigned char imagem[][MAXLARGURA], int altura, int largura) {
	//*** Negativar a imagem ***//
	for(i=0;i<altura;i++)
	  for(j=0;j<largura;j++) {
		valor = (int)imagem[i][j];   //pega o valor do pixel
		valor = 255-valor;              //inverte o pixel
		imagem[i][j] = (unsigned char)valor;   //modifica o pixel
	  }
	 std::stringstream numFiltro; // Cria uma string que pode receber um INT
	 numFiltro << numeroFiltro; // String recebe qual o indice do filtro aplicado
	 filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Negativo"; // String que informa os filtros que foram aplicados
}

void espelhar(unsigned char imagem[][MAXLARGURA], int altura, int largura) {
	int resposta;
	// Opções para Horizontal e Vertical
	cout << "1 - Horizontal" << endl;
	cout << "2 - Vertical" << endl;
	cout << "Qual tipo de espelhamento deseja aplicar? : ";
	cin >> resposta;
	if(resposta == 1) {
		//*** Espelha horizontalmente ***//
		for(i=0;i<altura;i++)
		  for(j=0;j<largura/2;j++) {
			auxEspelho = (int)imagem[i][largura-j-1]; // Aux recebe o ultimo pixel
			imagem[i][largura-j-1] = imagem[i][j];    // Ultima posição recebe o primeiro pixal
			imagem[i][j] = (unsigned char)auxEspelho; // Primeiro pixel recebe ultimo pixel
		  }
		std::stringstream numFiltro;
		numFiltro << numeroFiltro;
		filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Espelho Horizontal";
	} else {
		//*** Espelha verticalmente ***//
		for(i=0;i<largura;i++)
		  for(j=0;j<altura/2;j++) {
			auxEspelho = (int)imagem[altura-j-1][i];
			imagem[altura-j-1][i] = imagem[j][i];
			imagem[j][i] = (unsigned char)auxEspelho;
		  }
		std::stringstream numFiltro;
		numFiltro << numeroFiltro;
		filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Espelho Vertical";
	}
}

// Não saiu como esperado, vou deixar apenas por curiosidade mesmo
void colorir(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura, unsigned char imagem[][MAXLARGURA], char tipo[]) {
    int a,b,c,auxValorR, auxValorG, auxValorB, excedenteR=1, excedenteG, excedenteB = 0, resposta;
    srand(time(NULL));
	string modelo;

	cout << "1 - Pixels Aleatorios" << endl;
	cout << "2 - Colorir por linhas" << endl;
	cout << "3 - Padrao de cor (Recomendado)" << endl;
	cout << "4 - Modelo por Intensidade" << endl;
	cout << "Como deseja colorir a imagem? : ";
	cin >> resposta;
	
    if(resposta == 3) {
		a = rand()%(18);
		b = rand()%(18-a);
		c = 18-a-b;
		modelo = " - Padrao de cor";
	}

	for(i=0;i<altura;i++) {
	  if(resposta == 2) {
		modelo = " - Por Linhas";
		a = rand()%(18);
		b = rand()%(18-a);
		c = 18-a-b;
	  }
	  for(j=0;j<largura;j++) {
		valor = (int)imagem[i][j]*3;
		if(resposta == 1) {
			modelo = " - Pixels Aleatorios";
			a = rand()%(18);
			b = rand()%(18-a);
			c = 18-a-b;
		}
		if(resposta == 4) {
			modelo = " - Por Intensidade";
			if(valor/3 <= 25) {
				a=18;b=0;c=0;
			} else if(valor/3 > 25 && valor/3 <= 50) {
				a=15;b=2;c=1;
			} else if(valor/3 > 50 && valor/3 <= 75) {
				a=10;b=3;c=5;
			} else if(valor/3 > 75 && valor/3 <= 100) {
				a=5;b=5;c=8;
			} else if(valor/3 > 100 && valor/3 <= 125) {
				a=0;b=18;c=0;
			} else if(valor/3 > 125 && valor/3 <= 150) {
				a=2;b=13;c=3;
			} else if(valor/3 > 150 && valor/3 <= 175) {
				a=3;b=8;c=7;
			} else if(valor/3 > 175 && valor/3 <= 200) {
				a=0;b=9;c=9;
			} else if(valor/3 > 200 && valor/3 <= 225) {
				a=2;b=2;c=14;
			} else if(valor/3 > 225 && valor/3 <= 255) {
				a=0;b=0;c=18;
			}
		}
		for(int pow=0; pow<2; pow++) {
			auxValorR = ((valor/18)*a)+(valor%18)+excedenteB;
			if(auxValorR > 255) {
				excedenteR = auxValorR-255;
				auxValorR = 255;
			} else {
				excedenteR = 0;
			}
			auxValorG = ((valor/18)*b)+excedenteR;
			if(auxValorG > 255) {
				excedenteG = auxValorG-255;
				auxValorG = 255;
			} else {
				excedenteG = 0;
				excedenteR = 0;
			}
			auxValorB = ((valor/18)*c)+excedenteG;
			if(auxValorB > 255) {
				excedenteB = auxValorB-255;
				auxValorB = 255;
			} else {
				excedenteB = 0;
				excedenteG = 0;
				excedenteR = 0;
			}
		}

		R[i][j] = (unsigned char)auxValorR;
		G[i][j] = (unsigned char)auxValorG;
		B[i][j] = (unsigned char)auxValorB;
	  }
	}
	  tipo[1] = '3';
	  std::stringstream numFiltro;
	  numFiltro << numeroFiltro;
	  filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Efeito Colorir"+modelo;
}

void aplicaFiltro(unsigned char imagem[][MAXLARGURA], int altura, int largura, int filtro[][MAXFILTRO], int x, int y, int coeficiente) {
	unsigned char imagemFiltro[MAXALTURA][MAXLARGURA]; // Matriz auxiliar
	for(i=0;i<altura;i++)
	  for(j=0;j<largura;j++) {
		imagemFiltro[i][j] = imagem[i][j]; // Copia a imagem para a Matriz Auxiliar
	}

	valor = 0;
	int auxX = x/2; // Recebe quantas posições de altura a matriz deve caminhar para cima e para baixo
	int auxY = y/2; // Recebe quantas posições de largura a matriz deve caminhar para direita e para esquerda

    // Percorre todos os pixels da imagem
	for(i=0;i<altura;i++) {
      for(j=0;j<largura;j++) {
        // Percorre todas os valores do filtro
         for(int k=0;k<x;k++) {
            for(int l=0;l<y;l++) {
               if( !(i-auxX < 0 || i-auxX > altura-1 || j-auxY < 0 || j-auxY > largura-1) ) // Não aplicar a operação em posições fora da matriz da imagem
                  valor += (int)imagemFiltro[i-auxX][j-auxY]*filtro[k][l]; //Aplica o filtro no pixel da imagem
               auxY--; // Caminha com a largura na imagem
            }
            auxY = y/2; // Reinicia a largura, porque trocou de linha
            auxX--; // Caminha com a linha na imagem
         }
         auxX = x/2; //Reinicia a linha, porque trocou de pixel
         valor = (valor)*(1.0/coeficiente); //Aplica coeficiente no filtro, como no caso do MotionBlur

         if (valor < 0)
            valor = 0;
         else if(valor > 255)
            valor = 255;

         imagem[i][j] = (unsigned char)valor; //Aplica o novo valor do pixel na matriz
         valor = 0;
      }
   }
}

/////////////////////////////////////////////////////////////////////
///////////// Funções para imagens Coloridas ////////////////////////
/////////////////////////////////////////////////////////////////////

void escurecer(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura) {
	cout << "Qual o fator de escurecimento (1-255) ? ";
	cin >> fator;

	//*** Escurece a imagem ***//
	for(i=0;i<altura;i++)
	  for(j=0;j<largura*3;j+=3) {
		// RED
		valor = (int)R[i][j];   //pega o valor RED do pixel
		valor -= fator;              //escurece o RED do pixel
		if (valor<0)                 //se der negativo, deixa RED 0
		  valor = 0;
		R[i][j] = (unsigned char)valor;   //modifica o RED do pixel
		// GREEN
		valor = (int)G[i][j+1];   //pega o valor GREEN do pixel
		valor -= fator;              //escurece o GREEN do pixel
		if (valor<0)                 //se der negativo, deixa GREEN 0
		  valor = 0;
		G[i][j+1] = (unsigned char)valor;   //modifica o GREEN do pixel
		// BLUE
		valor = (int)B[i][j+2];   //pega o valor BLUE do pixel
		valor -= fator;              //escurece o BLUE do pixel
		if (valor<0)                 //se der negativo, deixa BLUE 0
		  valor = 0;
		B[i][j+2] = (unsigned char)valor;   //modifica o BLUE do pixel
	  }
	 std::stringstream intensidade;
	 std::stringstream numFiltro;
	 numFiltro << numeroFiltro;
	 intensidade << fator;
	 filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Escurecer ("+intensidade.str()+")";
}

void clarear(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura) {
	cout << "Qual o fator de clareamento (1-255) ? ";
	cin >> fator;

	//*** Clarear a imagem ***//
	for(i=0;i<altura;i++)
	  for(j=0;j<largura;j++) {
		// RED
		valor = (int)R[i][j];   //pega o valor RED do pixel
		valor += fator;              //aumenta o RED do pixel
		if (valor>255)                 //se der maior que 255, deixa RED em 255
		  valor = 255;
		R[i][j] = (unsigned char)valor;   //modifica o RED do pixel
		// GREEN
		valor = (int)G[i][j];   //pega o valor GREEN do pixel
		valor += fator;              //aumenta o GREEN do pixel
		if (valor>255)                 //se der maior que 255, deixa GREEN em 255
		  valor = 255;
		G[i][j] = (unsigned char)valor;   //modifica o GREEN do pixel
		// BLUE
		valor = (int)B[i][j];   //pega o valor BLUE do pixel
		valor += fator;              //aumenta o BLUE do pixel
		if (valor>255)                 //se der maior que 255, deixa BLUE em 255
		  valor = 255;
		B[i][j] = (unsigned char)valor;   //modifica o BLUE do pixel
	  }
	 std::stringstream intensidade;
 	 std::stringstream numFiltro;
  	 numFiltro << numeroFiltro;
	 intensidade << fator;
	 filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Clarear ("+intensidade.str()+")";
}

void negativo(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura){
	//*** Negativar a imagem ***//
	for(i=0;i<altura;i++)
	  for(j=0;j<largura;j++) {
		//RED
		valor = (int)R[i][j];   //pega o valor RED do pixel
		valor = 255-valor;              //inverte o RED do pixel
		R[i][j] = (unsigned char)valor;   //modifica o RED do pixel
		//GREEN
		valor = (int)G[i][j];   //pega o valor GREEN do pixel
		valor = 255-valor;              //inverte o GREEN do pixel
		G[i][j] = (unsigned char)valor;   //modifica o GREEN do pixel
		//BLUE
		valor = (int)B[i][j];   //pega o valor BLUE do pixel
		valor = 255-valor;              //inverte o BLUE do pixel
		B[i][j] = (unsigned char)valor;   //modifica o BLUE do pixel
	  }
	std::stringstream numFiltro;
	numFiltro << numeroFiltro;
	filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Negativo";
}

void espelhar(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura) {
	int resposta;
	cout << "1 - Horizontal" << endl;
	cout << "2 - Vertical" << endl;
	cout << "Qual tipo de espelhamento deseja aplicar? : ";
	cin >> resposta;
	if(resposta == 1) {
		//*** Espelha horizontalmente ***//
		for(i=0;i<altura;i++)
		  for(j=0;j<largura/2;j++) {
			//RED
			auxEspelho = (int)R[i][largura-j-1];
			R[i][largura-j-1] = R[i][j];
			R[i][j] = (unsigned char)auxEspelho;
			//GREEN
			auxEspelho = (int)G[i][largura-j-1];
			G[i][largura-j-1] = G[i][j];
			G[i][j] = (unsigned char)auxEspelho;
			//BLUE
			auxEspelho = (int)B[i][largura-j-1];
			B[i][largura-j-1] = B[i][j];
			B[i][j] = (unsigned char)auxEspelho;
		  }
		std::stringstream numFiltro;
		numFiltro << numeroFiltro;
		filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Espelho Horizontal";
	} else {
		//*** Espelha Verticalmente ***//
		for(i=0;i<largura;i++)
		  for(j=0;j<altura/2;j++) {
			//RED
			auxEspelho = (int)R[altura-j-1][i];
			R[altura-j-1][i] = R[j][i];
			R[j][i] = (unsigned char)auxEspelho;
			//GREEN
			auxEspelho = (int)G[altura-j-1][i];
			G[altura-j-1][i] = G[j][i];
			G[j][i] = (unsigned char)auxEspelho;
			//BLUE
			auxEspelho = (int)B[altura-j-1][i];
			B[altura-j-1][i] = B[j][i];
			B[j][i] = (unsigned char)auxEspelho;
		}
		std::stringstream numFiltro;
		numFiltro << numeroFiltro;
		filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Espelho Vertical";
	}
}

void tonsCinza(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura, unsigned char imagem[][MAXLARGURA], char tipo[]) {
	for(i=0;i<altura;i++)
	  for(j=0;j<largura;j++) {
		imagem[i][j] = (R[i][j]+G[i][j]+B[i][j])/3;
	  }
	  tipo[1] = '2';
	  std::stringstream numFiltro;
	  numFiltro << numeroFiltro;
	  filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Efeito Preto e Branco";
}

void aplicaFiltro(unsigned char R[][MAXLARGURA], unsigned char G[][MAXLARGURA], unsigned char B[][MAXLARGURA], int altura, int largura, int filtro[][MAXFILTRO], int x, int y, int coeficiente) {
	unsigned char filtroR[MAXALTURA][MAXLARGURA], filtroG[MAXALTURA][MAXLARGURA], filtroB[MAXALTURA][MAXLARGURA];
	int valorR, valorG, valorB;
	for(i=0;i<altura;i++)
	  for(j=0;j<largura;j++) {
		filtroR[i][j] = R[i][j];
		filtroG[i][j] = G[i][j];
		filtroB[i][j] = B[i][j];
	}

	valorR = 0;
	valorG = 0;
	valorB = 0;
	int auxX = x/2;
	int auxY = y/2;

	for(i=0;i<altura;i++)
	  for(j=0;j<largura;j++) {
		for(int k=0;k<x;k++) {
		  for(int l=0;l<y;l++) {
		    if( !(i-auxX < 0 || i-auxX > altura-1 || j-auxY < 0 || j-auxY > largura-1) ) {
				valorR += (int)filtroR[i-auxX][j-auxY]*filtro[k][l];
				valorG += (int)filtroG[i-auxX][j-auxY]*filtro[k][l];
				valorB += (int)filtroB[i-auxX][j-auxY]*filtro[k][l];
		    }
			auxY--;
		  }
		auxY = y/2;
		auxX--;
		}
	  auxX = x/2;
	  //RED
      valorR = (valorR)*(1.0/coeficiente);
	  if (valorR < 0)
		valorR = 0;
	  else if(valorR > 255)
		valorR = 255;
	  R[i][j] = (unsigned char)valorR;
	  valorR = 0;
	  //GREEN
	  valorG = (valorG)*(1.0/coeficiente);
	  if (valorG < 0)
		valorG = 0;
	  else if(valorG > 255)
		valorG = 255;
	  G[i][j] = (unsigned char)valorG;
	  valorG = 0;
	  //BLUE
	  valorB = (valorB)*(1.0/coeficiente);
	  if (valorB < 0)
		valorB = 0;
	  else if(valorB > 255)
		valorB = 255;
	  B[i][j] = (unsigned char)valorB;
	  valorB = 0;
	}
}

/////////////////////////////////////
/////////// Filtros /////////////////
/////////////////////////////////////

int Sobel(int filtro[][MAXFILTRO], int &x, int &y) {
    x = 3; // Altura do filtro
    y = 3; // Largura do filtro
    int cont = 0; // Contador
    int auxFiltro[MAXFILTRO*MAXFILTRO] = {1,2,1,0,0,0,-1,-2,-1}; // Valores do filtro
    for(i=0; i<x; i++)
        for(j=0; j<y; j++) {
            filtro[i][j] = auxFiltro[cont]; // Joga os valores do filtro, na matriz Filtro
            cont++;
        }
    std::stringstream numFiltro;
    numFiltro << numeroFiltro;
    filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Efeito Sobel";
    return 1; // Coeficiente do filtro
}

int Laplace(int filtro[][MAXFILTRO], int &x, int &y) {
    x = 3;
    y = 3;
    int cont = 0;
    int auxFiltro[MAXFILTRO*MAXFILTRO] = {0,-1,0,-1,4,-1,0,-1,0};
    for(i=0; i<x; i++)
        for(j=0; j<y; j++) {
            filtro[i][j] = auxFiltro[cont];
            cont++;
        }
    std::stringstream numFiltro;
    numFiltro << numeroFiltro;
    filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Efeito Laplace";
    return 1;
}

int RealcarImagem(int filtro[][MAXFILTRO], int &x, int &y) {
    x = 3;
    y = 3;
    int cont = 0;
    int auxFiltro[MAXFILTRO*MAXFILTRO] = {0,-1,0,-1,5,-1,0,-1,0};
    for(i=0; i<x; i++)
        for(j=0; j<y; j++) {
            filtro[i][j] = auxFiltro[cont];
            cont++;
        }
    std::stringstream numFiltro;
    numFiltro << numeroFiltro;
    filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Realcar Imagem";
    return 1;
}

int Desfocagem(int filtro[][MAXFILTRO], int &x, int &y) {
    x = 3;
    y = 3;
    int cont = 0;
    int auxFiltro[MAXFILTRO*MAXFILTRO] = {1,2,1,2,4,2,1,2,1};
    for(i=0; i<x; i++)
        for(j=0; j<y; j++) {
            filtro[i][j] = auxFiltro[cont];
            cont++;
        }
    std::stringstream numFiltro;
    numFiltro << numeroFiltro;
    filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Efeito Desfocagem Gaussiana";
    return 16;
}

int Sharpen(int filtro[][MAXFILTRO], int &x, int &y) {
    x = 3;
    y = 3;
    int cont = 0;
    int auxFiltro[MAXFILTRO*MAXFILTRO] = {-1,-1,-1,-1,9,-1,-1,-1,-1};
    for(i=0; i<x; i++)
        for(j=0; j<y; j++) {
            filtro[i][j] = auxFiltro[cont];
            cont++;
        }
    std::stringstream numFiltro;
    numFiltro << numeroFiltro;
    filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Efeito Sharpen";
    return 1;
}

int MotionBlur(int filtro[][MAXFILTRO], int &x, int &y) {
    x = 4;
    y = 4;
    int cont = 0;
    int auxFiltro[MAXFILTRO*MAXFILTRO] = {0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0};
    for(i=0; i<x; i++)
        for(j=0; j<y; j++) {
            filtro[i][j] = auxFiltro[cont];
            cont++;
        }
    std::stringstream numFiltro;
    numFiltro << numeroFiltro;
    filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Efeito Motion Blur";
    return 3;
}

int SemNome(int filtro[][MAXFILTRO], int &x, int &y) {
    x = 3;
    y = 3;
    int cont = 0;
    int auxFiltro[MAXFILTRO*MAXFILTRO] = {1,0,-1,2,0,-2,1,0,-1};
    for(i=0; i<x; i++)
        for(j=0; j<y; j++) {
            filtro[i][j] = auxFiltro[cont];
            cont++;
        }
    std::stringstream numFiltro;
    numFiltro << numeroFiltro;
    filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Efeito Sem Nome";
    return 1;
}

int EdgeDetect(int filtro[][MAXFILTRO], int &x, int &y) {
    x = 3;
    y = 3;
    int cont = 0;
    int auxFiltro[MAXFILTRO*MAXFILTRO] = {0,1,0,1,-4,1,0,1,0};
    for(i=0; i<x; i++)
        for(j=0; j<y; j++) {
            filtro[i][j] = auxFiltro[cont];
            cont++;
        }
    std::stringstream numFiltro;
    numFiltro << numeroFiltro;
    filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Edge-Detect";
    return 1;
}

int Emboss(int filtro[][MAXFILTRO], int &x, int &y) {
    x = 3;
    y = 3;
    int cont = 0;
    int auxFiltro[MAXFILTRO*MAXFILTRO] = {-2,-1,0,-1,1,1,0,1,2};
    for(i=0; i<x; i++)
        for(j=0; j<y; j++) {
            filtro[i][j] = auxFiltro[cont];
            cont++;
        }
    std::stringstream numFiltro;
    numFiltro << numeroFiltro;
    filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Efeito Emboss";
    return 1;
}

int Random(int filtro[][MAXFILTRO], int &x, int &y) {
	srand(time(NULL)); // Inicia o modo aleatorio
    x = 1+rand()%(20); // Sorteia uma altura X para o filtro
    y = 1+rand()%(20); // Sorteia uma largura Y para o filtro
    for(i=0; i<x; i++)
        for(j=0; j<y; j++)
            filtro[i][j] = -10+rand()%(21); // Sorteia numero aleatorio para cada posição do filtro

    std::stringstream numFiltro;
    numFiltro << numeroFiltro;
    filtrosAplicados = filtrosAplicados+"\n"+numFiltro.str()+") Efeito Randomico";
    return 1+rand()%(2); // Sorteia um coeficiente aleatorio do filtro
}
