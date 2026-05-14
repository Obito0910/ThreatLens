// ReportGenerator.cpp
// TODO: Implement ReportGenerator.cpp

/**
 * @file ReportGenerator.cpp
 * @brief Implementation of ReportGenerator class
 */

#include "../include/ReportGenerator.h"
#include "../include/Exceptions.h"
#include "../include/Utility.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

// ==================== Constructor & Destructor ====================

ReportGenerator::ReportGenerator(const std::string& directory) 
    : reportDirectory(directory) {
    std::cout << "[ReportGenerator] Initialized with directory: " 
              << reportDirectory << std::endl;
}

ReportGenerator::~ReportGenerator() {
    std::cout << "[ReportGenerator] Destroyed" << std::endl;
}

// ==================== Core Methods ====================

std::string ReportGenerator::generateReport(const FileSample& file, 
                                           const AnalysisResult& result,
                                           const User& user) {
    std::cout << "[ReportGenerator] Generating report for: " 
              << file.getFileName() << std::endl;
    
    // Generate report content
    std::string content = generateReportContent(file, result, user);
    
    // Generate unique filename
    std::string filename = generateReportFilename(file.getFileName());
    std::string fullPath = reportDirectory + filename;
    
    // Write to file
    std::ofstream reportFile(fullPath.c_str());
    
    if (!reportFile.is_open()) {
        throw FileOpenException("Cannot create report file: " + fullPath);
    }
    
    reportFile << content;
    reportFile.close();
    
    std::cout << "[ReportGenerator] Report saved: " << fullPath << std::endl;
    
    return fullPath;
}

std::string ReportGenerator::generateSummaryReport(const AnalysisResult& result) {
    std::cout << "[ReportGenerator] Generating summary report" << std::endl;
    
    std::string filename = generateReportFilename(result.getAnalyzedFileName() + "_summary");
    std::string fullPath = reportDirectory + filename;
    
    std::ofstream reportFile(fullPath.c_str());
    
    if (!reportFile.is_open()) {
        throw FileOpenException("Cannot create summary report: " + fullPath);
    }
    
    // Write summary header
    reportFile << "========================================\n";
    reportFile << "   ANALYSIS SUMMARY REPORT\n";
    reportFile << "========================================\n\n";
    
    reportFile << "File:       " << result.getAnalyzedFileName() << "\n";
    reportFile << "Risk Score: " << result.getRiskScore() << "/100\n";
    reportFile << "Verdict:    " << result.getVerdict() << "\n";
    reportFile << "Timestamp:  " << result.getTimestamp() << "\n\n";
    
    reportFile << "Findings: " << result.getFindingsCount() << "\n";
    
    reportFile.close();
    
    return fullPath;
}

// ==================== Private Helper Methods ====================

std::string ReportGenerator::generateReportContent(const FileSample& file, 
                                                  const AnalysisResult& result,
                                                  const User& user) const {
    std::stringstream ss;
    
    // Header
    ss << "============================================\n";
    ss << "        MALWARE ANALYSIS REPORT\n";
    ss << "============================================\n\n";
    
    // Analyst Information
    ss << "ANALYST INFORMATION\n";
    ss << "-------------------------------------------\n";
    ss << "Analyst:      " << user.getUsername() << "\n";
    ss << "Role:         " << user.getRole() << "\n";
    ss << "Analysis Date: " << result.getTimestamp() << "\n";
    ss << "Report Date:   " << getCurrentTimestamp() << "\n\n";
    
    // File Information
    ss << "FILE INFORMATION\n";
    ss << "-------------------------------------------\n";
    ss << "File Name:     " << file.getFileName() << "\n";
    ss << "File Path:     " << file.getFilePath() << "\n";
    ss << "File Size:     " << file.getFileSize() << " bytes\n";
    ss << "File Extension: " << file.getExtension() << "\n";
    ss << "File Hash:     " << result.getHashValue() << "\n\n";
    
    // Analysis Results
    ss << "ANALYSIS RESULTS\n";
    ss << "-------------------------------------------\n";
    ss << "Risk Score:    " << result.getRiskScore() << " / 100\n";
    ss << "Verdict:       " << result.getVerdict() << "\n";
    ss << "Total Findings: " << result.getFindingsCount() << "\n\n";
    
    // Detailed Findings
    ss << "DETAILED FINDINGS\n";
    ss << "-------------------------------------------\n";
    
    const std::vector<std::string>& findings = result.getFindings();
    if (findings.empty()) {
        ss << "No suspicious findings detected.\n";
    } else {
        for (size_t i = 0; i < findings.size(); ++i) {
            ss << (i + 1) << ". " << findings[i] << "\n";
        }
    }
    ss << "\n";
    
    // Risk Assessment
    ss << "RISK ASSESSMENT\n";
    ss << "-------------------------------------------\n";
    
    if (result.getRiskScore() <= 20) {
        ss << "Risk Level: LOW\n";
        ss << "This file appears to be safe based on the analysis.\n";
    } else if (result.getRiskScore() <= 50) {
        ss << "Risk Level: MEDIUM\n";
        ss << "This file exhibits some suspicious characteristics.\n";
    } else {
        ss << "Risk Level: HIGH\n";
        ss << "This file shows strong indicators of malicious behavior.\n";
    }
    ss << "\n";
    
    // Recommendations
    ss << "RECOMMENDATIONS\n";
    ss << "-------------------------------------------\n";
    ss << generateRecommendations(result.getVerdict(), result.getRiskScore());
    ss << "\n";
    
    // Footer
    ss << "============================================\n";
    ss << "        END OF REPORT\n";
    ss << "============================================\n";
    
    return ss.str();
}

std::string ReportGenerator::generateReportFilename(const std::string& baseName) const {
    // Extract filename without extension
    std::string cleanName = baseName;
    size_t dotPos = cleanName.find_last_of('.');
    if (dotPos != std::string::npos) {
        cleanName = cleanName.substr(0, dotPos);
    }
    
    // Replace spaces and special characters with underscores
    for (size_t i = 0; i < cleanName.length(); ++i) {
        if (!isalnum(cleanName[i])) {
            cleanName[i] = '_';
        }
    }
    
    // Add timestamp
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    
    std::stringstream ss;
    ss << cleanName << "_"
       << (1900 + timeinfo->tm_year)
       << std::setw(2) << std::setfill('0') << (1 + timeinfo->tm_mon)
       << std::setw(2) << std::setfill('0') << timeinfo->tm_mday << "_"
       << std::setw(2) << std::setfill('0') << timeinfo->tm_hour
       << std::setw(2) << std::setfill('0') << timeinfo->tm_min
       << std::setw(2) << std::setfill('0') << timeinfo->tm_sec
       << "_report.txt";
    
    return ss.str();
}

std::string ReportGenerator::getCurrentTimestamp() const {
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

std::string ReportGenerator::generateRecommendations(const std::string& verdict, 
                                                     int riskScore) const {
    std::stringstream ss;
    
    if (verdict == "SAFE" || riskScore <= 20) {
        ss << "- File appears to be safe for use.\n";
        ss << "- No immediate action required.\n";
        ss << "- Continue regular security monitoring.\n";
        
    } else if (verdict == "SUSPICIOUS" || riskScore <= 50) {
        ss << "- Exercise caution when handling this file.\n";
        ss << "- Consider additional scanning with updated signatures.\n";
        ss << "- Avoid executing the file in production environments.\n";
        ss << "- Monitor system behavior if file has been executed.\n";
        ss << "- Consider quarantining the file for further analysis.\n";
        
    } else {  // DANGEROUS
        ss << "- DO NOT execute this file.\n";
        ss << "- IMMEDIATELY quarantine the file.\n";
        ss << "- Scan the system for additional malware.\n";
        ss << "- Review system logs for signs of compromise.\n";
        ss << "- Change passwords if sensitive data may be exposed.\n";
        ss << "- Report to security team immediately.\n";
        ss << "- Consider full system scan and restoration from backup.\n";
    }
    
    return ss.str();
}

// ==================== Getters & Setters ====================

const std::string& ReportGenerator::getReportDirectory() const {
    return reportDirectory;
}

void ReportGenerator::setReportDirectory(const std::string& directory) {
    reportDirectory = directory;
    std::cout << "[ReportGenerator] Report directory updated: " 
              << reportDirectory << std::endl;
}