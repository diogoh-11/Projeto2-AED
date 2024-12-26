

#include <assert.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

int main(void)
{
    // What kind of graph is dig01?
    for (int numVertice = 2; numVertice < 10; numVertice++)
    {
        Graph *dig01 = GraphCreate(numVertice, 1, 0);

        for (int v = 0; v < numVertice - 2; v++)
        {
            for (int edgge = 0; edgge < numVertice; edgge++)
            {
                if (edgge != v)
                {
                    GraphAddEdge(dig01, v, edgge);
                }
            }
        }

        // Bellman-Ford Algorithm

        // Consider each vertex as a start vertex
        printf("%d", GraphGetNumEdges(dig01));
        GraphBellmanFordAlg *BF_result = GraphBellmanFordAlgExecute(dig01, 0);

        printf("Numero de vertices: %d\n", numVertice);
        printf("Numero de iterações :%d \n", InstrCount[0]);
        InstrPrint();
        printf("\n");

        GraphBellmanFordAlgDestroy(&BF_result);

        GraphDestroy(&dig01);
    }

    return 0;
}