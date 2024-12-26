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

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph* GraphComputeTransitiveClosure(Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g));
  assert(GraphIsWeighted(g) == 0);

  // COMPLETE THE CODE

  unsigned int numVertices = GraphGetNumVertices(g);
  Graph* transitiveClosure = GraphCreate(numVertices, 1, 0); // Digrafo sem pesos

  for (unsigned int i = 0; i < numVertices; i++) {

    GraphBellmanFordAlg* bellmanFord = GraphBellmanFordAlgExecute(g, i); // Algoritmo Bellman-Ford para cada vértice

    for (unsigned int v = 0; v < numVertices; v++){
        if (GraphBellmanFordAlgReached(bellmanFord, v)) {
            // Se o vértice for alcançado adicionamos ao novo grafo
            GraphAddEdge(transitiveClosure, i, v);
        }
    }
    GraphBellmanFordAlgDestroy(&bellmanFord); // Eliminar o grafo auxiliar
  }
  return transitiveClosure;
}
