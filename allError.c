#include "allError.h"

/* Funktionen printer fejl ud fra errorIndex */
void printError(int errorIndex, char* text) {
    switch (errorIndex) {
    case 100:
        printf("Error 100: Unable to allocate space. ");
        break;
    case 202:
        printf("Error 202: No corresponding date&time found for API data. ");
        break;
    case 401:
        printf("Error 401: Input file is not formatted correctly. ");
        break;
    case 402:
        printf("Error 402: Number can't be negative. ");
        break;  
    case 403:
        printf("Error 403: Number can't be negative or zero. ");
        break;  
    case 404:
        printf("Error 404: File not found. ");
        break;
    case 409:
        printf("Error 409: File could not be closed. ");
        break;
    default:
        printf("An unknown error occurred. ");
        break;
    }
    printf("Error in %s\n", text);
    exit(0);
}

