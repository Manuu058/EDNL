//lo primero qeu haremos sera guaradr en un vector los pedidos restantes para cada cliente

template <typename T>
vector<int> ped(const Grafo<T>& A){
    vector<int> vec(A.NumVert());
    vec[0]=0; //almacen

    for(int i=1; i<A.numVert(); i++){
        vec[i]=pedido(i);
    }

    return vec;
}


bool faltanpedidos(vector<int> a){
    int suma=0;
    for(int i=0; i<a.size(); i++){
        suma+=a[i];
    }
    if(suma!=0){
        return true;
    }else{
        return false;
    }
}

template <typename T>

T distanciatotal(const Grafo<T>& A, int capacidad){

    vector<int> pedidosporcliente=ped(A);

    int almacen=0; //indice del almacen
    int copiacapacidad=capacidad;
    T suma=0;
    //aplicamos floyd al grafo para conocer el punto mas corto desde el qeu partp
    matriz<typename Grafo<T>::vertice> vert(A.NumVert());
    matriz<T> coste(A.NumVert());
    coste=floyd(A,vert);

    while(faltanpedidos(pedidosporcliente)){

        int actual=0; //partimos desde el almacen
        copiacapacidad=capacidad;

        while(copiacapacidad>0 && faltanpedidos(pedidosporcliente)){//mientras tengamos para repartir seguimos

            //buscamos punto mas cercano a actual que tenga pedidos
            T distancia=Grafo<T>::INFINITO;
            int proximo;
            for(int i=1; i<A.NumVert(); i++){
                if(pedidosporcliente[i]>0 && i!=actual){
                    if(coste[actual][i]<distancia){
                        distancia=coste[actual][i];
                        proximo=i;
                    }
                }
            }
            
            if(pedidosporcliente[proximo]>copiacapacidad){
                pedidosporcliente[proximo]-=copiacapacidad;
                copiacapacidad=0;
            }else{
                if(pedidosporcliente[proximo]<copiacapacidad){
                    copiacapacidad-=pedidosporcliente[proximo];
                    pedidosporcliente[proximo]=0;
                }else{
                    pedidosporcliente[proximo]=0;
                    copiacapacidad=0;
                }
            }

            suma+=coste[actual][proximo];

            actual=proximo; //en el caso de no tener capacidad sale del bucle y se actualiza a 0;
            //no pongo la matriz a infinito cuando ya hemos entregado en ese punto porque al selecionar el camino mas corto mirop si le
            //quedan pedidos

        }

        suma+=coste[actual][almacen]; //preguntar al profesor si una vez que esten todo repartidos debemos de volver al almacen, en ese
        //caso implementar un if aqui que si qeudan cliente por servir se sume


    }


    return suma;

}
