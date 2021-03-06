#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdbool.h>

typedef struct Graph Graph;

typedef struct Edge Edge;

Edge* createEdge(int start, int end, int weight, bool oriented);

Graph* createGraph(int countEdges, int countVertex, Edge** edges);

Graph* createGraphWithIncidenceMatrix(int** incidenceMatrix, int countEdges, int countVertex);

void destroyGraph(Graph* graph);

bool depthFirstSearch(Graph* graph, int currentVertex, int* vertexState);

bool isConnected(int fromVertex, int toVertex, Graph* graph);

bool isCycled(Graph* graph);

int getEdgeStart(Edge* edge);

int getEdgeEnd(Edge* edge);

int getEdgeWeight(Edge* edge);

int getGraphVertexCount(Graph* graph);

int getGraphEdgesCount(Graph* graph);

void printGraph(Graph* graph);

int* dijkstraAlgorithm(Graph* graph, int startVertex);

#endif
