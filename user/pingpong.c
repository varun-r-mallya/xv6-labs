#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int p[2];
    pipe(p);
    int q[2];
    pipe(q);
    int pid = fork();
    if (pid == 0) {
        close(p[1]);
        close(q[0]);
        char n = 69;
        read(p[0], &n, sizeof(n));
        fprintf(2, "%d: received ping\n", getpid());
        close(p[0]);
        write(q[1], &n, sizeof(n));
        exit(0);
    } else {
        close(p[0]);
        close(q[1]);
        char n = 69;
        write(p[1], &n, sizeof(n));
        close(p[1]);
        read(q[0], &n, sizeof(n));
        fprintf(2, "%d: received pong\n", getpid());
        close(q[0]);
        exit(0);
    }
    return 0;
}