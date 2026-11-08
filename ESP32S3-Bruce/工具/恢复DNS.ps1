# 还原 DNS 为「自动获取（DHCP）」
#
# 如果改了 DNS 之后某些网站反而变慢或打不开，运行这个还原。
# 需要管理员权限，会弹 UAC。

$ErrorActionPreference = "Stop"

$isAdmin = ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)

if (-not $isAdmin) {
    Write-Host "需要管理员权限，正在申请提权..." -ForegroundColor Yellow
    Start-Process powershell -Verb RunAs -ArgumentList @(
        "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", "`"$PSCommandPath`""
    )
    exit
}

$adapters = Get-NetAdapter -Physical | Where-Object { $_.Status -eq "Up" }

foreach ($a in $adapters) {
    Write-Host "网卡: $($a.Name)" -ForegroundColor Cyan
    Set-DnsClientServerAddress -InterfaceIndex $a.ifIndex -ResetServerAddresses
    $new = (Get-DnsClientServerAddress -InterfaceIndex $a.ifIndex -AddressFamily IPv4).ServerAddresses -join ", "
    Write-Host "  已还原为: $(if ($new) { $new } else { '(自动获取)' })" -ForegroundColor Green
}

Clear-DnsClientCache
Write-Host ""
Write-Host "完成，DNS 已恢复为自动获取。" -ForegroundColor Yellow
Write-Host "按任意键关闭..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
