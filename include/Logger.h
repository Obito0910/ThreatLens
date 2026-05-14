// Logger.h
// TODO: Implement Logger.h

/**
 * @file Logger.h
 * @brief Logging system for analysis activities
 * @details Writes activity logs to file for audit and debugging
 * 
 * OOP Concepts Demonstrated:
 * - File I/O (writing logs)
 * - Encapsulation (private file stream)
 * - Static members (log counter)
 * - Exception handling (file write errors)
 */

#ifndef LOGGER_H
#define LOGGER_H

#include "User.h"
#include "AnalysisResult.h"
#include "FileSample.h"
#include <string>
#include <fstream>

/**
 * @class Logger
 * @brief Handles logging of all system activities to file
 * 
 * The Logger writes timestamped entries to a log file for:
 * - Analysis activities
 * - User actions
 * - System events
 * - Error tracking
 * 
 * All logs are appended to the file (not overwritten) to maintain
 * a complete audit trail.
 */
class Logger {
private:
    std::string logFilePath;       ///< Path to the log file
    std::ofstream logStream;       ///< Output file stream (kept open for efficiency)
    bool isOpen;                   ///< Flag indicating if log file is open
    
    // Static member - shared log counter
    static int totalLogs;          ///< Total number of log entries written
    
    /**
     * @brief Generates current timestamp for log entries
     * @return Timestamp string
     */
    std::string getCurrentTimestamp() const;
    
    /**
     * @brief Opens the log file for writing
     * @throws FileOpenException if file cannot be opened
     * 
     * Private helper for encapsulation.
     */
    void openLogFile();
    
    /**
     * @brief Closes the log file
     */
    void closeLogFile();
    
public:
    /**
     * @brief Constructor with log file path
     * @param filePath Path to the log file
     */
    explicit Logger(const std::string& filePath);
    
    /**
     * @brief Destructor - ensures log file is closed
     */
    ~Logger();
    
    /**
     * @brief Logs a general message
     * @param level Log level (INFO, WARNING, ERROR)
     * @param message Message to log
     * 
     * General purpose logging method.
     */
    void log(const std::string& level, const std::string& message);
    
    /**
     * @brief Logs an analysis operation
     * @param user User who performed the analysis
     * @param result Analysis result
     * 
     * Logs complete analysis details including:
     * - Username
     * - Timestamp
     * - File name
     * - Risk score
     * - Verdict
     * - Number of findings
     */
    void logAnalysis(const User& user, const AnalysisResult& result);
    
    /**
     * @brief Logs user login event
     * @param username Username of logged in user
     */
    void logLogin(const std::string& username);
    
    /**
     * @brief Logs user logout event
     * @param username Username of logged out user
     */
    void logLogout(const std::string& username);
    
    /**
     * @brief Logs file quarantine event
     * @param username User who quarantined the file
     * @param fileName Name of quarantined file
     */
    void logQuarantine(const std::string& username, const std::string& fileName);
    
    /**
     * @brief Logs an error
     * @param error Error message
     */
    void logError(const std::string& error);
    
    /**
     * @brief Checks if logger is operational
     * @return true if log file is open and writable
     */
    bool isOperational() const;
    
    /**
     * @brief Gets the log file path
     * @return Log file path
     */
    const std::string& getLogFilePath() const;
    
    /**
     * @brief Flushes the log buffer to disk
     * 
     * Ensures all pending log entries are written to file.
     */
    void flush();
    
    // ==================== Static Methods ====================
    
    /**
     * @brief Gets total number of logs written
     * @return Total log count
     */
    static int getTotalLogs();
    
    /**
     * @brief Resets the log counter
     */
    static void resetLogCounter();
};

#endif // LOGGER_H