

#include <assert.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

int main(void)
{
    // What kind of graph is dig01?
    for (int numVertice = 2; numVertice < 1000; numVertice = numVertice + 100)
    {
        Graph *dig01 = GraphCreate(numVertice, 1, 0);

        GraphCheckInvariants(dig01);

        // Bellman-Ford Algorithm

        // Consider each vertex as a start vertex

        GraphBellmanFordAlg *BF_result = GraphComputeTransitiveClosure(dig01, 0);

        printf("Numero de iterações :%d \n", InstrCount[0]);
        InstrPrint();
        printf("\n");
        GraphBellmanFordAlgDestroy(&BF_result);

        GraphDestroy(&dig01);
    }

    return 0;
}