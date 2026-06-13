#include "alg_GRAFOPMC.h"
#include <vector>
#include <algorithm>

using namespace std;

enum Transporte {
    CARRETERA,
    TREN,
    AVION
};

vector<bool> Ciudades(const GrafoP<double>& Gcarretera,
                      const GrafoP<double>& Gtren,
                      const GrafoP<double>& Gavion,
                      Transporte alergia,
                      double dinero,
                      typename GrafoP<double>::vertice Origen)
{
    const GrafoP<double>* A;
    const GrafoP<double>* B;

    if(alergia == CARRETERA)
    {
        A = &Gtren;
        B = &Gavion;
    }
    else if(alergia == TREN)
    {
        A = &Gcarretera;
        B = &Gavion;
    }
    else
    {
        A = &Gcarretera;
        B = &Gtren;
    }

    vector<typename GrafoP<double>::vertice> P1;
    vector<typename GrafoP<double>::vertice> P2;

    vector<double> D1 = Dijkstra(*A, Origen, P1);
    vector<double> D2 = Dijkstra(*B, Origen, P2);

    vector<bool> ciudades(Gcarretera.numVert(), false);

    for(size_t i = 0; i < Gcarretera.numVert(); i++)
    {
        if(min(D1[i], D2[i]) <= dinero)
        {
            ciudades[i] = true;
        }
    }

    return ciudades;
}