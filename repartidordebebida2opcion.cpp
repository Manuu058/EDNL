
//obtenemos ruta mas corta desde el punto actual
int rutamascercana(matriz<double>& B, int origen, vector<bool>& clientespedidos){

    double dist=Grafo<double>::INFINITO;
    int indice=0;
    for(int i=1; i<B.size(); i++){
        if(!clientespedidos[i] && B[origen][i]<dist){
            dist=B[origen][i];
            indice=i;
        }
    }

    return indice;
}

bool comprobar(vector<bool>& clientespedidos){
    for(int i=1; i<clientespedidos.size(); i++){
        if(clientespedidos[i]==false){
            return false
        }
    }
    return true;
}


double repartidor(const Grafo<double>& A, int capacidad){

    matriz<typename Grafo<double>::vertice> vert(A.NumVert());
    matriz<double> coste(A.NumVert());
    coste=floyd(A,vert);

    vector<bool> clientespedidos(A.NumVert(), false);
    clientespedidos[0]=true;

    vector<int> pedidosrestantes(A.NumVert(), 0);
    vector<bool> visitado(A.NumVert(), false); // para distinguir "primera visita"

    double suma=0;
    int copiacapacidad=capacidad;
    int almacen=0;
    int actual=almacen;

    while(!comprobar(clientespedidos)){

        actual=almacen;
        copiacapacidad=capacidad;

        while(copiacapacidad>0 && !comprobar(clientespedidos)){

            int proximo=rutamascercana(coste, actual, clientespedidos);

            suma+=coste[actual][proximo];
            actual=proximo;

            if(!visitado[proximo]){
                pedidosrestantes[proximo]=pedido();
                visitado[proximo]=true;
            }

            if(pedidosrestantes[proximo]>=copiacapacidad){
                pedidosrestantes[proximo]-=copiacapacidad;
                copiacapacidad=0;
            }else{
                copiacapacidad-=pedidosrestantes[proximo];
                pedidosrestantes[proximo]=0;
            }

            if(pedidosrestantes[proximo]==0){
                clientespedidos[proximo]=true;
                
            }
        }

        suma+=coste[actual][almacen];

    }

    return suma;
}