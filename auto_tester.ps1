$script = $args[0]
$i = 1
$inputs = Test-Path -LiteralPath ".\tests"
Write-Host "  -----EXE auto tester-----"
Write-Host "{CAN BE USED AFTER FIRST RUN}"
Write-Host "     MADE BY ADAM TANÁCS"
if (-not ($inputs))
{
    Write-Host "SETTING UP .\tests FOR INPUT FILES!"
    New-Item -Name ".\tests" -ItemType "directory" | Out-Null
}
$outputs = Test-Path ".\outputs"
if (-not ($outputs))
{
    Write-Host "SETTING UP .\outputs FOR OUTPUT FILES!"
    New-Item -Name ".\outputs" -ItemType "directory" | Out-Null
}

$errors = Test-Path ".\errors"
if (-not ($errors))
{
    Write-Host "SETTING UP .\errors FOR ERROR LOGS!"
    New-Item -Name ".\errors" -ItemType "directory" | Out-Null
}

if (-not ($inputs -and $outputs -and $errors))
{
    Write-Host "SETUP COMPLETED"
    exit
}
foreach ($files in (Get-ChildItem ".\tests" -ErrorAction stop))
{
    Write-Host "$i. Test: "$files
    # $content = Get-Content ".\tests\$files"
    $name = "output"+$i+".txt"
    Start-Process -FilePath ".\$script" -RedirectStandardInput ".\tests\$files" -RedirectStandardOutput ".\outputs\$name" -RedirectStandardError ".\errors\Errors$i.txt"
    # | Out-File -FilePath ".\outputs\$name"
    $i = $i + 1
}
Write-Host "       TESTS COMPLETED"