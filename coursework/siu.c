#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here



// Global variables for filename and FITNESS_DATA array
typedef struct {
    char start_time[26];
    char end_time[26];
} interval;


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }


void inputfile(const char *filename, FITNESS_DATA fit[], int *counter);
int findfeweststeps(FITNESS_DATA *fit, int counter);
int findmoststeps(FITNESS_DATA *fit, int counter);

void longestperiod(FITNESS_DATA *fit, int counter, interval *longest_period);




// Complete the main function
int main() {
   FITNESS_DATA fit [1000];
    int counter = 0;

    char option;

    
    interval longestPeriod;
    while (option != 'Q'){
    printf("A: Specify the filename to be imported\n");
    printf("B: Display the total number of records in the file\n");
    printf("C: Find the date and time of the timeslot with the fewest steps\n");
    printf("D: Find the date and time of the timeslot with the largest number of steps\n");
    printf("E: Find the mean step count of all the records in the file\n");
    printf("F: Find the longest continuous period where the step count is above 500 steps\n");
    printf("Q: Quit\n");

    scanf(" %c", &option);


    switch (option) {
        case 'A':
            inputfile("FitnessData_2023.csv", fit, &counter);
            printf("file imported\n");
            break;

        case 'B':
            printf("Total number of records: %d\n", counter);
            break;

        case 'C': {
            int fewestIndex = findfeweststeps(fit, counter);
            printf("Fewest steps: %s/%s\n", fit[fewestIndex].date, fit[fewestIndex].time);
            break;
        }

        case 'D': {
            int mostIndex = findmoststeps(fit, counter);
            printf("Largest steps: %s/%s\n", fit[mostIndex].date, fit[mostIndex].time);
            break;
    

        case 'E': {

            break;
        }

        case 'F':{
            longestperiod(fit, counter, &longestPeriod);
            printf("Longest period: %s/%s - %s/%s\n", fit[mostIndex].date, longestPeriod.start_time , fit[mostIndex].date, longestPeriod.end_time);
            break;
        }
        
        case 'Q':
            printf("Quitting program\n");
            break;

        default:
            printf("Invalid option\n");
    }

    }
}
    return 0;
}


void inputfile(const char *filename, FITNESS_DATA fit[], int *counter) {
    FILE *input = fopen(filename, "r");

    if (input == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }

    char line[269];
    char date[11], time[6];
    char steps[20];

    while (fgets(line, sizeof(line), input) != NULL) {
       
        
        // Allocate memory for date and time
        tokeniseRecord(line, ",", date, time, steps);
        strcpy((fit)[*counter].date, date);
        strcpy((fit)[*counter].time, time);
        (fit)[*counter].steps = atoi(steps);
        

        // Increment counter
        (*counter)++;

        // Free memory for date and time

    }

    fclose(input);
}

int findfeweststeps(FITNESS_DATA *fit, int counter) {
    int feweststeps = fit[0].steps;
    int feweststepsIndex = 0;

    for (int i = 0; i < counter; i++) {
        if (fit[i].steps < feweststeps) {
            feweststeps = fit[i].steps;
            feweststepsIndex = i;
        }
    }

    return feweststepsIndex;
}

int findmoststeps(FITNESS_DATA *fit, int counter) {
    int moststeps = fit[0].steps;
    int moststepsIndex = 0;

    for (int i = 0; i < counter; i++) {
        if (fit[i].steps > moststeps) {
            moststeps = fit[i].steps;
            moststepsIndex = i;
        }
    }

    return moststepsIndex;
}










void longestperiod(FITNESS_DATA *fit, int counter, interval *longest_period) {
    int currentCount = 0;
    int maxCount = 0;
    int currentStartTime = 0;
    int maxStartTime = 0;
    int currentEndTime = 0;

    for (int i = 0; i < counter; i++) {
        if (fit[i].steps > 500) {
            if (currentCount == 0) {
                currentStartTime = i;
            }
            currentCount++;
        } else {
            if (currentCount > maxCount) {
                maxCount = currentCount;
                maxStartTime = currentStartTime;
                currentEndTime = i - 1;
            }
            currentCount = 0;
        }
    }

    if (currentCount > maxCount) {
        maxCount = currentCount;
        maxStartTime = currentStartTime;
        currentEndTime = counter - 1;
    }

    for (int i = 0; i < sizeof(fit[0].time); i++) {
        longest_period->start_time[i] = fit[maxStartTime].time[i];
        longest_period->end_time[i] = fit[currentEndTime].time[i];
    }
}