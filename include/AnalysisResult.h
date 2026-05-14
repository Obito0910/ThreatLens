// AnalysisResult.h
// TODO: Implement AnalysisResult.h

/**
 * @file AnalysisResult.h
 * @brief Contains the results of a malware analysis
 * @details Stores findings, risk scores, verdicts, and metadata
 * 
 * OOP Concepts Demonstrated:
 * - Encapsulation
 * - Operator overloading (+=, >, <<)
 * - Friend functions
 * - Copy constructor and assignment operator
 * - Const correctness
 */

#ifndef ANALYSISRESULT_H
#define ANALYSISRESULT_H

#include <string>
#include <vector>
#include <iostream>

// Forward declaration for friend function
class ReportGenerator;

/**
 * @class AnalysisResult
 * @brief Stores the complete results of a malware analysis operation
 * 
 * This class accumulates findings from various analyzers, maintains
 * a risk score, and provides a final verdict about the file's safety.
 * It supports operator overloading for convenient usage patterns.
 */
class AnalysisResult {
private:
    int riskScore;                        ///< Risk score (0-100)
    std::vector<std::string> findings;    ///< List of suspicious findings
    std::string verdict;                  ///< Final verdict (Safe/Suspicious/Dangerous)
    std::string hashValue;                ///< Hash of the analyzed file
    std::string timestamp;                ///< Time when analysis was performed
    std::string analyzedFileName;         ///< Name of the file that was analyzed
    
public:
    /**
     * @brief Default constructor
     */
    AnalysisResult();
    
    /**
     * @brief Copy constructor (deep copy)
     * @param other AnalysisResult to copy from
     */
    AnalysisResult(const AnalysisResult& other);
    
    /**
     * @brief Assignment operator
     * @param other AnalysisResult to assign from
     * @return Reference to this object
     */
    AnalysisResult& operator=(const AnalysisResult& other);
    
    /**
     * @brief Destructor
     */
    ~AnalysisResult();
    
    // ==================== Core Methods ====================
    
    /**
     * @brief Adds a finding to the result
     * @param finding Description of the suspicious finding
     */
    void addFinding(const std::string& finding);
    
    /**
     * @brief Sets the risk score
     * @param score Risk score (0-100)
     * 
     * Score is automatically clamped between 0 and 100.
     */
    void setRiskScore(int score);
    
    /**
     * @brief Increments the risk score by a given amount
     * @param amount Amount to add (can be negative)
     */
    void addToRiskScore(int amount);
    
    /**
     * @brief Calculates and sets the verdict based on risk score
     * 
     * Verdicts:
     * - 0-20:   Safe
     * - 21-50:  Suspicious
     * - 51-100: Dangerous
     */
    void calculateVerdict();
    
    /**
     * @brief Sets the file hash value
     * @param hash Hash string (e.g., SHA-256)
     */
    void setHashValue(const std::string& hash);
    
    /**
     * @brief Sets the timestamp of analysis
     * @param time Timestamp string
     */
    void setTimestamp(const std::string& time);
    
    /**
     * @brief Sets the name of the analyzed file
     * @param name File name
     */
    void setAnalyzedFileName(const std::string& name);
    
    /**
     * @brief Prints a summary of the analysis to console
     */
    void printSummary() const;
    
    /**
     * @brief Clears all data (resets to default state)
     */
    void clear();
    
    // ==================== Getters ====================
    
    /**
     * @brief Gets the risk score
     * @return Risk score (0-100)
     */
    int getRiskScore() const;
    
    /**
     * @brief Gets the verdict
     * @return Verdict string
     */
    const std::string& getVerdict() const;
    
    /**
     * @brief Gets all findings
     * @return Vector of finding strings
     */
    const std::vector<std::string>& getFindings() const;
    
    /**
     * @brief Gets the hash value
     * @return Hash string
     */
    const std::string& getHashValue() const;
    
    /**
     * @brief Gets the timestamp
     * @return Timestamp string
     */
    const std::string& getTimestamp() const;
    
    /**
     * @brief Gets the analyzed file name
     * @return File name
     */
    const std::string& getAnalyzedFileName() const;
    
    /**
     * @brief Gets the number of findings
     * @return Count of findings
     */
    int getFindingsCount() const;
    
    // ==================== Operator Overloading ====================
    
    /**
     * @brief Addition assignment operator for adding findings
     * @param finding Finding string to add
     * @return Reference to this object
     * 
     * Usage: result += "Suspicious string found: malware.exe";
     */
    AnalysisResult& operator+=(const std::string& finding);
    
    /**
     * @brief Greater than operator for comparing risk scores
     * @param other AnalysisResult to compare with
     * @return true if this result has higher risk score
     * 
     * Allows sorting results by risk level.
     */
    bool operator>(const AnalysisResult& other) const;
    
    /**
     * @brief Less than operator for comparing risk scores
     * @param other AnalysisResult to compare with
     * @return true if this result has lower risk score
     */
    bool operator<(const AnalysisResult& other) const;
    
    /**
     * @brief Equality operator
     * @param other AnalysisResult to compare with
     * @return true if risk scores are equal
     */
    bool operator==(const AnalysisResult& other) const;
    
    // ==================== Friend Functions ====================
    
    /**
     * @brief Stream insertion operator (friend function)
     * @param os Output stream
     * @param result AnalysisResult to output
     * @return Reference to the output stream
     * 
     * Allows: cout << result;
     * Friend function can access private members for formatting.
     */
    friend std::ostream& operator<<(std::ostream& os, const AnalysisResult& result);
};

#endif // ANALYSISRESULT_H