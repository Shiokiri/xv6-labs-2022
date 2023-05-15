#include "kernel/types.h"
#include "user/user.h"

void child_prime(int readpipe[2]) {
    int num;
    read(readpipe[0], &num, sizeof(num));
    if (num == -1) {
        exit(0);
    }
    printf("prime %d\n", num);
    int writepipe[2];
    pipe(writepipe);
    if (fork() == 0) {
        close(readpipe[0]);
        close(writepipe[1]);
        child_prime(writepipe);
    }
    else
    {
        close(writepipe[0]);
        int temp = 0;
        while (read(readpipe[0], &temp, sizeof(temp)) && temp != -1)
        {
            if (temp % num != 0)
            {
                write(writepipe[1], &temp, sizeof(temp));
            }
        }
        temp = -1;
        write(writepipe[1], &temp, sizeof(temp));
        wait(0);
        exit(0);
    }
}

int main() {
    int input[2];
    pipe(input);
    int ret = fork();
    if (ret == 0) {
        close(input[1]);
        child_prime(input);
        exit(0);
    }
    else {
        int i;
        close(input[0]);
        for (i = 2; i <= 35; i++) {
            write(input[1], &i, sizeof(i));
        }
        i = -1;
        write(input[1], &i, sizeof(i));
    }
    wait(0);
    exit(0);
}