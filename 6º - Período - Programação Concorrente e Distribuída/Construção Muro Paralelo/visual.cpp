#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

mutex mtx_tijolo_central;           // mutex for critical section
mutex mtx_incremento;
int contador = 0;

struct Tijolo {
    bool construido;
    int pedreiro;
    int i, j;

    Tijolo() {
        pedreiro = 0;
        construido = false;
        i = j = -1;
    }

    Tijolo(int p, int ii, int jj) {
        pedreiro = p;
        i = ii;
        j = jj;
    }

    bool possoPor(int *linhas, Tijolo **muro, int tam) {
        if(muro[i+1][j].construido) { // Condição nescessario, tijolo de baixo estar no muro

            //Condições para que o tijolo possa ser colocado
            if(i%2) { // Em linhas impares
                if(j > tam/2+1 && muro[i+1][j+1].construido)
                    return true;
                else if(j < tam/2+1 && muro[i+1][j-1].construido)
                    return true;
                else if(muro[i+1][j+1].construido && muro[i+1][j-1].construido)
                    return true;

                if(j == 1 || j == tam+1) // Meio tijolo só precisa do tijolo de baixo
                    return true;


            } else {
                if(j < tam/2+1 && muro[i+1][j+1].construido) // Tijolo inteiro precisa do tijolo da diagonal inferior esquerda
                    return true;
                else if(j > tam/2+1 && muro[i+1][j-1].construido)
                    return true;
            }

        }

        return false;
    }

    bool colocaTijolo(Tijolo **muro, int tam) {
        if(i%2 && j == tam/2+1) { // Tijolo do meio das linhas impares
            if(muro[i][j].construido) // Se já foi colocado não faz nada
                return false;

            if(mtx_tijolo_central.try_lock()) { // Região Critica (tijolo do meio), caso já tenha outra thread nessa região não faz nada
            	mtx_incremento.lock(); // Região de incremento do numero de tijolos
	            	contador++;
	            	if(contador%12 == 0) { // Imprimir de 12 em 12, faz outras threads não colocar tijolos, até o fim da impressão
	            		construido = true;
                		muro[i][j] = *this;
	                	imprimeMuro(muro, tam);
	                	cout << "Thread Impressora: " << pedreiro << "   -   numero tijolos: " << contador << endl;
	               		cout << endl << endl;
                        cin.get();
	            	}
	            mtx_incremento.unlock();

            	construido = true;
                muro[i][j] = *this;
                mtx_tijolo_central.unlock();

                return true;
            }
        }
        else {
        	mtx_incremento.lock(); // Região de incremento do numero de tijolos
            	contador++;
            	if(contador%12 == 0) { // Imprimir de 12 em 12, faz outras threads não colocar tijolos, até o fim da impressão
            		construido = true;
            		muro[i][j] = *this;
                	imprimeMuro(muro, tam);
                	cout << "Thread Impressora: " << pedreiro << "   -   numero tijolos: " << contador << endl;
               		cout << endl << endl;
                    cin.get();
            	}
	        mtx_incremento.unlock();
        	construido = true;
            muro[i][j] = *this; // Coloca tijolo no muro

            return true;
        }

        return false;
    }

    friend void imprimeMuro(Tijolo **muro, int tam);
};

// Só as formatação muita louca, passamo mal
void imprimeMuro(Tijolo **muro, int tam) {
    for(int i=0; i<tam*6+1; i++)
        cout << "_";
    cout << endl;

    int limite = tam+1;
    int eoq = 0;

    for(int i=1; i<=tam; i++) {
        for(int j=1; j<=limite; j++) {
            if(i%2 == 0 && j==tam/2+1)
                j++;
            cout << "|";
            if((i%2) && (j == 1 || j == tam+1))
                cout << "  ";
            else
                cout << "     ";
        }
        cout << "|" << endl;

        for(int j=1; j<=limite; j++) {
            if(i%2 == 0 && j==tam/2+1)
                j++;
            cout << "|";

            if(!(i%2) && j == tam/2+1)
                eoq = 1;
            else
                eoq = 0;

            if(muro[i][j+eoq].pedreiro > 9) {
                if(!(i%2) || (j != 1 && j != tam+1))
                    cout << " ";
            } else {
                if((i%2) && (j == 1 || j == tam+1))
                    cout << " ";
                else
                    cout << "  ";
            }

            if(muro[i][j+eoq].pedreiro)
                cout << muro[i][j+eoq].pedreiro;
            else
                cout << " ";

            if(!(i%2) || (j != 1 && j != tam+1))
                cout << "  ";
        }
        cout << "|" << endl;

        for(int j=1; j<=limite; j++) {
            if(i%2 == 0 && j==tam/2+1)
                j++;
            cout << "|";
            if((i%2) && (j == 1 || j == tam+1))
                cout << "__";
            else
                cout << "_____";
        }
        cout << "|" << endl;
    }
}

void constroiMuro(int inicio, int fim, int tam, Tijolo **muro, int id, int n) {
    int *linhas = new int[tam+1]; // Vetor numero minimo de tijolos que a threads deve por em cada linha

    if(linhas == NULL) {
        cout << "Falha ao alocar vetor de linhas para a thread: " << id << endl;
        exit(0);
    }

    for(int i=0; i<=tam; i++)
        if(i%2)
            linhas[i] = tam/n; // Numero minimo de tijolos que a thread deve por na linha i
        else
            linhas[i] = 10000000;

    queue<Tijolo> fila;

    // Cria a fila dos tijolos que a thread ID pode colocar no muro
    for(int i=inicio; i<=fim; i++) {
        Tijolo aux(id, tam, i);
        fila.push(aux);
    }

    // Constroe a parte do muro que foi designada a thread
    Tijolo aux;
    while(!fila.empty()) {
        aux = fila.front();
        fila.pop();

        if(aux.possoPor(linhas, muro, tam)) {
            linhas[aux.i]--; // Diminui número minimo de tijolos que devem ser colocados na linha
            if(aux.colocaTijolo(muro, tam)) {
                if(linhas[aux.i] == 0 && !muro[aux.i][tam/2+1].construido) {
                	Tijolo aux2(id, aux.i, tam/2+1);
                	fila.push(aux2);
            	}

            	if(aux.j != tam/2+1 && aux.i > 1) {
                	Tijolo aux2(id, aux.i-1, aux.j);
               		fila.push(aux2);
           		}
            }
        }
        else
            fila.push(aux); // Caso não seja possivel colocar o tijolo volta com ele para a fila
    }
}

bool alocaVetores(Tijolo ***muro, int tam, thread **t, int n) {
    *muro = new Tijolo*[tam];
    for(int i=0; i<tam; i++)
        (*muro)[i] = new Tijolo[tam+1];

    *t = new thread[n];

    if((*muro) == NULL) {
        cout << "Falha ao alocar (*muro)" << endl;
        return false;
    }

    if(*t == NULL) {
        cout << "Falha ao alocar vetor de threads" << endl;
        return false;
    }

    //Cercando linhas muro
    for(int i=0; i<tam; i++) {
        (*muro)[i][0].construido = (*muro)[i][tam].construido = true;
        (*muro)[i][0].pedreiro = (*muro)[i][tam].pedreiro = 0;
    }

    //Cercando colunas muro
    for(int i=0; i<=tam; i++) {
        (*muro)[0][i].pedreiro = (*muro)[tam-1][i].pedreiro = 0;
        (*muro)[0][i].construido = (*muro)[tam-1][i].construido = true;
    }

    // Define tijolos do meio que não podem ser construidos (Linhas pares) como true
    tam -= 2;
    for(int i=2; i<tam+2; i+=2)
        (*muro)[i][tam/2+1].construido = true;

    return true;
}

void deletaVetores(Tijolo ***muro, int tam, thread **t) {
    for(int i=0; i<tam; i++)
        delete[] (*muro)[i];

    delete[] (*muro);
    delete[] (*t);
}

int main() {
    Tijolo **muro;
    thread *t; //Vetor de threads

    int tam_muro = 10000;
    int n_threads = 80;

    // Faz leitura do tamnho do muro
    do {
        cout << "Informe o tamanho do muro (Par): ";
        cin >> tam_muro;
    } while(tam_muro%2);

    // Faz leitura do tamanho das threads
    do {
        cout << "Informe o numero de threads (Par e divisor do tamanho do muro): ";
        cin >> n_threads;
    } while(n_threads%2 || tam_muro%n_threads);
    cin.get();

    // TAM_MURO: +2 para cercar matriz, +1 para simular tijolo do meio=> +3
    if(!alocaVetores(&muro, tam_muro+2, &t, n_threads))
        exit(0);
    else
        cout << "Muro e vetor de threads alocados com sucesso" << endl << endl;

    // Vetores que armazenam a coluna de inicio e fim de cada thread
    int *ini = new int[n_threads];
    int *fim = new int[n_threads];

    if(ini == NULL || fim == NULL) {
        cout << "Falha ao alocar vetor de inicio e fim" << endl;
        exit(0);
    }

    // Define em qual coluna cada thread ira começar e terminar a construir o muro
    ini[0] = 1;
    fim[0] = tam_muro/n_threads;
    for(int i=1; i<n_threads; i++) {
        ini[i] = fim[i-1]+1;
        fim[i] = fim[i-1]+tam_muro/n_threads;

        if(i == n_threads/2) { // Solta o bloco do meio
            ini[i]++;
            fim[i]++;
        }
    }

    // Cria as N threads
    for(int i=0; i<n_threads; i++)
        t[i] = thread(constroiMuro, ini[i], fim[i], tam_muro, muro, i+1, n_threads);

    // Sincroniza as N threads
    for(int i=0; i<n_threads; i++)
        t[i].join();

    cout << "Muro construido" << endl;
    imprimeMuro(muro, tam_muro);

    deletaVetores(&muro, tam_muro+2, &t);

    return 0;
}
