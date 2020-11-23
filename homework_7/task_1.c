#include "../library/commonUtils/numericOperations.h"
#include "../library/graph/graph.h"
#include <stdio.h>
#include <stdlib.h>

int getStudentsNumber()
{
    int studentsNumber = 0;

    printf("Введите количество студентов: ");
    scanf("%d", &studentsNumber);

    return studentsNumber;
}

// Возвращает рёбра, связывающие номера двух студентов(или номер студента и -1, если он не сдал работу).
Edge** getWorksConnectionsEdges(int studentsNumber, int* maxStudentNumber)
{
    *maxStudentNumber = 0;
    bool isMaxStudentNumberInitialized = false;
    Edge** worksConnectionsEdges = (Edge**)malloc(studentsNumber * sizeof(Edge*));

    printf("Для каждого студента введите два числа через пробел: номер самого студента и номер того, у кого он списал.\n");
    printf("Если же студент не сдал работу, вторым числом введите -1.\n");

    int firstStudentNumber = 0, secondStudentNumber = 0;
    for (int i = 0; i < studentsNumber; ++i) {
        scanf("%d %d", &firstStudentNumber, &secondStudentNumber);

        if (*maxStudentNumber < firstStudentNumber || *maxStudentNumber < secondStudentNumber || !isMaxStudentNumberInitialized) {
            *maxStudentNumber = max(firstStudentNumber, secondStudentNumber);
            isMaxStudentNumberInitialized = true;
        }

        worksConnectionsEdges[i] = createEdge(firstStudentNumber, secondStudentNumber, 1, true);
    }

    return worksConnectionsEdges;
}

int findStudentVariant(int currentStudent, Graph* worksConnectionsGraph, int maxStudentNumber)
{
    int* vertexState = (int*)calloc(maxStudentNumber + 1, sizeof(int));

    depthFirstSearch(worksConnectionsGraph, currentStudent, vertexState);

    if (vertexState[1] > 0) {
        free(vertexState);
        return 1;
    }

    if (vertexState[2] > 0) {
        free(vertexState);
        return 2;
    }

    if (vertexState[3] > 0) {
        free(vertexState);
        return 3;
    }

    free(vertexState);
    return -1;
}

// Возвращает двумерный массив, где внутренние массивы длины 2 связывают номер студента и сданный им вариант(или -1, если работы нет).
int** findStudentsWorks(Graph* worksConnectionsGraph, Edge** worksConnectionEdges, int studentsNumber, int maxStudentNumber)
{
    int** worksVariants = (int**)calloc(studentsNumber, sizeof(int*));
    for (int i = 0; i < studentsNumber; ++i)
        worksVariants[i] = (int*)calloc(2, sizeof(int));

    for (int i = 0; i < studentsNumber; ++i) {
        int currentStudentNumber = getEdgeStart(worksConnectionEdges[i]);
        int currentStudentVariant = findStudentVariant(currentStudentNumber, worksConnectionsGraph, maxStudentNumber);

        worksVariants[i][0] = currentStudentNumber;
        worksVariants[i][1] = currentStudentVariant;
    }

    return worksVariants;
}

void printWorksInformation(int** studentsWorksVariants, int studentsNumber)
{
    printf("Номера студентов, которых надо отчислить: ");
    for (int i = 0; i < studentsNumber; ++i)
        if (studentsWorksVariants[i][1] == -1) // Если текущий студент ничего не сдал.
            printf("%d ", studentsWorksVariants[i][0]); // Выводим его номер.
    printf("\n");

    printf("Номера студентов и варианты списанных ими работ: ");
    for (int i = 0; i < studentsNumber; ++i)
        if (studentsWorksVariants[i][1] != -1)
            printf("%d - %d ", studentsWorksVariants[i][0], studentsWorksVariants[i][1]);
}

void destroyEdgesArray(Edge** edgesArray, int arrayLength)
{
    for (int i = 0; i < arrayLength; ++i)
        free(edgesArray[i]);
    free(edgesArray);
}

int destroyWorksVariantsArray(int** array, int arrayLength)
{
    for (int i = 0; i < arrayLength; ++i)
        free(array[i]);
    free(array);
}

int main()
{
    int studentsNumber = getStudentsNumber();
    int maxStudentNumber = 0;
    Edge** worksConnectionsEdges = getWorksConnectionsEdges(studentsNumber, &maxStudentNumber);
    Graph* worksConnectionsGraph = createGraph(studentsNumber, maxStudentNumber + 1, worksConnectionsEdges);
    int** studentsWorksVariants = findStudentsWorks(worksConnectionsGraph, worksConnectionsEdges, studentsNumber, maxStudentNumber);

    printWorksInformation(studentsWorksVariants, studentsNumber);

    destroyGraph(worksConnectionsGraph);
    destroyEdgesArray(worksConnectionsEdges, studentsNumber);
    destroyWorksVariantsArray(studentsWorksVariants, studentsNumber);

    return 0;
}