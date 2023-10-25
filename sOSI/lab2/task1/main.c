#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid, ppid, pgrp;
    uid_t uid, euid;
    gid_t gid, egid;

    //возвращает идентификатор текущего процесса
    pid = getpid();
    printf("PID: %d\n", pid);

    //возвращает идентификатор родительского процесса
    ppid = getppid();
    printf("PPID: %d\n", ppid);

    //возвращает идентификатор группы вызывающего процесса
    pgrp = getpgrp();
    printf("PGID: %d\n", pgrp);

    //возвращает реальный идентификатор владельца.
    uid = getuid();
    printf("Real UID: %d\n", uid);

    //возвращает эффективный идентификатор владельца.
    euid = geteuid();
    printf("Effective UID: %d\n", euid);

    //возвращает реальный идентификатор группы владельца.
    gid = getgid();
    printf("Real GID: %d\n", gid);

    //возвращает эффективный идентификатор группы владельца.
    egid = getegid();
    printf("Effective GID: %d\n", egid);



    return 0;
}
