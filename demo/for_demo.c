#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int i = 0;
    FILE *file = fopen("fordemo_state.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &i);
        fclose(file);
    }

    for (; i < 100; i++) {
        printf("i = %d\n", i);
        sleep(1); // 模拟一些工作
        file = fopen("fordemo_state.txt", "w");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        fprintf(file, "%d\n", i + 1);
        fclose(file);
    }

    remove("fordemo_state.txt"); // 清除状态文件
    return 0;
}

