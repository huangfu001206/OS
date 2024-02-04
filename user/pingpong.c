#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

// int main() {
//     int p1[2];
//     int p2[2];
//     pipe(p1);
//     pipe(p2);
//     if(fork() == 0) {
//         //子进程
//         close(p1[1]);
//         close(p2[0]);
//         char buf[100];
//         read(p1[0], buf, sizeof(buf));
//         int cur_pid = getpid();
//         printf("%d: received %s\n", cur_pid, buf);
//         close(p1[0]);
//         write(p2[1], "pong",4);
//         close(p2[1]);
//     } else {
//         char buf[100];
//         close(p1[0]);
//         close(p2[1]);
//         write(p1[1], "ping", 4);
//         close(p1[1]);
//         read(p2[0], buf, sizeof(buf));
//         int cur_pid = getpid();
//         printf("%d: received %s\n",cur_pid, buf);
//         close(p2[0]);
//     }
//     exit(0);
// }

int main() {
    int p[2];
    pipe(p);
    if(fork() == 0) {
        //子进程
        char buf[100];
        read(p[0], buf, sizeof(buf));
        int cur_pid = getpid();
        printf("%d: received %s\n", cur_pid, buf);
        close(p[0]);
        write(p[1], "pong",4);
        close(p[1]);
    } else {
        char buf[100];
        write(p[1], "ping", 4);
        close(p[1]);
        wait(0);
        read(p[0], buf, sizeof(buf));
        int cur_pid = getpid();
        printf("%d: received %s\n",cur_pid, buf);
        close(p[0]);
    }
    exit(0);
}