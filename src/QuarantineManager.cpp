// QuarantineManager.cpp
// TODO: Implement QuarantineManager.cpp

/**
 * @file QuarantineManager.cpp
 * @brief Implementation of QuarantineManager class
 */

#include "../include/QuarantineManager.h"
#include "../include/Exceptions.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>

// ==================== Constructor & Destructor ====================

QuarantineManager::QuarantineManager(Logger* log, const std::string& quarantineLog)
    : logger(log), quarantineLogPath(quarantineLog) {
    std::cout << "[QuarantineManager] Initialized with log: " 
              << quarantineLogPath << std::endl;
}

QuarantineManager::~QuarantineManager() {
    std::cout << "[QuarantineManager] Destroyed (Total quarantined: " 
              << quarantinedFiles.size() << ")" << std::endl;
}

// ==================== Core Quarantine Methods ====================

bool QuarantineManager::quarantine(const FileSample& file, 
                                   const AnalysisResult& result, 
                                   const User& user) {
    
    std::cout << "\n[QuarantineManager] Quarantine request for: " 
              << file.getFileName() << std::endl;
    
    // Check if file is dangerous enough to quarantine
    if (result.getVerdict() != "DANGEROUS") {
        std::cout << "[QuarantineManager] File is not dangerous (Verdict: " 
                  << result.getVerdict() << ")" << std::endl;
        std::cout << "[QuarantineManager] Quarantine denied - only DANGEROUS files can be quarantined" 
                  << std::endl;
        return false;
    }
    
    // Check if already quarantined
    if (isQuarantined(file.getFilePath())) {
        std::cout << "[QuarantineManager] File already in quarantine" << std::endl;
        return true;
    }
    
    try {
        // Add to quarantine list
        quarantinedFiles.push_back(file.getFilePath());
        
        // Write to quarantine log
        writeQuarantineLog(user.getUsername(), 
                          file.getFilePath(),
                          result.getVerdict(),
                          result.getRiskScore());
        
        // Log to main logger
        if (logger) {
            logger->logQuarantine(user.getUsername(), file.getFileName());
        }
        
        std::cout << "[QuarantineManager] ✓ File quarantined successfully" << std::endl;
        std::cout << "[QuarantineManager] Quarantined by: " << user.getUsername() << std::endl;
        std::cout << "[QuarantineManager] Risk Score: " << result.getRiskScore() << std::endl;
        
        return true;
        
    } catch (const std::exception& e) {
        throw QuarantineException("Failed to quarantine file: " + std::string(e.what()));
    }
}

bool QuarantineManager::isQuarantined(const std::string& filePath) const {
    return std::find(quarantinedFiles.begin(), quarantinedFiles.end(), filePath) 
           != quarantinedFiles.end();
}

const std::vector<std::string>& QuarantineManager::getQuarantinedFiles() const {
    return quarantinedFiles;
}

int QuarantineManager::getQuarantineCount() const {
    return static_cast<int>(quarantinedFiles.size());
}

void QuarantineManager::displayQuarantineList() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "       QUARANTINED FILES" << std::endl;
    std::cout << "========================================" << std::endl;
    
    if (quarantinedFiles.empty()) {
        std::cout << "No files in quarantine.\n" << std::endl;
        return;
    }
    
    std::cout << "Total quarantined: " << quarantinedFiles.size() << "\n" << std::endl;
    
    for (size_t i = 0; i < quarantinedFiles.size(); ++i) {
        std::cout << (i + 1) << ". " << quarantinedFiles[i] << std::endl;
    }
    
    std::cout << "========================================\n" << std::endl;
}

bool QuarantineManager::removeFromQuarantine(const std::string& filePath) {
    std::vector<std::string>::iterator it = std::find(quarantinedFiles.begin(), 
                                                      quarantinedFiles.end(), 
                                                      filePath);
    
    if (it != quarantinedFiles.end()) {
        quarantinedFiles.erase(it);
        std::cout << "[QuarantineManager] File removed from quarantine: " 
                  << filePath << std::endl;
        return true;
    }
    
    return false;
}

// ==================== Private Helper Methods ====================

void QuarantineManager::writeQuarantineLog(const std::string& username, 
                                          const std::string& filePath,
                                          const std::string& verdict,
                                          int riskScore) {
    
    std::ofstream logFile(quarantineLogPath.c_str(), std::ios::app);
    
    if (!logFile.is_open()) {
        throw FileOpenException("Cannot open quarantine log: " + quarantineLogPath);
    }
    
    std::string timestamp = getCurrentTimestamp();
    
    logFile << "\n========================================" << std::endl;
    logFile << "[" << timestamp << "] FILE QUARANTINED" << std::endl;
    logFile << "========================================" << std::endl;
    logFile << "User:       " << username << std::endl;
    logFile << "File:       " << filePath << std::endl;
    logFile << "Verdict:    " << verdict << std::endl;
    logFile << "Risk Score: " << riskScore << std::endl;
    logFile << "========================================\n" << std::endl;
    
    logFile.close();
}

std::string QuarantineManager::getCurrentTimestamp() const {
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