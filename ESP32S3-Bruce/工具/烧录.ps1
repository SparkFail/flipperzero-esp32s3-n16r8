# 一键烧录 ESP32-S3 N16R8
# 用法:  .\烧录.ps1 -Port COM8

param(
    [string]$Port = "COM8"
)

$ErrorActionPreference = "Stop"

$bin = Join-Path (Split-Path $PSScriptRoot -Parent) "固件\Bruce-s3-n16r8-multitool.bin"

if (-not (Test-Path $bin)) {
    Write-Host "找不到固件: $bin" -ForegroundColor Red
    exit 1
}

Write-Host "端口   : $Port" -ForegroundColor Cyan
Write-Host "固件   : $bin" -ForegroundColor Cyan
Write-Host "大小   : $([math]::Round((Get-Item $bin).Length/1MB, 2)) MB" -ForegroundColor Cyan
Write-Host ""

python -m esptool --chip esp32s3 --port $Port --baud 921600 write-flash 0x0 $bin

if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Write-Host "烧录完成，哈希已校验。" -ForegroundColor Green
    Write-Host "请按一下板上的 RST 键（或拔插一次 USB）启动应用。" -ForegroundColor Yellow
    Write-Host "（ESP32-S3 用 USB 软复位会停在下载模式，这是正常的）" -ForegroundColor DarkGray
} else {
    Write-Host ""
    Write-Host "烧录失败。试着手动进下载模式：按住 BOOT 不放 -> 点一下 RST -> 松开 BOOT" -ForegroundColor Red
}
