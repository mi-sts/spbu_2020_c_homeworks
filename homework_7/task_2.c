#include "../library/commonUtils/numericOperations.h"
#include "../library/graph/graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Country {
    int citiesCount;
    int* citiesArray;
    int citiesArrayBorder;
    int* distancesToOtherCities;
} Country;

Country* createCountry()
{
    Country* country = (Country*)calloc(1, sizeof(Country));
    country->citiesArrayBorder = 1;
    country->citiesArray = (int*)calloc(country->citiesArrayBorder, sizeof(int));
    country->citiesCount = 0;
    country->distancesToOtherCities = NULL;

    return country;
}

void destroyCountry(Country* country)
{
    if (country == NULL)
        return;

    if (country->citiesArray != NULL)
        free(country->citiesArray);

    if (country->distancesToOtherCities != NULL)
        free(country->distancesToOtherCities);

    free(country);
}

void setCountryDistancesToOtherCities(Country* country, int* distances)
{
    if (country == NULL)
        return;

    if (country->distancesToOtherCities != NULL)
        free(country->distancesToOtherCities);
    country->distancesToOtherCities = distances;
}

void addCityToCountry(Country* country, int cityNumber)
{
    if (country == NULL)
        return;

    if (country->citiesCount == country->citiesArrayBorder) {
        country->citiesArrayBorder *= 2;
        country->citiesArray = (int*)realloc(country->citiesArray, country->citiesArrayBorder * sizeof(int));
    }

    country->citiesArray[country->citiesCount] = cityNumber;
    country->citiesCount++;
}

void getCitiesEdges(FILE* inputFile, Edge*** citiesEdgesPointer, int edgesCount)
{
    *citiesEdgesPointer = (Edge**)malloc(edgesCount * sizeof(Edge*));
    int firstCityNumber = 0, secondCityNumber = 0;
    int length = 0;
    for (int i = 0; i < edgesCount; ++i) {
        fscanf(inputFile, "%d %d %d", &firstCityNumber, &secondCityNumber, &length);
        (*citiesEdgesPointer)[i] = createEdge(firstCityNumber, secondCityNumber, length, false);
    }
}

void getCapitalsNumbers(FILE* inputFile, int** capitalsNumbersPointer, int capitalsCount)
{
    *capitalsNumbersPointer = (int*)calloc(capitalsCount, sizeof(int));
    int capitalNumber = 0;
    for (int i = 0; i < capitalsCount; ++i) {
        fscanf(inputFile, "%d", &capitalNumber);
        (*capitalsNumbersPointer)[i] = capitalNumber;
    }
}

void getInputInformation(FILE* inputFile, int* n, int* m, Edge*** citiesEdgesPointer, int* k, int** capitalsNumbersPointer)
{
    fscanf(inputFile, "%d %d", n, m);
    getCitiesEdges(inputFile, citiesEdgesPointer, *m);
    fscanf(inputFile, "%d", k);
    getCapitalsNumbers(inputFile, capitalsNumbersPointer, *k);
}

int locateInArray(int* array, int arraySize, int value)
{
    int valueIndex = -1;
    for (int i = 0; i < arraySize; ++i) {
        if (array[i] == value) {
            valueIndex = i;
            break;
        }
    }

    return valueIndex;
}

void removeFromArray(int* array, int arraySize, int valueIndex)
{
    array[valueIndex] = 0;

    for (int i = valueIndex + 1; i < arraySize; ++i)
        array[i - 1] = array[i];
}

bool removeValueFromArray(int* array, int arraySize, int value)
{
    int valueIndex = locateInArray(array, arraySize, value);
    if (valueIndex == -1)
        return false;

    removeFromArray(array, arraySize, valueIndex);

    return true;
}

void addNearestCityToCountry(Country* country, Graph* citiesGraph, int* freeCitiesNumbers, int* freeCitiesCount)
{
    int nearestCityDistance = -1;
    int nearestCityNumber = -1;

    bool isNearestCityInitialized = false;
    int* minCountryDistances = country->distancesToOtherCities;
    int citiesCount = getGraphVertexCount(citiesGraph);

    for (int i = 0; i <= *freeCitiesCount; ++i) { // Поиск ближайшего свободного города.
        int currentCityNumber = freeCitiesNumbers[i];
        int currentCityDistance = minCountryDistances[currentCityNumber];

        if (currentCityDistance == -1) // Если город недостижим.
            continue;

        if (!isNearestCityInitialized) {
            nearestCityNumber = currentCityNumber;
            nearestCityDistance = currentCityDistance;
            isNearestCityInitialized = true;
            continue;
        }

        if (currentCityDistance < nearestCityDistance) {
            nearestCityNumber = currentCityNumber;
            nearestCityDistance = currentCityDistance;
        }
    }

    if (nearestCityDistance == -1)
        return;

    if (removeValueFromArray(freeCitiesNumbers, *freeCitiesCount, nearestCityNumber)) { // Удаление номера города из массива свободных городов.
        (*freeCitiesCount)--;
    }

    int* nearestCityDistances = dijkstraAlgorithm(citiesGraph, nearestCityNumber); // Поиск расстояний от найденного ближайшего города до остальных городов.
    int* minCityDistances = (int*)calloc(citiesCount, sizeof(int));

    for (int i = 0; i < getGraphVertexCount(citiesGraph); ++i) { // Обновление расстояний от страны до других городов.
        if (country->distancesToOtherCities[i] == -1) { // Если до обновления расстояний i-й город был недостижим.
            minCityDistances[i] = nearestCityDistances[i];
            continue;
        }

        if (nearestCityDistances[i] == -1) { // Если для теку
            minCityDistances[i] = country->distancesToOtherCities[i];
            continue;
        }

        minCityDistances[i] = min(nearestCityDistances[i], country->distancesToOtherCities[i]);
    }

    addCityToCountry(country, nearestCityNumber);
    setCountryDistancesToOtherCities(country, minCityDistances);
    free(nearestCityDistances);
}

// Возвращает двумерный массив, где i-й подмассив содержит города (i + 1)-го государства.
Country** findCountriesCities(int citiesCount, int roadsCount, Edge** citiesEdges, int capitalsCount, int* capitalsNumbers)
{
    int currentCapitalNumbersIndex = 0;
    Country** countries = (Country**)malloc(*capitalsNumbers * sizeof(Country*));
    for (int i = 0; i < capitalsCount; ++i)
        countries[i] = createCountry();

    int* freeCitiesNumbers = (int*)calloc(citiesCount, sizeof(int)); // Номера ещё не занятых городов.
    int freeCitiesCount = citiesCount;
    for (int i = 1; i <= freeCitiesCount; ++i)
        freeCitiesNumbers[i - 1] = i;

    Graph* citiesGraph = createGraph(roadsCount, citiesCount + 1, citiesEdges);

    int currentCapitalNumber = 0;
    for (int i = 0; i < capitalsCount; ++i) { // Добавление столиц по странам.
        currentCapitalNumber = capitalsNumbers[i];
        Country* currentCountry = countries[i];

        int* currentCapitalDistances = dijkstraAlgorithm(citiesGraph, currentCapitalNumber); // Поиск минимальных расстояний от столицы до остальных городов.

        addCityToCountry(currentCountry, currentCapitalNumber); // Добавление города в страну и обновление растояний.
        setCountryDistancesToOtherCities(currentCountry, currentCapitalDistances);

        if (removeValueFromArray(freeCitiesNumbers, freeCitiesCount, currentCapitalNumber)) // Удаление города из массива свободных городов.
            freeCitiesCount--;
    }

    int currentCountryIndex = 0;
    Country* currentCountry = NULL;
    for (int i = 0; i < citiesCount - capitalsCount; ++i) { // Распределение городов.
        currentCountryIndex = i % capitalsCount;
        currentCountry = countries[currentCountryIndex];
        addNearestCityToCountry(currentCountry, citiesGraph, freeCitiesNumbers, &freeCitiesCount);
    }

    destroyGraph(citiesGraph);
    free(freeCitiesNumbers);

    return countries;
}

void printCountriesCities(Country** countries, int countriesCount)
{
    for (int i = 0; i < countriesCount; ++i) {
        int countryNumber = i + 1;
        Country* currentCountry = countries[i];
        printf("Номер государства - %d\n", countryNumber);
        printf("Номера городов, входящих в него: ");
        for (int j = 0; j < currentCountry->citiesCount; ++j)
            printf("%d ", currentCountry->citiesArray[j]);
        printf("\n");
    }
}

void destroyEdgesArray(Edge** edgesArray, int arraySize)
{
    for (int i = 0; i < arraySize; ++i)
        free(edgesArray[i]);
    free(edgesArray);
}

void destroyCountryArray(Country** countryArray, int arraySize)
{
    for (int i = 0; i < arraySize; ++i)
        destroyCountry(countryArray[i]);
    free(countryArray);
}

int main()
{
    int n = 0, m = 0;
    Edge** citiesEdges = NULL;
    int k = 0;
    int* capitalsNumbers = NULL;

    FILE* inputFile = fopen("../homework_7/task_2_input.txt", "r");
    getInputInformation(inputFile, &n, &m, &citiesEdges, &k, &capitalsNumbers);

    Country** countriesCities = findCountriesCities(n, m, citiesEdges, k, capitalsNumbers);

    printCountriesCities(countriesCities, k);

    fclose(inputFile);
    destroyEdgesArray(citiesEdges, m);
    free(capitalsNumbers);
    destroyCountryArray(countriesCities, k);

    return 0;
}