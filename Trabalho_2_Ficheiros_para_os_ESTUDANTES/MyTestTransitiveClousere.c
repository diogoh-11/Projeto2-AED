

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

        GraphCheckInvariants(dig01);

        for (int v = 0; v < numVertice; v++)
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

        Graph *BF_result = GraphComputeTransitiveClosure(dig01, 0);
        printf("Numero de vertices: %d\n", numVertice);
        printf("Numero de iterações :%d \n", InstrCount[3]);
        printf("Numero de Altea~çoes de distancia :%d \n", InstrCount[4]);

        InstrPrint();
        printf("\n");

        GraphDestroy(&dig01);
    }

    return 0;
}