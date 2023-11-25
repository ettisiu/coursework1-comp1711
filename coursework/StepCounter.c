#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
    typedef struct{
        char start_time[100];
        char end_time[100];
    }interval;

    int buffer_size = 269; // The buffer temporarily holds the data from the file before it is needed
    char line[buffer_size];
    int counter = 0; // Keeps track of the loops in the file

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


void inputfile(const char *input){

FILE *input = fopen("FitnessData_2023.csv", "r"); 

if (input == NULL) {
    printf("There was a error when printing.\n"); 
    return 1;
    }




int findfeweststeps(FITNESS_DATA *fit , int counter){
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

int findmoststeps(FITNESS_DATA *fit , int counter){
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




int findmeansteps(FITNESS_DATA *fit, int counter) {
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
void longestperiod(FITNESS_DATA *fit, int counter){
    int the_current_count = 0;
    int the_max_count = 0;
    int start_index = 0;
    char the_current_start_time;
    char the_current_end_time;

    for (int i = 0; i < counter; i++){
        if (fit[i].steps == 1){
            if (the_current_count == 0){
                the_current_start_time = fit[i].date[NULL] + fit[i].time[NULL];

            }
            the_current_count++;
        }
    }else{
        if (the_current_count > the_max_count){
            the_max_count = the_current_count;
            the_current_end_time = fit[i].date[NULL] + fit[i].time[NULL];
            start_index = i - the_current_count;
        }
        the_current_count = 0;
    }
}
if (the_current_count > the_max_count){
    the_max_count = the_current_count;
    the_current_end_time = fit[i].date[NULL] + fit[i].time[NULL];
    start_index = i - the_current_count;
}
if (the_max_count >= 500){
    interval longest_period;
    longest_period.start_time = the_current_start_time;
    longest_period.end_time = the_current_end_time;
}
return longest_period;

}



// Complete the main function
int main() {
    FITNESS_DATA *fit = malloc(120 * sizeof(fit)); // Is here to allocate the memory dynamically


char date[120]; // Setting variables for the date, time and steps and the size of the array it can hold
char time[120];
int steps;


 while (fgets(line, buffer_size, input) != NULL) // Fgets is a pointer to an array of charchters where the string 
 //Read will be stored. 
 //Buffer_size is the maximum amount of of charchers its reading
    {// Input is the file pointer which will find the file and it will read the file
    tokeniseRecord(line, ",", date, time, &steps);
    fit = realloc(fit, (counter + 1) * sizeof(FITNESS_DATA));
    strcpy(fit[counter].date, date);
    strcpy(fit[counter].time, time);
    



    char stepsgone[40]; // Assuming a maximum of 40 characters for the steps value
    snprintf(stepsgone, sizeof(stepsgone), "%d", steps);
    fit[counter].steps = atoi(stepsgone); // Atoi means it coverts ascii to an integer
    counter++;
   
   
   
   
    }
}
   
   char option

   printf("A: Specify the filename to be imported\n");
   printf("B: Display the total number of records in the file\n");
   printf("C: Find the date and time of the timeslot with the fewest steps");
   printf("D: Find the date and time of the timeslot with the largest number of steps");
   printf("E: Find the mean step count of all the records in the file");
   printf("F: Find the longest continuous period where the step count is above 500 steps");
   printf("Q: Quit");

   scanf("%c", &option);
   

   switch(option){
    
    case 'A';
    const char *input = "FitnessData_2023.csv";
    inputfile(input);
    printf("Error: could not open file\n");
    break;
   
    
    case 'B';
    printf("Total number of records: %d\n", counter);
    break;

    case 'C';
    printf("feweststeps: %s/%s\n", findfeweststeps(lowestStepsIndex).date, findfeweststeps(lowestStepsIndex).time);
    break;

    case 'D';
    printf("Largest steps: %s/%s\n", findmoststeps(moststepsIndex).date, findmoststeps(moststepsIndex).time);
    break;

    case 'E';
    printf("Mean step count: %d\n", findmeansteps(meanstepsIndex).steps);
    break;

    case 'F';
    printf("Longest period: %s - %s\n", longest_period.start_time, longest_period.end_time");
    break;

    case 'Q';
    printf("Quitting program\n");
    break;
    
    default; break;
}
fclose(input);
   }
    return 0;



