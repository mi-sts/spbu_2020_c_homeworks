#include "graph.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Edge {
    int start;
    int end;
    int weight;
    bool oriented;
};

struct Graph {
    int** matrix;
    int countVertex;
    int countEdges;
};

Edge* createEdge(int start, int end, int weight, bool oriented)
{
    Edge* edge = malloc(sizeof(Edge));
    edge->start = start;
    edge->end = end;
    edge->weight = weight;
    edge->oriented = oriented;

    return edge;
}

Graph* createGraph(int countEdges, int countVertex, Edge** edges)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->countVertex = countVertex;
    graph->countEdges = countEdges;
    graph->matrix = (int**)malloc(countVertex * sizeof(int*));

    for (int i = 0; i < countVertex; ++i) {
        graph->matrix[i] = (int*)malloc(countVertex * sizeof(int));
        memset(graph->matrix[i], 0, countVertex * sizeof(int));
    }

    for (int i = 0; i < countEdges; ++i) {
        if (edges[i] == NULL)
            continue;

        graph->matrix[edges[i]->start][edges[i]->end] = edges[i]->weight;
        if (!edges[i]->oriented)
            graph->matrix[edges[i]->end][edges[i]->start] = edges[i]->weight;
    }

    return graph;
}

void destroyGraph(Graph* graph)
{
    for (int i = 0; i < graph->countVertex; ++i)
        if (graph->matrix[i] != NULL)
            free(graph->matrix[i]);

    free(graph->matrix);
    free(graph);
}

bool isConnected(int fromVertex, int toVertex, Graph* graph)
{
    int* vertexState = (int*)malloc(graph->countVertex * sizeof(int));
    memset(vertexState, 0, graph->countVertex * sizeof(int));

    depthFirstSearch(graph, fromVertex, vertexState);

    return vertexState[toVertex] > 0;
}

bool depthFirstSearch(Graph* graph, int currentVertex, int* vertexState)
{
    vertexState[currentVertex] = 1;

    for (int i = 0; i < graph->countVertex; i++) {
        if (graph->matrix[currentVertex][i] != 0) {
            if (vertexState[i] == 1)
                return true;

            if (vertexState[i] == 0)
                if (depthFirstSearch(graph, i, vertexState))
                    return true;
        }
    }

    vertexState[currentVertex] = 2;

    return false;
}

bool isCycled(Graph* graph)
{
    int* vertexState = (int*)malloc(graph->countVertex * sizeof(int));
    memset(vertexState, 0, graph->countVertex * sizeof(int));

    for (int i = 0; i < graph->countVertex; ++i) {
        if (vertexState[i] == 0)
            if (depthFirstSearch(graph, i, vertexState))
                return true;
    }

    return false;
}

int getEdgeStart(Edge* edge)
{
    if (edge == NULL)
        return 0;

    return edge->start;
}

int getEdgeEnd(Edge* edge)
{
    if (edge == NULL)
        return 0;

    return edge->end;
}

int getEdgeWeight(Edge* edge)
{
    if (edge == NULL)
        return 0;

    return edge->weight;
}
