// History.h
// TODO: Implement History.h

/**
 * @file History.h
 * @brief Template class for storing history of analysis results
 * @details Generic container that can store history of any type
 * 
 * OOP Concepts Demonstrated:
 * - Templates (generic class)
 * - Encapsulation
 * - STL integration (vector)
 * - Const correctness
 */

#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <stdexcept>

/**
 * @class History
 * @brief Template class for maintaining a history of records
 * @tparam T Type of records to store (e.g., AnalysisResult)
 * 
 * This template demonstrates generic programming by allowing storage
 * of any type while maintaining type safety. Commonly used to store
 * analysis results for each user.
 * 
 * Usage Example:
 * @code
 *   History<AnalysisResult> userHistory(50);
 *   userHistory.add(result);
 *   AnalysisResult latest = userHistory.get(0);
 * @endcode
 */
template <typename T>
class History {
private:
    std::vector<T> records;  ///< Container storing the history records
    int maxSize;             ///< Maximum number of records to keep
    
public:
    /**
     * @brief Constructs a History object with a maximum size
     * @param max Maximum number of records to maintain (default: 100)
     * @throws std::invalid_argument if max is less than 1
     */
    explicit History(int max = 100) : maxSize(max) {
        if (max < 1) {
            throw std::invalid_argument("History max size must be at least 1");
        }
        records.reserve(max);  // Pre-allocate for efficiency
    }
    
    /**
     * @brief Copy constructor
     * @param other History object to copy from
     */
    History(const History<T>& other) 
        : records(other.records), maxSize(other.maxSize) {
        // Deep copy of vector handled automatically by std::vector
    }
    
    /**
     * @brief Assignment operator
     * @param other History object to assign from
     * @return Reference to this object
     */
    History<T>& operator=(const History<T>& other) {
        if (this != &other) {
            records = other.records;
            maxSize = other.maxSize;
        }
        return *this;
    }
    
    /**
     * @brief Adds a new record to the history
     * @param record Record to add
     * 
     * If the history is full (size >= maxSize), the oldest record
     * is removed before adding the new one (FIFO behavior).
     */
    void add(const T& record) {
        // If at capacity, remove oldest record
        if (static_cast<int>(records.size()) >= maxSize) {
            records.erase(records.begin());
        }
        records.push_back(record);
    }
    
    /**
     * @brief Retrieves a record at a specific index
     * @param index Index of the record (0 = most recent)
     * @return Const reference to the record
     * @throws std::out_of_range if index is invalid
     * 
     * Index 0 returns the most recent record, 1 the second most recent, etc.
     */
    const T& get(int index) const {
        if (index < 0 || index >= static_cast<int>(records.size())) {
            throw std::out_of_range("History index out of range");
        }
        // Return in reverse order (most recent first)
        return records[records.size() - 1 - index];
    }
    
    /**
     * @brief Retrieves all records
     * @return Const reference to the vector of all records
     */
    const std::vector<T>& getAll() const {
        return records;
    }
    
    /**
     * @brief Returns the number of records currently stored
     * @return Number of records
     */
    int size() const {
        return static_cast<int>(records.size());
    }
    
    /**
     * @brief Checks if the history is empty
     * @return true if no records exist, false otherwise
     */
    bool isEmpty() const {
        return records.empty();
    }
    
    /**
     * @brief Clears all records from the history
     */
    void clear() {
        records.clear();
    }
    
    /**
     * @brief Returns the maximum capacity
     * @return Maximum number of records that can be stored
     */
    int getMaxSize() const {
        return maxSize;
    }
    
    /**
     * @brief Sets a new maximum size
     * @param newMax New maximum size
     * @throws std::invalid_argument if newMax is less than 1
     * 
     * If the new size is smaller than current number of records,
     * oldest records are removed to fit the new limit.
     */
    void setMaxSize(int newMax) {
        if (newMax < 1) {
            throw std::invalid_argument("History max size must be at least 1");
        }
        
        maxSize = newMax;
        
        // Remove oldest records if necessary
        while (static_cast<int>(records.size()) > maxSize) {
            records.erase(records.begin());
        }
    }
};

#endif // HISTORY_H