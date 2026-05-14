// HashAnalyzer.h
// TODO: Implement HashAnalyzer.h

/**
 * @file HashAnalyzer.h
 * @brief Analyzer that computes file hashes/checksums
 * @details Generates a simple checksum for file identification and integrity checking
 * 
 * OOP Concepts Demonstrated:
 * - Inheritance (derives from Analyzer)
 * - Polymorphism (overrides virtual methods)
 * - Encapsulation (private helper methods)
 */

#ifndef HASHANALYZER_H
#define HASHANALYZER_H

#include "Analyzer.h"

/**
 * @class HashAnalyzer
 * @brief Computes a checksum/hash for file identification
 * 
 * This analyzer generates a simple checksum of the file contents.
 * In a real implementation, this would use SHA-256 or MD5, but for
 * educational purposes we use a simple checksum algorithm.
 * 
 * Hash values are useful for:
 * - File identification
 * - Duplicate detection
 * - Integrity verification
 * - Signature database matching
 */
class HashAnalyzer : public Analyzer {
private:
    std::string hashAlgorithm;  ///< Name of hash algorithm (e.g., "SimpleChecksum")
    
    /**
     * @brief Computes a simple checksum of file contents
     * @param filePath Path to the file
     * @return Hexadecimal checksum string
     * @throws FileOpenException if file cannot be read
     * 
     * This is a private helper method demonstrating encapsulation.
     * External code cannot call this directly - they must use analyze().
     */
    std::string computeChecksum(const std::string& filePath) const;
    
    /**
     * @brief Converts an integer to hexadecimal string
     * @param value Integer value
     * @return Hexadecimal string representation
     */
    std::string toHex(unsigned int value) const;
    
public:
    /**
     * @brief Default constructor
     */
    HashAnalyzer();
    
    /**
     * @brief Parameterized constructor
     * @param algorithm Name of the hash algorithm to use
     */
    explicit HashAnalyzer(const std::string& algorithm);
    
    /**
     * @brief Destructor
     */
    virtual ~HashAnalyzer();
    
    /**
     * @brief Performs hash analysis on the file
     * @param file FileSample to analyze
     * @param result AnalysisResult to store findings
     * 
     * Overrides the pure virtual function from Analyzer.
     * Computes file hash and stores it in the result.
     */
    virtual void analyze(FileSample& file, AnalysisResult& result);
    
    /**
     * @brief Gets the name of this analyzer
     * @return "Hash Analyzer"
     * 
     * Overrides the pure virtual function from Analyzer.
     */
    virtual std::string getName() const;
    
    /**
     * @brief Gets the hash algorithm name
     * @return Algorithm name
     */
    const std::string& getHashAlgorithm() const;
};

#endif // HASHANALYZER_H