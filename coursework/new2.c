#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char date[26];
    char time[26];
    int steps;
} FITNESS_DATA;

typedef struct {
    char start_time[26];
    char end_time[26];
} interval;

void tokeniseRecord(const char *input, const char *delimiter,
                    char **date, char **time, int *steps);
void inputfile(const char *filename, FITNESS_DATA **fit, int *counter);
int findfeweststeps(FITNESS_DATA *fit, int counter);
int findmoststeps(FITNESS_DATA *fit, int counter);
int findmeansteps(FITNESS_DATA *fit, int counter);
void longestperiod(FITNESS_DATA *fit, int counter, interval *longest_period);
void freeMemory(FITNESS_DATA *fit, int counter);

int main() {
    FITNESS_DATA *fit = NULL;
    int counter = 0;

    char option;

    printf("A: Specify the filename to be imported\n");
    printf("B: Display the total number of records in the file\n");
    printf("C: Find the date and time of the timeslot with the fewest steps\n");
    printf("D: Find the date and time of the timeslot with the largest number of steps\n");
    printf("E: Find the mean step count of all the records in the file\n");
    printf("F: Find the longest continuous period where the step count is above 500 steps\n");
    printf("Q: Quit\n");

    scanf(" %c", &option);

    interval longestPeriod;

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
            longestperiod(fit, counter, &longestPeriod);
            printf("Longest period: %s - %s\n", longestPeriod.start_time, longestPeriod.end_time);
            break;

        case 'Q':
            printf("Quitting program\n");
            break;

        default:
            printf("Invalid option\n");
    }
}

    // Free allocated memory
    freeMemory(fit, counter);

    return 0;
}

void tokeniseRecord(const char *input, const char *delimiter,
                    char **date, char **time, int *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);

    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        *date = strdup(token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        *time = strdup(token);
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
    char *date, *time;
    int steps;

    while (fgets(line, sizeof(line), input) != NULL) {
        *fit = realloc(*fit, (*counter + 1) * sizeof(FITNESS_DATA));

        tokeniseRecord(line, ",", &date, &time, &steps);

        strcpy((*fit)[*counter].date, date);
        strcpy((*fit)[*counter].time, time);
        (*fit)[*counter].steps = steps;

        // Increment counter
        (*counter)++;

        // Free memory for date and time
        free(date);
        free(time);
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

void longestperiod(FITNESS_DATA *fit, int counter, interval *longest_period) {
    int currentCount = 0;
    int maxCount = 0;
    int startTime = 0;
    int currentStartTime = 0;
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
                currentEndTime = i - 1;
            }
            currentCount = 0;
        }
    }

    if (currentCount > maxCount) {
        maxCount = currentCount;
        currentEndTime = counter - 1;
        startTime = currentStartTime;
    }

    strcpy(longest_period->start_time, fit[startTime].time);
    strcpy(longest_period->end_time, fit[currentEndTime].time);
}

void freeMemory(FITNESS_DATA *fit, int counter) {
    for (int i = 0; i < counter; i++) {
        // Free memory for date and time
        free(fit[i].date);
        free(fit[i].time);
    }
    // Free the array itself
    free(fit);
}
