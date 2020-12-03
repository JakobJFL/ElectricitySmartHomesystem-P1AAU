#include "allErrorFile.h"

/* Printerfejl ud fra errorIndex */
void printError(int errorIndex) {
    switch (errorIndex) {
    case 100:
        printf("Error 100: Can not allocated space\n");
        break;
    case 201:
        printf("Error 201: Input file is not formatted correctly.\n");
        break;
    case 202:
        printf("Error 202: No electricity prices found.\n");
        break;
    case 404:
        printf("Error 404: File not found.\n");
        break;
    default:
        printf("An unknown error occurred\n");
        break;
    }
    exit(0);
}

