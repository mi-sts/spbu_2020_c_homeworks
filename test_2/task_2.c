#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int DATE_LENGTH = 10;

bool isDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

bool isPoint(char symbol)
{
    return symbol == '.';
}

bool isDate(char* text)
{
    if (strlen(text) != 10)
        return false;

    for (int i = 0; i < DATE_LENGTH; ++i) {
        if (i == 2 || i == 5) {
            if (!isPoint(text[i]))
                return false;
        }
        else if (!isDigit(text[i]))
            return false;
    }

    return true;
}

long long getDays(char* date)
{
    long long days = atof(date);

    return days;
}

long long getMonths(char* date)
{
    char* monthsPart = calloc(3, sizeof(char));
    memcpy(monthsPart, date + (3 * sizeof(char)), 2 * sizeof(char));
    long long months = atof(monthsPart);


    free(monthsPart);
    return months;
}

long long getYears(char* date)
{
    char* yearsPart = calloc(5, sizeof(char));
    memcpy(yearsPart, date + (6 * sizeof(char)), 4 * sizeof(char));
    long long years = atof(yearsPart);

    free(yearsPart);
    return years;
}

void printResult(long long days, long long months, long long years)
{
    printf("Наименьшая дата: %lld.%lld.%lld", days, months, years);
}

void findSmallestDate(FILE* file)
{
    bool isInitialized = false;
    long long smallestYears = 0;
    long long smallestMonths = 0;
    long long smallestDays = 0;

    char* currentText = (char*)calloc(DATE_LENGTH + 1, sizeof(char));

    while (!feof(file)) {
        fscanf(file, "%10s", currentText);
        if (isDate(currentText)) {
            if (!isInitialized) {
                smallestYears = getYears(currentText);
                smallestMonths = getMonths(currentText);
                smallestDays = getDays(currentText);

                isInitialized = true;
            } else {
                long long currentYears = getYears(currentText);
                long long currentMonths = getMonths(currentText);
                long long currentDays = getDays(currentText);

                if (currentYears < smallestYears || (currentYears == smallestYears && currentMonths < smallestMonths) || (currentYears == smallestYears && currentMonths == smallestMonths && currentDays < smallestDays)) {
                    smallestYears = currentYears;
                    smallestMonths = currentMonths;
                    smallestDays = currentDays;
                }
            }
        }
    }

    printResult(smallestDays, smallestMonths, smallestYears);
}

int main()
{
    FILE* file;
    file = fopen("../test_2/dates.txt", "r");

    findSmallestDate(file);

    return 0;
}