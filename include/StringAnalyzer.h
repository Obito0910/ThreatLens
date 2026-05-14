// StringAnalyzer.h
// TODO: Implement StringAnalyzer.h

/**
 * @file StringAnalyzer.h
 * @brief Analyzer that searches for suspicious strings in files
 * @details Loads suspicious keywords from data file and searches extracted strings
 * 
 * OOP Concepts Demonstrated:
 * - Inheritance (derives from Analyzer)
 * - Polymorphism (overrides virtual methods)
 * - File I/O (loading keyword database)
 * - Static members (shared keyword list)
 */

#ifndef STRINGANALYZER_H
#define STRINGANALYZER_H

#include "Analyzer.h"
#include <vector>

/**
 * @class StringAnalyzer
 * @brief Searches file strings for suspicious patterns and keywords
 * 
 * This analyzer loads a database of suspicious strings (e.g., "cmd.exe",
 * "registry", "keylogger") and searches the file's extracted strings
 * for matches. Each match increases the risk score.
 * 
 * Suspicious strings may indicate:
 * - System manipulation (cmd.exe, regedit, powershell)
 * - Malicious behavior (keylogger, ransomware, backdoor)
 * - Network activity (download, socket, connect)
 */
class StringAnalyzer : public Analyzer {
private:
    std::vector<std::string> suspiciousPatterns;  ///< List of suspicious keywords
    bool patternsLoaded;                          ///< Flag indicating if patterns are loaded
    int riskPerMatch;                             ///< Risk score added per match
    
    // Static member - shared across all StringAnalyzer instances
    static std::vector<std::string> globalSuspiciousKeywords;  ///< Global keyword list
    
    /**
     * @brief Loads suspicious patterns from file
     * @param filePath Path to the patterns file
     * @throws FileOpenException if file cannot be opened
     * 
     * Private helper method for encapsulation.
     */
    void loadPatternsFromFile(const std::string& filePath);
    
    /**
     * @brief Checks if a string contains a suspicious pattern
     * @param str String to check
     * @return true if suspicious pattern found
     */
    bool containsSuspiciousPattern(const std::string& str) const;
    
public:
    /**
     * @brief Default constructor
     */
    StringAnalyzer();
    
    /**
     * @brief Parameterized constructor
     * @param patternsFile Path to file containing suspicious patterns
     * @param riskPerMatch Risk score to add per match (default: 10)
     */
    explicit StringAnalyzer(const std::string& patternsFile, int riskPerMatch = 10);
    
    /**
     * @brief Destructor
     */
    virtual ~StringAnalyzer();
    
    /**
     * @brief Performs string analysis on the file
     * @param file FileSample to analyze
     * @param result AnalysisResult to store findings
     * 
     * Overrides the pure virtual function from Analyzer.
     * Searches extracted strings for suspicious patterns.
     */
    virtual void analyze(FileSample& file, AnalysisResult& result);
    
    /**
     * @brief Gets the name of this analyzer
     * @return "String Analyzer"
     * 
     * Overrides the pure virtual function from Analyzer.
     */
    virtual std::string getName() const;
    
    /**
     * @brief Manually loads patterns from a file
     * @param filePath Path to patterns file
     */
    void loadPatterns(const std::string& filePath);
    
    /**
     * @brief Gets the number of loaded patterns
     * @return Pattern count
     */
    int getPatternCount() const;
    
    /**
     * @brief Initializes the global keyword list
     * 
     * Static method to initialize shared data.
     */
    static void initializeGlobalKeywords();
};

#endif // STRINGANALYZER_H