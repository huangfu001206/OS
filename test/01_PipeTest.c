#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// int main() {
//     int p[2];
//     char *argv[2];
//     argv[0] = "wc";
//     argv[1] = 0;
//     pipe(p);
//     if (fork() == 0) {
//         close(0);
//         dup(p[0]);
//         close(p[0]);
//         close(p[1]);
//         printf("execute /bin/wc pre\n");
//         execl("/bin/wc", argv);
//         printf("execute /bin/wc finished\n");
//     } else {
//         close(p[0]);
//         sleep(3);
//         printf("write hello_world pre\n");
//         write(p[1], "hello world\n", 12);
//         write(p[1], "hello world!!!\n", 15);
//         write(p[1], "hello world!!!\n", 15);
//         write(p[1], "hello world!!!\n", 15);
//         write(p[1], "hello world!!!\n", 15);
//         close(p[1]);
//         printf("write hello_world finished\n");
//     }
//     return 0;
// }
int main() {
    int p[2];
    char buf[124];
    pipe(p);
    if(fork() == 0) {
        close(p[1]);
        printf("子进程读取数据之前\n");
        read(p[0], buf, sizeof(buf));
        printf("子进程读取到数据 : %s\n", buf);
        close(p[0]);
    } else {
        close(p[0]);
        sleep(3);
        write(p[1], "huangfu\n",8);
        close(p[1]);
        printf("父进程写入数据\n");
    }
}