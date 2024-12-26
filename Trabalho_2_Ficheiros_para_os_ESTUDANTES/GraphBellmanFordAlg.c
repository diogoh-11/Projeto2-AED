//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphBellmanFord - Bellman-Ford Algorithm
//

// Student Name :Luís Tojal
// Student Number :119636
// Student Name :Diogo Duarte
// Student Number : 120482

/*** COMPLETE THE GraphBellmanFordAlgExecute FUNCTION ***/

#include "GraphBellmanFordAlg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "IntegersStack.h"
#include "instrumentation.h"
struct _GraphBellmanFordAlg
{
  unsigned int *marked; // To mark vertices when reached for the first time
  int *distance;        // The number of edges on the path from the start vertex
                        // distance[i]=-1, if no path found from the start vertex to i
  int *predecessor;     // The predecessor vertex in the shortest path
                        // predecessor[i]=-1, if no predecessor exists
  Graph *graph;
  unsigned int startVertex; // The root of the shortest-paths tree
};
#define InstrName [0] = "COUNTITERATIONS";

GraphBellmanFordAlg *GraphBellmanFordAlgExecute(Graph *g,
                                                unsigned int startVertex)
{
  assert(g != NULL);
  assert(startVertex < GraphGetNumVertices(g));
  assert(GraphIsWeighted(g) == 0);

  GraphBellmanFordAlg *result =
      (GraphBellmanFordAlg *)malloc(sizeof(struct _GraphBellmanFordAlg));
  assert(result != NULL);
  InstrReset();
  // Given graph and start vertex for the shortest-paths
  result->graph = g;
  result->startVertex = startVertex;

  unsigned int numVertices = GraphGetNumVertices(g);
  unsigned int numEdges = GraphGetNumEdges(g);

  //
  // TO BE COMPLETED !!
  //
  // CREATE AND INITIALIZE
  // result->marked
  // result->distance
  // result->predecessor
  //

  // Mark all vertices as not yet visited, i.e., ZERO
  // No vertex has (yet) a (valid) predecessor
  // No vertex has (yet) a (valid) distance to the start vertex

  // inicialize the arrays
  result->predecessor = (int *)malloc(sizeof(int) * numVertices);
  result->marked = (unsigned int *)malloc(sizeof(unsigned int) * numVertices);
  result->distance = (int *)malloc(sizeof(int) * numVertices);
  assert(result->predecessor != NULL && result->marked != NULL && result->distance != NULL);

  // create an array if the vertex to iterate always starting in the staring vertex
  unsigned int vertices[numVertices];
  vertices[0] = startVertex;
  unsigned int index = 1;

  for (unsigned int m = 0; m < numVertices; m++)
  {
    InstrCount[0]++;
    // incialize the starting values
    result->marked[m] = 0;
    result->distance[m] = -1;
    result->predecessor[m] = -1;
    // Inicialize the array of the vertice
    if (m != startVertex)
    {
      vertices[index++] = m;
    }
  }
  // THE ALGORTIHM TO BUILD THE SHORTEST-PATHS TREE

  result->distance[startVertex] = 0;
  result->marked[startVertex] = 1;

  // if the graph doesn have any edge return and avoid wasting time
  if (numEdges == 0)
  {
    free(result->predecessor);
    free(result->marked);
    free(result->distance);
    free(result);
    return result;
  }

  // variables that will be needed
  unsigned int vertice;           // vertice working on
  unsigned int numbAdjacentsTo;   // numb the vertices adjance to the vertice
  unsigned int idAdjacentVertice; // id of one os the vertices adjante to the vertice
  int unChange;                   // check if the iteracion made any changes
  unsigned int *adjantesinfo;

  for (unsigned int j = 0; j < numVertices - 1; j++)
  {
    // first time lopping will always be in the startVertex
    unChange = 0;
    for (unsigned int v = 0; v < numVertices; v++)
    {
      vertice = vertices[v];
      // printf("Using the vertice: %d \n", vertice);
      //  if there is no path to this vertice skip iteracion
      if (result->marked[vertice] == 0)
      {
        // printf("There is no path to this vertice: %d end \n", vertice);
        continue;
      }
      // information about the adhacent vertices
      adjantesinfo = GraphGetAdjacentsTo(g, vertice);

      numbAdjacentsTo = adjantesinfo[0];
      // printf("Number of adjacents vertices: %d\n", numbAdjacentsTo);
      for (unsigned int adjacents = 1; adjacents <= numbAdjacentsTo; adjacents++)
      {
        // get the id of the adjancent vertice
        idAdjacentVertice = adjantesinfo[adjacents];
        // mark the vertice as visit
        InstrCount[0]++;
        // printf("vertice working on : %d\n", idAdjacentVertice);
        result->marked[idAdjacentVertice] = 1;
        // change the cost if the new is lower than the past one
        if (result->distance[idAdjacentVertice] > result->distance[vertice] + 1 || result->distance[idAdjacentVertice] == -1)
        {
          // printf("Changing dist on vertice : %d\n", idAdjacentVertice);
          result->predecessor[idAdjacentVertice] = vertice;
          unChange = 1;
          result->distance[idAdjacentVertice] = result->distance[vertice] + 1;
        }
      }
      free(adjantesinfo);
    }
    if (unChange == 0)
    {
      break;
    }
  }

  return result;
}

void GraphBellmanFordAlgDestroy(GraphBellmanFordAlg **p)
{
  assert(*p != NULL);

  GraphBellmanFordAlg *aux = *p;

  free(aux->marked);
  free(aux->predecessor);
  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the paths information

int GraphBellmanFordAlgReached(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

int GraphBellmanFordAlgDistance(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->distance[v];
}
Stack *GraphBellmanFordAlgPathTo(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack *s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0)
  {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current])
  {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBellmanFordAlgShowPath(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack *s = GraphBellmanFordAlgPathTo(p, v);

  while (StackIsEmpty(s) == 0)
  {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

// Display the Shortest-Paths Tree in DOT format
void GraphBellmanFordAlgDisplayDOT(const GraphBellmanFordAlg *p)
{
  assert(p != NULL);

  Graph *original_graph = p->graph;
  unsigned int num_vertices = GraphGetNumVertices(original_graph);

  // The paths tree is a digraph, with no edge weights
  Graph *paths_tree = GraphCreate(num_vertices, 1, 0);

  // Use the predecessors array to add the tree edges
  for (unsigned int w = 0; w < num_vertices; w++)
  {
    // Vertex w has a predecessor vertex v?
    int v = p->predecessor[w];
    if (v != -1)
    {
      GraphAddEdge(paths_tree, (unsigned int)v, w);
    }
  }

  // Display the tree in the DOT format
  GraphDisplayDOT(paths_tree);

  // Housekeeping
  GraphDestroy(&paths_tree);
}
