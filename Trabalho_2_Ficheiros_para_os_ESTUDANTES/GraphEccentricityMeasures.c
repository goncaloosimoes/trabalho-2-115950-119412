//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name : Gonçalo Simões
// Student Number : 115950
// Student Name : Gonçalo Silva
// Student Number : 115950

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"

#define INFINITE 1000000

struct _GraphEccentricityMeasures {
  unsigned int*
      centralVertices;  // centralVertices[0] = number of central vertices
                        // array size is (number of central vertices + 1)
  int* eccentricity;    // the eccentricity value of each vertex
  Graph* graph;         // the graph
  int graphRadius;      // the graph radius
  int graphDiameter;    // the graph diameter
};

// Função para calcular a excentricidade de um grafo
static int* GraphComputeEccentricity(const GraphAllPairsShortestDistances* p, unsigned int numVertices) {
  assert(p != NULL);

  int* eccentricityValues = (int*)malloc(numVertices * sizeof(int));
  assert(eccentricityValues != NULL);

  int maxDistance;
  // Para cada vértice (linha)
  for (unsigned int v = 0; v < numVertices; v++) {    
    maxDistance = -1; // vértices não alcançáveis
    for (unsigned int u = 0; u < numVertices; u++) {
      // Para cada vértice (coluna)
      int distance = GraphGetDistanceVW(p, v, u); // distância de v a u
      if (distance == -1) continue; // ignorar vértices não alcançáveis
      if (distance > maxDistance) {
        // Se a distância entre v e u for menor que a maior distância pré-definida, atualizamos
        maxDistance = distance;
      }
    }
    eccentricityValues[v] = maxDistance; // Armazenamos o maior valor encontrado (excentricidade)
  }
  return eccentricityValues;
}

// Função para calcular o raio de um grafo
static int GraphComputeRadius(int* eccentricityValues, unsigned int numVertices) {
  assert(eccentricityValues != NULL);
  
  int radius = INFINITE;
  for (unsigned int v = 0; v < numVertices; v++) {
    int eccentricity = eccentricityValues[v];
    if (eccentricity != -1 && eccentricity < radius) {
      radius = eccentricity;
    }
  }
  return radius == INFINITE ? -1 : radius;
}

// Função para calcular o diâmetro de um grafo
static int GraphComputeDiameter(int* eccentricityValues, unsigned int numVertices) {
  assert(eccentricityValues != NULL);

  int diameter = -1;

  for (unsigned int v = 0; v < numVertices; v++) {
    int eccentricity = eccentricityValues[v];
    if (eccentricity != -1 && eccentricity > diameter) {
      diameter = eccentricity;
    }
  }
  return diameter;
}

// Função para calcular so vértices centrais de um grafo
static unsigned int* GraphComputeCentralVertices(int* eccentricityValues, int radius, unsigned int numVertices) {
  assert(eccentricityValues != NULL);

  if (radius == -1) {
    unsigned int* emptyArr = (unsigned int*)malloc(sizeof(unsigned int));
    assert(emptyArr != NULL);
    emptyArr[0] = 0; // não há vértices centrais
    return emptyArr;
  }

  unsigned int numCentralVertices = 0;

  // Contagem do número de vértices para alocar
  for (unsigned int v = 0; v < numVertices; v++) {
    if (eccentricityValues[v] == radius) {
      numCentralVertices++;
    }
  }

  unsigned int* centralVertices = (unsigned int*)malloc((numCentralVertices + 1) * sizeof(unsigned int));
  assert(centralVertices != NULL);

  centralVertices[0] = numCentralVertices;

  unsigned int i = 1;
  for (unsigned int v = 0; v < numVertices; v++) {
    if (eccentricityValues[v] == radius) {
      centralVertices[i++] = v;
    }
  }
  
  return centralVertices;
}

// Allocate memory
// Compute the vertex eccentricity values
// Compute graph radius and graph diameter
// Compute the set of central vertices
GraphEccentricityMeasures* GraphEccentricityMeasuresCompute(Graph* g) {
  assert(g != NULL);

  // COMPLETE THE CODE
  // CREATE AUXILIARY (static) FUNCTIONS, IF USEFUL
  // Do not forget that -1 represents an IDEFINITE value

  GraphAllPairsShortestDistances* distancesMatrix = GraphAllPairsShortestDistancesExecute(g);
  unsigned int numVertices = GraphGetNumVertices(g);

  int* eccentricityValues = GraphComputeEccentricity(distancesMatrix, numVertices);

  GraphEccentricityMeasures* result = (GraphEccentricityMeasures*)malloc(sizeof( struct _GraphEccentricityMeasures));
  assert(result != NULL);

  result->graph = g;
  result->eccentricity = eccentricityValues;

  // Graph radius --- the smallest vertex eccentricity value
  int radius = GraphComputeRadius(eccentricityValues, numVertices);
  result->graphRadius = radius;

  // Graph diameter --- the largest vertex eccentricity value
  result->graphDiameter = GraphComputeDiameter(eccentricityValues, numVertices);

  // Computing the set of central vertices
  // Allocate the central vertices array : number of central vertices + 1
  // Fill in the central vertices array
  result->centralVertices = GraphComputeCentralVertices(eccentricityValues, radius, numVertices);

  GraphAllPairsShortestDistancesDestroy(&distancesMatrix);

  return result;
}

void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures** p) {
  assert(*p != NULL);

  GraphEccentricityMeasures* aux = *p;

  free(aux->centralVertices);
  free(aux->eccentricity);

  free(*p);
  *p = NULL;
}

// Getting the computed measures

int GraphGetRadius(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures* p,
                               unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(p->eccentricity != NULL);

  return p->eccentricity[v];
}

unsigned int* GraphGetCentralVertices(const GraphEccentricityMeasures* p) {
    assert(p != NULL);              // Verifica se o ponteiro p não é NULL
    assert(p->centralVertices != NULL); // Verifica se o campo centralVertices não é NULL

    // Alocar memória para o array de vértices centrais
    int numCentralVertices = p->centralVertices[0];
    unsigned int* centralVerticesCopy = (unsigned int*)malloc((numCentralVertices + 1) * sizeof(unsigned int));
    if (centralVerticesCopy == NULL) {
        return NULL; // Falha na alocação de memória
    }

    // O primeiro elemento será o número de vértices centrais
    centralVerticesCopy[0] = numCentralVertices;

    // Copiar os vértices centrais para o novo array
    for (int i = 1; i <= numCentralVertices; i++) {
        centralVerticesCopy[i] = p->centralVertices[i];
    }

    return centralVerticesCopy;  // Retorna o ponteiro para a cópia dos vértices centrais
}


void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
  // COMPLETE THE CODE
  int radius = GraphGetRadius(p);
  int diameter = GraphGetDiameter(p);
  unsigned int* centralVertices = GraphGetCentralVertices(p);

  // Print the graph radius and diameter
  printf("Radius: %d, Diameter: %d\n", radius, diameter);
  printf("-----------\n");

  // Print the vertex eccentricity values
  unsigned int numVertices = GraphGetNumVertices(p->graph); // retorna o total de vértices existentes no grafo
  for (unsigned int i = 0; i < numVertices ; i++) {
    // para cada vértice i é calculada a excentricidade
    int eccentricity = GraphGetVertexEccentricity(p, i);
    printf("Eccentricity of vertice %d -> %d\n", i, eccentricity);
  }
  printf("-----------\n");

  // Print the set of central vertices
  if (centralVertices != NULL) {
    if (centralVertices[0] > 1) {
      printf("%d Central vertices: ", centralVertices[0]);
    }
    else {
      printf("%d Central vertice: ", centralVertices[0]);
    }
    // printf("%d", centralVertices[0]);
    for (unsigned int i = 1; i <= centralVertices[0]; i++) {
      printf("%d ", centralVertices[i]);
    }
  }
  else {
    printf("Central Vertices: NULL");
  }
  printf("\n\n");

  free(centralVertices);
}
