#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void child_process(int p[]) {
    close(p[1]);//关闭写端
    char buf[1] = {0};
    read(p[0], buf, sizeof(buf));
    int firstNum = buf[0];
    if(firstNum == 0) {
        return;
    }
    // printf("firstNum : %d\n", firstNum);
    printf("prime %d\n", firstNum);

    int p1[2];
    int newNum = 0;
    pipe(p1);
    int pid = fork();
    if(pid == 0) {
        child_process(p1);
    } else {
        close(p1[0]);//关闭读端
        while(1) {
            buf[0] = 0;
            read(p[0], buf, sizeof(buf));
            newNum = buf[0];
            // printf("newNum : %d\n", newNum);
            if(newNum == 0) {
                break;
            }
            if(newNum % firstNum != 0) {
                write(p1[1], buf, 1);
            }
        }
        close(p[0]);//关闭读端
        close(p1[1]);//关闭写端
        wait(0);
    }
}

int main(int argc, char* argv[]) {
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid == 0) {
        child_process(p);
    }else {
        close(p[0]);
        for(int i = 2; i <= 35; i++) {
            char buf[1] = {0};
            buf[0] = i;
            write(p[1], buf, 1);
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}