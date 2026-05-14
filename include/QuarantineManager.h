// QuarantineManager.h
// TODO: Implement QuarantineManager.h

/**
 * @file QuarantineManager.h
 * @brief Manages file quarantine operations
 * @details Simulates quarantining dangerous files and logs actions
 * 
 * OOP Concepts Demonstrated:
 * - Aggregation (uses Logger but doesn't own it)
 * - File I/O (quarantine logging)
 * - Exception handling
 */

#ifndef QUARANTINEMANAGER_H
#define QUARANTINEMANAGER_H

#include "FileSample.h"
#include "AnalysisResult.h"
#include "User.h"
#include "Logger.h"
#include <string>
#include <vector>

/**
 * @class QuarantineManager
 * @brief Manages quarantine operations for suspicious files
 * 
 * The QuarantineManager simulates quarantining files by:
 * - Recording file paths in quarantine log
 * - Logging quarantine actions
 * - Maintaining list of quarantined files
 * 
 * Note: This is a simulation. In production, actual file operations
 * would move files to a secure quarantine directory with restricted access.
 */
class QuarantineManager {
private:
    std::vector<std::string> quarantinedFiles;  ///< List of quarantined file paths
    Logger* logger;                             ///< Logger for quarantine events
    std::string quarantineLogPath;              ///< Path to quarantine log file
    
    /**
     * @brief Writes quarantine entry to log file
     * @param username User who quarantined the file
     * @param filePath Path to quarantined file
     * @param verdict Analysis verdict
     * @param riskScore Risk score
     * @throws FileOpenException if log cannot be written
     * 
     * Private helper for encapsulation.
     */
    void writeQuarantineLog(const std::string& username, 
                           const std::string& filePath,
                           const std::string& verdict,
                           int riskScore);
    
    /**
     * @brief Gets current timestamp
     * @return Timestamp string
     */
    std::string getCurrentTimestamp() const;
    
public:
    /**
     * @brief Constructor with logger
     * @param log Logger instance for events (aggregation - doesn't own)
     * @param quarantineLog Path to quarantine log (default: "logs/quarantine.log")
     */
    explicit QuarantineManager(Logger* log, const std::string& quarantineLog = "logs/quarantine.log");
    
    /**
     * @brief Destructor
     */
    ~QuarantineManager();
    
    /**
     * @brief Quarantines a file based on analysis result
     * @param file FileSample to quarantine
     * @param result Analysis result
     * @param user User performing the quarantine
     * @return true if quarantine successful
     * @throws QuarantineException if quarantine fails
     * 
     * Only quarantines if verdict is "DANGEROUS".
     * If file is not dangerous, returns false without error.
     */
    bool quarantine(const FileSample& file, const AnalysisResult& result, const User& user);
    
    /**
     * @brief Checks if a file is quarantined
     * @param filePath Path to check
     * @return true if file is in quarantine
     */
    bool isQuarantined(const std::string& filePath) const;
    
    /**
     * @brief Gets list of all quarantined files
     * @return Vector of quarantined file paths
     */
    const std::vector<std::string>& getQuarantinedFiles() const;
    
    /**
     * @brief Gets the number of quarantined files
     * @return Quarantine count
     */
    int getQuarantineCount() const;
    
    /**
     * @brief Displays all quarantined files
     */
    void displayQuarantineList() const;
    
    /**
     * @brief Simulates removing a file from quarantine
     * @param filePath Path to remove
     * @return true if removed successfully
     * 
     * In production, this would restore the file from quarantine.
     */
    bool removeFromQuarantine(const std::string& filePath);
};

#endif // QUARANTINEMANAGER_H