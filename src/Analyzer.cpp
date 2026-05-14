/**
 * @file Analyzer.cpp
 * @brief Implementation of Analyzer base class
 */

#include "../include/Analyzer.h"
#include <iostream>

// Initialize static member
const int Analyzer::MAX_RISK_CONTRIBUTION = 50;

// ==================== Protected Constructor ====================

Analyzer::Analyzer(const std::string& name) 
    : analyzerName(name) {
    // Protected constructor - only derived classes can call this
}

// ==================== Virtual Destructor ====================

Analyzer::~Analyzer() {
    // Virtual destructor ensures proper cleanup of derived classes
    std::cout << "[Analyzer] Base destructor called for: " 
              << analyzerName << std::endl;
}

// ==================== Non-Virtual Methods ====================

const std::string& Analyzer::getAnalyzerName() const {
    return analyzerName;
}