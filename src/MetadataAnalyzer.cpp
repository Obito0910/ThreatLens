// MetadataAnalyzer.cpp
// TODO: Implement MetadataAnalyzer.cpp

/**
 * @file MetadataAnalyzer.cpp
 * @brief Implementation of MetadataAnalyzer class
 */

#include "../include/MetadataAnalyzer.h"
#include "../include/Exceptions.h"
#include "../include/Utility.h"
#include <fstream>
#include <iostream>

// Initialize static members
const long MetadataAnalyzer::SUSPICIOUS_SIZE_THRESHOLD = 100L * 1024L * 1024L;  // 100 MB
const long MetadataAnalyzer::TINY_SIZE_THRESHOLD = 1024L;  // 1 KB

// ==================== Constructors & Destructor ====================

MetadataAnalyzer::MetadataAnalyzer() 
    : Analyzer("Metadata Analyzer"), extensionsLoaded(false) {
    // Load default dangerous extensions
    try {
        loadExtensionsFromFile("data/dangerous_extensions.txt");
    } catch (const FileOpenException& e) {
        std::cerr << "[MetadataAnalyzer] Warning: " << e.what() << std::endl;
        std::cerr << "[MetadataAnalyzer] Using minimal default extensions" << std::endl;
        // Add basic dangerous extensions as fallback
        dangerousExtensions.push_back(".exe");
        dangerousExtensions.push_back(".dll");
        dangerousExtensions.push_back(".bat");
        dangerousExtensions.push_back(".cmd");
        dangerousExtensions.push_back(".vbs");
        dangerousExtensions.push_back(".ps1");
        extensionsLoaded = true;
    }
}

MetadataAnalyzer::MetadataAnalyzer(const std::string& extensionsFile) 
    : Analyzer("Metadata Analyzer"), extensionsLoaded(false) {
    loadExtensionsFromFile(extensionsFile);
}

MetadataAnalyzer::~MetadataAnalyzer() {
    std::cout << "[MetadataAnalyzer] Destroyed" << std::endl;
}

// ==================== Virtual Method Implementations ====================

void MetadataAnalyzer::analyze(FileSample& file, AnalysisResult& result) {
    std::cout << "[MetadataAnalyzer] Analyzing metadata for: " 
              << file.getFileName() << std::endl;
    
    if (!file.getIsLoaded()) {
        throw InvalidFileException("File must be loaded before metadata analysis");
    }
    
    int riskIncrease = 0;
    
    // Check 1: Dangerous extension
    std::string extension = file.getExtension();
    if (isDangerousExtension(extension)) {
        result.addFinding("Dangerous file extension detected: " + extension);
        riskIncrease += 20;
        std::cout << "[MetadataAnalyzer] Dangerous extension: " << extension << std::endl;
    } else {
        result.addFinding("File extension: " + extension + " (acceptable)");
    }
    
    // Check 2: Suspicious file size
    long fileSize = file.getFileSize();
    if (isSuspiciousSize(fileSize, extension)) {
        result.addFinding("Suspicious file size: " + Utility::toString(fileSize) + " bytes");
        riskIncrease += 10;
        std::cout << "[MetadataAnalyzer] Suspicious size: " << fileSize << " bytes" << std::endl;
    }
    
    // Check 3: Suspicious filename
    std::string fileName = file.getFileName();
    if (isSuspiciousFileName(fileName)) {
        result.addFinding("Suspicious filename pattern: " + fileName);
        riskIncrease += 15;
        std::cout << "[MetadataAnalyzer] Suspicious filename: " << fileName << std::endl;
    }
    
    // Apply risk increase
    if (riskIncrease > 0) {
        result.addToRiskScore(riskIncrease);
        std::cout << "[MetadataAnalyzer] Risk increased by " << riskIncrease << std::endl;
    } else {
        std::cout << "[MetadataAnalyzer] No suspicious metadata detected" << std::endl;
    }
}

std::string MetadataAnalyzer::getName() const {
    return "Metadata Analyzer";
}

// ==================== Private Helper Methods ====================

void MetadataAnalyzer::loadExtensionsFromFile(const std::string& filePath) {
    std::ifstream file(filePath.c_str());
    
    if (!file.is_open()) {
        throw FileOpenException("Cannot open extensions file: " + filePath);
    }
    
    dangerousExtensions.clear();
    std::string line;
    
    while (std::getline(file, line)) {
        line = Utility::trim(line);
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Ensure extension starts with a dot
        if (!line.empty() && line[0] != '.') {
            line = "." + line;
        }
        
        dangerousExtensions.push_back(Utility::toLowerCase(line));
    }
    
    file.close();
    extensionsLoaded = true;
    
    std::cout << "[MetadataAnalyzer] Loaded " << dangerousExtensions.size() 
              << " dangerous extensions from " << filePath << std::endl;
}

bool MetadataAnalyzer::isDangerousExtension(const std::string& extension) const {
    std::string lowerExt = Utility::toLowerCase(extension);
    
    for (size_t i = 0; i < dangerousExtensions.size(); ++i) {
        if (lowerExt == dangerousExtensions[i]) {
            return true;
        }
    }
    
    return false;
}

bool MetadataAnalyzer::isSuspiciousSize(long size, const std::string& extension) const {
    // Very large files are suspicious
    if (size > SUSPICIOUS_SIZE_THRESHOLD) {
        return true;
    }
    
    // Executables that are too small might be droppers or packed malware
    std::string lowerExt = Utility::toLowerCase(extension);
    if ((lowerExt == ".exe" || lowerExt == ".dll") && size < TINY_SIZE_THRESHOLD) {
        return true;
    }
    
    return false;
}

bool MetadataAnalyzer::isSuspiciousFileName(const std::string& fileName) const {
    std::string lowerName = Utility::toLowerCase(fileName);
    
    // Check for suspicious keywords in filename
    std::vector<std::string> suspiciousKeywords;
    suspiciousKeywords.push_back("crack");
    suspiciousKeywords.push_back("keygen");
    suspiciousKeywords.push_back("patch");
    suspiciousKeywords.push_back("hack");
    suspiciousKeywords.push_back("trojan");
    suspiciousKeywords.push_back("virus");
    suspiciousKeywords.push_back("malware");
    suspiciousKeywords.push_back("ransomware");
    suspiciousKeywords.push_back("backdoor");
    
    for (size_t i = 0; i < suspiciousKeywords.size(); ++i) {
        if (lowerName.find(suspiciousKeywords[i]) != std::string::npos) {
            return true;
        }
    }
    
    // Check for double extensions (e.g., "document.pdf.exe")
    size_t dotCount = 0;
    for (size_t i = 0; i < fileName.length(); ++i) {
        if (fileName[i] == '.') {
            dotCount++;
        }
    }
    
    if (dotCount >= 2) {
        return true;  // Double extension is suspicious
    }
    
    return false;
}

// ==================== Public Methods ====================

void MetadataAnalyzer::loadExtensions(const std::string& filePath) {
    loadExtensionsFromFile(filePath);
}

int MetadataAnalyzer::getExtensionCount() const {
    return static_cast<int>(dangerousExtensions.size());
}