#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char* argv[]) {
    if(argc != 2) {
        write(2,"error\n",6);
    }
    int seconds = atoi(argv[1]);
//    write(1,"start sleep\n",12);
    sleep(seconds);
//    write(1,"end sleep\n",10);
    exit(0);
}