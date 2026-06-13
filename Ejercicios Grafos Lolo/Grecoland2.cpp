/*
El coste de construccion del puente se considera irrelevante.
Consideramos minimizar el coste de viajar entre todas las ciudades.
Utilizamos las distancias euclideas
Se realizan todos los posibles proyectos
*/
#include "alg_GRAFOPMC.h"
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

struct Ciudad{
    double x,y;

    Ciudad(double x_, double y_): x(x_), y(y_){}
};

double DistanciaEuclidea(const Ciudad& A, const Ciudad& B)
{
    return sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2));
}

struct Puente{
    size_t A;
    size_t B;
    double coste;
    Puente(size_t A_=0, size_t B_=0, double c=0): A(A_), B(B_), coste(c){}
};

Puente Grecoland2(const matriz<bool>& Fobos, const matriz<bool>& Deimos, const vector<Ciudad>& CiudadFobos,  const vector<Ciudad>& CiudadDeimos,
const vector<bool>& CosterasFobos, const vector<bool>& CosterasDeimos)
{
    //Hay que construir el grafo lo que pasa que da igual el coste que tenga
    int n1=Fobos.size();
    int n2=Deimos.size();
    int n=n1+n2;
    GrafoP<double> Grecoland(n);

    for(size_t i=0; i<n1; i++)
    {
        for(size_t j=0; j<n1; j++)
        {
            if(Fobos[i][j])
            {
                double distancia=DistanciaEuclidea(CiudadFobos[i], CiudadFobos[j]);

                Grecoland[i][j]=distancia;
            }
        }
    }
    for(size_t i=0; i<n2; i++)
    {
        for(size_t j=0; j<n2; j++)
        {
            if(Deimos[i][j])
            {
                double distancia=DistanciaEuclidea(CiudadDeimos[i], CiudadDeimos[j]);

                Grecoland[i+n1][j+n1]=distancia;
            }
        }
    }

    //Ahora vamos a construir el puente 
    Puente bueno;
    double minimo=GrafoP<double>::INFINITO;

    for(size_t i=0; i<n1; i++)
    {
        for(size_t j=0; j<n2; j++)
        {
            if(CosterasFobos[i] && CosterasDeimos[j])
            {
                //Creamos siempre un aux con el grecoland si los puentes para que cuando meta el puente compare unicamente con ese
                GrafoP<double> aux(Grecoland);
                //Tenemos que meter el puente
                double distancia=DistanciaEuclidea(CiudadFobos[i], CiudadDeimos[j]);
                aux[i][j+n1]=distancia;
                aux[j+n1][i]=distancia;

                //Una vez que tenemos todo Aplicamos Floyd para unir todos los trayectos con el menor coste posible
                matriz<typename GrafoP<double>::vertice> Antecesores(aux.numVert());
                matriz<double> CostesMinimos=Floyd(aux, Antecesores);

                double coste=0;
                for(size_t a=0; a<CostesMinimos.size(); a++)
                {
                    for(size_t b=0; b<CostesMinimos.size(); b++)
                    {
                        coste+=CostesMinimos[a][b];
                    }
                }

                if(coste<minimo)
                {
                    minimo=coste;
                    bueno.A=i;
                    bueno.B=j;
                    bueno.coste=coste;
                }
            }
        }
    }

    return bueno;
}