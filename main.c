//todo: 36 linjer data.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define DATE_MAX_LENGTH 15

typedef struct {
    char date[DATE_MAX_LENGTH];
    float price;
}elspotPrices;

char* getCurrentTime(void);
int readFile(elspotPrices elPrArray[], int elPrArraylen);
double getEvCharging(double evArray[], int evArrayLen, double pro_ex, int* numOfEvCharging);
void generateEvArray(float evArray[], int evArrayLen);
elspotPrices makeElspotPrice(char date[DATE_MAX_LENGTH], float price);
double sumOfbatChargedNeeded(float evArray[], int evArrayLen);
int compare(const void *ep1, const void *ep2);
void printElspotPricesArray(elspotPrices array[], int arrayLength);
void printFloatArray(float array[], int arrayLength);

int main (void) {
    srand(10);

    char yn;
    printf("Do you want to get data? Type \"y\" for yes and \"n\" for no: ");
    scanf(" %c", &yn);
    if (yn == 'y') {
        system("APIGetelspotPrices\\elspotPrices.exe");
    }
    int elPrArrayLen = 30;
    elspotPrices* elPrArray = (elspotPrices*)malloc(elPrArrayLen*sizeof(elspotPrices)); 
    printf("Reading file: \n");

    if (readFile(elPrArray, elPrArrayLen)) {
        printf("Error 404: file not found.\n");
    }
    qsort(elPrArray, elPrArrayLen, sizeof(elspotPrices), compare);
    printElspotPricesArray(elPrArray, elPrArrayLen);
    
    int evArrayLen = 100;
    float* evArray = (float*)malloc(evArrayLen*sizeof(float)); 

    generateEvArray(evArray, evArrayLen);
    printFloatArray(evArray, evArrayLen);
    printf("sum: %f", sumOfbatChargedNeeded(evArray, evArrayLen));

    free(elPrArray);
    return(0);
}

int readFile(elspotPrices elPrArray[], int elPrArrayLen) {
    FILE *fpointer;
    float price = 0;
    char date[DATE_MAX_LENGTH];
    char singleline[25];
    int i = 0;

    fpointer = fopen("APIGetelspotPrices\\output.csv", "r"); /* For at fortælle at vi vil gerne læse fra den fil, vi bruger derfor "r" */
    if (fpointer != NULL) {
        while (!feof(fpointer)){
            fgets(singleline, 25, fpointer); /* For at læse den linje pr. linje */
            sscanf(singleline, "%[^;];%f", &date, &price);
            elPrArray[i] = makeElspotPrice(date, price);
            //printf("%s, %.2f\n", date, price);
            i++;
        }
    }
    else 
        return 1;

    return fclose(fpointer);
}

elspotPrices makeElspotPrice(char date[DATE_MAX_LENGTH], float price) {
    elspotPrices elPr;
    strcpy(elPr.date, date);
    elPr.price = price;
    return elPr;
}

double getEvCharging(double evArray[], int evArrayLen, double pro_ex, int* numOfEvCharging) {
    int pro_exTing = 0;
    int chargeRate = 11;
    
    *numOfEvCharging = 0;
    int i = 1;
    while (pro_ex+pro_exTing < 1000 && i < evArrayLen) {
        //printf(" [%f] ", pro_exTing);
        evArray[i] += 0.000916;
        ++(*numOfEvCharging);
        pro_exTing = (0.000916)*i;
        i++;
    }
    //printf(" {{{%f}} ",pro_ex+pro_exTing);

    return pro_ex+pro_exTing;
}

double sumOfbatChargedNeeded(float evArray[], int evArrayLen) {
    int i;
    int batCapacity = 50;
    double sum = 0;
    for(i = 0; i < evArrayLen; i++) {
        sum += ((100 - evArray[i])/100)*batCapacity;
    }
    return sum;
}

void generateEvArray(float evArray[], int evArrayLen){
    for (int i = 0; i < evArrayLen; i++){
        evArray[i] = rand() % (100-10) + 10;
    }
}

int compare(const void *p1, const void *p2) {
    const elspotPrices *elem1 = p1;    
    const elspotPrices *elem2 = p2;

    if (elem1->price < elem2->price)
            return -1;
        else if (elem1->price > elem2->price)
            return 1;
        else
            return 0;
        
}

void printFloatArray(float array[], int arrayLength) {
    int i;
    for(i = 0; i < arrayLength; i++) {
        printf("%.2f \n", array[i]);
    }
}

void printElspotPricesArray(elspotPrices array[], int arrayLength) {
    int i;
    for(i = 0; i < arrayLength; i++) {
        printf("%s, ", array[i].date);
        printf("%.2f\n", array[i].price);
    }
}


