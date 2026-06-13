#include "alg_GRAFOPMC.h"



using namespace std;

struct Casilla
{
    int fila, columna;
};

int Vertice(Casilla c)
{
    return c.fila * 8 + c.columna;
}

bool valida(int f, int c)
{
    return f >= 0 && f < 8 && c >= 0 && c < 8;
}

int MovimientosCaballo(Casilla entrada, Casilla salida)
{
    const int N = 8;
    const int TOTAL = N * N;

    GrafoP<int> G(TOTAL);

    int df[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for(int f = 0; f < N; f++) {
        for(int c = 0; c < N; c++) {
            int origen = f * N + c;

            for(int k = 0; k < 8; k++) {
                int nf = f + df[k];
                int nc = c + dc[k];

                if(valida(nf, nc)) {
                    int destino = nf * N + nc;
                    G[origen][destino] = 1;
                }
            }
        }
    }

    vector<GrafoP<int>::vertice> P(TOTAL);
    vector<int> D = Dijkstra(G, Vertice(entrada), P);

    return D[Vertice(salida)];
}
