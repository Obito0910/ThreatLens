// SignatureAnalyzer.cpp
// TODO: Implement SignatureAnalyzer.cpp

/**
 * @file SignatureAnalyzer.cpp
 * @brief Implementation of SignatureAnalyzer class
 */

#include "../include/SignatureAnalyzer.h"
#include "../include/Exceptions.h"
#include "../include/Utility.h"
#include <fstream>
#include <iostream>

// Initialize static members
std::map<std::string, std::string> SignatureAnalyzer::signatureDatabase;
bool SignatureAnalyzer::staticDatabaseLoaded = false;

// ==================== Constructors & Destructor ====================

SignatureAnalyzer::SignatureAnalyzer() 
    : Analyzer("Signature Analyzer"), databaseLoaded(false) {
    // Load default signature database
    try {
        loadDatabaseFromFile("data/signatures.txt");
    } catch (const FileOpenException& e) {
        std::cerr << "[SignatureAnalyzer] Warning: " << e.what() << std::endl;
        std::cerr << "[SignatureAnalyzer] Operating with empty database" << std::endl;
    }
}

SignatureAnalyzer::SignatureAnalyzer(const std::string& databaseFile) 
    : Analyzer("Signature Analyzer"), databaseLoaded(false) {
    loadDatabaseFromFile(databaseFile);
}

SignatureAnalyzer::~SignatureAnalyzer() {
    std::cout << "[SignatureAnalyzer] Destroyed" << std::endl;
}

// ==================== Virtual Method Implementations ====================

void SignatureAnalyzer::analyze(FileSample& file, AnalysisResult& result) {
    std::cout << "[SignatureAnalyzer] Checking signatures for: " 
              << file.getFileName() << std::endl;
    
    if (!file.getIsLoaded()) {
        throw InvalidFileException("File must be loaded before signature analysis");
    }
    
    // Get the file hash from result (should be set by HashAnalyzer)
    std::string fileHash = result.getHashValue();
    
    if (fileHash.empty()) {
        result.addFinding("Signature check skipped: no hash available");
        std::cout << "[SignatureAnalyzer] No hash available for comparison" << std::endl;
        return;
    }
    
    // Check if hash matches any known malware signature
    if (matchesKnownSignature(fileHash)) {
        std::string malwareName = getMalwareName(fileHash);
        
        // CRITICAL FINDING - Known malware detected!
        result.addFinding("CRITICAL: Known malware detected - " + malwareName);
        result.addToRiskScore(50);  // Major risk increase
        
        std::cout << "[SignatureAnalyzer] *** MALWARE DETECTED: " 
                  << malwareName << " ***" << std::endl;
    } else {
        result.addFinding("No matching malware signatures found");
        std::cout << "[SignatureAnalyzer] File hash clean (not in database)" << std::endl;
    }
    
    if (signatureDatabase.empty()) {
        result.addFinding("Warning: Signature database is empty");
    }
}

std::string SignatureAnalyzer::getName() const {
    return "Signature Analyzer";
}

// ==================== Private Helper Methods ====================

void SignatureAnalyzer::loadDatabaseFromFile(const std::string& filePath) {
    // Only load once (static database)
    if (staticDatabaseLoaded) {
        databaseLoaded = true;
        std::cout << "[SignatureAnalyzer] Using cached signature database ("
                  << signatureDatabase.size() << " signatures)" << std::endl;
        return;
    }
    
    std::ifstream file(filePath.c_str());
    
    if (!file.is_open()) {
        throw FileOpenException("Cannot open signature database: " + filePath);
    }
    
    signatureDatabase.clear();
    std::string line;
    
    while (std::getline(file, line)) {
        line = Utility::trim(line);
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Format: signature,malware_name
        std::vector<std::string> parts = Utility::split(line, ',');
        
        if (parts.size() >= 2) {
            std::string signature = Utility::trim(parts[0]);
            std::string malwareName = Utility::trim(parts[1]);
            signatureDatabase[signature] = malwareName;
        }
    }
    
    file.close();
    staticDatabaseLoaded = true;
    databaseLoaded = true;
    
    std::cout << "[SignatureAnalyzer] Loaded " << signatureDatabase.size() 
              << " signatures from " << filePath << std::endl;
}

bool SignatureAnalyzer::matchesKnownSignature(const std::string& hash) const {
    return signatureDatabase.find(hash) != signatureDatabase.end();
}

std::string SignatureAnalyzer::getMalwareName(const std::string& hash) const {
    std::map<std::string, std::string>::const_iterator it = signatureDatabase.find(hash);
    
    if (it != signatureDatabase.end()) {
        return it->second;
    }
    
    return "";
}

// ==================== Public Methods ====================

void SignatureAnalyzer::loadDatabase(const std::string& filePath) {
    staticDatabaseLoaded = false;  // Force reload
    loadDatabaseFromFile(filePath);
}

int SignatureAnalyzer::getSignatureCount() const {
    return static_cast<int>(signatureDatabase.size());
}

// ==================== Static Methods ====================

void SignatureAnalyzer::addSignature(const std::string& signature, const std::string& malwareName) {
    signatureDatabase[signature] = malwareName;
    std::cout << "[SignatureAnalyzer] Added signature: " << signature 
              << " -> " << malwareName << std::endl;
}

void SignatureAnalyzer::clearDatabase() {
    signatureDatabase.clear();
    staticDatabaseLoaded = false;
    std::cout << "[SignatureAnalyzer] Signature database cleared" << std::endl;
}