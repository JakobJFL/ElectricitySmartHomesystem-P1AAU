#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char* getCurrentTime(void);
int readFile(void);
double getEvCharging(double evArray[], int evArrayLen, double pro_ex, int* numOfEvCharging);
void generateEvArray(double evArray[], int evArrayLen);
int cmpFun(const void *ep1, const void *ep2);
void printArray(double array[], int arrayLen);

int main (void) {
    srand(10);

    char yn;
    printf("Do you want to get data? Type \"y\" for yes and \"n\" for no: ");
    scanf(" %c", &yn);
    if (yn == 'y') {
        system("APIGetElspotPrices\\ElspotPrices.exe");
    }
    
    printf("Reading file: \n");

    if (readFile()) {
        printf("Error 404: file not found.\n");
    }
    return(0);
}

int readFile(void) {
    int evArrayLen = 17000;
    double* evArray = (double*)malloc(evArrayLen*sizeof(double)); 
    int batCapacity = 50;

    FILE *fpointer;
    double prices = 0;
    char date[20];
    char singleline[25];

    fpointer = fopen("APIGetElspotPrices\\output.csv", "r"); /* For at fortælle at vi vil gerne læse fra det fil, vi bruger derfor "r" */
    generateEvArray(evArray, evArrayLen);
    qsort(evArray, evArrayLen, sizeof(double), cmpFun);

    if (fpointer != NULL) {
        while (!feof(fpointer)){
            fgets(singleline, 25, fpointer); /* For at læse den linje pr. linje */
            sscanf(singleline, "%[^;];%lf", &date, &prices);
            printf("%s, %.2f\n", date, prices);
        }
    }
    else 
        return 1;
    
    free(evArray);

    return fclose(fpointer);
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

void generateEvArray(double evArray[], int evArrayLen){
    for (int i = 0; i < evArrayLen; i++){
        evArray[i] = rand() % (100-10) + 10;
    }
}

int cmpFun(const void *ep1, const void *ep2) {
    double *tp1 = (double *)ep1,
           *tp2 = (double *)ep2;
    
    if(*tp1 < *tp2) 
        return -1;
    else if (*tp1 >*tp2)
        return 1;
    else
        return 0;
}

void printArray(double array[], int arrayLen) {
    for(int i = 0; i < arrayLen; i++ ) {
        printf(" %f ", array[i]);
    }
}


