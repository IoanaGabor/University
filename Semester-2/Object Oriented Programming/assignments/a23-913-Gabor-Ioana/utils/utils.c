#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "domain/vector.h"
#include <time.h>

int validateCategory(char *category) {
    if (strcmp(category, "dairy") == 0 || strcmp(category, "sweets") == 0
        || strcmp(category, "meat") == 0 || strcmp(category, "fruit") == 0) {
        return 0;
    }
    return -1;
}

int getPositiveIntegerFromString(char *string_to_be_transformed) {
    if(string_to_be_transformed == NULL){
        return -1;
    }
    int resulting_integer;
    if (sscanf(string_to_be_transformed, "%d", &resulting_integer) == 1) {
        return resulting_integer;
    }
    return -1;
}

int getNumberOfDaysBetweenCurrentDateAndThis(int year, int month, int day) {
    struct tm received_date, *current_time = NULL;
    received_date.tm_year = year - 1900;
    received_date.tm_mon = month - 1;
    received_date.tm_mday = day;
    received_date.tm_min = received_date.tm_sec = received_date.tm_hour = 0;
    time_t current_timestamp = time(NULL);
    current_time = localtime(&current_timestamp);
    current_time->tm_min = current_time->tm_sec = current_time->tm_hour = 0;
    received_date.tm_isdst = current_time->tm_isdst;
    current_timestamp = mktime(current_time);
    time_t timestamp_of_the_received_day = mktime(&received_date);
    double difference_in_seconds = difftime(timestamp_of_the_received_day, current_timestamp);
    return (int) difference_in_seconds / (60 * 60 * 24);
}

void getYearMonthDayFromDateString(char *string_to_be_transformed, int *year, int *month, int *day) {
    char *argument = strtok(string_to_be_transformed, "/");
    char **arguments = (char **) malloc(sizeof(char *) * 3);
    int arguments_length = 0;
    while (argument != NULL && arguments_length < 3) {
        arguments[arguments_length] = (char *) malloc(sizeof(char) * 100);
        strcpy(arguments[arguments_length], argument);
        arguments_length++;
        argument = strtok(NULL, "/");
    }
    if (argument != NULL) {
        (*year) = -1;
        return ;
    }
    (*year) = getPositiveIntegerFromString(arguments[0]);
    (*month) = getPositiveIntegerFromString(arguments[1]);
    (*day) = getPositiveIntegerFromString(arguments[2]);
    for(int i=0;i<arguments_length;i++){
        free(arguments[i]);
    }
    free(arguments);
}

void
vectorOfProductsToString(Vector *vector, void (*element_to_string)(TElement element, char *resulting_element_string),
                         char *resulting_vector_string) {
    resulting_vector_string[0] = 0;
    char integer_string[10];
    char element_string[100];
    for (int i = 0; i < vector->length; i++) {
        TElement current_element = *((TElement *) get_element_at_position(vector, i));
        strcat(resulting_vector_string, "Element ");
        integer_string[i] = 0;
        sprintf(integer_string, "%d", i);
        strcat(integer_string, " ");
        strcat(resulting_vector_string, integer_string);
        element_string[0] = 0;
        element_to_string(current_element, element_string);
        strcat(resulting_vector_string, element_string);
        strcat(resulting_vector_string, "\n");
    }
}