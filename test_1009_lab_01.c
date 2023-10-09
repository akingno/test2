#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROWS 4
#define COLUMNS 15000

int aiMatrix[ROWS][COLUMNS];
int iSum = 0;
pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;

void init() {
  int iRow, iColumn;
  int cont = 0;
  for(iRow = 0; iRow < ROWS; iRow++){
    for(iColumn = 0; iColumn < COLUMNS; iColumn++) {
      cont++;
      aiMatrix[iRow][iColumn] = cont;
    }
  }
}

void *calculateSum(void * arg){
  int iRow = *((int *) arg);
  int iColumn;
  int Coltmp = 0;
  for(iColumn = 0; iColumn < COLUMNS; iColumn++) {
    Coltmp = Coltmp + aiMatrix[iRow][iColumn];
  }
  pthread_mutex_lock(&sum_mutex);
  iSum += Coltmp;
  pthread_mutex_unlock(&sum_mutex);
  return NULL;
}

int main(){
  init();
  pthread_t threads[ROWS];
  int iRow;
  int row_indices[ROWS];
  for(iRow = 0; iRow < ROWS; iRow++){
    row_indices[iRow] = iRow;
    pthread_create(&threads[iRow], NULL, calculateSum, &row_indices[iRow]);
  }
  for(iRow = 0; iRow < ROWS; iRow++){
    pthread_join(threads[iRow], NULL);
  }
  printf("sum = %d\n", iSum);
  return 0;
}
