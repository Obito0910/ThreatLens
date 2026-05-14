/**
 * @file User.h
 * @brief Represents a user/analyst in the malware analysis system
 * @details Stores user credentials, role, and analysis history
 * 
 * OOP Concepts Demonstrated:
 * - Encapsulation (private credentials)
 * - Composition (owns History object)
 * - Const correctness
 */

#ifndef USER_H
#define USER_H

#include <string>
#include "History.h"
#include "AnalysisResult.h"

/**
 * @class User
 * @brief Represents a user/analyst with credentials and history
 * 
 * The User class stores:
 * - Authentication credentials (username, password)
 * - Role/permissions (Analyst, Admin, etc.)
 * - Personal analysis history
 * - Login timestamp
 * 
 * Each user maintains their own analysis history separate from
 * the global system history.
 */
class User {
private:
    std::string username;                    ///< Username for authentication
    std::string password;                    ///< Password (stored as plaintext for simplicity)
    std::string role;                        ///< User role (Analyst, Admin, etc.)
    std::string loginTimestamp;              ///< Last login time
    int analysisCount;                       ///< Number of analyses performed
    History<AnalysisResult> analysisHistory; ///< Personal analysis history
    
public:
    /**
     * @brief Default constructor
     */
    User();
    
    /**
     * @brief Parameterized constructor
     * @param user Username
     * @param pass Password
     * @param r Role
     */
    User(const std::string& user, const std::string& pass, const std::string& r);
    
    /**
     * @brief Copy constructor
     * @param other User to copy from
     */
    User(const User& other);
    
    /**
     * @brief Assignment operator
     * @param other User to assign from
     * @return Reference to this user
     */
    User& operator=(const User& other);
    
    /**
     * @brief Destructor
     */
    ~User();
    
    /**
     * @brief Authenticates user with password
     * @param pass Password to check
     * @return true if password matches
     */
    bool authenticate(const std::string& pass) const;
    
    /**
     * @brief Adds an analysis result to user's history
     * @param result Analysis result to add
     */
    void addToHistory(const AnalysisResult& result);
    
    /**
     * @brief Sets the login timestamp
     * @param timestamp Timestamp string
     */
    void setLoginTimestamp(const std::string& timestamp);
    
    /**
     * @brief Increments the analysis count
     */
    void incrementAnalysisCount();
    
    /**
     * @brief Displays user information
     */
    void displayInfo() const;
    
    // ==================== Getters ====================
    
    /**
     * @brief Gets the username
     * @return Username
     */
    const std::string& getUsername() const;
    
    /**
     * @brief Gets the user role
     * @return Role
     */
    const std::string& getRole() const;
    
    /**
     * @brief Gets the login timestamp
     * @return Login timestamp
     */
    const std::string& getLoginTimestamp() const;
    
    /**
     * @brief Gets the analysis count
     * @return Number of analyses performed
     */
    int getAnalysisCount() const;
    
    /**
     * @brief Gets the analysis history
     * @return Const reference to history
     */
    const History<AnalysisResult>& getHistory() const;
    
    /**
     * @brief Gets the password (for authentication manager)
     * @return Password string
     * 
     * Note: In production, passwords should be hashed and never exposed.
     * This is simplified for educational purposes.
     */
    const std::string& getPassword() const;
};

#endif // USER_H