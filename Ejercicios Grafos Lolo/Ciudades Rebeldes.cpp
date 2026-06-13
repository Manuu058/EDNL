/*
Necesitamos las distancias minimas entre dos ciudades, solo tienen un sentido de la circulacion las carreteras, muchas ciudades estan tomadas
y muchas carreteras cortadas. Se exige pasar por la Capital: huele Dijkstra. 
*/
#include "alg_GRAFOPMC.h"
#include<vector>

using namespace std;

typedef pair<size_t, size_t> Carretera;

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


template<typename tCoste>
matriz<tCoste> CiudadesRebeldes(const GrafoP<tCoste>& Zuelandia, vector<bool>& CiudadesTomadas, vector<Carretera>& CarreteraCortada,
typename GrafoP<tCoste>::vertice Capital)
{
    //Montamos el Grafo en condiciones aplicando todos los cambios
    GrafoP<tCoste> G(Zuelandia);

    //Quitamos las ciudades
    for(size_t i=0; i<G.numVert();i++)
    {
        if(CiudadesTomadas[i])
        {
            for(size_t j=0; j<G.numVert();j++)
            {
                G[i][j]=GrafoP<tCoste>::INFINITO;
                G[j][i]=GrafoP<tCoste>::INFINITO;
            }   
        }
    }   

    //Quitamos las carreteras
    for(Carretera c : CarreteraCortada)
    {
        G[c.first][c.second]=GrafoP<tCoste>::INFINITO;
    }

    //Una vez que tenemos el grafo arreglado aplicamos Dijkstra para encontrar las uniones entre una ciudad como la capital y todas las demas
    vector<typename GrafoP<tCoste>::vertice> Antecesores(G.numVert());
    vector<tCoste> DesdeCapital=Dijkstra(G, Capital, Antecesores);
    vector<tCoste> HaciaCapital=DijkstraInv(G, Capital, Antecesores);

    //Creamos la matriz de costes minimos y la rellenamos
    matriz<tCoste> CostesMinimos(G.numVert());

    for(size_t i=0; i<G.numVert();i++)
    {
        for(size_t j=0; j<G.numVert();j++)
        {
            if(i==j)
            {
                CostesMinimos[i][j]=0;
            }
            else
            {
                CostesMinimos[i][j]=suma(HaciaCapital[i], DesdeCapital[j]);
            }

        }   
        
    }   

    return CostesMinimos;
}