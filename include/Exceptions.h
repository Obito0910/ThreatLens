// Exceptions.h
// TODO: Implement Exceptions.h

/**
 * @file Exceptions.h
 * @brief Custom exception classes for the Malware Analysis Simulator
 * @details Defines a hierarchy of exceptions derived from std::exception
 *          for handling various error conditions in the analysis system.
 * 
 * OOP Concepts Demonstrated:
 * - Exception Handling
 * - Inheritance (exception hierarchy)
 * - Polymorphism (virtual what() method)
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

/**
 * @class AnalyzerException
 * @brief Base exception class for all analyzer-related errors
 * 
 * Serves as the root of the exception hierarchy, allowing catch blocks
 * to handle all analyzer exceptions with a single handler if needed.
 */
class AnalyzerException : public std::exception {
protected:
    std::string message;  ///< Error message describing the exception
    
public:
    /**
     * @brief Constructs an AnalyzerException with a message
     * @param msg Error message describing what went wrong
     */
    explicit AnalyzerException(const std::string& msg);
    
    /**
     * @brief Returns the error message
     * @return C-string containing the error description
     */
    virtual const char* what() const throw();
    
    /**
     * @brief Virtual destructor for proper cleanup in derived classes
     */
    virtual ~AnalyzerException() throw();
};

/**
 * @class FileOpenException
 * @brief Exception thrown when a file cannot be opened or accessed
 * 
 * This exception is raised when attempting to open a file that doesn't exist,
 * lacks proper permissions, or cannot be accessed for any reason.
 */
class FileOpenException : public AnalyzerException {
public:
    /**
     * @brief Constructs a FileOpenException with a specific message
     * @param msg Description of the file access error
     */
    explicit FileOpenException(const std::string& msg);
};

/**
 * @class InvalidFileException
 * @brief Exception thrown when a file format is invalid or corrupted
 * 
 * Raised when a file's content doesn't match expected format, is corrupted,
 * or contains invalid data that cannot be properly analyzed.
 */
class InvalidFileException : public AnalyzerException {
public:
    /**
     * @brief Constructs an InvalidFileException with a specific message
     * @param msg Description of the file validation error
     */
    explicit InvalidFileException(const std::string& msg);
};

/**
 * @class AuthenticationException
 * @brief Exception thrown when authentication or authorization fails
 * 
 * Raised when user credentials are invalid, user doesn't have proper
 * permissions, or authentication system encounters an error.
 */
class AuthenticationException : public AnalyzerException {
public:
    /**
     * @brief Constructs an AuthenticationException with a specific message
     * @param msg Description of the authentication error
     */
    explicit AuthenticationException(const std::string& msg);
};

/**
 * @class QuarantineException
 * @brief Exception thrown when quarantine operations fail
 * 
 * Raised when attempting to quarantine a file fails due to system errors,
 * permission issues, or quarantine directory problems.
 */
class QuarantineException : public AnalyzerException {
public:
    /**
     * @brief Constructs a QuarantineException with a specific message
     * @param msg Description of the quarantine error
     */
    explicit QuarantineException(const std::string& msg);
};

#endif // EXCEPTIONS_H