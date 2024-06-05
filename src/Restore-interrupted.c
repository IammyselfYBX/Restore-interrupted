#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define STATUS_FILE "my_backup_status.txt"

// 保存进程ID到文件
void save_status(pid_t pid) {
    FILE *file = fopen(STATUS_FILE, "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d\n", pid);
    fclose(file);
}

// 从文件中读取进程ID
pid_t load_status() {
    FILE *file = fopen(STATUS_FILE, "r");
    if (file == NULL) {
        return -1;
    }
    pid_t pid;
    fscanf(file, "%d", &pid);
    fclose(file);
    return pid;
}

// 删除保存进程ID的文件
void delete_status() {
    unlink(STATUS_FILE);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program_to_execute> [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = load_status(); // 尝试加载保存的进程ID

    if (pid > 0) {
        printf("Resuming program with PID %d\n", pid);
        if (kill(pid, SIGCONT) == -1) {
            perror("kill");
            delete_status();
            exit(EXIT_FAILURE);
        }
        waitpid(pid, NULL, 0); // 等待子进程结束
        delete_status(); // 子进程结束后删除状态文件
        exit(EXIT_SUCCESS);
    }

    pid = fork(); // 创建子进程
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // 子进程执行
        execvp(argv[1], &argv[1]); // 执行目标程序
        perror("execvp");
        exit(EXIT_FAILURE);
    } else { // 父进程执行
        save_status(pid); // 保存子进程ID
        int status;
        waitpid(pid, &status, 0); // 等待子进程结束
        delete_status(); // 子进程结束后删除状态文件
        if (WIFEXITED(status)) {
            printf("Program exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Program killed by signal %d\n", WTERMSIG(status));
        }
        exit(EXIT_SUCCESS);
    }
}

