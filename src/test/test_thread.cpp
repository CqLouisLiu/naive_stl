#include "../thread/Thread_base.h"


using namespace naive;


void* thread_func(void* arg){

    printf("%lu\n",Thread_get_id());

}

int main(){


    thread_id tid;

    int err;
    if((err=Thread_create(&tid,NULL,thread_func,NULL))!=0){
        fprintf(stderr,"error at create thread",err);
    }

    printf("%lu\n",Thread_get_id());


    sleep(5);

    return 0;
}