#include <stdio.h>
#include "grafo_matrizadj.h"

bool inicializaGrafo(Grafo* grafo, int nv){
  int i,j;
  if(nv > MAXNUMVERTICES) {
    fprinf(stderr, "Erro na chamada de inicializaGrafo: numero de vertices maior que o permitido de %d. \n", MAXNUMVERTICES);
    return false;
  }
  if(nv <= 0) {
    fprinf(stderr, "Erro na chamada de inicializaGrafo: numero de vertices deve ser positivo. \n");
    return false;
  }
  grafo->numVertices = nv;
  grafo->numArestas = 0;
  for(i = 0, i < grafo->numVertices; i++){
    for(j = 0, j < grafo->numVertices; j++){
      grafo->mat[i][j] = AN;
    }
  }
  return true;
}
