# 读取 ESP32-S3 串口日志（排错用）
#
# 用法:
#   python 读串口日志.py            # 默认 COM8，读 15 秒
#   python 读串口日志.py COM7 30    # 指定端口和秒数
#
# 提示:
#   先按一下板上的 RST 键再运行本脚本。
#   如果看到 "waiting for download"，说明芯片在下载模式，
#   按 RST 或拔插 USB 即可退出。

import sys
import time

import serial
import serial.tools.list_ports

port = sys.argv[1] if len(sys.argv) > 1 else "COM8"
seconds = float(sys.argv[2]) if len(sys.argv) > 2 else 15.0

ports = [p.device for p in serial.tools.list_ports.comports()]
print("可用串口:", ", ".join(ports) if ports else "(无)")
print(f"打开 {port} @115200，读取 {seconds:.0f} 秒...\n")

s = serial.Serial(port, 115200, timeout=0.2)
# 释放控制线，避免把芯片按进下载模式或复位状态
s.dtr = False
s.rts = False

buf = b""
end = time.time() + seconds
while time.time() < end:
    buf += s.read(4096)
    time.sleep(0.05)

s.close()

text = buf.decode("utf-8", "replace")
print(f"===== 收到 {len(buf)} 字节 =====")
print(text if text.strip() else "(无输出)")

if "waiting for download" in text or "DOWNLOAD" in text:
    print("\n>>> 芯片处于下载模式，请按 RST 键或拔插 USB 后再试。")
elif not text.strip():
    print("\n>>> 没有输出。可能原因：")
    print("    1) 还没按 RST，芯片没启动应用")
    print("    2) 端口号不对（看设备管理器）")
    print("    3) 固件启动前就异常复位了")
