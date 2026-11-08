# 设置公共 DNS（修复 GitHub 域名解析）
#
# 问题现象: raw.githubusercontent.com 被解析成 0.0.0.0，导致下载失败
# 处理办法: 把网卡 DNS 改成 223.5.5.5 (阿里) + 119.29.29.29 (腾讯)
#
# 用法: 右键「使用 PowerShell 运行」，或在终端执行，
#       会弹出 UAC 提示，点「是」即可。

$ErrorActionPreference = "Stop"

$isAdmin = ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)

if (-not $isAdmin) {
    Write-Host "需要管理员权限，正在申请提权..." -ForegroundColor Yellow
    Start-Process powershell -Verb RunAs -ArgumentList @(
        "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", "`"$PSCommandPath`""
    )
    exit
}

$primary   = "223.5.5.5"
$secondary = "119.29.29.29"

$adapters = Get-NetAdapter -Physical | Where-Object { $_.Status -eq "Up" }

if (-not $adapters) {
    Write-Host "没有找到已连接的网络适配器。" -ForegroundColor Red
    exit 1
}

foreach ($a in $adapters) {
    $old = (Get-DnsClientServerAddress -InterfaceIndex $a.ifIndex -AddressFamily IPv4).ServerAddresses -join ", "
    Write-Host "网卡: $($a.Name)" -ForegroundColor Cyan
    Write-Host "  原 DNS : $(if ($old) { $old } else { '(自动获取)' })"
    Set-DnsClientServerAddress -InterfaceIndex $a.ifIndex -ServerAddresses @($primary, $secondary)
    $new = (Get-DnsClientServerAddress -InterfaceIndex $a.ifIndex -AddressFamily IPv4).ServerAddresses -join ", "
    Write-Host "  新 DNS : $new" -ForegroundColor Green
}

Clear-DnsClientCache
Write-Host ""
Write-Host "DNS 缓存已刷新。" -ForegroundColor Green
Start-Sleep -Seconds 1

Write-Host ""
Write-Host "验证解析:" -ForegroundColor Cyan
foreach ($d in @("github.com", "raw.githubusercontent.com", "codeload.github.com")) {
    try {
        $ips = (Resolve-DnsName -Name $d -Type A -QuickTimeout -ErrorAction Stop |
                Where-Object { $_.IPAddress } |
                Select-Object -ExpandProperty IPAddress) -join ", "
        Write-Host ("  {0,-28} {1}" -f $d, $ips)
    } catch {
        Write-Host ("  {0,-28} 解析失败" -f $d) -ForegroundColor Red
    }
}

Write-Host ""
Write-Host "完成。想还原就运行 恢复DNS.ps1。" -ForegroundColor Yellow
Write-Host "按任意键关闭..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
