#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>
#include<time.h>
#include<sched.h>
#include<string.h>


/**
 * 
 * Count A for Other Policy
 * Count B for FIFO policy
 * Count C for RR policy
*/


int FIFO_Priority = 1;
int OTHER_Priority = 0;
int RR_Priority = 1;

void *Count_A(void *arg){

    int policy = SCHED_OTHER, check;
    struct sched_param param;
    param.sched_priority = OTHER_Priority;
    OTHER_Priority += 1;
    pthread_t my_thread = pthread_self();
    check = pthread_setschedparam(my_thread, policy, &param);
    if(check == -1){
        printf("Failed");
        pthread_exit(NULL);
    }else{

        for(unsigned long int i = 0;i<4294967296;i++){

        }

    }

}

void *Count_B(void *arg){

    int policy = SCHED_FIFO, check;
    struct sched_param param;
    param.sched_priority = FIFO_Priority;
    FIFO_Priority += 1;
    pthread_t my_thread = pthread_self();
    check = pthread_setschedparam(my_thread, policy, &param);
    if(check == -1){
        printf("Failed");
        pthread_exit(NULL);
    }else{

        for(unsigned long int i = 0;i<4294967296;i++){

        }

    }

}

void *Count_C(void *arg){

    int policy = SCHED_RR, check;
    struct sched_param param;
    param.sched_priority = RR_Priority;
    FIFO_Priority += 1;
    pthread_t my_thread = pthread_self();
    check = pthread_setschedparam(my_thread, policy, &param);
    if(check == -1){
        printf("Failed");
        pthread_exit(NULL);
    }else{

        for(unsigned long int i = 0;i<4294967296;i++){

        }

    }

}

int main(){
    // 0 for Other , 1 for FIFO , 2 for RR
    struct timespec times[3][10];
    struct timespec  helper1[2], helper2[2], helper3[2];
    pthread_t thread_A, thread_B, thread_C;
    int count = 0;
    char FIFO_TIMES[200], RR_TIMES[200], OTHER_TIMES[200];
    char FIFO_HELPER[100], RR_HELPER[100], OTHER_HELPER[100];

    while(count != 10){

        clock_gettime(CLOCK_BOOTTIME, &helper1[0]);
        pthread_create(&thread_A, NULL, Count_A, NULL);
        pthread_join(thread_A, NULL);
        clock_gettime(CLOCK_BOOTTIME, &helper1[1]);
        //printf("\n%ld %ld\n",helper1[1].tv_nsec, helper1[0].tv_nsec);
        times[0][count].tv_nsec = helper1[1].tv_nsec - helper1[0].tv_nsec;
        times[0][count].tv_sec = helper1[1].tv_sec - helper1[0].tv_sec;

        //printf("\n%f\n", (times[0][count].tv_sec + (times[0][count].tv_nsec) * 0.000000001 ));

        clock_gettime(CLOCK_BOOTTIME, &helper2[0]);
        pthread_create(&thread_B, NULL, Count_B, NULL);
        pthread_join(thread_B, NULL);
        clock_gettime(CLOCK_BOOTTIME, &helper2[1]);

        times[1][count].tv_nsec = helper2[1].tv_nsec - helper2[0].tv_nsec;
        times[1][count].tv_sec = helper2[1].tv_sec - helper2[0].tv_sec;
        
        clock_gettime(CLOCK_BOOTTIME, &helper3[0]);
        pthread_create(&thread_C, NULL, Count_C, NULL);
        pthread_join(thread_C, NULL);
        clock_gettime(CLOCK_BOOTTIME, &helper3[1]);

        times[2][count].tv_nsec = helper3[1].tv_nsec - helper3[0].tv_nsec;
        times[2][count].tv_sec = helper3[1].tv_sec - helper3[0].tv_sec;

        count++;
    }

    // sprintf(OTHER_TIMES,"%ld",(times[0][0].tv_sec));
    // //printf("%ld",OTHER_TIMES);
    // sprintf(FIFO_TIMES,"%ld",times[1][0].tv_sec);
    // sprintf(RR_TIMES,"%ld",times[2][0].tv_sec);

    gcvt((times[0][0].tv_sec + (times[0][0].tv_nsec) * 0.000000001 ), 7, OTHER_TIMES);
    gcvt((times[1][0].tv_sec + (times[1][0].tv_nsec) * 0.000000001 ), 7, FIFO_TIMES);
    gcvt((times[2][0].tv_sec + (times[2][0].tv_nsec) * 0.000000001 ), 7, RR_TIMES);


    strcat(OTHER_TIMES," ");
    strcat(FIFO_TIMES," ");
    strcat(RR_TIMES," ");

    for(int i = 1;i<10;i++){
        
        gcvt((times[0][i].tv_sec + (times[0][i].tv_nsec) * 0.000000001 ), 7, OTHER_HELPER);
        strcat(OTHER_HELPER," ");

        gcvt((times[1][i].tv_sec + (times[1][i].tv_nsec) * 0.000000001 ), 7, FIFO_HELPER);
        strcat(FIFO_HELPER," ");   

        gcvt((times[2][i].tv_sec + (times[2][i].tv_nsec) * 0.000000001 ), 7, RR_HELPER);
        strcat(RR_HELPER," ");       

        strcat(OTHER_TIMES, OTHER_HELPER);
        strcat(FIFO_TIMES, FIFO_HELPER);
        strcat(RR_TIMES, RR_HELPER);

    }

    printf("%s\n",OTHER_TIMES);
    printf("%s\n",FIFO_TIMES);
    printf("%s\n",RR_TIMES);

    FILE *fp1, *fp2, *fp3;

    fp1 = fopen("OTHER.txt","w");
    fputs(OTHER_TIMES,fp1);
    fclose(fp1);

    fp2 = fopen("FIFO.txt","w");
    fputs(FIFO_TIMES,fp2);
    fclose(fp2);

    fp3 = fopen("RR.txt","w");
    fputs(RR_TIMES,fp3);
    fclose(fp3);
}