#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
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

Graph* createGraphWithIncidenceMatrix(int** incidenceMatrix, int countEdges, int countVertex)
{
    Edge** edges = (Edge**)calloc(countEdges, sizeof(Edge*));

    int startVertex = 0;
    int endVertex = 0;

    int edgesIndex = 0;

    for (int i = 0; i < countEdges; ++i) {
        startVertex = -1;
        endVertex = -1;

        bool oriented = true;

        for (int j = 0; j < countVertex; ++j) {
            if (incidenceMatrix[i][j] == 1)
                startVertex = j;
            else if (incidenceMatrix[i][j] == -1)
                endVertex = j;
            else if (incidenceMatrix[i][j] == 2) {
                startVertex = j;
                endVertex = j;
                oriented = false;
                break;
            }
        }
        if (startVertex == -1 || endVertex == -1)
            continue;

        Edge* currentEdge = createEdge(startVertex, endVertex, 1, oriented);
        edges[edgesIndex] = currentEdge;
        edgesIndex++;
    }

    Graph* graph = createGraph(edgesIndex, countVertex, edges);

    for (int i = 0; i < edgesIndex; ++i)
        free(edges[i]);
    free(edges);

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

bool depthFirstSearchWithVisualisation(Graph* graph, int currentVertex, int* vertexState)
{
    printf("%d\n", currentVertex);

    vertexState[currentVertex] = 1;

    for (int i = 0; i < graph->countVertex; i++) {
        if (graph->matrix[currentVertex][i] != 0) {
            if (vertexState[i] == 1)
                return true;

            if (vertexState[i] == 0) {
                if (depthFirstSearchWithVisualisation(graph, i, vertexState))
                    return true;
            }
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
