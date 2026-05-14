// AnalysisResult.cpp
// TODO: Implement AnalysisResult.cpp

/**
 * @file AnalysisResult.cpp
 * @brief Implementation of AnalysisResult class
 */

#include "../include/AnalysisResult.h"
#include "../include/Utility.h"
#include <iostream>
#include <iomanip>

// ==================== Constructors & Destructor ====================

AnalysisResult::AnalysisResult() 
    : riskScore(0), verdict("Not Analyzed"), hashValue(""), 
      timestamp(""), analyzedFileName("") {
    // Initialize with safe defaults
}

AnalysisResult::AnalysisResult(const AnalysisResult& other) 
    : riskScore(other.riskScore),
      findings(other.findings),
      verdict(other.verdict),
      hashValue(other.hashValue),
      timestamp(other.timestamp),
      analyzedFileName(other.analyzedFileName) {
    // Deep copy constructor - vector handles deep copy automatically
}

AnalysisResult& AnalysisResult::operator=(const AnalysisResult& other) {
    if (this != &other) {  // Self-assignment check
        riskScore = other.riskScore;
        findings = other.findings;
        verdict = other.verdict;
        hashValue = other.hashValue;
        timestamp = other.timestamp;
        analyzedFileName = other.analyzedFileName;
    }
    return *this;
}

AnalysisResult::~AnalysisResult() {
    // Destructor - no dynamic memory to clean up
}

// ==================== Core Methods ====================

void AnalysisResult::addFinding(const std::string& finding) {
    if (!finding.empty()) {
        findings.push_back(finding);
    }
}

void AnalysisResult::setRiskScore(int score) {
    // Clamp score between 0 and 100
    riskScore = Utility::clamp(score, 0, 100);
}

void AnalysisResult::addToRiskScore(int amount) {
    riskScore += amount;
    // Clamp after addition
    riskScore = Utility::clamp(riskScore, 0, 100);
}

void AnalysisResult::calculateVerdict() {
    if (riskScore >= 0 && riskScore <= 20) {
        verdict = "SAFE";
    } else if (riskScore >= 21 && riskScore <= 50) {
        verdict = "SUSPICIOUS";
    } else if (riskScore >= 51 && riskScore <= 100) {
        verdict = "DANGEROUS";
    } else {
        verdict = "UNKNOWN";
    }
}

void AnalysisResult::setHashValue(const std::string& hash) {
    hashValue = hash;
}

void AnalysisResult::setTimestamp(const std::string& time) {
    timestamp = time;
}

void AnalysisResult::setAnalyzedFileName(const std::string& name) {
    analyzedFileName = name;
}

void AnalysisResult::printSummary() const {
    std::cout << "\n========================================\n";
    std::cout << "       MALWARE ANALYSIS SUMMARY\n";
    std::cout << "========================================\n";
    std::cout << "File:       " << analyzedFileName << "\n";
    std::cout << "Hash:       " << (hashValue.empty() ? "N/A" : hashValue) << "\n";
    std::cout << "Timestamp:  " << (timestamp.empty() ? "N/A" : timestamp) << "\n";
    std::cout << "Risk Score: " << riskScore << " / 100\n";
    std::cout << "Verdict:    " << verdict << "\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Findings (" << findings.size() << "):\n";
    
    if (findings.empty()) {
        std::cout << "  (No suspicious findings)\n";
    } else {
        for (size_t i = 0; i < findings.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << findings[i] << "\n";
        }
    }
    
    std::cout << "========================================\n\n";
}

void AnalysisResult::clear() {
    riskScore = 0;
    findings.clear();
    verdict = "Not Analyzed";
    hashValue = "";
    timestamp = "";
    analyzedFileName = "";
}

// ==================== Getters ====================

int AnalysisResult::getRiskScore() const {
    return riskScore;
}

const std::string& AnalysisResult::getVerdict() const {
    return verdict;
}

const std::vector<std::string>& AnalysisResult::getFindings() const {
    return findings;
}

const std::string& AnalysisResult::getHashValue() const {
    return hashValue;
}

const std::string& AnalysisResult::getTimestamp() const {
    return timestamp;
}

const std::string& AnalysisResult::getAnalyzedFileName() const {
    return analyzedFileName;
}

int AnalysisResult::getFindingsCount() const {
    return static_cast<int>(findings.size());
}

// ==================== Operator Overloading ====================

AnalysisResult& AnalysisResult::operator+=(const std::string& finding) {
    addFinding(finding);
    return *this;
}

bool AnalysisResult::operator>(const AnalysisResult& other) const {
    return riskScore > other.riskScore;
}

bool AnalysisResult::operator<(const AnalysisResult& other) const {
    return riskScore < other.riskScore;
}

bool AnalysisResult::operator==(const AnalysisResult& other) const {
    return riskScore == other.riskScore;
}

// ==================== Friend Function Implementation ====================

/**
 * @brief Stream insertion operator implementation
 * 
 * This friend function has access to private members of AnalysisResult,
 * allowing it to format the output directly without using getters.
 */
std::ostream& operator<<(std::ostream& os, const AnalysisResult& result) {
    os << "AnalysisResult {\n";
    os << "  File: " << result.analyzedFileName << "\n";
    os << "  Risk Score: " << result.riskScore << "\n";
    os << "  Verdict: " << result.verdict << "\n";
    os << "  Hash: " << result.hashValue << "\n";
    os << "  Findings: " << result.findings.size() << "\n";
    
    for (size_t i = 0; i < result.findings.size(); ++i) {
        os << "    - " << result.findings[i] << "\n";
    }
    
    os << "}";
    return os;
}