

/*-------------------------------------------------------------------

	Exemplo com uso das funcoes obrigatorias:
		iniciar
		executar
		eventoTeclado
		eventoMouse

	Programador: Vladimir Oliveira Di Iorio
	Data: 02/06/2005

-------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;


/*-------------------------------------------------------------------
	Primeiro passo: incluir "BaseParaJogo.h", para poder acessar
	as funcoes definidas.
-------------------------------------------------------------------*/
#include "BaseParaJogo.h"



/*-------------------------------------------------------------------
	Macros
-------------------------------------------------------------------*/
#define numFantasma 4
#define numHaduken 6
#define dimensao 40

#define blocoChao 7
#define blocoParede 0
#define blocoFruta 1
#define blocoTunelEntrada 4
#define blocoTunelSaida 5
#define blocoTunelMeio 3
#define blocoPonte 2
#define blocoTeP 6
#define blocoHadouken 8

/*-------------------------------------------------------------------
	Struct's
-------------------------------------------------------------------*/
struct personagem {
	int posX; //Posição horizontal do personagem
	int posY; //Posição vertical do personagem
	
	int direcaoNova; //Direção que ira movimentar quando possivel
	int direcaoAtual; //Direção que esta movimentando
	int inteligencia; //Nivel de inteligencia do personagem
	int inteligenciaInicial; //Nivel inicial de inteligencia das maratonas
	int hadukenInicial; //Quantidade de Haduken que começa
	int qtDehaduken; //Quantidade maxima de hadukens
	int velocidadeExtra; //Velocidade extra
	bool morto; //Verifica se o personagem esta morto
	
	int figura[5][4]; //Figuras do personagem
};
/*-------------------------------------------------------------------
	Cabeçalho Funçoes
-------------------------------------------------------------------*/
bool podeMovimentar(int direcao, personagem person); //Retorna se personagem "person" pode movimentar na direção "direcao" (0-Direita) (1-Baixo) (2-Esquerda) (3-Cima)
int inteligencia(int chance, int y, int x); //Retorna melhor direção até a posição "y, x" com chance de "chance"%
void movimenta(personagem *person); //Movimenta o personagem "person" no mapa
void teleporte(personagem *person); //Teleporta o personagem "person" quando sai do mapa
bool encruzilhada(); //Retorna se esta em uma encruzilhada
bool pegueiVoce(personagem person1, personagem person2); //Retorna se "person2" encostou no "person1"
void comeFruta(); //Verifica se adquiriu cash, money, time (because time is money)
void desenha(); //Desenha o Jogo ( mapa + personagens )
void haduken(); //Cria a Greve
void desenhaPlacar(int score2); //Desenha placar na tela
void leArquivos(); //Lê os arquivos do jogo
void fimDeJogo(); //Tela GameOver
void ganhouJogo(); //Tela ganhou jogo
void noMenu(); //Tela menu inicial
void nasOpcoes(); //Tela opções
void naHistoria(); //Tela da historia
void nosCreditos(); //Tela de creditos
void noJogo(); //Jogo propriamente dito

/*-------------------------------------------------------------------
	Variaveis Globais
-------------------------------------------------------------------*/
int gameSom, greveSom, gameOverSom, winSom, comboSom, menuInicialSom, historiaSom, configSom, creditosSom; //Audios
bool somGameOver, somGame, somWin, somMenuInicial, somHistoria, somConfig, somCreditos; //Controladores de Audio
bool gameOver, winGame, inGame, inMenu, inConfig, inCreditos, inHistoria; //Controladores de tela
bool paraAudio = false;//Para audio mais chato do jogo
bool umaVez = true; //Carrega arquivos 1 vez
bool movimento; //Animação Pac-Man
int i, j; //Variaveis de iteracao
int score; //Score
int imgScore[13]; //Imagens do Score
int imgMenu[8]; //Imagens do Menu
int imgConfig[8]; //Imagens do Menu de Opções
int imgHistoria[2]; //Imagens da Historia
int imgCreditos[2]; //Imagens da Creditos
int posYhistoria; //Posição do texto da historia
int posYcreditos, troca; //Posição do texto dos creditos
int totalFrutas; //Quantidade de Dinheiro na fase
int frutasComidas; //Quantidade de Dinheiro adquirido
int bloco[15]; //Imagens dos blocos da fase
int contHaduken; //Quantidade de Greves usadas
int qtHaduken; //Quantidade de Greves na fase
int animacao; //Animações dos Personagens
int animacao2; //Animação zZz
int gameOverImagem[4]; //Imagens do GameOver
int winImagem[4]; //Imagens da tela de Vencedor
int mapa[16][21]; //MAtriz do mapa
int eixoY[6], eixoX[6]; //Posições dos botões do Menu
int eixoY2[6], eixoX2[6]; //Posições dos botões do Menu de Opções
personagem PacMan; //Struct do Andre
personagem Fantasma[numFantasma]; //Struct das Maratonas
personagem Haduken[numHaduken]; //Struct das Greves
personagem configDificuldade; //Configurações de dificuldade do fantasma

int velocidade = 2; //Velocidade do Jogo
/*-------------------------------------------------------------------
	Funcao OBRIGATORIA que eh executada apenas uma vez pela aplicacao.
-------------------------------------------------------------------*/


void iniciar() {		
	if(umaVez) // Lê os arquivos uma unica vez
		leArquivos();
		
	/*----------------------------------------------------------	
	---- Lê o Mapa e coloca na Matriz ( Repare a Extensão ) ----
	----------------------------------------------------------*/
	ifstream arqentrada;
	arqentrada.open("mapa.andq",ios::in);
	for(int i=0; i<16; i++)
		for(int j=0; j<21; j++) {
			arqentrada >> mapa[i][j];
			arqentrada.get();
		}
    arqentrada.close();
	
	/*--------------------------------------------	
	---- Posições Iniciais dos Botões do Menu ----
	--------------------------------------------*/
	eixoY[1] = 250;
	eixoY[2] = 320;
	eixoY[3] = 390;
	eixoY[4] = 460;
	eixoY[5] = -200;
	eixoX[1] = -100;
	eixoX[2] = -300;
	eixoX[3] = -500;
	eixoX[4] = -700;
	eixoX[5] = 0;
	
	eixoY2[1] = 250;
	eixoY2[2] = 320;
	eixoY2[3] = 390;
	eixoY2[4] = 460;
	eixoY2[5] = -200;
	eixoX2[1] = -100;
	eixoX2[2] = -300;
	eixoX2[3] = -500;
	eixoX2[4] = -700;
	eixoX2[5] = 0;
	
	posYhistoria = 620;
	posYcreditos = 620;
	troca = 0;
	
	/*----------------------------	
	---- Para todos os audios ----
	----------------------------*/
	paraSom(winSom);
	paraSom(historiaSom);
	paraSom(configSom);
	paraSom(creditosSom);
	paraSom(gameSom);
	paraSom(gameOverSom);
	paraSom(comboSom);
	paraSom(greveSom);
	
	/*--------------------------------------	
	---- Configurações iniciais do jogo ----
	--------------------------------------*/
	//Audios Ligados/Desligados
	somMenuInicial = true;
	inMenu = true;
	if (paraAudio)
		somMenuInicial = false;
	
	somWin = false;
	somHistoria = false;
	somConfig = false;
	somCreditos = false;
	somGame = false;
	somGameOver = false;
	
	//Telas Ligadas/Desligadas
	winGame = false;
	inHistoria = false;
	inConfig = false;
	inCreditos = false;
	inGame = false;
	gameOver = false;
	
	//Valores iniciais
	score = 0;
	qtHaduken = configDificuldade.hadukenInicial;
	contHaduken = 0;
	animacao = 0;
	animacao2 = 0;
	PacMan.posX = 40;
	PacMan.posY = 40;
	PacMan.direcaoNova = 4;
	PacMan.direcaoAtual = 4;
	PacMan.velocidadeExtra = 0;
	
	for(i=0; i<numFantasma; i++) {
		Fantasma[i].posX = 8*dimensao;
		Fantasma[i].posY = 8*dimensao;
		Fantasma[i].direcaoNova = i;
		Fantasma[i].direcaoAtual = i;
		Fantasma[i].inteligencia = i*configDificuldade.inteligencia+configDificuldade.inteligenciaInicial;
		Fantasma[i].velocidadeExtra = 0;
	}
	
	totalFrutas = 0;
	frutasComidas = 0;
	for(i=0; i<15; i++)
		for(j=0; j<20; j++)
			if(mapa[i][j] == blocoFruta || mapa[i][j] == blocoHadouken)
				totalFrutas++;
}


/*-------------------------------------------------------------------
	Funcao OBRIGATORIA que eh executada continuamente pela aplicacao,
	ate que o usuario pressione a tecla "ESC".
-------------------------------------------------------------------*/

void executar() {
	//Para audio da oplçao Desativar audio do Menu
	if(paraAudio) {
		paraSom(menuInicialSom);
		paraSom(configSom);
		paraSom(gameSom);
		somMenuInicial = false;
		somConfig = true;
		somGame = true;
	}
	
	//Verifica qual tela deve ser exibida
	if (inMenu)
		noMenu();
	else if (gameOver)
		fimDeJogo();
	else if(winGame)
		ganhouJogo();
	else if(inGame)
		noJogo();
	else if(inHistoria)
		naHistoria();
	else if(inCreditos)
		nosCreditos();
	else if(inConfig)
		nasOpcoes();
}

/*-------------------------------------------------------------------
	Funcao OBRIGATORIA que eh executada quando ocorre um evento
	de teclado.
-------------------------------------------------------------------*/

void eventoTeclado (int tipoEvento, int tecla) {
	if (tipoEvento == TECLA_FOI_PRESSIONADA) {
		if (tecla == TECLA_LEFT) {
			PacMan.direcaoNova = 2;
		} else if (tecla == TECLA_RIGHT) {
			PacMan.direcaoNova = 0;
		} else if (tecla == TECLA_UP) {
			PacMan.direcaoNova = 3;
		} else if (tecla == TECLA_DOWN) {
			PacMan.direcaoNova = 1;
		} else if (tecla == TECLA_SPACE) {
			//Verifica se pode usar hadouken/Usa hadouken
			if(contHaduken < qtHaduken) {
				haduken();
				contHaduken++;
			}
		}
	}
}


/*-------------------------------------------------------------------
	Funcao OBRIGATORIA que eh executada quando ocorre um evento
	de mouse.
-------------------------------------------------------------------*/

void eventoMouse(int tipoEvento, int botao, int x, int y) {
	if (tipoEvento == BOTAO_FOI_LIBERADO) {
		//Voltar para menu inicial, ao clicar nas telas abaixo
		if(gameOver || winGame || inHistoria || inCreditos) {
			iniciar();
		} else {
			//Botões do menu inicial
			if(inMenu) {
				//Botão Play
				if(x >= eixoX[1] && x <= eixoX[1]+200 && y >= eixoY[1] && y <= eixoY[1]+50) {
					paraSom(menuInicialSom);
					inMenu = false;
					inGame = true;
				}
				//Botão Opções
				if(x >= eixoX[2] && x <= eixoX[2]+200 && y >= eixoY[2] && y <= eixoY[2]+50) {
					paraSom(menuInicialSom);
					inMenu = false;
					inConfig = true;
				}
				//Botão Historia
				if(x >= eixoX[3] && x <= eixoX[3]+200 && y >= eixoY[3] && y <= eixoY[3]+50) {
					paraSom(menuInicialSom);
					inMenu = false;
					inHistoria = true;
				}
				//Botão Creditos
				if(x >= eixoX[4] && x <= eixoX[4]+200 && y >= eixoY[4] && y <= eixoY[4]+50) {
					paraSom(menuInicialSom);
					inMenu = false;
					inCreditos = true;
				}
			} else if(inConfig) { //Boões do Menu de Opções
				//Modo easy
				if(x >= eixoX2[1] && x <= eixoX2[1]+200 && y >= eixoY2[1] && y <= eixoY2[1]+50) {
					configDificuldade.inteligencia = 15;
					configDificuldade.inteligenciaInicial = 0;		
					configDificuldade.hadukenInicial = 3;
					iniciar();
				}
				//Modo Medium
				if(x >= eixoX2[2] && x <= eixoX2[2]+200 && y >= eixoY2[2] && y <= eixoY2[2]+50) {
					configDificuldade.inteligencia = 20;
					configDificuldade.inteligenciaInicial = 20;
					configDificuldade.hadukenInicial = 2;
					iniciar();
				}
				//Modo hard
				if(x >= eixoX2[3] && x <= eixoX2[3]+200 && y >= eixoY2[3] && y <= eixoY2[3]+50) {
					configDificuldade.inteligencia = 20;
					configDificuldade.inteligenciaInicial = 50;		
					configDificuldade.hadukenInicial = 0;
					iniciar();
				}
				//Retira audio chato
				if(x >= eixoX2[4] && x <= eixoX2[4]+200 && y >= eixoY2[4] && y <= eixoY2[4]+50) {
					paraAudio = !paraAudio;
					somConfig = !somConfig;
				}
				//Botão Voltar
				if(x >= eixoX2[5] && x <= eixoX2[5]+470 && y >= eixoY2[5] && y <= eixoY2[5]+130) {
					iniciar();
				}
			}
		}
	}
}

/*-------------------------------------------------------------------
	Funções
-------------------------------------------------------------------*/
void nasOpcoes() {
	desenhaFigura (imgConfig[0], 0, 0);
	desenhaFigura (imgConfig[5], 0, eixoY2[5]);
	if(eixoY2[5] < 0) //Botão Voltar
		eixoY2[5] += 2;
	else {
		for(i=1; i<5; i++) { //Demais botões
			if(eixoX2[i] < 120)
				eixoX2[i] += 5;
			desenhaFigura (imgConfig[i], eixoX2[i], eixoY2[i]);
		}
	}
	
	if(!somConfig) { //Inicia som, caso esteja desligado
		iniciaSom(configSom, true);
		somConfig = true;
	}
}

void nosCreditos() {
	desenhaFigura (imgCreditos[0], 0, 0);
	desenhaFigura (imgCreditos[1], 0, posYcreditos);
	troca++;
	if(posYcreditos >= -1500 && troca%2) {
		posYcreditos --;
	}
	if(!somCreditos && posYcreditos <= 500) {
		paraSom(somMenuInicial);
		iniciaSom(creditosSom);
		somCreditos = true;
	}
	
	if(posYcreditos <= -1500) { //Altera Posição do Texto
		iniciar();
	}
}

void naHistoria() {
	desenhaFigura (imgHistoria[0], 0, 0);
	desenhaFigura (imgHistoria[1], 0, posYhistoria);
	if(posYhistoria >= -2550) {
		posYhistoria --;
	}
	if(!somHistoria) {
		paraSom(somMenuInicial);
		iniciaSom(historiaSom, true);
		somHistoria = true;
	}
	
	if(posYhistoria <= -2550) {
		iniciar();
	}	
}

void noMenu() {
	desenhaFigura (imgMenu[0], 0, 0);
	desenhaFigura (imgMenu[5], 0, eixoY[5]);
	if(eixoY[5] < 0) //Placa "Andre's Quest"
		eixoY[5] += 2;
	else {
		for(i=1; i<5; i++) { //Botões
			if(eixoX[i] < 120)
				eixoX[i] += 5;
			desenhaFigura (imgMenu[i], eixoX[i], eixoY[i]);
		}
	}
	
	if(somMenuInicial) {
		iniciaSom(menuInicialSom, true);
		somMenuInicial = false;
	}
}

void fimDeJogo () {
	if(animacao>=19) //Condição da variavel que faz a troca das imagens
			animacao=0;
		else
			animacao++;
			
	desenhaFigura (gameOverImagem[animacao/5], 0, 0);
	if(somGameOver) {
		paraSom(gameSom);
		iniciaSom(gameOverSom, true);
		somGameOver = false;
	}
}

void ganhouJogo() {
	if(animacao>=19)
			animacao=0;
		else
			animacao++;
			
	desenhaFigura (winImagem[animacao/5], 0, 0);
	if(somWin) {
		paraSom(gameSom);
		iniciaSom(winSom, true);
		somWin = false;
	}
}

void noJogo() {
	//Ao usar 2 Greves, solta som ComboGreve
	int contCombo = 0; 
	for(i=0; i<numHaduken; i++) {
		if(!Haduken[i].morto)
			contCombo++;
	}
	if(contCombo >= 2)
		iniciaSom(comboSom);
	
	//Inicia som do jogo
	if(!somGame) {
		iniciaSom(gameSom, true);
		somGame = true;
	}
	//Teletransportes
	for(i=0; i<numHaduken; i++)
		if(!(Haduken[i].morto))
			teleporte(&Haduken[i]);
	
	teleporte(&PacMan);
	for(i=0; i<numFantasma; i++)
		teleporte(&Fantasma[i]);
		
	//Muda direcaoNova dos Objetos
		//Fantasmas
	for(i=0; i<numFantasma; i++) {
		//Renasce Fantasma na interceção do tunel com a ponte
		if(Fantasma[i].morto && mapa[Fantasma[i].posY/40][Fantasma[i].posX/40] == blocoTeP && Fantasma[i].posY%dimensao == 0 && Fantasma[i].posX%dimensao == 0) {
			Fantasma[i].morto = false;
			Fantasma[i].velocidadeExtra = 0;
		}
		//Verifica se esta morto, para ver se vai ate o ponto de respawn ou o PacMan
		if(mapa[Fantasma[i].posY/40][Fantasma[i].posX/40] != blocoTeP && encruzilhada())
			if(Fantasma[i].morto)
				Fantasma[i].direcaoAtual = inteligencia(100, 8*40, 8*40);
			else
				Fantasma[i].direcaoAtual = inteligencia(Fantasma[i].inteligencia, PacMan.posY, PacMan.posX);
	}
		//PacMan
	if(podeMovimentar(PacMan.direcaoNova, PacMan) && mapa[PacMan.posY/40][PacMan.posX/40] != blocoTeP)
		PacMan.direcaoAtual = PacMan.direcaoNova;

	
	//Movimenta objetos
		//Movimenta Hadukens
	for(i=0; i<numHaduken; i++)
		if(!(Haduken[i].morto))
			if(!(podeMovimentar(Haduken[i].direcaoAtual, Haduken[i])))
				Haduken[i].morto = true;
			else
				movimenta(&Haduken[i]);
		//Movimenta Fantasma
	for(i=0; i<numFantasma; i++)
		movimenta(&Fantasma[i]);
			
	movimento = false; //Para de fazer animação do PacMan caso ele pare
	movimenta(&PacMan);//Movimenta PacMan
	
	//Haduken Mata Fantasma
	for(i=0; i<numHaduken; i++) {
		for(j=0; j<numFantasma; j++)
			if (pegueiVoce(Fantasma[j], Haduken[i]) && !(Haduken[i].morto) && !(Fantasma[j].morto)) { //Mato o fantasma, reconfigurando ele
				score += 300;
				Fantasma[j].morto = true;
				Fantasma[j].velocidadeExtra = -1;
				Haduken[i].morto = true;
			}
		if (mapa[Haduken[i].posY/40][Haduken[i].posX/40] == blocoParede && Haduken[i].posY%dimensao == 0 && Haduken[i].posX%dimensao == 0) //Mata o haduken se encostar na parede
			Haduken[i].morto = true;
	}
	
	//Detecta se foi Game-Over
	for(i=0; i<numFantasma; i++)
		if (pegueiVoce(PacMan, Fantasma[i])) {
			gameOver = true;
			somGameOver = true;
		}
	 
	// Verifica se ganhou o jogo
	if(frutasComidas == totalFrutas) {
		winGame = true;
		somWin = true;
		inGame = false;
	}
	//Faz animação do PacMan
	if(movimento) {
		if(animacao>=19)
			animacao=0;
		else
			animacao++;
	}
	//Faz animação dos fantasmas
	if(animacao2 >= 19)
			animacao2=0;
		else
			animacao2++;
	
	desenha(); //Desenha mapa+pacMan+Fantasmas
	comeFruta(); //Pega os dinheiros
	desenhaPlacar(score); //Desenha o score
}

void desenhaPlacar(int score2) {
	int aux = 10000;
	int auxX = 80;
	int auxY = 565;
	
	desenhaFigura(imgScore[11], auxX-5, auxY-3);
	
	Verifica se o numero é negativo
	if(score2 < 0) {
		desenhaFigura(imgScore[10], auxX, auxY);
		score2 *= -1;
	}
	//Desloca uma unidade na posição, para desenhar proximo numero
	auxX += 20;
	//Desenha o cada numero separadamente
	for(int i=0; i<5; i++) {
		desenhaFigura(imgScore[score2/aux], auxX, auxY);
		score2 %= aux;
		aux /= 10;
		auxX += 20;
	}
	auxX += 460;
	desenhaFigura(imgScore[12], auxX, auxY-3);
	desenhaFigura(imgScore[qtHaduken-contHaduken], auxX+45, auxY);
}

void haduken() {
	//Verifica se pode usar o haduken/Liga haduken
	if (podeMovimentar(PacMan.direcaoAtual, PacMan)) {
		iniciaSom(greveSom);
		score -= 500;
		Haduken[contHaduken].morto = false;
		Haduken[contHaduken].posY = PacMan.posY;
		Haduken[contHaduken].posX = PacMan.posX;
		Haduken[contHaduken].direcaoAtual = PacMan.direcaoAtual;
		Haduken[contHaduken].velocidadeExtra = 2;
	} else
		contHaduken--;
}

bool pegueiVoce(personagem person1, personagem person2) {

	if(person2.morto)
		return false;
	//Verifica se estão na interseção do tunel e ponte, para ver se pode ou não matar
	if ( (person1.posY >= 320-dimensao && person1.posY <= 320+dimensao && person1.posX >= 320-dimensao && person1.posX <= 320+dimensao) && (person1.direcaoAtual == person2.direcaoAtual+1 || person1.direcaoAtual == (person2.direcaoAtual+3)%4))
		return false;
		
	if(
		person1.posY+(dimensao/2) >= person2.posY && person1.posY+(dimensao/2) <= person2.posY+dimensao-1 &&
		person1.posX+(dimensao/2) >= person2.posX && person1.posX+(dimensao/2) <= person2.posX+dimensao-1
	)
		return true;
	else
		return false;
}
	
int inteligencia(int chance, int y, int x) {
	int chanceAux;
	int num;
	int contAtoa = 0;
	int a = Fantasma[i].direcaoAtual;
	chanceAux = 1+rand()%100;
	num = 1+rand()%2;
	if(chanceAux <= chance) { //Condição da % de inteligencia
		do { //Faz inteligencia, sorteia uma direção de preferencia ( horizontal, vertical )
			if(num%2 == 0) {
				if(y < Fantasma[i].posY && podeMovimentar(3, Fantasma[i]) && (a+2)%4 != 3)
					return 3;
				if(y > Fantasma[i].posY && podeMovimentar(1, Fantasma[i]) && (a+2)%4 != 1)
					return 1;
			} else {
				if(x < Fantasma[i].posX && podeMovimentar(2, Fantasma[i]) && (a+2)%4 != 2)
					return 2;
				if(x > Fantasma[i].posX && podeMovimentar(0, Fantasma[i]) && (a+2)%4 != 0) 
					return 0;
			}
			num++;
			contAtoa++;
		} while(contAtoa <= 1);
	}
	int b;
	b = Fantasma[i].direcaoAtual;
	do { //Sorteia direção aleatoria
		a = rand()%4;
	} while (a==(b+2)%4 || !(podeMovimentar(a, Fantasma[i])));
	 return a;
}

bool encruzilhada() {
	int contador = 0, a, b;
	b = Fantasma[i].direcaoAtual;
	for(a=0; a<4; a++)
		if(a != b)
			if (podeMovimentar(a, Fantasma[i]))
				contador++;

	if (contador >= 2)
		return true;
	else
		return false;
}

void teleporte(personagem *person) { //Se sair do mapa, sorteia uma entrada aleatoria
	if( (person->posX == -80+(velocidade+person->velocidadeExtra)) || (person->posX == 800) || (person->posY == -40+(velocidade+person->velocidadeExtra)) || (person->posY == 600)) {
		int a = rand()%4;
		switch(a) {
			case 0: person->direcaoAtual = 0; person->direcaoNova = 0; person->posY = 9*dimensao; person->posX = -80+(velocidade+person->velocidadeExtra); break;
			case 1: person->direcaoAtual = 1; person->direcaoNova = 1; person->posY = -40+(velocidade+person->velocidadeExtra); person->posX = 5*dimensao; break;
			case 2: person->direcaoAtual = 2; person->direcaoNova = 2; person->posY = 5*dimensao; person->posX = 800; break;
			case 3: person->direcaoAtual = 3; person->direcaoNova = 3; person->posY = 600; person->posX = 14*dimensao; break;
		}
	}
}

bool podeMovimentar(int direcao, personagem person) {
	int y = person.posY/40;
	int y2 = (person.posY+dimensao-1)/40;
	int x = person.posX/40;
	int x2 = (person.posX+dimensao-1)/40;
	
	if (direcao == 0) {
		if(mapa[y][(person.posX+dimensao-1+(velocidade+person.velocidadeExtra))/40] == blocoParede || mapa[y2][(person.posX+dimensao-1+(velocidade+person.velocidadeExtra))/40] == blocoParede)
			return false;
	} else if (direcao == 1) {
		if(mapa[(person.posY+dimensao-1+(velocidade+person.velocidadeExtra))/40][x] == blocoParede || mapa[(person.posY+dimensao-1+(velocidade+person.velocidadeExtra))/40][x2] == blocoParede)
			return false;
	} else if (direcao == 2) {
		if(mapa[y][(person.posX-(velocidade+person.velocidadeExtra))/40] == blocoParede || mapa[y2][(person.posX-(velocidade+person.velocidadeExtra))/40] == blocoParede)
			return false;
	} else if (direcao == 3) {
		if(mapa[(person.posY-(velocidade+person.velocidadeExtra))/40][x] == blocoParede || mapa[(person.posY-(velocidade+person.velocidadeExtra))/40][x2] == blocoParede)
			return false;
	}
	
	return true;
}

void movimenta(personagem *person) {
	if (person->direcaoAtual == 0 && podeMovimentar(0, *person)) {
		person->posX += velocidade + person->velocidadeExtra;
		movimento = true;
	} else if (person->direcaoAtual == 1 && podeMovimentar(1, *person)) {
		person->posY += velocidade + person->velocidadeExtra;
		movimento = true;
	} else if (person->direcaoAtual == 2 && podeMovimentar(2, *person)) {
		person->posX -= velocidade + person->velocidadeExtra;
		movimento = true;
	} if (person->direcaoAtual == 3 && podeMovimentar(3, *person)) {
		person->posY -= velocidade + person->velocidadeExtra;
		movimento = true;
	}
}

void desenha() {
	
	/*-----------------------------
	------- Desenha Matriz --------
	------------------------------*/	
	for(i=0; i<15; i++)
		for(j=0; j<20; j++)
			if (!(mapa[i][j] == blocoTunelMeio || mapa[i][j] == blocoTunelEntrada || mapa[i][j] == blocoTunelSaida || mapa[i][j] == blocoParede))
				if(mapa[i][j] == blocoHadouken)
					desenhaFigura(bloco[mapa[i][j]+animacao2/5], j*dimensao, i*dimensao);
				else
					desenhaFigura(bloco[mapa[i][j]], j*dimensao, i*dimensao);
		
		
	/*-----------------------------
	------ Desenha Fantasma  ------
	------------------------------*/	
	for(i=0; i<numFantasma; i++)
		if( !((Fantasma[i].posY >= 320-dimensao && Fantasma[i].posY <= 320+dimensao && Fantasma[i].posX == 320) && (Fantasma[i].direcaoAtual == 1 || Fantasma[i].direcaoAtual == 3)) )
			if(Fantasma[i].morto)
				desenhaFigura(Fantasma[i].figura[1][animacao2/10], Fantasma[i].posX, Fantasma[i].posY);
			else
				desenhaFigura(Fantasma[i].figura[0][0], Fantasma[i].posX, Fantasma[i].posY);

	/*-----------------------------
	------ Desenha Haduken  ------
	------------------------------*/	
	for(i=0; i<numHaduken; i++)
		if(!(Haduken[i].morto))
			desenhaFigura(Haduken[i].figura[0][0], Haduken[i].posX, Haduken[i].posY);
			
	/*-----------------------------
	------- Desenha PacMan  -------
	------------------------------*/
	if( !((PacMan.posY >= 320-dimensao && PacMan.posY <= 320+dimensao && PacMan.posX >= 320 && PacMan.posX <= 320+dimensao) && (PacMan.direcaoAtual == 1 || PacMan.direcaoAtual == 3)) )
		desenhaFigura(PacMan.figura[PacMan.direcaoAtual][animacao/5], PacMan.posX, PacMan.posY);

	/*-----------------------------
	--- Desenhar Tunel e Parede ---
	------------------------------*/
	for(i=0; i<15; i++)
		for(j=0; j<20; j++)
			if( (mapa[i][j] == blocoTunelMeio || mapa[i][j] == blocoTunelEntrada || mapa[i][j] == blocoTunelSaida || mapa[i][j] == blocoParede) )
				desenhaFigura(bloco[mapa[i][j]], j*dimensao, i*dimensao);
}

void comeFruta() {
	if (mapa[PacMan.posY/40][PacMan.posX/40] == blocoFruta && PacMan.posY%dimensao == 0 && PacMan.posX%dimensao == 0) {
		mapa[PacMan.posY/40][PacMan.posX/40] = blocoChao;
		frutasComidas++;
		score += 100;
	}
	
	if (mapa[PacMan.posY/40][PacMan.posX/40] == blocoHadouken && PacMan.posY%dimensao == 0 && PacMan.posX%dimensao == 0) {
		mapa[PacMan.posY/40][PacMan.posX/40] = blocoChao;
		qtHaduken++;
		frutasComidas++;
		score += 200;

	}
}

void leArquivos() {
	redefineJanelaPrincipal("Andre's Quest", 200, 50, 800, 600);
	cout << "Iniciando aplicacao..." << endl;
	srand(time(NULL));
	bloco[blocoFruta] = carregaFiguraDeArquivo ("Resources/Pictures/Fruta.png");
	bloco[blocoParede] = carregaFiguraDeArquivo ("Resources/Pictures/Parede.png");
	bloco[blocoTunelMeio] = carregaFiguraDeArquivo ("Resources/Pictures/Tunel.png");
	bloco[blocoPonte] = carregaFiguraDeArquivo ("Resources/Pictures/Ponte.png");
	bloco[blocoTeP] = carregaFiguraDeArquivo ("Resources/Pictures/TP.png");
	bloco[blocoChao] = carregaFiguraDeArquivo ("Resources/Pictures/Chao.png");
	bloco[blocoTunelEntrada] = carregaFiguraDeArquivo ("Resources/Pictures/EntradaTunel.png");
	bloco[blocoTunelSaida] = carregaFiguraDeArquivo ("Resources/Pictures/SaidaTunel.png");
	bloco[blocoHadouken] = carregaFiguraDeArquivo ("Resources/Pictures/z.png");
	bloco[blocoHadouken+1] = carregaFiguraDeArquivo ("Resources/Pictures/zz.png");
	bloco[blocoHadouken+2] = carregaFiguraDeArquivo ("Resources/Pictures/zzz.png");
	bloco[blocoHadouken+3] = carregaFiguraDeArquivo ("Resources/Pictures/zzzz.png");
	
	PacMan.figura[0][0] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan00.png");
	PacMan.figura[0][1] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan01.png");
	PacMan.figura[0][2] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan02.png");
	PacMan.figura[0][3] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan01.png");
	PacMan.figura[0][4] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan01.png");
	PacMan.figura[1][0] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan10.png");
	PacMan.figura[1][1] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan11.png");
	PacMan.figura[1][2] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan12.png");
	PacMan.figura[1][3] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan11.png");
	PacMan.figura[2][0] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan20.png");
	PacMan.figura[2][1] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan21.png");
	PacMan.figura[2][2] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan22.png");
	PacMan.figura[2][3] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan21.png");
	PacMan.figura[3][0] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan30.png");
	PacMan.figura[3][1] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan31.png");
	PacMan.figura[3][2] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan32.png");
	PacMan.figura[3][3] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan31.png");
	PacMan.figura[4][0] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan00.png");
	PacMan.figura[4][1] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan00.png");
	PacMan.figura[4][2] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan00.png");
	PacMan.figura[4][3] = carregaFiguraDeArquivo ("Resources/Pictures/pacMan00.png");
	
	Fantasma[0].figura[0][0] = carregaFiguraDeArquivo ("Resources/Pictures/Fantasma3.png");
	Fantasma[0].figura[1][0] = carregaFiguraDeArquivo ("Resources/Pictures/morto.png");
	Fantasma[0].figura[1][1] = carregaFiguraDeArquivo ("Resources/Pictures/morto2.png");
	Fantasma[1].figura[0][0] = carregaFiguraDeArquivo ("Resources/Pictures/Fantasma0.png");
	Fantasma[1].figura[1][0] = carregaFiguraDeArquivo ("Resources/Pictures/morto.png");
	Fantasma[1].figura[1][1] = carregaFiguraDeArquivo ("Resources/Pictures/morto2.png");
	Fantasma[2].figura[0][0] = carregaFiguraDeArquivo ("Resources/Pictures/Fantasma1.png");
	Fantasma[2].figura[1][0] = carregaFiguraDeArquivo ("Resources/Pictures/morto.png");
	Fantasma[2].figura[1][1] = carregaFiguraDeArquivo ("Resources/Pictures/morto2.png");
	Fantasma[3].figura[0][0] = carregaFiguraDeArquivo ("Resources/Pictures/Fantasma2.png");
	Fantasma[3].figura[1][0] = carregaFiguraDeArquivo ("Resources/Pictures/morto.png");
	Fantasma[3].figura[1][1] = carregaFiguraDeArquivo ("Resources/Pictures/morto2.png");
	
	imgScore[0] = carregaFiguraDeArquivo ("Resources/Pictures/score0.png");
	imgScore[1] = carregaFiguraDeArquivo ("Resources/Pictures/score1.png");
	imgScore[2] = carregaFiguraDeArquivo ("Resources/Pictures/score2.png");
	imgScore[3] = carregaFiguraDeArquivo ("Resources/Pictures/score3.png");
	imgScore[4] = carregaFiguraDeArquivo ("Resources/Pictures/score4.png");
	imgScore[5] = carregaFiguraDeArquivo ("Resources/Pictures/score5.png");
	imgScore[6] = carregaFiguraDeArquivo ("Resources/Pictures/score6.png");
	imgScore[7] = carregaFiguraDeArquivo ("Resources/Pictures/score7.png");
	imgScore[8] = carregaFiguraDeArquivo ("Resources/Pictures/score8.png");
	imgScore[9] = carregaFiguraDeArquivo ("Resources/Pictures/score9.png");
	imgScore[10] = carregaFiguraDeArquivo ("Resources/Pictures/score10.png");
	imgScore[11] = carregaFiguraDeArquivo ("Resources/Pictures/score11.png");
	imgScore[12] = carregaFiguraDeArquivo ("Resources/Pictures/score12.png");
	
	imgMenu[0] = carregaFiguraDeArquivo ("Resources/Pictures/menu.png");
	imgMenu[1] = carregaFiguraDeArquivo ("Resources/Pictures/menuPlay.png");
	imgMenu[2] = carregaFiguraDeArquivo ("Resources/Pictures/menuOpcoes.png");
	imgMenu[3] = carregaFiguraDeArquivo ("Resources/Pictures/menuHistoria.png");
	imgMenu[4] = carregaFiguraDeArquivo ("Resources/Pictures/menuCreditos.png");
	imgMenu[5] = carregaFiguraDeArquivo ("Resources/Pictures/menuTitulo.png");
	
	imgConfig[0] = carregaFiguraDeArquivo ("Resources/Pictures/config.png");
	imgConfig[1] = carregaFiguraDeArquivo ("Resources/Pictures/configEasy.png");
	imgConfig[2] = carregaFiguraDeArquivo ("Resources/Pictures/configMedium.png");
	imgConfig[3] = carregaFiguraDeArquivo ("Resources/Pictures/configHard.png");
	imgConfig[4] = carregaFiguraDeArquivo ("Resources/Pictures/configAudio.png");
	imgConfig[5] = carregaFiguraDeArquivo ("Resources/Pictures/configVoltar.png");
	
	imgHistoria[0] = carregaFiguraDeArquivo ("Resources/Pictures/historia0.png");
	imgHistoria[1] = carregaFiguraDeArquivo ("Resources/Pictures/historia1.png");
	
	imgCreditos[0] = carregaFiguraDeArquivo ("Resources/Pictures/creditos0.png");
	imgCreditos[1] = carregaFiguraDeArquivo ("Resources/Pictures/creditos1.png");

	for(i=0; i<numHaduken; i++)
		Haduken[i].figura[0][0] = carregaFiguraDeArquivo ("Resources/Pictures/Haduken.png");

	gameOverImagem[0] = carregaFiguraDeArquivo ("Resources/Pictures/gameOver0.png");
	gameOverImagem[1] = carregaFiguraDeArquivo ("Resources/Pictures/gameOver1.png");
	gameOverImagem[2] = carregaFiguraDeArquivo ("Resources/Pictures/gameOver2.png");
	gameOverImagem[3] = carregaFiguraDeArquivo ("Resources/Pictures/gameOver3.png");
	
	winImagem[0] = carregaFiguraDeArquivo ("Resources/Pictures/win0.png");
	winImagem[1] = carregaFiguraDeArquivo ("Resources/Pictures/win1.png");
	winImagem[2] = carregaFiguraDeArquivo ("Resources/Pictures/win2.png");
	winImagem[3] = carregaFiguraDeArquivo ("Resources/Pictures/win3.png");
	
	gameSom = carregaSom("Resources/Sounds/andar.wav");
	greveSom = carregaSom("Resources/Sounds/greve.wav");
	gameOverSom = carregaSom("Resources/Sounds/gameOver.wav");
	winSom = carregaSom("Resources/Sounds/win.wav");
	comboSom = carregaSom("Resources/Sounds/combo.wav");
	menuInicialSom = carregaSom("Resources/Sounds/menuInicial.wav");
	historiaSom = carregaSom("Resources/Sounds/historia.wav");
	creditosSom = carregaSom("Resources/Sounds/creditos.wav");
	configSom = carregaSom("Resources/Sounds/config.wav");
	
	configDificuldade.inteligencia = 20;
	configDificuldade.inteligenciaInicial = 20;
	configDificuldade.hadukenInicial = 2;
	
	umaVez = false;
}