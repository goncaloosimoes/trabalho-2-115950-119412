#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

void Teste1();
void Teste2();


int main(void) {

  TestInit();
  //Teste1();
  Teste2();
  return 0;
}

void Teste1() {

  //  Variar número de arestas (nº vértices fixo)
  unsigned int numVertices = 6;
  unsigned int numEdges[] = {5, 10, 15, 20, 25, 30};
  for (int i = 0; i < 6; i++) {
    Graph* g = GraphCreate(numVertices, 1, 0);
    unsigned int nEdges = numEdges[i];
    // Adicionar as arestas
    while (GraphGetNumEdges(g) != nEdges) {
      unsigned int u = rand() % numVertices;
      unsigned int v = rand() % numVertices;
      if (u != v) {
        GraphAddEdge(g, u, v);
      }
    }
    printf("=== Digrafo %d ===\n", i);
    GraphDisplayDOT(g);
    // Algortimo Belman-Ford
    for (unsigned int k = 0; k < numVertices; k++) {
      InstrReset();
      GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(g, k);
      printf("The shortest path tree rooted at %u\n", k);
      GraphBellmanFordAlgDisplayDOT(BF_result);
      printf("\n");
      printf("Metrics:\n");
      InstrPrint();
      printf("\n");
      GraphBellmanFordAlgDestroy(&BF_result);
    }
    GraphDestroy(&g);
  }
}

void Teste2() {

  // Variar o número de vértices (nº arestas fixo)
  unsigned int numEdges = 15;
  unsigned int numVertices[] = {6, 8, 10, 12, 14, 16};
  for (int i = 0; i < 6; i++) {
    unsigned int nVertices = numVertices[i];
    Graph* g = GraphCreate(nVertices, 1, 0);
    // Adicionar as arestas
    while (GraphGetNumEdges(g) != numEdges) {
      unsigned int u = rand() % nVertices;
      unsigned int v = rand() % nVertices;
      if (u != v) {
        GraphAddEdge(g, u, v);
      }
    }
    printf("=== Digrafo %d ===\n", i);
    GraphDisplayDOT(g);
    // Algoritmo de Bellman-Ford
    for (unsigned int k = 0; k < nVertices; k++) {
      InstrReset();
      GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(g, k);
      printf("The shortest path tree rooted at %u\n", k);
      GraphBellmanFordAlgDisplayDOT(BF_result);
      printf("\n");
      printf("Metrics:\n");
      InstrPrint();
      printf("\n");
      GraphBellmanFordAlgDestroy(&BF_result);
    }
    GraphDestroy(&g);
  } 
}