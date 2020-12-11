#include "allError.h"

/* Funktionen printer fejl ud fra errorIndex */
void printError(int errorIndex) {
    switch (errorIndex) {
    case 100:
        printf("Error 100: Unable to allocate space.\n");
        break;
    case 202:
        printf("Error 202: No corresponding date&time found for API data.\n");
        break;
    case 401:
        printf("Error 201: Input file is not formatted correctly.\n");
        break;
    case 402:
        printf("Error 402: Number can't be negative.\n");
        break;  
    case 403:
        printf("Error 402: Number can't be negative or zero.\n");
        break;  
    case 404:
        printf("Error 404: File not found.\n");
        break;
    case 409:
        printf("Error 409: File could not be closed.\n");
        break;
    default:
        printf("An unknown error occurred.\n");
        break;
    }
    exit(0);
}

