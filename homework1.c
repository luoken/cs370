#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void threadSplit(void* threadid, int totalLengthofArray, int numberOfThreads);
int**  dynamicArraySplit(int* array, int totalLengthofArray, int numberOfThreads);
int sequentialCounter(int* array, int key, int sizeOfArray);
int** allocate2dArray(int row, int col);
void freeSpace(int** array, int row);
void *Counter(void* threadid){
  long tid;
  tid = (long) threadid;
  //tells you the thread created
  printf("created %ld\n", tid);
  pthread_exit(NULL);
  }

int main(int argc, char *argv[]){
  int N = 0, z = 0, k = 0, M = 0;
  //n will be the amount of intergers to generate
  //z will be the range from 0 - z
  //k is the number you're searching for.
  //M is the amount of partitions you're going to have

  //sets my array to null  
  int *array = NULL;

  if(argc < 4){
    printf("not enough arguments, please enter more.");
    return 0;
  }

  N = atoi(argv[1]);
  z = atoi(argv[2]);
  k = atoi(argv[3]);
  M = atoi(argv[4]);

  //makes space for array  
  array = (int*) malloc(z * sizeof(int));

  //print out what N z k M are set to
  printf("N = %d\n", N);
  printf("z = %d\n", z);
  printf("k = %d\n", k);
  printf("M = %d\n", M);

  pthread_t threads[M];
  
  int rc = 0;
  //i and k are just counter variables.

  for(int x = 0; x < N; x++){
    array[x] = rand() % z + 1;
  }

  for(long i = 0; i < M; i++){
    //void * i will start the thread at that point like void*3 will make it at thread 3
    //forcing i to be anything. casting/stripping it and say (void *)
    //&threads[i] is a array of thread 
    //& give me the address of the thread
    rc = pthread_create(&threads[i], NULL, Counter, (void *) i);

    //if rc is true then there is an error.

    if(rc){
      printf("Error!! return code from pthread_create() is %d\n", rc);
      exit(-1);
    }


  }
  

  for(int temp = 0; temp < N; temp++){
    printf("%d %d\n",temp,array[temp]);
  }

  printf("%d Appears in the array %d times.\n", k, sequentialCounter(array,k, N));
  




  dynamicArraySplit(array, N, M);

  
  pthread_exit(NULL);
  
  return 0;
}
  //N will be the amount of intergers to generate
  //z will be the range from 0 - z
  //k is the number you're searching for.
  //M is the amount of partitions you're going to have
void freeSpace(int** array, int row){
  for(int i = 0; i < row; i++){
    free(array[i]);
  }
  free(array);
}

int sequentialCounter(int* array, int key, int sizeOfArray){
  int counter = 0;
  for(int i = 0; i < sizeOfArray ; i++){
    if(array[i] == key){

	counter++;
      }
  }
  return counter;
}

int** dynamicArraySplit(int* array, int totalLengthofArray, int numberOfThreads){
  int totalOfValuesPerArray = totalLengthofArray / numberOfThreads;
  int remainder = totalLengthofArray % numberOfThreads;

  int** newArray = (int**)malloc(numberOfThreads * sizeof(int *));
  for(int i = 0; i < numberOfThreads; i++){
    newArray[i] = (int*)malloc(totalOfValuesPerArray * sizeof(int));
  }


  printf("before arrayCounter");

  int arrayCounter = 0;

  for(int i = 0; i < totalLengthofArray; i++){
    for(int k = 0; k < totalOfValuesPerArray; k++){
      newArray[i][k] = array[arrayCounter];
      arrayCounter++;
    }
  }

  printf("made it to here");

  for(int i = 0; i < totalLengthofArray; i++){
    for(int k = 0; k < totalOfValuesPerArray; k++){
      printf("%d ", newArray[i][k]);
    }
    printf("\n");
  }

  return newArray;
}

int** allocate2dArray(int row, int col){
  int** array = (int**)malloc(row * sizeof(int *));
  for(int i = 0; i < row; i++){
    array[i] = (int*)malloc(col * sizeof(int));
  }
  return array;
}
