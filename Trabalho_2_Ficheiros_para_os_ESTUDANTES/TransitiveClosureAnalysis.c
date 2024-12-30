#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"
#include "GraphTransitiveClosure.h"


void Teste1();
void Teste2();
void TesteComArvores();

int main(void) {

  TestInit2();

  //Teste1();
	//Teste2();
	TesteComArvores();
	return 0;
}

void GenerateTree(Graph* g) {
	unsigned int numVertices = GraphGetNumVertices(g);
	for (unsigned int i = 1; i < numVertices; i++) {
		unsigned int u = rand() % i;
		GraphAddEdge(g, u, i);
	}
}


void TesteComArvores() {
	unsigned int numVertices = 15;
	for (int j = 0; j < 10; j++) {
		Graph* g = GraphCreate(numVertices, 1, 0);
		GenerateTree(g);
		printf("Tree %d\n", j);
		GraphDisplayDOT(g);
		InstrReset();
		Graph* transitiveClosureResult = GraphComputeTransitiveClosure(g);
		printf("Transitive Closure Tree %d\n", j);
    GraphDisplayDOT(transitiveClosureResult);
    printf("\n");
    printf("Metrics:\n");
    InstrPrint();
    printf("\n");
    GraphDestroy(&transitiveClosureResult);
		GraphDestroy(&g);
	}
	
}


void Teste1() {
	//  Variar número de arestas (nº vértices fixo)
  unsigned int numVertices = 15;
  unsigned int numEdges[] = {0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 210};
  for (int i = 0; i < 12; i++) {
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
    InstrReset();
    Graph* transitiveClosureResult = GraphComputeTransitiveClosure(g);
		printf("Transitive Closure Digraph %d\n", i);
    GraphDisplayDOT(transitiveClosureResult);
    printf("\n");
    printf("Metrics:\n");
    InstrPrint();
    printf("\n");
    GraphDestroy(&transitiveClosureResult);
    GraphDestroy(&g);
	}
}

void Teste2() {
		//  Variar número de vértices (nº arestas fixo)
  unsigned int numVertices[] = {10, 30, 50, 70, 90, 110, 130, 150, 170, 190};
  unsigned int numEdges = 25;
  for (int i = 0; i < 10; i++) {
		unsigned int nV = numVertices[i];
    Graph* g = GraphCreate(nV, 1, 0);
    // Adicionar as arestas
    while (GraphGetNumEdges(g) != numEdges) {
      unsigned int u = rand() % nV;
      unsigned int v = rand() % nV;
      if (u != v) {
        GraphAddEdge(g, u, v);
      }
    }
    printf("=== Digrafo %d ===\n", i);
    GraphDisplayDOT(g);
    InstrReset();
    Graph* transitiveClosureResult = GraphComputeTransitiveClosure(g);
		printf("Transitive Closure Digraph %d\n", i);
    GraphDisplayDOT(transitiveClosureResult);
    printf("\n");
    printf("Metrics:\n");
    InstrPrint();
    printf("\n");
    GraphDestroy(&transitiveClosureResult);
    GraphDestroy(&g);
  }
}