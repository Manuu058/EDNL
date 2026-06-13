/*
Cierre de ciudad, habra que quitarla de donde sea.
Quitar la ciudad aplicar floy y luego dijkstra para meter las ciudades que tienen como origen o destino la capital
*/

#include "alg_GRAFOPMC.h"
#include<vector>

using namespace std;


template<typename tCoste>
vector<tCoste> DijkstraInv(const GrafoP<tCoste>& G, typename GrafoP<tCoste>::vertice v, vector<typename GrafoP<tCoste>::vertice>& P)
{
    GrafoP<tCoste> Invertido(G.numVert());

    for(size_t i=0; i<G.numVert();i++)
    {
        for(size_t j=0; j<G.numVert();j++)
        {
            Invertido[i][j]=G[j][i];
        }   
    }   

    return Dijkstra(Invertido, v, P);
}

#include "alg_GRAFOPMC.h"
#include <vector>

using namespace std;

template<typename tCoste>
matriz<tCoste> ToxicidadZuelandia(typename GrafoP<tCoste>::vertice Capital,
const GrafoP<tCoste>& Zuelandia)
{
    GrafoP<tCoste> Copia(Zuelandia);

    // Prohibimos pasar por la capital
    for(size_t i = 0; i < Copia.numVert(); i++)
    {
        Copia[i][Capital] = GrafoP<tCoste>::INFINITO;
        Copia[Capital][i] = GrafoP<tCoste>::INFINITO;
    }

    matriz<typename GrafoP<tCoste>::vertice> P(Copia.numVert());
    matriz<tCoste> CostesMinimos = Floyd(Copia, P);

    // Se permite que la capital sea origen o destino
    for(size_t i = 0; i < Zuelandia.numVert(); i++)
    {
        CostesMinimos[Capital][i] = Zuelandia[Capital][i];
        CostesMinimos[i][Capital] = Zuelandia[i][Capital];
    }

    CostesMinimos[Capital][Capital] = 0;

    return CostesMinimos;
}