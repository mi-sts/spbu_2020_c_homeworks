#include "../library/graph/graph.h"
#include "../library/commonUtils/numericOperations.h"
#include <stdio.h>
#include <stdlib.h>

int** getIncidenceMatrix(int* countVertex, int* countEdges)
{
    printf("Введите число вершин графа: ");
    scanf("%d", countVertex);
    printf("Введите число рёбер графа: ");
    scanf("%d", countEdges);

    int** incidenceMatrix = (int**)calloc(*countEdges, sizeof(int*));
    for (int i = 0; i < *countEdges; ++i)
        incidenceMatrix[i] = (int*)calloc(*countVertex, sizeof(int));

    printf("Введите матрицу инцидентности, числа через пробел.\n");
    printf("В n-й строке вводятся числа для n-й вершины.\n");
    for (int i = 0; i < *countVertex; ++i) {
        for (int j = 0; j < *countEdges; ++j) {
            scanf("%d", &incidenceMatrix[j][i]);
        }
    }

    return incidenceMatrix;
}

int getVertexNumber() {
    int vertexNumber = 0;
    printf("Введите номер вершины, от которой вести поиск: ");
    scanf("%d", &vertexNumber);

    return vertexNumber;
}

void printResult(int* vertexState, int countVertex)
{
    printf("Эти вершины недостижимы из данной вершины:\n");
    for (int i = 0; i < countVertex; ++i)
        if (vertexState[i] == 0)
            printf("%d\n", i);
}

void destroyIncidenceMatrix(int** incidenceMatrix, int countEdges)
{
    for (int i = 0; i < countEdges; ++i)
        free(incidenceMatrix[i]);
    free(incidenceMatrix);
}

int main()
{
    int countVertex = 0;
    int countEdges = 0;

    int** incidenceMatrix = getIncidenceMatrix(&countVertex, &countEdges);

    Graph* graph = createGraphWithIncidenceMatrix(incidenceMatrix, countEdges, countVertex);
    int vertexNumber = getVertexNumber();
    int* vertexState = (int*)calloc(countVertex, sizeof(int));

    depthFirstSearch(graph, vertexNumber, vertexState);

    printResult(vertexState, countVertex);

    destroyIncidenceMatrix(incidenceMatrix, countEdges);
    free(vertexState);
    destroyGraph(graph);

    return 0;
}