#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"


int main(void) {

  TestInit();
	
  // Variar número de arestas (nº vértices fixo)
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