// Exceptions.cpp
// TODO: Implement Exceptions.cpp

/**
 * @file Exceptions.cpp
 * @brief Implementation of custom exception classes
 */

#include "../include/Exceptions.h"

// ==================== AnalyzerException ====================

AnalyzerException::AnalyzerException(const std::string& msg) 
    : message(msg) {
    // Initializer list ensures efficient initialization
}

const char* AnalyzerException::what() const throw() {
    return message.c_str();
}

AnalyzerException::~AnalyzerException() throw() {
    // Virtual destructor ensures proper cleanup in derived classes
}

// ==================== FileOpenException ====================

FileOpenException::FileOpenException(const std::string& msg) 
    : AnalyzerException("File Open Error: " + msg) {
    // Prepends error type to message for clarity
}

// ==================== InvalidFileException ====================

InvalidFileException::InvalidFileException(const std::string& msg) 
    : AnalyzerException("Invalid File Error: " + msg) {
    // Prepends error type to message for clarity
}

// ==================== AuthenticationException ====================

AuthenticationException::AuthenticationException(const std::string& msg) 
    : AnalyzerException("Authentication Error: " + msg) {
    // Prepends error type to message for clarity
}

// ==================== QuarantineException ====================

QuarantineException::QuarantineException(const std::string& msg) 
    : AnalyzerException("Quarantine Error: " + msg) {
    // Prepends error type to message for clarity
}