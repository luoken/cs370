#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//creates 5 threads
#define NUM_THREADS 5



void *PrintHello(void *threadid){
  long tid;
  tid = (long) threadid;
  //prints out hello world and the thread id
  //#%ld is long id?
  printf("Hello world! It's me, thread #%ld! \n", tid);
  //exit pthread;
  pthread_exit(NULL);  
}

int main(int argc, char *argv[]){
  //creates number of threads up top. and grabs the number here
  pthread_t threads[NUM_THREADS];

  int rc = 2;
  //makes sure t is set to 0;
  long t = 0;
  //sets thread count to 1.
  for(t = 1; t < NUM_THREADS; t++){

    //creating the thread here.
    printf("In main: creating thread %ld \n", t);
    //passes the number into t. if after void * set to number it'll stay at that number
    rc = pthread_create(&threads[t], NULL, PrintHello, (void *) t);
    //if has error
    if(rc){
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  //exit p threads
  pthread_exit(NULL);

  return 0;
}
