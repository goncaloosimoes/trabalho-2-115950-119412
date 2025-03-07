//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphAllPairsShortestDistances
//

// Student Name : Gonçalo Simões
// Student Number : 119412
// Student Name : Gonçalo Silva
// Student Number : 115950

/*** COMPLETE THE GraphAllPairsShortestDistancesExecute FUNCTION ***/

#include "GraphAllPairsShortestDistances.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"

#define INDEFINITE -1
#define INFINITO 1000000

struct _GraphAllPairsShortestDistances {
  int** distance;  // The 2D matrix storing the all-pairs shortest distances
                   // It is stored as an array of pointers to 1D rows
                   // Idea: an INDEFINITE distance value is stored as -1
  Graph* graph;
};

// Allocate memory and initialize the distance matrix
// Compute the distances between vertices by running the Bellman-Ford algorithm
GraphAllPairsShortestDistances* GraphAllPairsShortestDistancesExecute(Graph* g) {
  assert(g != NULL);

  // COMPLETE THE CODE

  unsigned int numVertices = GraphGetNumVertices(g);
  
  GraphAllPairsShortestDistances* result = (GraphAllPairsShortestDistances*)malloc(sizeof(struct _GraphAllPairsShortestDistances));
  assert(result != NULL);

  result->graph = g;

  // Alocar memória para a matriz 2D
  result->distance = (int**)malloc(numVertices*sizeof(int*));
  assert(result->distance != NULL);

  for (unsigned int i = 0; i < numVertices; i++) {
    result->distance[i] = (int*)malloc(numVertices*sizeof(int));
    assert(result->distance[i] != NULL);
  }

  // Inicializar a matriz
  for (unsigned int i = 0; i < numVertices; i++){
    for (unsigned int j = 0; j < numVertices; j++) {
      result->distance[i][j] = INDEFINITE;
    }
  }

  for (unsigned int src = 0; src < numVertices; src++) {
    // Executa Bellman-Ford a partir do vértice `src`
    GraphBellmanFordAlg* bellmanFordResult = GraphBellmanFordAlgExecute(g, src);

    for (unsigned int dest = 0; dest < numVertices; dest++) {
        int dist = GraphBellmanFordAlgDistance(bellmanFordResult, dest);
        if (dist != INFINITO && dist >= 0) {
          result->distance[src][dest] = dist;
        }
    }
    
    // Libertar a memória usada pelo resultado de Bellman-Ford
    GraphBellmanFordAlgDestroy(&bellmanFordResult);
  }
  return result;
}

void GraphAllPairsShortestDistancesDestroy(GraphAllPairsShortestDistances** p) {
  assert(*p != NULL);

  GraphAllPairsShortestDistances* aux = *p;
  unsigned int numVertices = GraphGetNumVertices(aux->graph);

  for (unsigned int i = 0; i < numVertices; i++) {
    free(aux->distance[i]);
  }

  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the result

int GraphGetDistanceVW(const GraphAllPairsShortestDistances* p, unsigned int v,
                       unsigned int w) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(w < GraphGetNumVertices(p->graph));

  return p->distance[v][w];
}

// DISPLAYING on the console

void GraphAllPairsShortestDistancesPrint(
    const GraphAllPairsShortestDistances* p) {
  assert(p != NULL);

  unsigned int numVertices = GraphGetNumVertices(p->graph);
  printf("Graph distance matrix - %u vertices\n", numVertices);

  for (unsigned int i = 0; i < numVertices; i++) {
    for (unsigned int j = 0; j < numVertices; j++) {
      int distanceIJ = p->distance[i][j];
      if (distanceIJ == -1) {
        // INFINITY - j was not reached from i
        printf(" INF");
      } else {
        printf(" %3d", distanceIJ);
      }
    }
    printf("\n");
  }
}
