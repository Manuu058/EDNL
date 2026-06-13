
template <typename T>

matriz<T> toxicidad(const Grafo<T>& zuelandia, size_t capital){

    Grafo<T> copia(zuelandia);

    //como nos dice qeu no podemos pasar por zuelandia como ciudad inetremdia pondremos tanto los caminos
    //de salida y de entrada a infinito.

    for(size_t i=0; i<copia.NumVert(); i++){
        if(i!=capital){
            copia[i][capital]=copia[capital][i]=Grafo<T>::INFINITO;
        }
    }

    //ahora lo que haremos sera floyd para obtener los caminos minimos entre cada par de ciudades

    matriz<typename Grafo<T>::vertices> vert(copia.NumVert());
    matriz<T> coste(copia.NumVert());

    coste=floyd(copia,vert); 

    //una vez construido floyd sintener como intermediario a la cpaital ahora lo que habar que hacer es hacer djkistra para montar 
    //los camimos que tiene como origen o destino la capital, para esto hacemos djkistra

    vector<typename Grafo<T>::vertices> antecesores(copia.NumVert());
    vector<T> costecapital(copia.NumVert());

    costecapital=dijistra(zuelandia, capital, antecesores);
    //como es un grafo no dirigo no hace falta hacer djkistra inverso ya que seran iguales los caminos

    for(size_t i=0; i<copia.NumVert(); i++){
        if(i!=capital){
            coste[i][capital]=coste[capital][i]=costecapital[i];
        }
    }

    coste[capital][capital] = 0;

    return coste; //esto creo qeu no esta bien ya qeu nos pide los caminos resultantes 

}