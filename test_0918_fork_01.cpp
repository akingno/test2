#include <iostream>  
#include <pthread.h>   
#include<cstdio>
using namespace std;  
  
void* hjzgg(void* arg)  
{  
    while(1){
        cout<<"Hello, everyone! I am hjzgg!"<<endl;  
        getchar();
    }
    return NULL;
}  
  
int main(int args, char* argv[])  
{  
    pthread_t tid;  
    pthread_create(&tid, NULL, hjzgg, NULL);     
    while(1);//主线程不要提前结束 
    return 0;    
} 

