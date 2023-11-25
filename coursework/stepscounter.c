#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file
typedef struct {
    char start_time[26];
    char end_time[26];
} interval;

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array


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


// Function prototypes
void inputfile(const char *filename, FITNESS_DATA **fit, int *counter);
FILE *input = fopen("FitnessData_2023.csv", "r"); 

if input == NULL {
    printf("There was a error when printing.\n"); 
    return 1;
    }



int findfeweststeps(FITNESS_DATA *fit, int counter){
int feweststeps = 0;
    int feweststepsIndex = 0;
    
    int feweststeps = fit[0].steps;
    for (int i = 0; i < counter; i++){
        if (fit[i].steps < feweststeps){
            feweststeps = fit[i].steps;
            lowestStepsIndex = i;
        }

    }
    return lowestStepsIndex;
}




int findmoststeps(FITNESS_DATA *fit, int counter){
    int moststeps = 0;
    int moststepsIndex = 0;
    
    
    int moststeps = fit[0].steps;
    for (int i = 0; i < counter; i++){
        if (fit[i].steps > moststeps){
            moststeps = fit[i].steps;
            moststepsIndex = i;

        }
    }
    return moststepsIndex;
}



int findmeansteps(FITNESS_DATA *fit, int counter){
    double meansteps = 0;
    int meanstepsIndex = 0;

    for (int i = 0; i < counter; i++) {
        meansteps += fit[i].steps;
    }

    double meansteps1 = meansteps / counter;

    // Now, find the index of the entry with steps closest to the mean
    double themindifference = (fit[0].steps - meansteps1);
    for (int i = 1; i < counter; i++) {
        double difference = (fit[i].steps - meansteps1);
        if (difference < themindifference) {
            themindifference = difference;
            meanstepsIndex = i;
        }
    }

    return meanstepsIndex;
}


typedef struct {
    char start_time;
    char end_time;
} interval;

void longestperiod(FITNESS_DATA *fit, int counter) {
    int the_current_count = 0;
    int the_max_count = 0;
    int start_index = 0;
    char the_current_start_time;
    char the_current_end_time;

    interval longest_period; // Declare outside the block

    for (int i = 0; i < counter; i++) {
        if (fit[i].steps == 1) {
            if (the_current_count == 0) {
                the_current_start_time = fit[i].date[NULL] + fit[i].time[NULL];
            }
            the_current_count++;
        } else {
            if (the_current_count > the_max_count) {
                the_max_count = the_current_count;
                the_current_end_time = fit[i].date[NULL] + fit[i].time[NULL];
                start_index = i - the_current_count;
            }
            the_current_count = 0;
        }
    }

    if (the_current_count > the_max_count) {
        the_max_count = the_current_count;
        the_current_end_time = fit[i].date[NULL] + fit[i].time[NULL];
        start_index = i - the_current_count;
    }

    if (the_max_count >= 500) {
        // Use longest_period
        longest_period.start_time = the_current_start_time;
        longest_period.end_time = the_current_end_time;
    }

    // Handle the case when the_max_count is less than 500

    // Return the longest_period (might be uninitialized if the_max_count < 500)
    return longest_period;
}







int main() {
    FITNESS_DATA *fit = NULL; // Initialize to NULL
    int counter = 0;

    char option;

    printf("A: Specify the filename to be imported\n");
    printf("B: Display the total number of records in the file\n");
    printf("C: Find the date and time of the timeslot with the fewest steps\n");
    printf("D: Find the date and time of the timeslot with the largest number of steps\n");
    printf("E: Find the mean step count of all the records in the file\n");
    printf("F: Find the longest continuous period where the step count is above 500 steps\n");
    printf("Q: Quit\n");

    scanf(" %c", &option); // Add a space before %c to consume the newline character

    switch (option) {
        case 'A':
            inputfile("FitnessData_2023.csv", &fit, &counter);
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
        }

        case 'E': {
            int meanIndex = findmeansteps(fit, counter);
            printf("Mean step count: %d\n", fit[meanIndex].steps);
            break;
        }

        case 'F':
            longestperiod(fit, counter);
            break;

        case 'Q':
            printf("Quitting program\n");
            break;

        default:
            printf("Invalid option\n");
    }

    // Free allocated memory
    free(fit);

    return 0;
}

void inputfile(const char *filename, FITNESS_DATA **fit, int *counter) {
    FILE *input = fopen(filename, "r");

    if (input == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }

    char line[269];
    char date[100];
    char time[100];
    int steps;

    while (fgets(line, sizeof(line), input) != NULL) {
        *fit = realloc(*fit, (*counter + 1) * sizeof(FITNESS_DATA));

        tokeniseRecord(line, ",", date, time, &steps);

        strcpy((*fit)[*counter].date, date);
        strcpy((*fit)[*counter].time, time);
        (*fit)[*counter].steps = steps;

        (*counter)++;
    }

    fclose(input);
}