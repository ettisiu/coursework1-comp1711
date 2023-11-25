#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}

int compare(const void *a, const void *b) {

return ((FitnessData *)a)->steps - ((FitnessData *)b)->steps;
}

int main() {
 char FitnessData[100];
    printf("Enter the name of the file: ");
    fgets(FitnessData, sizeof(FitnessData), stdin);
    FitnessData[strcspn(FitnessData, "\n")] = '\0';

    FILE *file = fopen(FitnessData, "r");
    if (file == NULL){
        printf("Error opening the file.\n");
        return 1;
    }

    int count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        ++count;
    }
    rewind(file);
    




}


