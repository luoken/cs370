#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  //sets n and z to 0
  int N = 0, z = 0;
  //sets the array to null
  int *array = NULL;

  //this tells you if you are taking in too little argument
  if (argc < 2){

    printf("usage: %s <N> <z>\n", argv[0]);
    return 0;
  }
  //takes in the values for n and z from compiling
  N = atoi(argv[1]);
  z = atoi(argv[2]);
  printf("N = %d\n", N);
  printf("z= %d\n", z);

  array = (int*) malloc(z * sizeof(int));


  //have a for loop so N deals with the size of the array
  for(int i = 0; i < N; i++){
    //rand()%z will return a value between 0- z and set it to the array
    array[i] = rand() % z;
 
}

  for(int i = 0; i < N; i++){
    // i is the like number and array[i]is the value inside of array.
    printf("%d %d\n", i, array[i]);
   

  }

  return 0;
}
