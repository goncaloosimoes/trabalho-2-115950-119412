//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphBellmanFord - Bellman-Ford Algorithm
//

// Student Name : Gonçalo Simões
// Student Number : 119412
// Student Name : Gonçalo Silva
// Student Number : 115950

/*** COMPLETE THE GraphBellmanFordAlgExecute FUNCTION ***/

#include "GraphBellmanFordAlg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "IntegersStack.h"
#include "instrumentation.h"

#define INFINITO 1000000

void TestInit() {
  InstrCalibrate();
  InstrName[0] = "memops"; // 
  InstrName[1] = "dist_comps";
  InstrName[2] = "updates";
  InstrName[6] = "comps";
}

#define MEMOPS InstrCount[0] // número operações de acesso à memória
#define DIST_COMPS InstrCount[1] // número de comparações entre distâncias
#define UPDATES InstrCount[2] // número de atualizações dos arrays marked, distance e predecessor
#define COMPS InstrCount[6] // número de comparações totais

struct _GraphBellmanFordAlg {
  unsigned int* marked;  // To mark vertices when reached for the first time
  int* distance;  // The number of edges on the path from the start vertex
                  // distance[i]=-1, if no path found from the start vertex to i
  int* predecessor;  // The predecessor vertex in the shortest path
                     // predecessor[i]=-1, if no predecessor exists
  Graph* graph;
  unsigned int startVertex;  // The root of the shortest-paths tree
};

GraphBellmanFordAlg* GraphBellmanFordAlgExecute(Graph* g, unsigned int startVertex) {
  assert(g != NULL);
  assert(startVertex < GraphGetNumVertices(g));
  assert(GraphIsWeighted(g) == 0);

  GraphBellmanFordAlg* result = (GraphBellmanFordAlg*)malloc(sizeof(struct _GraphBellmanFordAlg));
  assert(result != NULL);

  // Given graph and start vertex for the shortest-paths
  result->graph = g;
  result->startVertex = startVertex;

  unsigned int numVertices = GraphGetNumVertices(g);

  //
  // TO BE COMPLETED !!
  //
  // CREATE AND INITIALIZE
  result->marked = (unsigned int*)malloc(numVertices*sizeof(unsigned int));
  result->distance = (int*)malloc(numVertices*sizeof(int));
  result->predecessor = (int*)malloc(numVertices*sizeof(int));
  
  assert(result->marked != NULL);
  assert(result->distance != NULL);
  assert(result->predecessor != NULL);

  // Inicialização das estruturas
  for (unsigned int i = 0; i < numVertices; i++) {
    result->marked[i] = 0;
    result->predecessor[i] = -1;
    result->distance[i] = INFINITO;
  }

  // A distância ao vértice inicial é 0
  result->distance[startVertex] = 0;
  result->marked[startVertex] = 1;
  
  // THE ALGORTIHM TO BUILD THE SHORTEST-PATHS TREE
  
  for (unsigned int i = 0; i < numVertices-1; i++) {
    COMPS++;
    for (unsigned int u = 0; u < numVertices; u++) {
      if (result->distance[u] == INFINITO) continue; // Ignora vértices não alcançáveis
      COMPS+=2;
      unsigned int* adjacents = GraphGetAdjacentsTo(g, u);
      unsigned int numAdjacents = adjacents[0]; // número vértices adjacentes
      MEMOPS += 3 + 3*numAdjacents + 2;
      for (unsigned int k = 1; k <= numAdjacents; k++) {
        unsigned int v = adjacents[k];
        DIST_COMPS++; COMPS+=2;
        MEMOPS+=3;
        if (result->distance[u] + 1 < result->distance[v]) {
          result->distance[v] = result->distance[u]+1;
          result->predecessor[v] = u;
          result->marked[v] = 1; // Marca o vértice como alcançado
          UPDATES+=3;
          MEMOPS+=4;
        }
      }
      free(adjacents); // Liberta a memória dos vértices adjacentes
    }
  }
  return result;
}

void GraphBellmanFordAlgDestroy(GraphBellmanFordAlg** p) {
  assert(*p != NULL);

  GraphBellmanFordAlg* aux = *p;

  free(aux->marked);
  free(aux->predecessor);
  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the paths information

int GraphBellmanFordAlgReached(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

int GraphBellmanFordAlgDistance(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->distance[v];
}
Stack* GraphBellmanFordAlgPathTo(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0) {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current]) {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBellmanFordAlgShowPath(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = GraphBellmanFordAlgPathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

// Display the Shortest-Paths Tree in DOT format
void GraphBellmanFordAlgDisplayDOT(const GraphBellmanFordAlg* p) {
  assert(p != NULL);

  Graph* original_graph = p->graph;
  unsigned int num_vertices = GraphGetNumVertices(original_graph);

  // The paths tree is a digraph, with no edge weights
  Graph* paths_tree = GraphCreate(num_vertices, 1, 0);

  // Use the predecessors array to add the tree edges
  for (unsigned int w = 0; w < num_vertices; w++) {
    // Vertex w has a predecessor vertex v?
    int v = p->predecessor[w];
    if (v != -1) {
      GraphAddEdge(paths_tree, (unsigned int)v, w);
    }
  }

  // Display the tree in the DOT format
  GraphDisplayDOT(paths_tree);

  // Housekeeping
  GraphDestroy(&paths_tree);
}
