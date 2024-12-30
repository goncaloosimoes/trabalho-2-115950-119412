//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name : Gonçalo Simões
// Student Number : 119412
// Student Name : Gonçalo Silva
// Student Number : 115950

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

void TestInit2() {
  InstrCalibrate();
  InstrName[0] = "memops";
  InstrName[1] = "dist_comps";
  InstrName[2] = "updates";
  InstrName[3] = "addedEdges";
  InstrName[4] = "reachedVertices";
  InstrName[5] = "reachedChecks";
  InstrName[6] = "comps";
}

#define MEMOPS InstrCount[0] // número operações de acesso à memória
#define ADDED_EDGES InstrCount[3] // número de arestas adicionadas ao grafo
#define REACHED_VERTICES InstrCount[4] // número de vértices alcançados
#define REACHED_CHECKS InstrCount[5] // número de verificações de vértices alcançados
#define COMPS InstrCount[6] // número de comparações totais

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph* GraphComputeTransitiveClosure(Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g));
  assert(GraphIsWeighted(g) == 0);

  // COMPLETE THE CODE

  unsigned int numVertices = GraphGetNumVertices(g);
  MEMOPS++;
  Graph* transitiveClosure = GraphCreate(numVertices, 1, 0); // Digrafo sem pesos
  MEMOPS += 7 + 5*numVertices;

  for (unsigned int i = 0; i < numVertices; i++) {
    COMPS++;
    GraphBellmanFordAlg* bellmanFord = GraphBellmanFordAlgExecute(g, i); // Algoritmo Bellman-Ford para cada vértice

    for (unsigned int v = 0; v < numVertices; v++){
        MEMOPS++;
        REACHED_CHECKS++;
        COMPS+=3;
        if (i != v && GraphBellmanFordAlgReached(bellmanFord, v)) { // i != v porque não há lacetes
            // Se o vértice for alcançado adicionamos ao novo grafo
            GraphAddEdge(transitiveClosure, i, v);
            MEMOPS++;
            ADDED_EDGES++;
            REACHED_VERTICES++;
        }
    }
    GraphBellmanFordAlgDestroy(&bellmanFord); // Eliminar o grafo auxiliar
    MEMOPS++;
  }
  return transitiveClosure;
}
