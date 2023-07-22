#pragma once

#include <string.h>

int validateCategory(char *category);

int getPositiveIntegerFromString(char *string_to_be_transformed);

void getYearMonthDayFromDateString(char *string_to_be_transformed, int *year, int *month, int *day);

int getNumberOfDaysBetweenCurrentDateAndThis(int year, int month, int day);