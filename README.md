# Restore-interrupted

## 说明
```Restore-interrupted``` 是一个用于恢复被中断的下载任务的工具，支持多线程下载，支持断点续传。

## 编译
```shell
gcc -o Restore-interrupted Restore-interrupted.c 
```

## 使用
### 程序编写规范
#### C语言
```c  
// 主函数开头添加
FILE *file = fopen("fordemo_state.txt", "r");
if (file != NULL) {
    fscanf(file, "%d", &i);
    fclose(file);
}

// 在需要保存状态的地方添加
file = fopen("fordemo_state.txt", "w");
if (file == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
}
fprintf(file, "%d\n", i + 1);
fclose(file);
```

#### Python语言
```python
# 主函数开头添加
state_file = "fordemo_state.txt"
i = 0
if os.path.exists(state_file):
    with open(state_file, "r") as f:
        i = int(f.read().strip())

# 在需要保存状态的地方添加        
with open(state_file, "w") as f:
        f.write(f"{i + 1}")
```
    

### 执行
```shell
# 执行C语言程序
./Restore-interrupted <要执行的C语言程序> <程序的参数>

# 执行Python程序
./Restore-interrupted <要执行的Python程序>
```

## 案例
```shell
# 执行C语言程序
gcc -o my_backup demo/my_backup.c
./Restore-interrupted my_backup

# 执行Python程序
./Restore-interrupted python3 demo/my_backup.py
```


