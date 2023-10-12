#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROWS 4
#define COLUMNS 15000

int aiMatrix[ROWS][COLUMNS];
int iSum = 0;
pthread_mutex_t sum_mutex;  // ����һ��������

// ��ʼ������
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

// ����ÿһ�еĺ�
void* calculateSum(void * arg){
  int iRow = *((int *) arg);
  int iColumn;
  int Coltmp = 0;
  for(iColumn = 0; iColumn < COLUMNS; iColumn++) {
    Coltmp = Coltmp + aiMatrix[iRow][iColumn];
  }
  pthread_mutex_lock(&sum_mutex);  // ����
  iSum += Coltmp;  // ����ȫ�ֱ���
  pthread_mutex_unlock(&sum_mutex);  // ����
  free(arg);  // �ͷŶ�̬������ڴ�
  return NULL;
}

int main(){
  int iRow;  // �Ƶ�����
  init();
  pthread_t threads[ROWS];

  pthread_mutex_init(&sum_mutex, NULL);  // ��ʼ��������

  // ����һ���߳�������ÿһ��
  for(iRow = 0; iRow < ROWS; iRow++){
    int *arg = malloc(sizeof(*arg));
    if ( arg == NULL ) {
      fprintf(stderr, "Couldn't allocate memory for thread arg.\n");
      exit(EXIT_FAILURE);
    }
    *arg = iRow;
    pthread_create(&threads[iRow], NULL, calculateSum, arg);
  }

  // �ȴ������߳����
  for(iRow = 0; iRow < ROWS; iRow++){
    pthread_join(threads[iRow], NULL);
  }

  pthread_mutex_destroy(&sum_mutex);  // ���ٻ�����

  printf("sum = %d\n", iSum);
  return 0;
}

