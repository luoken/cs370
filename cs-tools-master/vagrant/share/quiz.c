#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>

int world_size;
int my_rank;
char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

void doBoss();
void doWorker();
static int N = 20;

int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Get_processor_name(processor_name, &name_len);
  srand((int)getpid());

  if (my_rank == 0) {
    doBoss();
  } else {
    doWorker();
  }

  MPI_Finalize();

  return 0;
}

void doBoss()
{
  MPI_Status status;
  int i = 0;
  int done = 0;
  int worker_size = world_size - 1;
   for(i = 0; i < 10; i++){
   int worker = 1 + (rand() % worker_size);
   MPI_Send(&done, 1, MPI_INT, worker, 0, MPI_COMM_WORLD);
   MPI_Send(&N, 1, MPI_INT, worker, 0, MPI_COMM_WORLD);	
   
   MPI_Recv(&N, 1, MPI_INT, worker, 0, MPI_COMM_WORLD, 
              &status);
   }
   for(i = 1; i < world_size; i++){
   done = 1;
   MPI_Send(&done, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
   MPI_Send(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
   }

}

void doWorker()
{
  MPI_Status status;
  int master_id = 0;
  int N = 0;
  int touch = 0, done = 0;
 while(done == 0){
  MPI_Recv(&done, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,&status);
  MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
  printf("worker N: %d", N);
   if(touch == 1){
     N--;
   }
   if(touch == 0){
    N++;
    touch = 1;
   }
    if(done == 1){
     break;
    }

  MPI_Send(&N, 1, MPI_INT, master_id, 0, MPI_COMM_WORLD);
 }


}
