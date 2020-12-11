#include "spotPrices.h"
#include "electricVehicle.h"
#include "files.h"
#include "allError.h"

/*Funktionen readFile læser datafilen, og lægger det læste data ind i elPrArray*/
int readSpotPricesFile(spotPrices elPrArray[], int elPrArrayLen) {
    FILE *fpointer;
    float price = 0;
    char date[DATE_MAX];
    char singleline[FILE_LINE_LENGTH];
    int i = 0;
    int numOfLineData = 0;

    fpointer = fopen("output.csv", "r"); /*Åbner fil i readmode, derfor: "r"*/
    if (fpointer != NULL) {
        while (!feof(fpointer)){
            fgets(singleline, FILE_LINE_LENGTH, fpointer); /*Der læses én linje ad gangen*/
            numOfLineData = sscanf(singleline, "%[^;];%f", elPrArray[i].date, &elPrArray[i].price);
            
            if (numOfLineData != 2)
                printError(201);
            i++;
        }
    }
    else 
        printError(404);
    
    return fclose(fpointer);
}

/* Laver et array med options fra: "readOptionsFile".   */
int getOption(enum options option) {
    /* Laver statisk lagerallokering sådan arrayet ikke slettes hver gang funktionen kaldes. */
    static enum options optionsArray[OPTIONS_LENGTH]; 
    static int isFileRead;
    if (!isFileRead) {
        if(readOptionsFile(optionsArray)) 
            printError(402);
        isFileRead = 1;
    }    
    return optionsArray[option];
}

/* Læser data om elbiler fra EVdata.csv, og lægger dataen i et array*/
int readFileEV(electricVehicle array[], int arrayLen){
    FILE *fpointer = fopen("EVdata.csv", "r"); 
    char singleline[FILE_LINE_LENGTH];
    int i = 0;
    int numOfLineData = 0;

    if (fpointer != NULL){
        while (!feof(fpointer)){
            fgets(singleline, FILE_LINE_LENGTH, fpointer);

            numOfLineData = sscanf(singleline, "%[^;]; %f; %f; %d; %f", 
            array[i].modelName, 
            &array[i].capacity, 
            &array[i].chargeRate, 
            &array[i].numOfEV, 
            &array[i].kmPrKwh);
            
            if (numOfLineData != 5)
                printError(201);
        i++;
        }
    }
    else 
        printError(404);

    return fclose(fpointer);
}

/*Læser tekstfilen med options, og lægger data derfra ind i et optionsArray*/
int readOptionsFile(enum options optionsArray[]) {
    FILE *fpointer = fopen("options.txt", "r"); 
    char singleline[FILE_LINE_LENGTH];
    int numOfLineData = 0;
    int i = 0;
    int lineData = 0;

    if (fpointer != NULL) {
        while (!feof(fpointer)) { /*Læser fra fil så længe filpointer ikke er ved enden af filen*/
            fgets(singleline, FILE_LINE_LENGTH, fpointer);
            numOfLineData = sscanf(singleline, "%*[^:]:%d", &lineData); 
            optionsArray[i] = lineData;
            if (numOfLineData != 1)
                printError(201);
            i++;
        }
    }
    else 
        printError(404);

    return fclose(fpointer);
}