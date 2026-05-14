// FileSample.h
// TODO: Implement FileSample.h

/**
 * @file FileSample.h
 * @brief Represents a file sample for malware analysis
 * @details Encapsulates file information, metadata, and extracted strings
 * 
 * OOP Concepts Demonstrated:
 * - Encapsulation (private data members)
 * - Constructors (default, parameterized, copy)
 * - Static members (counters)
 * - Operator overloading (==)
 * - Const correctness
 */

#ifndef FILESAMPLE_H
#define FILESAMPLE_H

#include <string>
#include <vector>

/**
 * @class FileSample
 * @brief Represents a file being analyzed by the malware detection system
 * 
 * This class encapsulates all information about a file sample including
 * its path, metadata, and extracted content. It provides methods for
 * loading files, extracting strings, and accessing file properties.
 */
class FileSample {
private:
    std::string filePath;                    ///< Full path to the file
    std::string fileName;                    ///< Name of the file without path
    std::string extension;                   ///< File extension (e.g., ".exe")
    long fileSize;                           ///< Size of file in bytes
    std::vector<std::string> extractedStrings;  ///< Strings extracted from file
    bool isLoaded;                           ///< Flag indicating if file was successfully loaded
    
    // Static members for tracking statistics
    static int totalFilesAnalyzed;           ///< Total number of files analyzed
    static long totalBytesProcessed;         ///< Total bytes processed across all files
    
public:
    /**
     * @brief Default constructor
     */
    FileSample();
    
    /**
     * @brief Parameterized constructor
     * @param path Path to the file
     */
    explicit FileSample(const std::string& path);
    
    /**
     * @brief Copy constructor (deep copy)
     * @param other FileSample object to copy from
     */
    FileSample(const FileSample& other);
    
    /**
     * @brief Assignment operator
     * @param other FileSample object to assign from
     * @return Reference to this object
     */
    FileSample& operator=(const FileSample& other);
    
    /**
     * @brief Destructor
     */
    ~FileSample();
    
    /**
     * @brief Loads the file and extracts metadata
     * @throws FileOpenException if file cannot be opened
     * @throws InvalidFileException if file is invalid or corrupted
     * 
     * This method opens the file, reads its size, extracts the filename
     * and extension, and prepares it for analysis.
     */
    void load();
    
    /**
     * @brief Extracts printable strings from the file
     * @param minLength Minimum length of strings to extract (default: 4)
     * @throws FileOpenException if file cannot be read
     * 
     * Searches for sequences of printable ASCII characters in the file
     * content and stores them for analysis by StringAnalyzer.
     */
    void extractStrings(int minLength = 4);
    
    /**
     * @brief Displays file information to console
     */
    void displayInfo() const;
    
    // ==================== Getters ====================
    
    /**
     * @brief Gets the full file path
     * @return File path as const reference
     */
    const std::string& getFilePath() const;
    
    /**
     * @brief Gets the file name without path
     * @return File name
     */
    const std::string& getFileName() const;
    
    /**
     * @brief Gets the file extension
     * @return File extension (e.g., ".txt")
     */
    const std::string& getExtension() const;
    
    /**
     * @brief Gets the file size in bytes
     * @return File size
     */
    long getFileSize() const;
    
    /**
     * @brief Gets extracted strings from the file
     * @return Vector of extracted strings
     */
    const std::vector<std::string>& getExtractedStrings() const;
    
    /**
     * @brief Checks if file was successfully loaded
     * @return true if loaded, false otherwise
     */
    bool getIsLoaded() const;
    
    // ==================== Setters ====================
    
    /**
     * @brief Sets the file path
     * @param path New file path
     */
    void setFilePath(const std::string& path);
    
    // ==================== Static Methods ====================
    
    /**
     * @brief Gets total number of files analyzed across all instances
     * @return Total file count
     */
    static int getTotalFilesAnalyzed();
    
    /**
     * @brief Gets total bytes processed across all instances
     * @return Total bytes processed
     */
    static long getTotalBytesProcessed();
    
    /**
     * @brief Increments the analyzed file counter
     * 
     * Called internally when a file is successfully loaded and analyzed.
     */
    static void incrementAnalyzedCount();
    
    /**
     * @brief Resets all static counters to zero
     * 
     * Useful for testing or starting fresh analysis sessions.
     */
    static void resetCounters();
    
    // ==================== Operator Overloading ====================
    
    /**
     * @brief Equality operator
     * @param other FileSample to compare with
     * @return true if both represent the same file path
     */
    bool operator==(const FileSample& other) const;
    
    /**
     * @brief Inequality operator
     * @param other FileSample to compare with
     * @return true if files are different
     */
    bool operator!=(const FileSample& other) const;
};

#endif // FILESAMPLE_H