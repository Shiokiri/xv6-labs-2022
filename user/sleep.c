#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("enter error\n");
        exit(1);
    }
    else {
        int time = atoi(argv[1]);
        sleep(time);
    }
    exit(0);
}
