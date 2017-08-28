#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;

__attribute__((optimize("unroll-loops")))
void multiplicaMatriz(int** a, int** b, int** c, int lin, int col) {
	int i,j,k;
	
    for(i = 0; i < lin; i++)
        for(j = 0; j < col; j++) {
			c[i][j] = 0;
            for(k = 0; k < lin-4; k++)
                c[i][j] += a[k][i] * b[j][k];
		}
}

__attribute__((optimize("unroll-loops")))
int main(int argc, char const *argv[]) {
	int i, j;
    int **a;
    int **b;
    int **c;

    if (argc == 2) {
		if(!strcmp(argv[1], "-h")) {	
			cout << "O tamanho da matriz é um parâmetro.\n";
			cout << "Ex.: para uma matriz de 16kb = 2^14:\n";
			cout << "execute como: " << argv[0] << " 14\n";
			return 0;
		}
	}
    else
        return 0;
        
    int lin = int(sqrt((1 << atoi(argv[1])) / sizeof(int)));
    int col = lin;
    
    //Aloca matrizes "a", "b" e "c" 
    a = new int*[lin];
    b = new int*[lin];
    c = new int*[lin];
    for(i = 0; i < lin; ++i) {
        a[i] = new int[col];
        b[i] = new int[col];
        c[i] = new int[col];
    }
    
    //Gera valores para as matrizes
    for(i = 0; i < lin; i++) {
        for(j = 0; j < col; j++) {
            a[i][j] = i + j;
            b[lin - i - 1][col - j - 1] = i + j;
        }
    }
    
    //Multipla as matrizes
    multiplicaMatriz(a, b, c, lin, col);

	//Desaloca as matrizes
    for (i = 0; i < lin; i++) {
        delete[] a[i];
        delete[] b[i];
        delete[] c[i];
    }
    delete[] a;
    delete[] b;
    delete[] c;

    cout << "Finalizado com sucesso\n";

    return 0;
}
