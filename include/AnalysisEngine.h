// AnalysisEngine.h
// TODO: Implement AnalysisEngine.h

/**
 * @file AnalysisEngine.h
 * @brief Core engine that orchestrates the malware analysis process
 * @details Manages all analyzers and coordinates the analysis workflow
 * 
 * OOP Concepts Demonstrated:
 * - Composition (owns Analyzer objects)
 * - Static members (statistics tracking)
 * - File I/O (timestamp generation)
 * - Exception handling
 */

#ifndef ANALYSISENGINE_H
#define ANALYSISENGINE_H

#include "Analyzer.h"
#include "FileSample.h"
#include "AnalysisResult.h"
#include "User.h"
#include "History.h"
#include <vector>
#include <string>

/**
 * @class AnalysisEngine
 * @brief Core engine that coordinates all analyzers and performs analysis
 * 
 * The AnalysisEngine is the heart of the malware analysis system.
 * It OWNS all analyzer objects (composition) and is responsible for:
 * - Managing the lifecycle of analyzers
 * - Running analysis in proper sequence
 * - Tracking global statistics
 * - Maintaining analysis history
 * 
 * Composition relationship: AnalysisEngine ⊕ Analyzer[]
 * When AnalysisEngine is destroyed, all owned analyzers are destroyed.
 */
class AnalysisEngine {
private:
    std::vector<Analyzer*> analyzers;           ///< Owned analyzer objects (composition)
    History<AnalysisResult> analysisHistory;    ///< History of all analyses performed
    
    // Static members - shared across all AnalysisEngine instances
    static int totalFilesAnalyzed;              ///< Total files analyzed globally
    static int totalThreatsDetected;            ///< Total threats detected globally
    
    /**
     * @brief Generates current timestamp string
     * @return Timestamp in format "YYYY-MM-DD HH:MM:SS"
     * 
     * Private helper method for timestamp generation.
     */
    std::string getCurrentTimestamp() const;
    
public:
    /**
     * @brief Default constructor
     */
    AnalysisEngine();
    
    /**
     * @brief Destructor - deletes all owned analyzers
     * 
     * CRITICAL: Demonstrates composition - the engine OWNS the analyzers.
     * When the engine is destroyed, all analyzers are automatically cleaned up.
     */
    ~AnalysisEngine();
    
    /**
     * @brief Adds an analyzer to the engine (transfers ownership)
     * @param analyzer Pointer to analyzer object
     * 
     * IMPORTANT: The engine takes ownership of the analyzer.
     * The caller should NOT delete the analyzer after adding it.
     * 
     * Example:
     * @code
     *   engine.addAnalyzer(new HashAnalyzer());  // Engine now owns it
     * @endcode
     */
    void addAnalyzer(Analyzer* analyzer);
    
    /**
     * @brief Runs complete analysis on a file
     * @param file FileSample to analyze
     * @param user User performing the analysis
     * @return AnalysisResult containing all findings
     * @throws InvalidFileException if file is not loaded
     * @throws AnalyzerException if analysis fails
     * 
     * This method:
     * 1. Extracts strings from the file
     * 2. Runs all registered analyzers sequentially
     * 3. Calculates final verdict
     * 4. Updates statistics
     * 5. Adds result to history
     */
    AnalysisResult runAnalysis(FileSample& file, User& user);
    
    /**
     * @brief Gets the number of registered analyzers
     * @return Analyzer count
     */
    int getAnalyzerCount() const;
    
    /**
     * @brief Gets analysis history
     * @return Const reference to history
     */
    const History<AnalysisResult>& getHistory() const;
    
    /**
     * @brief Clears all analysis history
     */
    void clearHistory();
    
    /**
     * @brief Removes all analyzers (with cleanup)
     * 
     * Deletes all owned analyzer objects and clears the vector.
     */
    void clearAnalyzers();
    
    // ==================== Static Methods ====================
    
    /**
     * @brief Gets total number of files analyzed globally
     * @return Total file count
     */
    static int getTotalFilesAnalyzed();
    
    /**
     * @brief Gets total number of threats detected globally
     * @return Total threat count
     */
    static int getTotalThreatsDetected();
    
    /**
     * @brief Prints global statistics
     * 
     * Displays cumulative statistics across all analysis sessions.
     */
    static void printStats();
    
    /**
     * @brief Resets all global statistics to zero
     * 
     * Useful for starting fresh or testing.
     */
    static void resetStats();
};

#endif // ANALYSISENGINE_H