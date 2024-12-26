//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name :Luís Tojal
// Student Number :119636
// Student Name :Diogo Duarte
// Student Number : 120482

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"
#define InstrName [0] = "COUNTITERATIONS";

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph *GraphComputeTransitiveClosure(Graph *g)
{
  InstrReset();

  assert(g != NULL);
  assert(GraphIsDigraph(g));
  assert(GraphIsWeighted(g) == 0);

  // COMPLETE THE CODE
  unsigned int numVertices = GraphGetNumVertices(g);
  unsigned int numEdges = GraphGetNumEdges(g);
  Graph *res = GraphCreate(numVertices, GraphIsDigraph(g), GraphIsWeighted(g));

  // if the graph doesn have any edge return and avoid wasting time
  if (numEdges == 0)
  {
    InstrCount[0]++;

    return res;
  }
  GraphBellmanFordAlg *BF_result;
  // for every vertice
  for (unsigned int startVertex = 0; startVertex < numVertices; startVertex++)
  {
    // create a graph using the bellman algorith for that starting vertx
    BF_result = GraphBellmanFordAlgExecute(g, startVertex);
    for (unsigned int v = 0; v < numVertices; v++)
    {
      // check the distance of that vertice
      // printf("Vertice Starting: %d  Vertice Checking: %d \n", startVertex, v);
      int value = GraphBellmanFordAlgDistance(BF_result, v);
      // printf("Value: %d\n", value);
      //  check if the distance is grater than 0
      InstrCount[0]++;

      if (value > 0)
      {
        // add the vertice
        GraphAddEdge(res, startVertex, v);
      }
    }
    GraphBellmanFordAlgDestroy(&BF_result);
  }

  return res;
}
