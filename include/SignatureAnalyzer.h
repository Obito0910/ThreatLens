// SignatureAnalyzer.h
// TODO: Implement SignatureAnalyzer.h

/**
 * @file SignatureAnalyzer.h
 * @brief Analyzer that matches file signatures against malware database
 * @details Uses static signature database shared across all instances
 * 
 * OOP Concepts Demonstrated:
 * - Inheritance (derives from Analyzer)
 * - Polymorphism (overrides virtual methods)
 * - Static members (shared signature database)
 * - File I/O (loading signature database)
 */

#ifndef SIGNATUREANALYZER_H
#define SIGNATUREANALYZER_H

#include "Analyzer.h"
#include <map>

/**
 * @class SignatureAnalyzer
 * @brief Matches file signatures against known malware patterns
 * 
 * This analyzer maintains a database of known malware signatures and
 * checks if the file's hash or content patterns match any known threats.
 * The signature database is static, meaning it's shared across all
 * SignatureAnalyzer instances (loaded once, used by all).
 * 
 * Signature matching is a common technique in antivirus software:
 * - Hash-based: Compare file hash with known malware hashes
 * - Pattern-based: Search for byte patterns characteristic of malware
 */
class SignatureAnalyzer : public Analyzer {
private:
    bool databaseLoaded;  ///< Flag indicating if database is loaded
    
    // Static signature database - SHARED ACROSS ALL INSTANCES
    static std::map<std::string, std::string> signatureDatabase;  ///< Hash -> Malware Name
    static bool staticDatabaseLoaded;  ///< Flag for static database initialization
    
    /**
     * @brief Loads signature database from file
     * @param filePath Path to signature database file
     * @throws FileOpenException if file cannot be opened
     * 
     * Private helper demonstrating encapsulation.
     */
    void loadDatabaseFromFile(const std::string& filePath);
    
    /**
     * @brief Checks if a hash matches any known signature
     * @param hash Hash string to check
     * @return true if signature match found
     */
    bool matchesKnownSignature(const std::string& hash) const;
    
    /**
     * @brief Gets malware name associated with a signature
     * @param hash Hash/signature to look up
     * @return Malware name or empty string if not found
     */
    std::string getMalwareName(const std::string& hash) const;
    
public:
    /**
     * @brief Default constructor
     */
    SignatureAnalyzer();
    
    /**
     * @brief Parameterized constructor
     * @param databaseFile Path to signature database file
     */
    explicit SignatureAnalyzer(const std::string& databaseFile);
    
    /**
     * @brief Destructor
     */
    virtual ~SignatureAnalyzer();
    
    /**
     * @brief Performs signature analysis on the file
     * @param file FileSample to analyze
     * @param result AnalysisResult to store findings
     * 
     * Overrides the pure virtual function from Analyzer.
     * Checks if file hash matches any known malware signatures.
     */
    virtual void analyze(FileSample& file, AnalysisResult& result);
    
    /**
     * @brief Gets the name of this analyzer
     * @return "Signature Analyzer"
     * 
     * Overrides the pure virtual function from Analyzer.
     */
    virtual std::string getName() const;
    
    /**
     * @brief Manually loads signature database
     * @param filePath Path to database file
     */
    void loadDatabase(const std::string& filePath);
    
    /**
     * @brief Gets the number of signatures in database
     * @return Signature count
     */
    int getSignatureCount() const;
    
    /**
     * @brief Adds a signature to the database
     * @param signature Hash/signature string
     * @param malwareName Name of the malware
     * 
     * Useful for dynamic updates to the signature database.
     */
    static void addSignature(const std::string& signature, const std::string& malwareName);
    
    /**
     * @brief Clears the entire signature database
     * 
     * Static method affecting all instances.
     */
    static void clearDatabase();
};

#endif // SIGNATUREANALYZER_H