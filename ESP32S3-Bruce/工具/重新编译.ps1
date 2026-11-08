# 编译固件（可换屏幕档案）
#
# 用法:
#   .\重新编译.ps1                    # 默认 1.44" ST7789 128x128
#   .\重新编译.ps1 -Screen 240        # 1.3"  ST7789 240x240
#   .\重新编译.ps1 -Screen 240x320    # 2.0"  ST7789 240x320
#   .\重新编译.ps1 -Screen 7735-160   # 1.8"  ST7735 128x160
#   .\重新编译.ps1 -Screen 7735-80    # 0.96" ST7735 80x160
#   .\重新编译.ps1 -Screen ili9341    # 2.8"  ILI9341 240x320
#
# 引脚改这里:
#   F:\esp32-build\firmware-main\boards\s3-n16r8-multitool\pins_arduino.h
# 屏幕参数改这里:
#   F:\esp32-build\firmware-main\boards\s3-n16r8-multitool\screen_profiles.h

param(
    [ValidateSet("128", "240", "240x320", "7735-160", "7735-80", "ili9341")]
    [string]$Screen = "128"
)

$ErrorActionPreference = "Stop"

$envMap = @{
    "128"      = "s3-n16r8-multitool"
    "240"      = "s3-n16r8-screen-240"
    "240x320"  = "s3-n16r8-screen-240x320"
    "7735-160" = "s3-n16r8-screen-7735-160"
    "7735-80"  = "s3-n16r8-screen-7735-80"
    "ili9341"  = "s3-n16r8-screen-ili9341"
}

$envName = $envMap[$Screen]
$proj = "F:\esp32-build\firmware-main"

if (-not (Test-Path $proj)) {
    Write-Host "找不到工程目录: $proj" -ForegroundColor Red
    exit 1
}

$env:PATH                = "F:\pio-core\bin;$env:PATH"
$env:PYTHONIOENCODING    = "utf-8"
$env:PLATFORMIO_CORE_DIR = "F:\pio-core"
$env:PIP_INDEX_URL       = "https://pypi.tuna.tsinghua.edu.cn/simple"
$env:UV_INDEX_URL        = "https://pypi.tuna.tsinghua.edu.cn/simple"
$env:GIT_TERMINAL_PROMPT = "0"

Set-Location $proj

Write-Host "屏幕档案: $Screen  ->  编译环境: $envName" -ForegroundColor Cyan
Write-Host "开始编译（第一次约 10-25 分钟，之后增量会快很多）..." -ForegroundColor Cyan
python -m platformio run -e $envName

if ($LASTEXITCODE -eq 0) {
    $out = Join-Path $proj "Bruce-$envName.bin"
    Write-Host ""
    if (Test-Path $out) {
        Write-Host "编译成功: $out" -ForegroundColor Green
    } else {
        Write-Host "编译成功。产物在 .pio\build\$envName\" -ForegroundColor Green
    }
    Write-Host "接着运行 工具\烧录.ps1 即可。" -ForegroundColor Yellow
} else {
    Write-Host ""
    Write-Host "编译失败，看上面第一条 error。" -ForegroundColor Red
}
