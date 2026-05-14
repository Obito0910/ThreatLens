// Create a simple test file: test_week1.cpp
#include "include/FileSample.h"
#include "include/AnalysisResult.h"
#include "include/History.h"
#include <iostream>

int main() {
    try {
        // Test FileSample
        FileSample file("samples/safe_sample.txt");
        file.displayInfo();
        
        // Test AnalysisResult
        AnalysisResult result;
        result += "Test finding";
        result.setRiskScore(25);
        result.calculateVerdict();
        result.printSummary();
        
        // Test History
        History<AnalysisResult> history(10);
        history.add(result);
        std::cout << "History size: " << history.size() << std::endl;
        
        std::cout << "\nWeek 1 Foundation - All tests passed!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}

// This is a test file for week 1 
