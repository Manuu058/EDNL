struct carretera{
    size_t origen;
    size_t destino;
};

template <typename T>

matriz<T> ciudadesrebeldes(Grafo<T>& G,vector<size_t>& ciudadestomadas, vector<carreteras>& carreterastomadas, size_t capital){

    //hacemos copia del grafo

    Grafo<T> copia=G;

    //ponemos tanta las carreteras como las ciudaes que han sido tomadas a infinito

    for(size_t i:ciudadestomadas){
        for(size_t j=0; j<copia.NumVert(); j++){
            if(i!=j){
                copia[j][i]=Abin<T>::INFINITO;
            }
        }
    }

    for(const carreteras& c:carreterastomadas){
        copia[c.origen][c.destino]=Abin<T>::INFINITO;
    }

    vector<typename Abin<T>::vertice> antecesores(copia.NumVert());
    vector<typename Abin<T>::vertice> antecesoresInv(copia.NumVert());
    vector<T> capitalavertices(copia.NumVert());
    vector<T> verticesacapital(copia.NumVert());

    capitalavertices=djkistra(copia, capital, antecesores);
    verticesacapital=djkistraInv(copia, capital, antecesoresInv);

    //recorremos la matriz de floyd y le sumamos a cada traslado el coste de ir a la ciudad y salir de ella

    matriz<T> final(copia.NumVert());


    for(size_t i=0; i<copia.NumVert(); i++){
        for(size_t j=0; j<copia.NumVert(); j++){
            if(i==j){
                final[i][j]=0;
            }else{
                if(verticesacapital[i]==Abin<T>::INFINITO || capitalavertices[j]==Abin<T>::INFINITO){
                    final[i][j]=INFINITO;
                }else{
                    final[i][j]=verticesacapital[i]+capitalavertices[j];
                }
            }
        }
    }

    return final;

}


template <typename T>
vector<T> djkistraInv(const GrafoP<T>& G, size_t c, vector<typename Abin<T>::vertice>& ant)
{
    GrafoP<T> Inv(G.numVert());

    for (size_t i = 0; i < G.numVert(); ++i) {
        for (size_t j = 0; j < G.numVert(); ++j) {
            Inv[i][j] = G[j][i];
        }
    }

    return djkistra(Inv, c, ant);
}