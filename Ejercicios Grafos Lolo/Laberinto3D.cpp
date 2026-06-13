#include "alg_GRAFOPMC.h"
#include<vector>
#include "colanela.h"

struct Casilla{
    size_t x, y,z;

    Casilla(size_t x_, size_t y_, size_t z_): x(x_), y(y_), z(z_){}
};

struct Pared{
    Casilla A;
    Casilla B;
};

typename GrafoP<int>::vertice CasillaToVertice(const Casilla& A, int N)
{
    return A.x+A.y*N+A.z*N*N;
}

struct Camino_Coste{
    typename GrafoP<int>::tCamino Camino;
    int Coste;

    Camino_Coste(typename GrafoP<int>::tCamino c, int cost): Camino(c), Coste(cost){}
};


Camino_Coste Laberinto3D(int N, const vector<Pared>& Paredes, const Casilla& origen, const Casilla& destino)
{
    //Primero montamos el GrafoP
    GrafoP<int> laberinto(N*N*N);

    for(size_t z=0; z<N; z++)
    {
        for(size_t y=0; y<N; y++)
        {
            for(size_t x=0; x<N; x++)
            {
                typename GrafoP<int>::vertice v1=CasillaToVertice(Casilla(x,y,z), N);

                if(z+1<N)
                {
                    typename GrafoP<int>::vertice v2=CasillaToVertice(Casilla(x,y,z+1), N);

                    laberinto[v1][v2]=1;
                    laberinto[v2][v1]=1;
                }
                if(z>0)
                {
                    typename GrafoP<int>::vertice v2=CasillaToVertice(Casilla(x,y,z-1), N);

                    laberinto[v1][v2]=1;
                    laberinto[v2][v1]=1;
                }
                if(y+1<N)
                {
                    typename GrafoP<int>::vertice v2=CasillaToVertice(Casilla(x,y+1,z), N);

                    laberinto[v1][v2]=1;
                    laberinto[v2][v1]=1;
                }
                if(y>0)
                {
                    typename GrafoP<int>::vertice v2=CasillaToVertice(Casilla(x,y-1,z), N);

                    laberinto[v1][v2]=1;
                    laberinto[v2][v1]=1;
                }
                if(x+1<N)
                {
                    typename GrafoP<int>::vertice v2=CasillaToVertice(Casilla(x+1,y,z), N);

                    laberinto[v1][v2]=1;
                    laberinto[v2][v1]=1;
                }
                if(x>0)
                {
                    typename GrafoP<int>::vertice v2=CasillaToVertice(Casilla(x-1,y,z), N);

                    laberinto[v1][v2]=1;
                    laberinto[v2][v1]=1;
                }
                
            }
        }
    }

    //Ahora quitamos las paredes
    for(const Pared& p : Paredes)
    {
        typename GrafoP<int>::vertice v1=CasillaToVertice(p.A,N);
        typename GrafoP<int>::vertice v2=CasillaToVertice(p.B,N);

        laberinto[v1][v2]=GrafoP<int>::INFINITO;
        laberinto[v2][v1]=GrafoP<int>::INFINITO;
    }

    //Una vez tenemos el grafo listo hacemos dijkstra 
    vector<typename GrafoP<int>::vertice> Antecesores(laberinto.numVert());
    typename GrafoP<int>::vertice Vorigen=CasillaToVertice(origen,N);
    vector<int> DesdeOrigen=Dijkstra(laberinto, Vorigen, Antecesores);

    typename GrafoP<int>::vertice Vdestino=CasillaToVertice(destino,N);
    int coste=DesdeOrigen[Vdestino];

    
    typename GrafoP<int>::vertice actual=Vdestino;
    typename GrafoP<int>::tCamino Camino;
    Camino.insertar(actual, Camino.primera());

    while(actual!=Vorigen)
    {
        actual=Antecesores[actual];
        Camino.insertar(actual, Camino.primera());
    }

    return Camino_Coste(Camino, coste);
}