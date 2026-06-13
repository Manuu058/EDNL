#include "alg_GRAFOPMC.h"
#include <vector>
using namespace std;

/*
    Parte del almacen con la maxima carga y al cliente mas proximo
    Si no tiene suficientes para atender le entrega todo y ya lo hara despues
    Si le quedan va al siguiente y marca como completado si no le queda lo marca y se vuelve al almacen 

*/


struct Cliente{
    int cantidad;

    int pedido(){return cantidad;}
    void atender(int c){cantidad-=c;}
};

typename GrafoP<double>::vertice CalcularDestino(const matriz<double>& Reparto,const vector<bool>& ClientesRealizados, 
typename GrafoP<double>::vertice actual)
{
    double distMaxima=GrafoP<double>::INFINITO;

    typename GrafoP<double>::vertice destino;
    for(size_t i=0; i<Reparto.size();i++)
    {
        if(!ClientesRealizados[i] && distMaxima>Reparto[actual][i])
        {
            distMaxima=Reparto[actual][i];
            destino= i;
        }
    }

    return destino;
}

double DistanciaTotal(const GrafoP<double>& Reparto, int CapacidadMaxima, vector<Cliente>& Clientes, 
    typename GrafoP<double>::vertice almacen)
{
    //Declaramos variables de seguimiento 
    typename GrafoP<double>::vertice actual=almacen;
    int cargaActual=CapacidadMaxima;
    vector<bool> ClientesRealizados(Clientes.size(), false);
    ClientesRealizados[almacen]=true;

    int contador=0;
    for(size_t i=0; i<ClientesRealizados.size();i++)
    {
        if(!ClientesRealizados[i])
        {
            contador++;
        }
    }

    //Usamos Floyd para que una todos con todos con el menor coste
    matriz<typename GrafoP<double>::vertice> Antecesores(Reparto.numVert());
    matriz<double> CostesMinimos=Floyd(Reparto, Antecesores);

    double kilometros=0;
    while(contador>0)
    {
        typename GrafoP<double>::vertice destino=CalcularDestino(CostesMinimos, ClientesRealizados, actual);

        //Vamos para alli
        kilometros+=CostesMinimos[actual][destino];
        actual=destino;
        int ped=Clientes[actual].pedido();

        if(ped>cargaActual)
        {
            Clientes[actual].atender(cargaActual);
            kilometros+=CostesMinimos[actual][almacen];
            actual=almacen;
            cargaActual=CapacidadMaxima;
        }
        else{
            ClientesRealizados[actual]=true;
            contador--;
            if(ped<cargaActual)
            {
                Clientes[actual].atender(ped);
            }
            else{
                Clientes[actual].atender(cargaActual);
                kilometros+=CostesMinimos[actual][almacen];
                actual=almacen;
                cargaActual=CapacidadMaxima;
            }
        }
    }

    return kilometros;
}