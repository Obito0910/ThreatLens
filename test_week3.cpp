/**
 * @file test_week3.cpp
 * @brief Week 3 Testing - Engine and Reporting Layer
 * 
 * This test demonstrates:
 * - Composition (AnalysisEngine owns analyzers)
 * - Aggregation (ReportGenerator uses results)
 * - File I/O (logging and reporting)
 * - Complete analysis workflow
 */

#include "include/FileSample.h"
#include "include/AnalysisResult.h"
#include "include/User.h"
#include "include/Analyzer.h"
#include "include/HashAnalyzer.h"
#include "include/StringAnalyzer.h"
#include "include/SignatureAnalyzer.h"
#include "include/MetadataAnalyzer.h"
#include "include/AnalysisEngine.h"
#include "include/Logger.h"
#include "include/ReportGenerator.h"
#include "include/Exceptions.h"
#include <iostream>

using namespace std;

/**
 * @brief Test basic engine functionality
 */
void testEngineBasics() {
    cout << "\n========================================" << endl;
    cout << "   TEST 1: ENGINE BASICS" << endl;
    cout << "========================================\n" << endl;
    
    AnalysisEngine engine;
    
    // Add analyzers (engine takes ownership - composition)
    cout << "Adding analyzers to engine..." << endl;
    engine.addAnalyzer(new HashAnalyzer());
    engine.addAnalyzer(new StringAnalyzer());
    engine.addAnalyzer(new SignatureAnalyzer());
    engine.addAnalyzer(new MetadataAnalyzer());
    
    cout << "\nEngine has " << engine.getAnalyzerCount() << " analyzers" << endl;
    
    // No need to delete analyzers - engine owns them (composition)
    cout << "\nEngine will automatically clean up analyzers in destructor" << endl;
}

/**
 * @brief Test complete analysis workflow
 */
void testCompleteWorkflow() {
    cout << "\n========================================" << endl;
    cout << "   TEST 2: COMPLETE ANALYSIS WORKFLOW" << endl;
    cout << "========================================\n" << endl;
    
    try {
        // Create user
        User analyst("john_doe", "password123", "Security Analyst");
        cout << "Created user: " << analyst.getUsername() << endl;
        
        // Create logger
        Logger logger("logs/analysis.log");
        logger.logLogin(analyst.getUsername());
        
        // Create analysis engine
        AnalysisEngine engine;
        engine.addAnalyzer(new HashAnalyzer());
        engine.addAnalyzer(new StringAnalyzer());
        engine.addAnalyzer(new SignatureAnalyzer());
        engine.addAnalyzer(new MetadataAnalyzer());
        
        // Load file
        FileSample file("samples/suspicious_sample.txt");
        file.load();
        
        // Run analysis
        AnalysisResult result = engine.runAnalysis(file, analyst);
        
        // Log the analysis
        logger.logAnalysis(analyst, result);
        
        // Display results
        result.printSummary();
        
        // Generate report (aggregation - generator uses result but doesn't own it)
        ReportGenerator reportGen("reports/");
        string reportPath = reportGen.generateReport(file, result, analyst);
        
        cout << "\nReport generated: " << reportPath << endl;
        
        logger.logLogout(analyst.getUsername());
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/**
 * @brief Test static statistics
 */
void testStaticStatistics() {
    cout << "\n========================================" << endl;
    cout << "   TEST 3: STATIC STATISTICS" << endl;
    cout << "========================================\n" << endl;
    
    try {
        AnalysisEngine::resetStats();
        
        User analyst("alice", "pass456", "Analyst");
        AnalysisEngine engine;
        
        engine.addAnalyzer(new HashAnalyzer());
        engine.addAnalyzer(new StringAnalyzer());
        engine.addAnalyzer(new MetadataAnalyzer());
        
        // Analyze multiple files
        cout << "Analyzing safe file..." << endl;
        FileSample file1("samples/safe_sample.txt");
        file1.load();
        AnalysisResult result1 = engine.runAnalysis(file1, analyst);
        
        cout << "\nAnalyzing suspicious file..." << endl;
        FileSample file2("samples/suspicious_sample.txt");
        file2.load();
        AnalysisResult result2 = engine.runAnalysis(file2, analyst);
        
        // Display global statistics
        AnalysisEngine::printStats();
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/**
 * @brief Test logger functionality
 */
void testLogger() {
    cout << "\n========================================" << endl;
    cout << "   TEST 4: LOGGER FUNCTIONALITY" << endl;
    cout << "========================================\n" << endl;
    
    try {
        Logger logger("logs/test_logger.log");
        
        logger.log("INFO", "Testing logger functionality");
        logger.log("WARNING", "This is a warning message");
        logger.log("ERROR", "This is an error message");
        
        logger.logLogin("test_user");
        logger.logQuarantine("test_user", "malware.exe");
        logger.logLogout("test_user");
        
        cout << "Total logs written: " << Logger::getTotalLogs() << endl;
        cout << "Check logs/test_logger.log for output" << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/**
 * @brief Test report generation
 */
void testReportGeneration() {
    cout << "\n========================================" << endl;
    cout << "   TEST 5: REPORT GENERATION" << endl;
    cout << "========================================\n" << endl;
    
    try {
        User analyst("bob", "pass789", "Senior Analyst");
        FileSample file("samples/safe_sample.txt");
        file.load();
        
        AnalysisResult result;
        result.setAnalyzedFileName(file.getFileName());
        result.setHashValue("a1b2c3d4");
        result.setTimestamp("2024-01-15 10:30:00");
        result.setRiskScore(15);
        result.addFinding("No suspicious strings detected");
        result.addFinding("File extension is safe");
        result.calculateVerdict();
        
        ReportGenerator reportGen("reports/");
        
        // Test full report
        string reportPath = reportGen.generateReport(file, result, analyst);
        cout << "Full report generated: " << reportPath << endl;
        
        // Test summary report
        string summaryPath = reportGen.generateSummaryReport(result);
        cout << "Summary report generated: " << summaryPath << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/**
 * @brief Demonstrate composition vs aggregation
 */
void demonstrateCompositionVsAggregation() {
    cout << "\n========================================" << endl;
    cout << "   COMPOSITION vs AGGREGATION DEMO" << endl;
    cout << "========================================\n" << endl;
    
    cout << "COMPOSITION (AnalysisEngine owns Analyzers):" << endl;
    cout << "- Engine creates: new HashAnalyzer()" << endl;
    cout << "- Engine stores in vector<Analyzer*>" << endl;
    cout << "- Engine OWNS the analyzer" << endl;
    cout << "- Engine MUST delete it in destructor" << endl;
    cout << "- If engine dies, analyzers die too\n" << endl;
    
    {
        AnalysisEngine engine;
        engine.addAnalyzer(new HashAnalyzer());
        cout << "Analyzer added to engine (composition)\n" << endl;
        // When scope ends, engine destructor deletes the analyzer
    }
    cout << "Engine destroyed - analyzer automatically cleaned up\n" << endl;
    
    cout << "\nAGGREGATION (ReportGenerator uses AnalysisResult):" << endl;
    cout << "- Generator receives: const AnalysisResult& result" << endl;
    cout << "- Generator USES result temporarily" << endl;
    cout << "- Generator does NOT own the result" << endl;
    cout << "- Generator does NOT delete it" << endl;
    cout << "- Result can exist independently\n" << endl;
    
    try {
        AnalysisResult result;
        result.setAnalyzedFileName("test.txt");
        result.setRiskScore(10);
        result.calculateVerdict();
        
        ReportGenerator reportGen("reports/");
        cout << "Result exists independently" << endl;
        cout << "Generator uses it (aggregation)" << endl;
        string path = reportGen.generateSummaryReport(result);
        cout << "Generator done - result still exists" << endl;
        cout << "Result verdict: " << result.getVerdict() << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/**
 * @brief Main test driver
 */
int main() {
    cout << "\n";
    cout << "============================================\n";
    cout << "   MALWARE ANALYZER - WEEK 3 TESTING\n";
    cout << "   Engine & Reporting Layer\n";
    cout << "============================================\n";
    
    try {
        testEngineBasics();
        testCompleteWorkflow();
        testStaticStatistics();
        testLogger();
        testReportGeneration();
        demonstrateCompositionVsAggregation();
        
        cout << "\n========================================" << endl;
        cout << "   ALL WEEK 3 TESTS COMPLETED" << endl;
        cout << "========================================\n" << endl;
        
    } catch (const exception& e) {
        cerr << "\nFATAL ERROR: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}