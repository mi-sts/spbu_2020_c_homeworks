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

// Возвращает рёбра, связывающие номера двух студентов(и помещает в массив studentsWithoutWork номера студетнов, не сдавших работу).
Edge** getWorksConnectionsEdges(int studentsNumber, int* maxStudentNumber, int** studentsWithoutWork, int* studentsWithoutWorkNumber, int* studentsWithWorkNumber)
{
    *maxStudentNumber = 0;
    bool isMaxStudentNumberInitialized = false;

    printf("Для каждого студента введите два числа через пробел: номер самого студента и номер того, у кого он списал.\n");
    printf("Если же студент не сдал работу, вторым числом введите -1.\n");

    int firstStudentNumber = 0, secondStudentNumber = 0;

    int studentsWithoutWorkIndex = 0;
    int studentsWithoutWorkBorder = 1;
    *studentsWithoutWork = (int*)calloc(1, sizeof(int));

    int studentsWithWorkIndex = 0;
    int studentsWithWorkBorder = 1;
    Edge** worksConnectionsEdges = (Edge**)malloc(1 * sizeof(Edge*));

    for (int i = 0; i < studentsNumber; ++i) {
        scanf("%d %d", &firstStudentNumber, &secondStudentNumber);

        if (*maxStudentNumber < firstStudentNumber || *maxStudentNumber < secondStudentNumber || !isMaxStudentNumberInitialized) {
            *maxStudentNumber = max(firstStudentNumber, secondStudentNumber);
            isMaxStudentNumberInitialized = true;
        }

        if (secondStudentNumber == -1) {
            if (studentsWithoutWorkBorder == studentsWithoutWorkIndex) {
                studentsWithoutWorkBorder *= 2;
                *studentsWithoutWork = (int*)realloc(*studentsWithoutWork, studentsWithoutWorkBorder * sizeof(int));
            }

            (*studentsWithoutWork)[studentsWithoutWorkIndex] = firstStudentNumber;
            studentsWithoutWorkIndex++;
            continue;
        }

        if (studentsWithWorkIndex == studentsWithWorkBorder) {
            studentsWithWorkBorder *= 2;
            worksConnectionsEdges = (Edge**)realloc(worksConnectionsEdges, studentsWithWorkBorder * sizeof(Edge*));
        }

        worksConnectionsEdges[studentsWithWorkIndex] = createEdge(firstStudentNumber, secondStudentNumber, 1, true);
        studentsWithWorkIndex++;
    }

    *studentsWithoutWorkNumber = studentsWithoutWorkIndex;
    *studentsWithWorkNumber = studentsWithWorkIndex;

    return worksConnectionsEdges;
}

int findStudentVariant(int currentStudent, Graph* worksConnectionsGraph, int maxStudentNumber)
{
    int* vertexState = (int*)calloc(maxStudentNumber + 1, sizeof(int));

    depthFirstSearch(worksConnectionsGraph, currentStudent, vertexState);

    for (int i = 1; i <= 3; ++i) {
        if (vertexState[i] > 0) {
            free(vertexState);
            return i;
        }
    }

    free(vertexState);
    return 0;
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

void printWorksInformation(int** studentsWorksVariants, int studentsNumber, int* studentsWithoutWork, int studentWithoutWorkNumber)
{
    printf("Номера студентов, которых надо отчислить: ");
    for (int i = 0; i < studentWithoutWorkNumber; ++i) {
        printf("%d ", studentsWithoutWork[i]);
    }
    printf("\n");

    printf("Номера студентов и варианты списанных ими работ:\n");
    for (int i = 0; i < studentsNumber; ++i)
        if (studentsWorksVariants[i][1] != -1)
            printf("%d - %d\n", studentsWorksVariants[i][0], studentsWorksVariants[i][1]);
}

void destroyEdgesArray(Edge** edgesArray, int arrayLength)
{
    for (int i = 0; i < arrayLength; ++i)
        free(edgesArray[i]);
    free(edgesArray);
}

void destroyWorksVariantsArray(int** array, int arrayLength)
{
    for (int i = 0; i < arrayLength; ++i)
        free(array[i]);
    free(array);
}

int main()
{
    int studentsNumber = getStudentsNumber(); // Общее число студентов.
    int maxStudentNumber = 0;
    int studentsWithoutWorkNumber = 0; // Число студентов без работы.
    int studentsWithWorkNumber = 0; // Число студентов с работой.
    int* studentsWithoutWork = NULL; // Массив с номерами студентов без работы.

    Edge** worksConnectionsEdges = getWorksConnectionsEdges(studentsNumber, &maxStudentNumber, &studentsWithoutWork, &studentsWithoutWorkNumber, &studentsWithWorkNumber);
    Graph* worksConnectionsGraph = createGraph(studentsWithWorkNumber, maxStudentNumber + 1, worksConnectionsEdges);
    int** studentsWorksVariants = findStudentsWorks(worksConnectionsGraph, worksConnectionsEdges, studentsWithWorkNumber, maxStudentNumber);

    printWorksInformation(studentsWorksVariants, studentsWithWorkNumber, studentsWithoutWork, studentsWithoutWorkNumber);

    destroyGraph(worksConnectionsGraph);
    destroyEdgesArray(worksConnectionsEdges, studentsWithWorkNumber);
    destroyWorksVariantsArray(studentsWorksVariants, studentsWithWorkNumber);
    free(studentsWithoutWork);

    return 0;
}