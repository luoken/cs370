//
//  Main.c
//  sample
//
//  Created by Ken Luo on 1/26/16.
//  Copyright © 2016 Ken Luo. All rights reserved.
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int average;

int size = 0;


void *calcAvg(void *arg);
int main(int argc, char *argv[]){
    /* initialize an array of the integers to be passed */
    int *nums = (int*)malloc((argc - 1)*sizeof(int));
    int i = 1;
    for(i = 1; i < argc ; i++){
        nums[i-1] = atoi(argv[i]);
        size++;
    }
    
    /* Thread Identifier */
    pthread_t avgThread;
    
    pthread_create(&avgThread, NULL, calcAvg, (void*)nums);
    
    pthread_join(avgThread, NULL);
    printf("average = %d \n",average);
    free(nums);
    
}
void *calcAvg(void *arg){
    int *val_p = (int *) arg;
    int sum = 0;
    int i = 0;
    for( i = 0; i < size; i++){
        sum += val_p[i];
    }
    average = sum / (size);
    pthread_exit(0);

}
