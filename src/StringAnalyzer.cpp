// StringAnalyzer.cpp
// TODO: Implement StringAnalyzer.cpp

/**
 * @file StringAnalyzer.cpp
 * @brief Implementation of StringAnalyzer class
 */

#include "../include/StringAnalyzer.h"
#include "../include/Exceptions.h"
#include "../include/Utility.h"
#include <fstream>
#include <iostream>

// Initialize static member
std::vector<std::string> StringAnalyzer::globalSuspiciousKeywords;

// ==================== Constructors & Destructor ====================

StringAnalyzer::StringAnalyzer() 
    : Analyzer("String Analyzer"), patternsLoaded(false), riskPerMatch(10) {
    // Load default patterns
    try {
        loadPatternsFromFile("data/suspicious_strings.txt");
    } catch (const FileOpenException& e) {
        std::cerr << "[StringAnalyzer] Warning: " << e.what() << std::endl;
        std::cerr << "[StringAnalyzer] Using minimal default patterns" << std::endl;
        // Add some basic patterns as fallback
        suspiciousPatterns.push_back("cmd.exe");
        suspiciousPatterns.push_back("powershell");
        suspiciousPatterns.push_back("registry");
        patternsLoaded = true;
    }
}

StringAnalyzer::StringAnalyzer(const std::string& patternsFile, int riskPerMatchVal) 
    : Analyzer("String Analyzer"), patternsLoaded(false), riskPerMatch(riskPerMatchVal) {
    loadPatternsFromFile(patternsFile);
}

StringAnalyzer::~StringAnalyzer() {
    std::cout << "[StringAnalyzer] Destroyed" << std::endl;
}

// ==================== Virtual Method Implementations ====================

void StringAnalyzer::analyze(FileSample& file, AnalysisResult& result) {
    std::cout << "[StringAnalyzer] Analyzing strings in: " 
              << file.getFileName() << std::endl;
    
    if (!file.getIsLoaded()) {
        throw InvalidFileException("File must be loaded before string analysis");
    }
    
    if (!patternsLoaded || suspiciousPatterns.empty()) {
        result.addFinding("String analysis skipped: no patterns loaded");
        return;
    }
    
    const std::vector<std::string>& strings = file.getExtractedStrings();
    
    if (strings.empty()) {
        result.addFinding("No strings extracted for analysis");
        return;
    }
    
    int matchCount = 0;
    std::vector<std::string> matchedStrings;
    
    // Search for suspicious patterns in extracted strings
    for (size_t i = 0; i < strings.size(); ++i) {
        if (containsSuspiciousPattern(strings[i])) {
            matchCount++;
            matchedStrings.push_back(strings[i]);
            
            // Limit stored matches to avoid overwhelming the report
            if (matchedStrings.size() <= 10) {
                result.addFinding("Suspicious string found: \"" + strings[i] + "\"");
            }
        }
    }
    
    if (matchCount > 0) {
        // Add to risk score
        int riskIncrease = matchCount * riskPerMatch;
        result.addToRiskScore(riskIncrease);
        
        if (matchCount > 10) {
            result.addFinding("... and " + Utility::toString(matchCount - 10) + 
                            " more suspicious strings");
        }
        
        std::cout << "[StringAnalyzer] Found " << matchCount 
                  << " suspicious strings (Risk +" << riskIncrease << ")" << std::endl;
    } else {
        result.addFinding("No suspicious strings detected");
        std::cout << "[StringAnalyzer] No suspicious strings found" << std::endl;
    }
}

std::string StringAnalyzer::getName() const {
    return "String Analyzer";
}

// ==================== Private Helper Methods ====================

void StringAnalyzer::loadPatternsFromFile(const std::string& filePath) {
    std::ifstream file(filePath.c_str());
    
    if (!file.is_open()) {
        throw FileOpenException("Cannot open patterns file: " + filePath);
    }
    
    suspiciousPatterns.clear();
    std::string line;
    
    while (std::getline(file, line)) {
        line = Utility::trim(line);
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        suspiciousPatterns.push_back(Utility::toLowerCase(line));
    }
    
    file.close();
    patternsLoaded = true;
    
    std::cout << "[StringAnalyzer] Loaded " << suspiciousPatterns.size() 
              << " patterns from " << filePath << std::endl;
}

bool StringAnalyzer::containsSuspiciousPattern(const std::string& str) const {
    std::string lowerStr = Utility::toLowerCase(str);
    
    for (size_t i = 0; i < suspiciousPatterns.size(); ++i) {
        if (lowerStr.find(suspiciousPatterns[i]) != std::string::npos) {
            return true;
        }
    }
    
    return false;
}

// ==================== Public Methods ====================

void StringAnalyzer::loadPatterns(const std::string& filePath) {
    loadPatternsFromFile(filePath);
}

int StringAnalyzer::getPatternCount() const {
    return static_cast<int>(suspiciousPatterns.size());
}

// ==================== Static Method ====================

void StringAnalyzer::initializeGlobalKeywords() {
    if (globalSuspiciousKeywords.empty()) {
        // Initialize with common malware indicators
        globalSuspiciousKeywords.push_back("cmd.exe");
        globalSuspiciousKeywords.push_back("powershell");
        globalSuspiciousKeywords.push_back("regedit");
        globalSuspiciousKeywords.push_back("registry");
        globalSuspiciousKeywords.push_back("keylogger");
        globalSuspiciousKeywords.push_back("ransomware");
        globalSuspiciousKeywords.push_back("backdoor");
        globalSuspiciousKeywords.push_back("trojan");
        
        std::cout << "[StringAnalyzer] Global keywords initialized" << std::endl;
    }
}