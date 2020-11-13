#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
k = 0;

char* getCurrentTime(void);
int readFile(void);

int main (void)
{
    if (readFile()) {
        printf("NEJ\n");
    }
    return(0);
}

int readFile(void) {
    FILE *fpointer;
    double price;
    char date[20];
    char singleline[20];
    fpointer = fopen("output.txt", "r"); /* For at fortælle at vi vil gerne læse fra det fil, vi bruger derfor "r" */

    if (fpointer != NULL) {
        int i = 0;
        while (!feof(fpointer)){
            for(int x = 0; x < 2; x++) {
                fgets(singleline, 20, fpointer); /* For at læse den linje pr. linje */
                if (x % 2 == 0) 
                    memcpy(date, strtok(singleline, "\n"), sizeof singleline);
                else 
                    price = atof(singleline); /* Konverterer til en double */
            } 
            if (strcmp(date, getCurrentTime()) == 0) {
                printf("Pris nu: %0.3f \x9Bre/kWh  - Dato: %s\n",(price/10), date);
                break;
            }
            i++;
        }
    }
    else 
        return 1;
    return fclose(fpointer);
}

char* getCurrentTime(void) {
    time_t timer;
    char* buffer;
    struct tm* tm_info;

    buffer = (char*)malloc(15);
    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer, 15, "%Y-%m-%d %H", tm_info);
    return buffer;
}