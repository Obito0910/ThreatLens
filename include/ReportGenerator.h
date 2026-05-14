// ReportGenerator.h
// TODO: Implement ReportGenerator.h

/**
 * @file ReportGenerator.h
 * @brief Generates detailed analysis reports
 * @details Creates comprehensive text reports and saves them to file
 * 
 * OOP Concepts Demonstrated:
 * - Aggregation (uses AnalysisResult but doesn't own it)
 * - File I/O (writing reports)
 * - String manipulation
 */

#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "AnalysisResult.h"
#include "FileSample.h"
#include "User.h"
#include <string>

/**
 * @class ReportGenerator
 * @brief Generates and saves detailed analysis reports
 * 
 * The ReportGenerator creates comprehensive text reports containing:
 * - File information (name, size, hash, extension)
 * - Analysis results (risk score, verdict, findings)
 * - User information (analyst name, timestamp)
 * - Recommendations
 * 
 * Aggregation relationship: ReportGenerator ◇ AnalysisResult
 * The generator USES results but doesn't OWN them.
 */
class ReportGenerator {
private:
    std::string reportDirectory;    ///< Directory where reports are saved
    
    /**
     * @brief Generates the report content as a string
     * @param file FileSample that was analyzed
     * @param result Analysis result
     * @param user User who performed the analysis
     * @return Complete report content
     * 
     * Private helper for encapsulation.
     */
    std::string generateReportContent(const FileSample& file, 
                                     const AnalysisResult& result,
                                     const User& user) const;
    
    /**
     * @brief Generates a unique filename for the report
     * @param baseName Base name (usually the analyzed file name)
     * @return Unique filename with timestamp
     */
    std::string generateReportFilename(const std::string& baseName) const;
    
    /**
     * @brief Gets current timestamp
     * @return Timestamp string
     */
    std::string getCurrentTimestamp() const;
    
    /**
     * @brief Generates recommendations based on verdict
     * @param verdict Analysis verdict
     * @param riskScore Risk score
     * @return Recommendation text
     */
    std::string generateRecommendations(const std::string& verdict, int riskScore) const;
    
public:
    /**
     * @brief Constructor with report directory
     * @param directory Directory where reports will be saved (default: "reports/")
     */
    explicit ReportGenerator(const std::string& directory = "reports/");
    
    /**
     * @brief Destructor
     */
    ~ReportGenerator();
    
    /**
     * @brief Generates and saves a complete analysis report
     * @param file FileSample that was analyzed
     * @param result Analysis result (aggregation - doesn't take ownership)
     * @param user User who performed the analysis
     * @return Path to the generated report file
     * @throws FileOpenException if report cannot be written
     * 
     * This method demonstrates AGGREGATION:
     * - Takes AnalysisResult as parameter (uses it)
     * - Does NOT take ownership
     * - Does NOT delete the result
     */
    std::string generateReport(const FileSample& file, 
                              const AnalysisResult& result,
                              const User& user);
    
    /**
     * @brief Generates a quick summary report (shorter version)
     * @param result Analysis result
     * @return Summary report file path
     */
    std::string generateSummaryReport(const AnalysisResult& result);
    
    /**
     * @brief Gets the report directory path
     * @return Report directory
     */
    const std::string& getReportDirectory() const;
    
    /**
     * @brief Sets the report directory
     * @param directory New directory path
     */
    void setReportDirectory(const std::string& directory);
};

#endif // REPORTGENERATOR_H