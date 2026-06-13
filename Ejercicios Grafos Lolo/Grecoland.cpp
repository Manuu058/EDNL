/*
Formado por dos islas con sus ciudades normales y costeras. Se dispone de coordenadas cartesianas para calcular es la distancia Euclidea,
reeconstruir al minimo coste:Kruskall. El puente siempre sera mas caro por lo que habra que diferenciarlo sumandole el coste maximo que exista.
El coste de viajar entre dos ciudades origen y destino: Dijkstra.
*/
#include "alg_GRAFOPMC.h"
#include<vector>
#include<cmath>
#include<algorithm>

struct Ciudad{
    double x,y;

    Ciudad(double x_, double y_): x(x_), y(y_){}
};

double DistanciaEuclidea(const Ciudad& A, const Ciudad& B)
{
    return sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2));
}

double Viaje(const vector<Ciudad>& CiudadesFobos, const vector<Ciudad>& CiudadesDeimos, const vector<bool>& CostaFobos, const vector<bool>&
CostaDeimos, typename GrafoP<double>::vertice Origen, typename GrafoP<double>::vertice Destino)
{
    //Hay que montar el grafo
    int N1=CiudadesFobos.size();
    int N2=CiudadesDeimos.size();
    int N=N1+N2;

    GrafoP<double> Grecoland(N);
    //Guardamos una variable con el maximo 
    double maximo=0;

    //Montamos Fobos
    for(size_t i=0; i<N1;i++)
    {
        for(size_t j=0; j<N1;j++)
        {
            double distancia=DistanciaEuclidea(CiudadesFobos[i],CiudadesFobos[j]);;
            Grecoland[i][j]=distancia;
            maximo=max(maximo, distancia);
        }
    }
    //Montamos Deimos
    for(size_t i=0; i<N2;i++)
    {
        for(size_t j=0; j<N2;j++)
        {
            double distancia=DistanciaEuclidea(CiudadesDeimos[i],CiudadesDeimos[j]);
            Grecoland[i+N1][j+N1]=distancia;
            maximo=max(maximo, distancia);
        }
    }
    // Montamos los puentes
    for(size_t i = 0; i < N1; i++)
    {
        for(size_t j = 0; j < N2; j++)
        {
            if(CostaFobos[i] && CostaDeimos[j])
            {
                double distancia = DistanciaEuclidea(CiudadesFobos[i], CiudadesDeimos[j]);

                Grecoland[i][j + N1] = distancia + maximo;
                Grecoland[j + N1][i] = distancia + maximo;
            }
        }
    }

    //Aplicamos Kruskall para reconstruir todo al menor coste posible
    Grecoland=Kruskall(Grecoland);

    // Quitamos la penalización de los puentes
    for(size_t i = 0; i < N1; i++)
    {
        for(size_t j = 0; j < N2; j++)
        {
            if(CostaFobos[i] && CostaDeimos[j] &&
            Grecoland[i][j + N1] != GrafoP<double>::INFINITO)
            {
                Grecoland[i][j + N1] -= maximo;
                Grecoland[j + N1][i] -= maximo;
            }
        }
    }

    //Una vez que tenemos ya la ciudad montada aplicamos dijkstra para que elija el mejor camino de origen a destino.
    vector<typename GrafoP<double>::vertice> Antecesores(Grecoland.numVert());
    vector<double> DesdeOrigen=Dijkstra(Grecoland, Origen, Antecesores);

    return DesdeOrigen[Destino];
}