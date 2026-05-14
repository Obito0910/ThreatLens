// MetadataAnalyzer.h
// TODO: Implement MetadataAnalyzer.h

/**
 * @file MetadataAnalyzer.h
 * @brief Analyzer that examines file metadata for suspicious characteristics
 * @details Checks file extension, size, and other metadata properties
 * 
 * OOP Concepts Demonstrated:
 * - Inheritance (derives from Analyzer)
 * - Polymorphism (overrides virtual methods)
 * - File I/O (loading extension blacklist)
 */

#ifndef METADATAANALYZER_H
#define METADATAANALYZER_H

#include "Analyzer.h"
#include <vector>

/**
 * @class MetadataAnalyzer
 * @brief Analyzes file metadata for suspicious characteristics
 * 
 * This analyzer examines file properties without reading content:
 * - File extension (executable, script, archive)
 * - File size (abnormally large/small)
 * - Filename patterns (suspicious names)
 * 
 * Metadata analysis is fast and can catch many threats before
 * deep content analysis is needed.
 */
class MetadataAnalyzer : public Analyzer {
private:
    std::vector<std::string> dangerousExtensions;  ///< List of high-risk extensions
    bool extensionsLoaded;                         ///< Flag indicating if extensions are loaded
    
    // Thresholds for size-based risk
    static const long SUSPICIOUS_SIZE_THRESHOLD;   ///< Very large file threshold
    static const long TINY_SIZE_THRESHOLD;         ///< Suspiciously small executable threshold
    
    /**
     * @brief Loads dangerous extensions from file
     * @param filePath Path to extensions file
     * @throws FileOpenException if file cannot be opened
     */
    void loadExtensionsFromFile(const std::string& filePath);
    
    /**
     * @brief Checks if an extension is dangerous
     * @param extension File extension (e.g., ".exe")
     * @return true if extension is in blacklist
     */
    bool isDangerousExtension(const std::string& extension) const;
    
    /**
     * @brief Checks if file size is suspicious
     * @param size File size in bytes
     * @param extension File extension
     * @return true if size is suspicious for this file type
     */
    bool isSuspiciousSize(long size, const std::string& extension) const;
    
    /**
     * @brief Checks if filename itself is suspicious
     * @param fileName Name of the file
     * @return true if filename pattern is suspicious
     */
    bool isSuspiciousFileName(const std::string& fileName) const;
    
public:
    /**
     * @brief Default constructor
     */
    MetadataAnalyzer();
    
    /**
     * @brief Parameterized constructor
     * @param extensionsFile Path to dangerous extensions file
     */
    explicit MetadataAnalyzer(const std::string& extensionsFile);
    
    /**
     * @brief Destructor
     */
    virtual ~MetadataAnalyzer();
    
    /**
     * @brief Performs metadata analysis on the file
     * @param file FileSample to analyze
     * @param result AnalysisResult to store findings
     * 
     * Overrides the pure virtual function from Analyzer.
     * Examines file metadata for suspicious characteristics.
     */
    virtual void analyze(FileSample& file, AnalysisResult& result);
    
    /**
     * @brief Gets the name of this analyzer
     * @return "Metadata Analyzer"
     * 
     * Overrides the pure virtual function from Analyzer.
     */
    virtual std::string getName() const;
    
    /**
     * @brief Manually loads dangerous extensions
     * @param filePath Path to extensions file
     */
    void loadExtensions(const std::string& filePath);
    
    /**
     * @brief Gets the number of loaded dangerous extensions
     * @return Extension count
     */
    int getExtensionCount() const;
};

#endif // METADATAANALYZER_H