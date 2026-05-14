// Analyzer.h
// TODO: Implement Analyzer.h

/**
 * @file Analyzer.h
 * @brief Abstract base class for all file analyzers
 * @details Defines the interface that all concrete analyzers must implement
 * 
 * OOP Concepts Demonstrated:
 * - Abstraction (pure virtual functions)
 * - Polymorphism (virtual methods)
 * - Inheritance (base class for analyzer hierarchy)
 * - Static members (shared data)
 */

#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>
#include <vector>
#include "FileSample.h"
#include "AnalysisResult.h"

/**
 * @class Analyzer
 * @brief Abstract base class for all file analyzers
 * 
 * This class defines the interface that all concrete analyzers must implement.
 * It cannot be instantiated directly - only derived classes can be created.
 * This demonstrates the Open-Closed Principle: open for extension (new analyzers),
 * closed for modification (base interface remains stable).
 * 
 * Usage Example:
 * @code
 *   Analyzer* analyzer = new HashAnalyzer();  // Polymorphism
 *   analyzer->analyze(file, result);
 *   delete analyzer;
 * @endcode
 */
class Analyzer {
protected:
    std::string analyzerName;  ///< Name of this analyzer
    
    /**
     * @brief Protected constructor (prevents direct instantiation)
     * @param name Name of the analyzer
     */
    explicit Analyzer(const std::string& name);
    
    // Static members shared across all analyzer instances
    static const int MAX_RISK_CONTRIBUTION;  ///< Maximum risk an analyzer can add
    
public:
    /**
     * @brief Pure virtual function to perform analysis
     * @param file FileSample object containing the file to analyze
     * @param result AnalysisResult object to store findings
     * 
     * This is a pure virtual function (= 0), making Analyzer abstract.
     * All derived classes MUST implement this method.
     * Demonstrates runtime polymorphism - the actual method called
     * depends on the object type at runtime.
     */
    virtual void analyze(FileSample& file, AnalysisResult& result) = 0;
    
    /**
     * @brief Pure virtual function to get analyzer name
     * @return Name of the analyzer
     * 
     * Each analyzer must identify itself. This is useful for logging
     * and reporting which analyzers contributed to findings.
     */
    virtual std::string getName() const = 0;
    
    /**
     * @brief Virtual destructor for proper cleanup
     * 
     * CRITICAL: Base classes with virtual functions MUST have virtual destructors.
     * This ensures derived class destructors are called when deleting through
     * a base class pointer, preventing memory leaks.
     */
    virtual ~Analyzer();
    
    /**
     * @brief Gets the analyzer's name (non-virtual accessor)
     * @return Analyzer name
     */
    const std::string& getAnalyzerName() const;
};

#endif // ANALYZER_H