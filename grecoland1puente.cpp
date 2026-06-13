struct coordenadas{
    double x;
    double y;
};

struct solucion{
    size_t origen;
    size_t destino;
    double coste;
};

double euclidea(coordenadas a, coordenadas b){
    return sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2));
}


solucion grecoland(const matriz<bool>& adyfobos, const matriz<bool>& adydeimos, const vector<coordenadas>& carrefobos, const 
                    vector<coordenadas>& carredeimos, const vector<size_t>& cfobos, const vector<size_t>& cdeimos){

                    //hacemos 2 grafos uno por cada isla y calculamos sus carreteras

                    size_t nf=carrefobos.size();
                    size_t nd=carredeimos.size();
                    Grafo<double> Fobos(nf);
                    Grafo<double> Deimos(nd);

                    //reconstruimos fobos

                    for(size_t i=0; i<nf; i++){
                        for(size_t j=0; j<nf; j++){
                            if(i==j){ //misma ciudad
                                Fobos[i][j]=0;
                            }else{
                                if(adyfobos[i][j]){//existe carretera
                                    double distancia=euclidea(carrefobos[i],carrefobos[j]);
                                    Fobos[i][j]=distancia;
                                }else{
                                    Fobos[i][j]=Grafo<double>::INFINITO
                                }
                            }
                        }
                    }

                    //reconstruimos deimos
                    for(size_t i=0; i<nd; i++){
                        for(size_t j=0; j<nd; j++){
                            if(i==j){ //misma ciudad
                                Deimos[i][j]=0;
                            }else{
                                if(adydeimos[i][j]){//existe carretera
                                    double distancia=euclidea(carredeimos[i],carredeimos[j]);
                                    Deimos[i][j]=distancia;
                                }else{
                                    Deimos[i][j]=Grafo<double>::INFINITO;
                                }
                            }
                        }
                    }

                    //una vez construido los grafos calculamos floyd en cada grafdo ya que los caminos de cada isla seran constnates
                    //independienetemente del puenete que elijamos
                    matriz<typename Grafo<double>::vertices> vertf(nf);
                    matriz<typename Grafo<double>::vertices> vertd(nd);
                    matriz<double> costefobos(nf);
                    matriz<double> costedeimos(nd);
                    costefobos=floyd(Fobos,vertf);
                    costedeimos=floyd(Deimos,vertd);

                    //ahora buscamso el puente entre las ciudades costeras
                    solucion sol;
                    double minimo=INFINITO;
                    for(size_t i:cfobos){
                        for(size_t j:cdeimos){
                           double puente=euclidea(carrefobos[i],carredeimos[j]);
                            double actual=0;
                            //como nd y nf no tiene poruqer ser iguales habra que hacer 2 bucles para recorres ambos floyds
                            for(size_t k=0; k<nf; k++){
                                for(size_t h=0; h<nd; h++){
                                    actual+=costefobos[k][i]+puente+costedeimos[j][h];
                                }
                            }

                            if(actual<minimo){
                                sol.origen=i;
                                sol.destino=j;
                                sol.coste=puente;
                                minimo=puente;
                            }
                        }
                    }

                    return sol;

                    }