//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name : Luis Tojal
// Student Number : 119636
// Student Name : Diogo Duarte
// Student Number : 120482

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"

struct _GraphEccentricityMeasures {
  unsigned int*
      centralVertices;  // centralVertices[0] = number of central vertices
                        // array size is (number of central vertices + 1)
  int* eccentricity;    // the eccentricity value of each vertex
  Graph* graph;         // the graph
  int graphRadius;      // the graph radius
  int graphDiameter;    // the graph diameter
};




// Auxiliar Functions

// Function to compute eccentricity of each vertex and graph radius & diameter
static void computeEccentricities(Graph* g, GraphAllPairsShortestDistances* allPairsDist, int* eccentricity, int* graphRadius, int* graphDiameter) {
    unsigned int numbVertex = GraphGetNumVertices(g);
    *graphRadius = -1;  // Start with -1 (infinite)
    *graphDiameter = -1;  // Start with -1 (infinite)

    for (unsigned int i = 0; i < numbVertex; i++) {
        int maxDist = -1;

        // Find the maximum distance to any other vertex for eccentricity
        for (unsigned int j = 0; j < numbVertex; j++) {
          if (i == j) continue; // skip self comparisons
          
          int dist = GraphGetDistanceVW(allPairsDist, i, j);
          if (dist != -1) {  // Only consider reachable vertices
              maxDist = (dist > maxDist) ? dist : maxDist;
          }
        }

        eccentricity[i] = (maxDist == -1) ? -1 : maxDist;

        // Update graph radius and diameter
        if (maxDist != -1) {
            if (*graphRadius == -1 || maxDist < *graphRadius) {
                *graphRadius = maxDist;
            }
            if (maxDist > *graphDiameter) {
                *graphDiameter = maxDist;
            }
        }
    }
}

// Function to compute central vertices (those whose eccentricity equals the radius)
static void computeCentralVertices(int* eccentricity, int graphRadius, unsigned int numbVertex, unsigned int* centralVertices) {
    unsigned int numCentralVertices = 0;
    for (unsigned int i = 0; i < numbVertex; i++) {
        if (eccentricity[i] == graphRadius) {
            centralVertices[numCentralVertices + 1] = i;  
            numCentralVertices++;
        }
    }
    centralVertices[0] = numCentralVertices;  
}

// Allocate memory
// Compute the vertex eccentricity values
// Compute graph radius and graph diameter
// Compute the set of central vertices
GraphEccentricityMeasures* GraphEccentricityMeasuresCompute(Graph* g) {
  assert(g != NULL);

  // COMPLETE THE CODE
  // CREATE AUXILIARY (static) FUNCTIONS, IF USEFUL
  // Graph radius --- the smallest vertex eccentricity value
  // Graph diameter --- the largest vertex eccentricity value
  // Do not forget that -1 represents an IDEFINITE value

  // Computing the set of central vertices
  // Allocate the central vertices array : number of central vertices + 1
  // Fill in the central vertices array

  unsigned int numbVertex = GraphGetNumVertices(g);

  // Allocate memory for the result structure
  GraphEccentricityMeasures* result = (GraphEccentricityMeasures*)malloc(sizeof(GraphEccentricityMeasures));
  if (result == NULL) {
    return NULL;
  }

  // Allocate memory for the eccentricity
  result->eccentricity = (int*)malloc(numbVertex * sizeof(int));
  if (result->eccentricity == NULL) {
    free(result);
    return NULL;
  }

  // Allocate memory for the centralVertices array
  result->centralVertices = (unsigned int*)malloc((numbVertex + 1) * sizeof(unsigned int));  // +1 for the count
  if (result->centralVertices == NULL) {
    free(result->eccentricity);
    free(result);
    return NULL;
  }

  result->graph = g;

  // Compute all-pairs shortest distances
  GraphAllPairsShortestDistances* allPairsDist = GraphAllPairsShortestDistancesExecute(g);
  if (allPairsDist == NULL) {
    free(result->eccentricity);
    free(result->centralVertices);
    free(result);
    return NULL;
  }

  // Compute eccentricities, graph radius and diameter
  computeEccentricities(g, allPairsDist, result->eccentricity, &result->graphRadius, &result->graphDiameter);

  // Compute central vertices
  computeCentralVertices(result->eccentricity, result->graphRadius, numbVertex, result->centralVertices);

 
  GraphAllPairsShortestDistancesDestroy(&allPairsDist);
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

// Getting a copy of the set of central vertices
// centralVertices[0] = number of central vertices in the set
unsigned int* GraphGetCentralVertices(const GraphEccentricityMeasures* p) {
  assert(p != NULL);
  assert(p->centralVertices != NULL);

  // COMPLETE THE CODE

  unsigned int count = p->centralVertices[0];
  unsigned int* centralVertices = (unsigned int*)malloc((count + 1) * sizeof(unsigned int));
  if (centralVertices == NULL) {
    return NULL;
  }

  for (unsigned int i = 0; i <= count; i++) {
    centralVertices[i] = p->centralVertices[i];
  }

  return centralVertices;
}

// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
  // COMPLETE THE CODE

  // Print the graph radius and diameter
  printf("Graph radius: ");
  if (p->graphRadius == -1) {
    printf("INF\n");
  } else {
    printf("%d\n", p->graphRadius);
  }

  printf("Graph diameter: ");
  if (p->graphDiameter == -1) {
    printf("INF\n");
  } else {
    printf("%d\n", p->graphDiameter);
  }

  // Print the vertex eccentricity values
  printf("Vertex eccentricities:\n");
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    printf("Vertex %u: ", i);
    if (p->eccentricity[i] == -1) {
      printf("INF\n");
    } else {
      printf("%d\n", p->eccentricity[i]);
    }
  }

  // Print the set of central vertices
  printf("Central vertices:\n");
  for (unsigned int i = 1; i <= p->centralVertices[0]; i++) {
    printf("Vertex %u\n", p->centralVertices[i]);
  }
}





