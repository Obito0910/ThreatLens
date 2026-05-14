# Create directories
New-Item -ItemType Directory -Force -Path logs | Out-Null
New-Item -ItemType Directory -Force -Path reports | Out-Null

# Compile
Write-Host "Compiling Week 3 test..." -ForegroundColor Cyan

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
    "test_week3_minimal.cpp"
)

$cmd = "g++ -std=c++11 -o test_week3.exe " + ($sources -join " ") + " -I./include"

Invoke-Expression $cmd

if ($LASTEXITCODE -eq 0) {
    Write-Host "✓ Compilation successful!" -ForegroundColor Green
    Write-Host "Running test..." -ForegroundColor Cyan
    .\test_week3.exe
} else {
    Write-Host "✗ Compilation failed!" -ForegroundColor Red
    exit 1
}