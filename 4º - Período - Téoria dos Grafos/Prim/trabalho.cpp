#include <iostream>

using namespace std;

#define INF 1000000000
const int N = 27

int g[N][N];
int dist[N];
int marc[N];

int prim() {
    for (int i = 0; i < N; i++) dist[i] = INF;
    dist[0] = 0;

    int curr = 0;
    int custo = 0;
    while (curr != -1) {
        marc[curr]=1;
        custo += dist[curr];

        for (int i = 0; i < N; i++) {
            if (g[curr][i]) dist[i] = min(dist[i],g[curr][i]);
        }

        curr=-1;
        int min_dist = INF;
        for (int i = 0; i < N; i++) {
            if (!marc[i] && dist[i] < min_dist) {
                curr = i;
                min_dist = dist[i];
            }
        }

    }
    return custo;
}

int main() {
    for(int i=0; i<27; i++)
        for(int j=0; j<27; j++)
            cin >> g[i][j];

    for(int i=0; i<27; i++)
        for(int j=0; j<27; j++)
            if(g[i][j] == -1)
                g[i][j] = g[j][i];

    return 0;
}
