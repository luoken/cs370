#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int numOfThreads;
int numOfValues;

int* createArray(int N, int z){
  int* array = (int*) malloc (N * sizeof(int));
  for(int i = 0; i < N; i++){
    array[i] = rand() % z;
  }
  return array;
}

void printArray(int* array, int n){
  for(int i = 0; i < n; i++){
    printf("%d %d\n", i, array[i]);
  }
}

int countArray(int* array, int left, int right, int k){
  int count = 0;
  for(int i = left; i < right; i++){
    if(array[i] == k){
      count++;
    }
  }
  return count;
}

struct threadArg{
  int* array;
  int id;
  int count;
  int k;
};

void* threadCount(void *arg){
  struct threadArg *tArg = (struct threadArg*) arg;
  tArg->count = 0;
  int left = tArg->id * (numOfValues / numOfThreads);
  int right;

  if(tArg->id == (numOfThreads -1)){
    right = numOfValues;
  }
  else
  right = (numOfValues / numOfThreads) + left;

  tArg->count = countArray(tArg->array, left, right, tArg->k);    

  printf("Thread id: %d: ", tArg->id);

  for(int i = left; i < right; i++){
    printf("%d", tArg->array[i]);
  }
  printf("\n");
   //print out result in its own loop. 
  //careful to print after all threads are done.

  pthread_exit(NULL);
}

int main(int argc, char *argv[]){
  srand(1024);

  int N = 0, z = 0, k = 0, M = 0;
  
  //N is the number of numbers you want
  //z is from 0 - z number
  //k is your key
  //M is the partitions, how many threads you want to open up
  if(argc < 4){
    printf("usage: %s <N> <z> <k> <M>\n", argv[0]);
    return 0;

  }

  N = atoi(argv[1]);
  z = atoi(argv[2]);
  k = atoi(argv[3]);
  M = atoi(argv[4]);

  numOfThreads = M;
  numOfValues = N;
  
  printf("N = %d \n", N);
  printf("z = %d \n", z);
  printf("k = %d \n", k);
  printf("M = %d \n", M);

int* array =  createArray(N,z);

 printArray(array, N);
 
 pthread_t thread[M];
 struct threadArg *tArg = malloc(M * sizeof(int)); 

 for(int i = 0; i < M; i++){
   pthread_create(&thread[i], NULL, threadCount, &tArg[i]);
   tArg[i].array = array;
   tArg[i].id = i;
   tArg[i].k = k;
 }

 for(int i = 0; i < M; i++){
   pthread_join(thread[i], NULL);
 }
 int total = 0;
 for(int i = 0; i < M; i++){
   total = total + tArg[i].count;
 }
 printf("The total count for %d is: %d\n",k , total);
  return 0;
}
