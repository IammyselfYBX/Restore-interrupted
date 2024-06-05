import time
import os

# 尝试从状态文件中加载 i 的值
state_file = "fordemo_state.txt"
i = 0
if os.path.exists(state_file):
    with open(state_file, "r") as f:
        i = int(f.read().strip())

# 模拟一个长时间运行的任务
for i in range(i, 100):
    print(f"i = {i}")
    time.sleep(1)  # 模拟一些工作
    # 保存当前状态
    with open(state_file, "w") as f:
        f.write(f"{i + 1}")

# 完成后删除状态文件
os.remove(state_file)

