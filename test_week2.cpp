/**
 * @file test_week2.cpp
 * @brief Week 2 Testing - Analyzer Hierarchy and Polymorphism
 * 
 * This test demonstrates:
 * - Abstract base class (Analyzer)
 * - Inheritance hierarchy
 * - Runtime polymorphism (virtual functions)
 * - Static members
 * - File I/O
 */

#include "include/FileSample.h"
#include "include/AnalysisResult.h"
#include "include/Analyzer.h"
#include "include/HashAnalyzer.h"
#include "include/StringAnalyzer.h"
#include "include/SignatureAnalyzer.h"
#include "include/MetadataAnalyzer.h"
#include "include/Exceptions.h"
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Demonstrates polymorphism with analyzer pointers
 */
void demonstratePolymorphism() {
    cout << "\n========================================" << endl;
    cout << "   POLYMORPHISM DEMONSTRATION" << endl;
    cout << "========================================\n" << endl;
    
    // Create array of base class pointers (polymorphism)
    vector<Analyzer*> analyzers;
    
    // Add different analyzer types
    analyzers.push_back(new HashAnalyzer());
    analyzers.push_back(new StringAnalyzer());
    analyzers.push_back(new SignatureAnalyzer());
    analyzers.push_back(new MetadataAnalyzer());
    
    // Display analyzer names using polymorphism
    cout << "Loaded analyzers:" << endl;
    for (size_t i = 0; i < analyzers.size(); ++i) {
        // Virtual function call - getName() resolves at runtime
        cout << "  " << (i + 1) << ". " << analyzers[i]->getName() << endl;
    }
    
    // Clean up (virtual destructors ensure proper cleanup)
    cout << "\nCleaning up analyzers..." << endl;
    for (size_t i = 0; i < analyzers.size(); ++i) {
        delete analyzers[i];  // Virtual destructor called
    }
    analyzers.clear();
}

/**
 * @brief Run complete analysis on a sample file
 */
void runCompleteAnalysis(const string& filePath) {
    cout << "\n========================================" << endl;
    cout << "   COMPLETE ANALYSIS TEST" << endl;
    cout << "========================================\n" << endl;
    
    try {
        // Load file
        FileSample file(filePath);
        cout << "Loading file: " << filePath << endl;
        file.load();
        file.extractStrings(4);  // Extract strings of length >= 4
        file.displayInfo();
        
        // Create result object
        AnalysisResult result;
        result.setAnalyzedFileName(file.getFileName());
        
        // Create analyzers (polymorphic array)
        vector<Analyzer*> analyzers;
        analyzers.push_back(new HashAnalyzer());
        analyzers.push_back(new StringAnalyzer());
        analyzers.push_back(new SignatureAnalyzer());
        analyzers.push_back(new MetadataAnalyzer());
        
        // Run all analyzers using polymorphism
        cout << "\nRunning analyzers...\n" << endl;
        for (size_t i = 0; i < analyzers.size(); ++i) {
            cout << "--- Running: " << analyzers[i]->getName() << " ---" << endl;
            try {
                analyzers[i]->analyze(file, result);  // Polymorphic call
            } catch (const AnalyzerException& e) {
                cerr << "Analyzer error: " << e.what() << endl;
            }
            cout << endl;
        }
        
        // Calculate final verdict
        result.calculateVerdict();
        
        // Display results
        result.printSummary();
        
        // Test operator overloading
        cout << "\n--- Testing Operator Overloading ---" << endl;
        result += "Manual finding added via operator+=";
        cout << "Added finding via operator+=" << endl;
        cout << "Current risk score: " << result.getRiskScore() << endl;
        
        // Clean up
        for (size_t i = 0; i < analyzers.size(); ++i) {
            delete analyzers[i];
        }
        
    } catch (const AnalyzerException& e) {
        cerr << "Analysis failed: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
    }
}

/**
 * @brief Test static members
 */
void testStaticMembers() {
    cout << "\n========================================" << endl;
    cout << "   STATIC MEMBERS TEST" << endl;
    cout << "========================================\n" << endl;
    
    // Test FileSample static counters
    cout << "Initial files analyzed: " << FileSample::getTotalFilesAnalyzed() << endl;
    cout << "Initial bytes processed: " << FileSample::getTotalBytesProcessed() << endl;
    
    try {
        FileSample file1("samples/safe_sample.txt");
        file1.load();
        
        FileSample file2("samples/suspicious_sample.txt");
        file2.load();
        
        cout << "\nAfter loading 2 files:" << endl;
        cout << "Total files analyzed: " << FileSample::getTotalFilesAnalyzed() << endl;
        cout << "Total bytes processed: " << FileSample::getTotalBytesProcessed() << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    // Test SignatureAnalyzer static database
    cout << "\n--- Testing Static Signature Database ---" << endl;
    SignatureAnalyzer::addSignature("deadbeef", "TestMalware");
    SignatureAnalyzer::addSignature("cafebabe", "AnotherThreat");
    
    SignatureAnalyzer analyzer1;
    SignatureAnalyzer analyzer2;
    
    cout << "Analyzer 1 signature count: " << analyzer1.getSignatureCount() << endl;
    cout << "Analyzer 2 signature count: " << analyzer2.getSignatureCount() << endl;
    cout << "(Both share the same static database)" << endl;
}

/**
 * @brief Main test driver
 */
int main() {
    cout << "\n";
    cout << "============================================\n";
    cout << "   MALWARE ANALYZER - WEEK 2 TESTING\n";
    cout << "   Analysis Layer & Polymorphism\n";
    cout << "============================================\n";
    
    try {
        // Test 1: Polymorphism demonstration
        demonstratePolymorphism();
        
        // Test 2: Static members
        testStaticMembers();
        
        // Test 3: Complete analysis (you can change the file path)
        runCompleteAnalysis("samples/safe_sample.txt");
        
        cout << "\n========================================" << endl;
        cout << "   ALL WEEK 2 TESTS COMPLETED" << endl;
        cout << "========================================\n" << endl;
        
    } catch (const exception& e) {
        cerr << "\nFATAL ERROR: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}