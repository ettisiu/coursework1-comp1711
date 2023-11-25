
#include <stdio.h>

void printArray(int a[][3] ){
  for (size_t i = 0; i <= 1; ++i) {
     for (size_t j = 0; j <= 2; ++j) {
        printf("%d ", a[i][j]);
     }
     printf("\n"); // start new line of output 
     }
}
//nested loops to print the array

int main() {
  int array1[2][3] = {{1, 2, 3}, {4, 5, 6}}; // we got a 0 at the end of the array
  printf("Values in array1 by row are:\n");
  printArray(array1);

  int array2[2][3] = {1, 2, 3, 4, 5}; // bc a 0 is printed instead of 6 is bc we didnt inzitialize it in the first arrat
  printf("Values in array2 by row are:\n");
  printArray(array2);


  int array3[2][3] = {{1, 2}, {4}}; // for any place that doesnt have a value it is replaced by 0
  printf("Values in array3 by row are:\n");
  printArray(array3);
  
  return 0;
}
