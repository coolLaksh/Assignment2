#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(){


    pid_t t1, t2, t3;

    int count = 0;

    t1 = fork();

    if(t1 == 0){

        int a = excel("/home/laksh/Assignment2/Question1.2/Test1.sh",NULL);
            if(a < 0){
                printf("ERROR - excel not working");
            }

    }else if(t1 > 0){

        t2 = fork();

        if(t2 == 0){

            int a = excel("/home/laksh/Assignment2/Question1.2/Test2.sh",NULL);
            if(a < 0){
                printf("ERROR - excel not working");
            }

        }else if(t2 > 0){

            if(t3 == 0){

            int a = excel("/home/laksh/Assignment2/Question1.2/Test3.sh",NULL);
            if(a < 0){
                printf("ERROR - excel not working");
            }

            }else if( t3 > 0){

            }

        }


    }


    

}