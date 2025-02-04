//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphAllPairsShortestDistances
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphAllPairsShortestDistancesExecute FUNCTION ***/

#include "GraphAllPairsShortestDistances.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"

struct _GraphAllPairsShortestDistances
{
  int **distance; // The 2D matrix storing the all-pairs shortest distances
                  // It is stored as an array of pointers to 1D rows
                  // Idea: an INDEFINITE distance value is stored as -1
  Graph *graph;
};

// Allocate memory and initialize the distance matrix
// Compute the distances between vertices by running the Bellman-Ford algorithm
GraphAllPairsShortestDistances *GraphAllPairsShortestDistancesExecute(
    Graph *g)
{
  assert(g != NULL);

  GraphAllPairsShortestDistances *result = (GraphAllPairsShortestDistances *)malloc(sizeof(GraphAllPairsShortestDistances));
  if (result == NULL){
    return NULL;
  }

  unsigned int numbVertex = GraphGetNumVertices(g);
  result->graph = g;

  // Allocate memory for the distance matriz
  result->distance = (int **)malloc(numbVertex * sizeof(int *));
  if (result->distance == NULL){
    free(result);
    return NULL;
  }

  // Initialize the distance matrix rows
  for (unsigned int i = 0; i < numbVertex; i++){
      result->distance[i] = (int *)malloc(numbVertex * sizeof(int));
      if (result->distance[i] == NULL){
          // Free previously allocated rows and the result structure
          for (unsigned int j = 0; j < i; j++){
              free(result->distance[j]);
          }
          free(result->distance);
          free(result);
          return NULL;
      }
  }

  GraphBellmanFordAlg *BFGraph = NULL;

  for (unsigned int startingVertex = 0; startingVertex < numbVertex; startingVertex++){
    // CREATE THE SHORTS PATH FOR EVERY VERTICE
    BFGraph = GraphBellmanFordAlgExecute(g, startingVertex);
    if (BFGraph == NULL){
            // Free memory and return NULL in case of failure
            for (unsigned int i = 0; i < numbVertex; i++){
                free(result->distance[i]);
            }
            free(result->distance);
            free(result);
            return NULL;
    }

    // Store the distances in the matriz
    for (unsigned int v = 0; v < numbVertex; v++){
      // get the distance
      result->distance[startingVertex][v] = GraphBellmanFordAlgDistance(BFGraph, v);
    }

    // Free the memory allocated for the Bellman-Ford algorithm result
    GraphBellmanFordAlgDestroy(&BFGraph);
  }

  return result;
}

void GraphAllPairsShortestDistancesDestroy(GraphAllPairsShortestDistances **p)
{
  assert(*p != NULL);

  GraphAllPairsShortestDistances *aux = *p;
  unsigned int numVertices = GraphGetNumVertices(aux->graph);

  for (unsigned int i = 0; i < numVertices; i++)
  {
    free(aux->distance[i]);
  }

  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the result

int GraphGetDistanceVW(const GraphAllPairsShortestDistances *p, unsigned int v,
                       unsigned int w)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(w < GraphGetNumVertices(p->graph));

  return p->distance[v][w];
}

// DISPLAYING on the console

void GraphAllPairsShortestDistancesPrint(
    const GraphAllPairsShortestDistances *p)
{
  assert(p != NULL);

  unsigned int numVertices = GraphGetNumVertices(p->graph);
  printf("Graph distance matrix - %u vertices\n", numVertices);

  for (unsigned int i = 0; i < numVertices; i++)
  {
    for (unsigned int j = 0; j < numVertices; j++)
    {
      int distanceIJ = p->distance[i][j];
      if (distanceIJ == -1)
      {
        // INFINITY - j was not reached from i
        printf(" INF");
      }
      else
      {
        printf(" %3d", distanceIJ);
      }
    }
    printf("\n");
  }
}
