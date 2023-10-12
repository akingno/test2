#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROWS 4
#define COLUMNS 15000

int aiMatrix[ROWS][COLUMNS];
int iSum = 0;
pthread_mutex_t sum_mutex;  // 定义一个互斥锁

// 初始化矩阵
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

// 计算每一行的和
void* calculateSum(void * arg){
  int iRow = *((int *) arg);
  int iColumn;
  int Coltmp = 0;
  for(iColumn = 0; iColumn < COLUMNS; iColumn++) {
    Coltmp = Coltmp + aiMatrix[iRow][iColumn];
  }
  pthread_mutex_lock(&sum_mutex);  // 加锁
  iSum += Coltmp;  // 更新全局变量
  pthread_mutex_unlock(&sum_mutex);  // 解锁
  return NULL;
}

int main(){
  init();
  int iRow;
  pthread_t threads[ROWS];

  pthread_mutex_init(&sum_mutex, NULL);  // 初始化互斥锁

  // 创建一个线程来处理每一行
  for(iRow = 0; iRow < ROWS; iRow++){
    pthread_create(&threads[iRow], NULL, calculateSum, &iRow);
  }

  // 等待所有线程完成
  for(iRow = 0; iRow < ROWS; iRow++){
    pthread_join(threads[iRow], NULL);
  }

  pthread_mutex_destroy(&sum_mutex);  // 销毁互斥锁

  printf("sum = %d\n", iSum);
  return 0;
}
