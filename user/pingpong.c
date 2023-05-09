#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p1[2], p2[2];
    char buf[8];
    pipe(p1);
    pipe(p2);
    int pid = fork();
    if (pid == 0)  { // child
        read(p1[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        write(p2[1], "pong", 4);
    }
    else {
        write(p1[1], "ping", 4);
        wait(0);
        read(p2[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
    }
    exit(0);
}
