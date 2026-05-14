# ========================================
# MALWARE ANALYZER - FINAL COMPILATION
# ========================================

Write-Host "`n========================================" -ForegroundColor Cyan
Write-Host "   COMPILING MALWARE ANALYZER" -ForegroundColor Cyan
Write-Host "========================================`n" -ForegroundColor Cyan

# Create required directories
Write-Host "Creating directories..." -ForegroundColor Yellow
New-Item -ItemType Directory -Force -Path logs | Out-Null
New-Item -ItemType Directory -Force -Path reports | Out-Null

# Define all source files
$sources = @(
    "src/Exceptions.cpp",
    "src/FileSample.cpp",
    "src/AnalysisResult.cpp",
    "src/Analyzer.cpp",
    "src/HashAnalyzer.cpp",
    "src/StringAnalyzer.cpp",
    "src/SignatureAnalyzer.cpp",
    "src/MetadataAnalyzer.cpp",
    "src/User.cpp",
    "src/AnalysisEngine.cpp",
    "src/Logger.cpp",
    "src/ReportGenerator.cpp",
    "src/AuthenticationManager.cpp",
    "src/QuarantineManager.cpp",
    "src/main.cpp"
)

# Compile
Write-Host "Compiling..." -ForegroundColor Yellow
$cmd = "g++ -std=c++11 -Wall -o MalwareAnalyzer.exe " + ($sources -join " ") + " -I./include"

Invoke-Expression $cmd

if ($LASTEXITCODE -eq 0) {
    Write-Host "`n========================================" -ForegroundColor Green
    Write-Host "   ✓ COMPILATION SUCCESSFUL!" -ForegroundColor Green
    Write-Host "========================================`n" -ForegroundColor Green
    
    Write-Host "Executable: MalwareAnalyzer.exe" -ForegroundColor White
    Write-Host "Run with: .\MalwareAnalyzer.exe`n" -ForegroundColor White
    
    # Display file count
    $headerCount = (Get-ChildItem -Path include -Filter *.h).Count
    $sourceCount = (Get-ChildItem -Path src -Filter *.cpp).Count
    
    Write-Host "Project Statistics:" -ForegroundColor Cyan
    Write-Host "  Header files: $headerCount" -ForegroundColor White
    Write-Host "  Source files: $sourceCount" -ForegroundColor White
    Write-Host "  Total files: $($headerCount + $sourceCount)" -ForegroundColor White
    
} else {
    Write-Host "`n========================================" -ForegroundColor Red
    Write-Host "   ✗ COMPILATION FAILED!" -ForegroundColor Red
    Write-Host "========================================`n" -ForegroundColor Red
    exit 1
}