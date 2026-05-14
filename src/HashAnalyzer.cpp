// HashAnalyzer.cpp
// TODO: Implement HashAnalyzer.cpp

/**
 * @file HashAnalyzer.cpp
 * @brief Implementation of HashAnalyzer class
 */

#include "../include/HashAnalyzer.h"
#include "../include/Exceptions.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

// ==================== Constructors & Destructor ====================

HashAnalyzer::HashAnalyzer() 
    : Analyzer("Hash Analyzer"), hashAlgorithm("SimpleChecksum") {
    std::cout << "[HashAnalyzer] Initialized with algorithm: " 
              << hashAlgorithm << std::endl;
}

HashAnalyzer::HashAnalyzer(const std::string& algorithm) 
    : Analyzer("Hash Analyzer"), hashAlgorithm(algorithm) {
    std::cout << "[HashAnalyzer] Initialized with algorithm: " 
              << hashAlgorithm << std::endl;
}

HashAnalyzer::~HashAnalyzer() {
    std::cout << "[HashAnalyzer] Destroyed" << std::endl;
}

// ==================== Virtual Method Implementations ====================

void HashAnalyzer::analyze(FileSample& file, AnalysisResult& result) {
    std::cout << "[HashAnalyzer] Analyzing file: " << file.getFileName() << std::endl;
    
    if (!file.getIsLoaded()) {
        throw InvalidFileException("File must be loaded before hash analysis");
    }
    
    try {
        // Compute checksum
        std::string hash = computeChecksum(file.getFilePath());
        
        // Store hash in result
        result.setHashValue(hash);
        
        // Add finding
        result.addFinding("Hash computed: " + hash);
        
        std::cout << "[HashAnalyzer] Hash: " << hash << std::endl;
        
        // Hash analysis doesn't add to risk score by default
        // (unless the hash matches a known malware hash in a database)
        
    } catch (const FileOpenException& e) {
        result.addFinding("Hash analysis failed: " + std::string(e.what()));
        throw;  // Re-throw to notify caller
    }
}

std::string HashAnalyzer::getName() const {
    return "Hash Analyzer";
}

// ==================== Private Helper Methods ====================

std::string HashAnalyzer::computeChecksum(const std::string& filePath) const {
    std::ifstream file(filePath.c_str(), std::ios::binary);
    
    if (!file.is_open()) {
        throw FileOpenException("Cannot open file for hash computation: " + filePath);
    }
    
    // Simple checksum algorithm (for educational purposes)
    // Real implementation would use SHA-256, MD5, etc.
    unsigned int checksum = 0;
    char byte;
    int position = 0;
    
    while (file.get(byte)) {
        // XOR with rotating position
        checksum ^= (static_cast<unsigned char>(byte) << (position % 24));
        checksum = (checksum << 1) | (checksum >> 31);  // Rotate left
        position++;
    }
    
    file.close();
    
    // Convert to hex string
    return toHex(checksum);
}

std::string HashAnalyzer::toHex(unsigned int value) const {
    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << value;
    return ss.str();
}

// ==================== Getters ====================

const std::string& HashAnalyzer::getHashAlgorithm() const {
    return hashAlgorithm;
}