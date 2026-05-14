// Logger.cpp
// TODO: Implement Logger.cpp

/**
 * @file Logger.cpp
 * @brief Implementation of Logger class
 */

#include "../include/Logger.h"
#include "../include/Exceptions.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

// Initialize static member
int Logger::totalLogs = 0;

// ==================== Constructor & Destructor ====================

Logger::Logger(const std::string& filePath) 
    : logFilePath(filePath), isOpen(false) {
    try {
        openLogFile();
        log("INFO", "Logger initialized: " + filePath);
    } catch (const FileOpenException& e) {
        std::cerr << "[Logger] Failed to initialize: " << e.what() << std::endl;
    }
}

Logger::~Logger() {
    if (isOpen) {
        log("INFO", "Logger shutting down");
        closeLogFile();
    }
}

// ==================== Core Logging Methods ====================

void Logger::log(const std::string& level, const std::string& message) {
    if (!isOpen) {
        std::cerr << "[Logger] Cannot log: file not open" << std::endl;
        return;
    }
    
    std::string timestamp = getCurrentTimestamp();
    
    // Format: [TIMESTAMP] [LEVEL] Message
    logStream << "[" << timestamp << "] "
              << "[" << level << "] "
              << message << std::endl;
    
    totalLogs++;
    
    // Also print to console for important messages
    if (level == "ERROR" || level == "WARNING") {
        std::cout << "[" << level << "] " << message << std::endl;
    }
}

void Logger::logAnalysis(const User& user, const AnalysisResult& result) {
    if (!isOpen) {
        std::cerr << "[Logger] Cannot log analysis: file not open" << std::endl;
        return;
    }
    
    std::string timestamp = getCurrentTimestamp();
    
    // Write detailed analysis log entry
    logStream << "\n========================================" << std::endl;
    logStream << "[" << timestamp << "] ANALYSIS COMPLETED" << std::endl;
    logStream << "========================================" << std::endl;
    logStream << "User:         " << user.getUsername() << std::endl;
    logStream << "Role:         " << user.getRole() << std::endl;
    logStream << "File:         " << result.getAnalyzedFileName() << std::endl;
    logStream << "Hash:         " << result.getHashValue() << std::endl;
    logStream << "Risk Score:   " << result.getRiskScore() << "/100" << std::endl;
    logStream << "Verdict:      " << result.getVerdict() << std::endl;
    logStream << "Findings:     " << result.getFindingsCount() << std::endl;
    logStream << "Timestamp:    " << result.getTimestamp() << std::endl;
    logStream << "========================================\n" << std::endl;
    
    totalLogs++;
    
    std::cout << "[Logger] Analysis logged for: " << result.getAnalyzedFileName() << std::endl;
}

void Logger::logLogin(const std::string& username) {
    log("INFO", "User logged in: " + username);
}

void Logger::logLogout(const std::string& username) {
    log("INFO", "User logged out: " + username);
}

void Logger::logQuarantine(const std::string& username, const std::string& fileName) {
    log("WARNING", "File quarantined by " + username + ": " + fileName);
}

void Logger::logError(const std::string& error) {
    log("ERROR", error);
}

// ==================== File Management ====================

void Logger::openLogFile() {
    logStream.open(logFilePath.c_str(), std::ios::app);  // Append mode
    
    if (!logStream.is_open()) {
        throw FileOpenException("Cannot open log file: " + logFilePath);
    }
    
    isOpen = true;
}

void Logger::closeLogFile() {
    if (logStream.is_open()) {
        logStream.close();
    }
    isOpen = false;
}

// ==================== Helper Methods ====================

std::string Logger::getCurrentTimestamp() const {
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

bool Logger::isOperational() const {
    return isOpen && logStream.good();
}

const std::string& Logger::getLogFilePath() const {
    return logFilePath;
}

void Logger::flush() {
    if (isOpen) {
        logStream.flush();
    }
}

// ==================== Static Methods ====================

int Logger::getTotalLogs() {
    return totalLogs;
}

void Logger::resetLogCounter() {
    totalLogs = 0;
}