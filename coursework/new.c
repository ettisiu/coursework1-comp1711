#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct moved to header file
typedef struct {
	char date[100];
	char time[100];
	int steps;
} FITNESS_DATA;

typedef struct {
    char start_time[100];
    char end_time[100];
} interval;

// Define any additional variables here


// Function prototypes
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, int *steps);
void inputfile(const char *filename, FITNESS_DATA **fit, int *counter);
int findfeweststeps(FITNESS_DATA *fit, int counter);
int findmoststeps(FITNESS_DATA *fit, int counter);
int findmeansteps(FITNESS_DATA *fit, int counter);
char longestperiod(FITNESS_DATA *fit, int counter, interval *longest_period);



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

    interval longestperiod;

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
            char longestperiod(fit, counter, longestperiod);
            printf("Longest period: %s - %s\n", longestperiod.start_time, longestperiod.end_time);
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

void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, int *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);

    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        strcpy(date, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        *steps = atoi(token);
    }

    // Free the duplicated string
    free(inputCopy);
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

int findmeansteps(FITNESS_DATA *fit, int counter) {
    int totalsteps = 0;

    for (int i = 0; i < counter; i++) {
        totalsteps += fit[i].steps;
    }

    return totalsteps / counter;
}


char longestperiod(FITNESS_DATA *fit, int counter, interval *longest_period) {
    int the_current_count = 0;
    int the_max_count = 0;
    int start_time = 0;
    int current_start_time = 0;
    int current_end_time = 0;

    for (int i = 0; i < counter; i++) {
        if (fit[i].steps > 500) {
            if (the_current_count == 0) {
                current_start_time = i;
            }
            the_current_count++;
        } else {
            if (the_current_count > the_max_count) {
                the_max_count = the_current_count;
                current_end_time = i - 1;
            }
            the_current_count = 0;
        }
    }

    if (the_current_count > the_max_count) {
        the_max_count = the_current_count;
        current_end_time = counter - 1;
        start_time = current_start_time;
    }

    strcpy(longest_period->start_time, fit[start_time].time);
    strcpy(longest_period->end_time, fit[current_end_time].time);
}