struct casila{
    int fila,columna;
};

struct resultado{
    bool seguro;
    int coste;
};

resultado fauno(int n, int m, const vector<casilla> trampa, const vector<casilla> caballeros){

    //creramos el grafo de las dimensiones descritas
    Grafo<int> g(n*m);

    //ponemos en 1 los posibles movimientos del caballo

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            Grafo<int>::vertice actual=convertir(i,j,m);

            if(i+2<n && j+1<m){
                g[actual][convertir(i+2,j+1,m)]=g[convertir(i+2,j+1,m)][actual]=1;
            }
            if(i+1<n && j+2<m){
                g[actual][convertir(i+1,j+2,m)]=g[convertir(i+1,j+2,m)][actual]=1;
            }
            if(i-1>=0 && j+2<m){
                g[actual][convertir(i-1,j+2,m)]=g[convertir(i-1,j+2,m)][actual]=1;
            }
            if(i-21>=0 && j+1<m){
                g[actual][convertir(i-2,j+1,m)]=g[convertir(i-2,j+1,m)][actual]=1;
            }
            if(i+1<n && j-2>=0){
                g[actual][convertir(i+1,j-2,m)]=g[convertir(i+1,j-2,m)][actual]=1;
            }
            if(i+2<n && j-1>=0){
                g[actual][convertir(i+2,j-1,m)]=g[convertir(i+2,j-1,m)][actual]=1;
            }
            if(i-1>=0 && j-2>=0){
                g[actual][convertir(i-1,j-2,m)]=g[convertir(i-1,j-2,m)][actual]=1;
            }
            if(i-2>=0 && j-1>=0){
                g[actual][convertir(i-2,j-1,m)]=g[convertir(i-2,j-1,m)][actual]=1;
            }
        }
    }

    //ponemos a infinito las casilla trampa

    for(casilla c:trampa){
        Grafo<int>::vertice t=convertir(c.fila,c.columna,m);
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                g[t][convertir(i,j,m)]=g[convertir(i,j,m)][t]=infinito;
            }
        } 
    }

    //ponemos los moviminetos de los caballeros los cuales matan si esatan en una casilla que los rodea y no si estas en la casilla justo

    for(casilla c:caballeros){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(c.fila-1>=0 && c.columna-1>=0){
                    g[convertir(c.fila-1,c.columna-1,m)][convertir(i,j,m)]=g[convertir(i,j,m)][convertir(c.fila-1,c.columna-1,m)]=infinito;
                }
                if(c.fila-1>=0){
                    g[convertir(c.fila-1,c.columna,m)][convertir(i,j,m)]=g[convertir(i,j,m)][convertir(c.fila-1,c.columna,m)]=infinito;
                }
                if(c.fila-1>=0 && c.columna+1<m){
                    g[convertir(c.fila-1,c.columna+1,m)][convertir(i,j,m)]=g[convertir(i,j,m)][convertir(c.fila-1,c.columna+1,m)]=infinito;
                }
                if(c.columna-1>=0){
                    g[convertir(c.fila,c.columna-1,m)][convertir(i,j,m)]=g[convertir(i,j,m)][convertir(c.fila,c.columna-1,m)]=infinito;
                }
                if(c.columna+1<m){
                    g[convertir(c.fila,c.columna+1,m)][convertir(i,j,m)]=g[convertir(i,j,m)][convertir(c.fila,c.columna+1,m)]=infinito;
                }
                if(c.fila+1<n && c.columna-1>=0){
                    g[convertir(c.fila+1,c.columna-1,m)][convertir(i,j,m)]=g[convertir(i,j,m)][convertir(c.fila+1,c.columna-1,m)]=infinito;
                }
                if(c.fila+1<n){
                    g[convertir(c.fila+1,c.columna,m)][convertir(i,j,m)]=g[convertir(i,j,m)][convertir(c.fila+1,c.columna,m)]=infinito;
                }
                if(c.fila+1<n && c.columna+1<m){
                    g[convertir(c.fila+1,c.columna+1,m)][convertir(i,j,m)]=g[convertir(i,j,m)][convertir(c.fila+1,c.columna+1,m)]=infinito;
                }
                
            }
        } 
    }

    vector<Grafo<int>::vertice> antecesores(g.NumVert());

    vector<int> r=djikstra(g,convertir(0,0,m),antecesores);

    resultado res;
    if(r[convertir(n-1,m-1,m)]!=infinito){
        res.seguro=true;
    }else{
        res.seguro=false;
    }
    res.coste=r[convertir(n-1,m-1,m)];

    return res;

}

//dunion que convierte las filas y columnas en nodos 
//siempre debo multiplicar por el numero de columnas en este caso como las dimesiones son n*m deboi multiplicar por m
//tambien es importante saber que tengo que multiplicar las filas y sumar siempre las columnas

Grafo<int>::vertice convertir(int f,int c, int m){
    return f*m + c;
}