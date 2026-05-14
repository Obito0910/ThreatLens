// AnalysisEngine.cpp
// TODO: Implement AnalysisEngine.cpp

/**
 * @file AnalysisEngine.cpp
 * @brief Implementation of AnalysisEngine class
 */

#include "../include/AnalysisEngine.h"
#include "../include/Exceptions.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

// Initialize static members
int AnalysisEngine::totalFilesAnalyzed = 0;
int AnalysisEngine::totalThreatsDetected = 0;

// ==================== Constructor & Destructor ====================

AnalysisEngine::AnalysisEngine() 
    : analysisHistory(100) {  // Keep last 100 analyses
    std::cout << "[AnalysisEngine] Engine initialized" << std::endl;
}

AnalysisEngine::~AnalysisEngine() {
    std::cout << "[AnalysisEngine] Shutting down engine..." << std::endl;
    
    // Clean up all owned analyzers (composition)
    for (size_t i = 0; i < analyzers.size(); ++i) {
        delete analyzers[i];
        analyzers[i] = NULL;
    }
    analyzers.clear();
    
    std::cout << "[AnalysisEngine] Engine destroyed" << std::endl;
}

// ==================== Core Methods ====================

void AnalysisEngine::addAnalyzer(Analyzer* analyzer) {
    if (analyzer == NULL) {
        std::cerr << "[AnalysisEngine] Warning: Attempted to add NULL analyzer" << std::endl;
        return;
    }
    
    analyzers.push_back(analyzer);
    std::cout << "[AnalysisEngine] Added analyzer: " 
              << analyzer->getName() << std::endl;
}

AnalysisResult AnalysisEngine::runAnalysis(FileSample& file, User& user) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "   STARTING ANALYSIS" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "User:     " << user.getUsername() << std::endl;
    std::cout << "File:     " << file.getFileName() << std::endl;
    std::cout << "Analyzers: " << analyzers.size() << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    // Validate file is loaded
    if (!file.getIsLoaded()) {
        throw InvalidFileException("File must be loaded before analysis");
    }
    
    // Check if we have any analyzers
    if (analyzers.empty()) {
        throw AnalyzerException("No analyzers registered in the engine");
    }
    
    // Create result object
    AnalysisResult result;
    result.setAnalyzedFileName(file.getFileName());
    result.setTimestamp(getCurrentTimestamp());
    
    // Extract strings if not already done
    if (file.getExtractedStrings().empty()) {
        std::cout << "[AnalysisEngine] Extracting strings from file..." << std::endl;
        try {
            file.extractStrings(4);  // Minimum string length: 4
        } catch (const FileOpenException& e) {
            std::cerr << "[AnalysisEngine] Warning: String extraction failed: " 
                      << e.what() << std::endl;
        }
    }
    
    // Run all analyzers sequentially
    int successfulAnalyzers = 0;
    int failedAnalyzers = 0;
    
    for (size_t i = 0; i < analyzers.size(); ++i) {
        try {
            std::cout << "[AnalysisEngine] Running: " 
                      << analyzers[i]->getName() << "..." << std::endl;
            
            // Polymorphic call - actual method depends on analyzer type
            analyzers[i]->analyze(file, result);
            successfulAnalyzers++;
            
        } catch (const AnalyzerException& e) {
            failedAnalyzers++;
            std::cerr << "[AnalysisEngine] Analyzer failed: " 
                      << e.what() << std::endl;
            result.addFinding("Analyzer error: " + std::string(e.what()));
        }
    }
    
    std::cout << "\n[AnalysisEngine] Analysis complete: " 
              << successfulAnalyzers << " succeeded, " 
              << failedAnalyzers << " failed" << std::endl;
    
    // Calculate final verdict based on risk score
    result.calculateVerdict();
    
    // Update statistics
    totalFilesAnalyzed++;
    
    // Check if threat detected (risk score > 20)
    if (result.getRiskScore() > 20) {
        totalThreatsDetected++;
    }
    
    // Add to history
    analysisHistory.add(result);
    
    // Add result to user's history
    user.addToHistory(result);
    
    std::cout << "[AnalysisEngine] Final verdict: " << result.getVerdict() 
              << " (Risk: " << result.getRiskScore() << "/100)" << std::endl;
    
    return result;
}

int AnalysisEngine::getAnalyzerCount() const {
    return static_cast<int>(analyzers.size());
}

const History<AnalysisResult>& AnalysisEngine::getHistory() const {
    return analysisHistory;
}

void AnalysisEngine::clearHistory() {
    analysisHistory.clear();
    std::cout << "[AnalysisEngine] Analysis history cleared" << std::endl;
}

void AnalysisEngine::clearAnalyzers() {
    // Delete all owned analyzers
    for (size_t i = 0; i < analyzers.size(); ++i) {
        delete analyzers[i];
        analyzers[i] = NULL;
    }
    analyzers.clear();
    std::cout << "[AnalysisEngine] All analyzers removed" << std::endl;
}

// ==================== Private Helper Methods ====================

std::string AnalysisEngine::getCurrentTimestamp() const {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    
    std::stringstream ss;
    ss << (1900 + timeinfo->tm_year) << "-"
       << std::setw(2) << std::setfill('0') << (1 + timeinfo->tm_mon) << "-"
       << std::setw(2) << std::setfill('0') << timeinfo->tm_mday << " "
       << std::setw(2) << std::setfill('0') << timeinfo->tm_hour << ":"
       << std::setw(2) << std::setfill('0') << timeinfo->tm_min << ":"
       << std::setw(2) << std::setfill('0') << timeinfo->tm_sec;
    
    return ss.str();
}

// ==================== Static Methods ====================

int AnalysisEngine::getTotalFilesAnalyzed() {
    return totalFilesAnalyzed;
}

int AnalysisEngine::getTotalThreatsDetected() {
    return totalThreatsDetected;
}

void AnalysisEngine::printStats() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "   GLOBAL ANALYSIS STATISTICS" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Total Files Analyzed:  " << totalFilesAnalyzed << std::endl;
    std::cout << "Total Threats Detected: " << totalThreatsDetected << std::endl;
    
    if (totalFilesAnalyzed > 0) {
        double threatPercentage = (static_cast<double>(totalThreatsDetected) / 
                                   static_cast<double>(totalFilesAnalyzed)) * 100.0;
        std::cout << "Threat Detection Rate:  " << std::fixed 
                  << std::setprecision(1) << threatPercentage << "%" << std::endl;
    }
    
    std::cout << "========================================\n" << std::endl;
}

void AnalysisEngine::resetStats() {
    totalFilesAnalyzed = 0;
    totalThreatsDetected = 0;
    std::cout << "[AnalysisEngine] Global statistics reset" << std::endl;
}