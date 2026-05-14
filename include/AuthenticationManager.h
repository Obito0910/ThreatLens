// AuthenticationManager.h
// TODO: Implement AuthenticationManager.h

/**
 * @file AuthenticationManager.h
 * @brief Manages user authentication and credentials
 * @details Loads user database and handles login/logout
 * 
 * OOP Concepts Demonstrated:
 * - File I/O (loading user database)
 * - Exception handling (authentication failures)
 * - Encapsulation (private user storage)
 */

#ifndef AUTHENTICATIONMANAGER_H
#define AUTHENTICATIONMANAGER_H

#include "User.h"
#include "Logger.h"
#include <string>
#include <map>

/**
 * @class AuthenticationManager
 * @brief Manages user authentication and session management
 * 
 * The AuthenticationManager is responsible for:
 * - Loading user credentials from file
 * - Authenticating users
 * - Managing current session
 * - Logging authentication events
 * 
 * User credentials are stored in data/users.txt with format:
 * username,password,role
 */
class AuthenticationManager {
private:
    std::map<std::string, User> users;  ///< User database (username -> User)
    User* currentUser;                  ///< Pointer to currently logged in user
    Logger* logger;                     ///< Logger for authentication events
    bool usersLoaded;                   ///< Flag indicating if users are loaded
    std::string userFilePath;           ///< Path to user credentials file
    
    /**
     * @brief Loads user credentials from file
     * @throws FileOpenException if file cannot be opened
     * 
     * Private helper for encapsulation.
     */
    void loadUsersFromFile();
    
    /**
     * @brief Generates current timestamp
     * @return Timestamp string
     */
    std::string getCurrentTimestamp() const;
    
public:
    /**
     * @brief Constructor with logger and user file path
     * @param log Logger instance for authentication events
     * @param userFile Path to user credentials file (default: "data/users.txt")
     */
    explicit AuthenticationManager(Logger* log, const std::string& userFile = "data/users.txt");
    
    /**
     * @brief Destructor
     */
    ~AuthenticationManager();
    
    /**
     * @brief Authenticates a user and creates session
     * @param username Username
     * @param password Password
     * @return Reference to authenticated User object
     * @throws AuthenticationException if authentication fails
     * 
     * If authentication succeeds:
     * - Sets currentUser
     * - Updates login timestamp
     * - Logs the login event
     */
    User& login(const std::string& username, const std::string& password);
    
    /**
     * @brief Logs out the current user
     * 
     * Clears the current session and logs the logout event.
     */
    void logout();
    
    /**
     * @brief Checks if a user exists in the system
     * @param username Username to check
     * @return true if user exists
     */
    bool userExists(const std::string& username) const;
    
    /**
     * @brief Gets the currently logged in user
     * @return Pointer to current user (NULL if not logged in)
     */
    User* getCurrentUser() const;
    
    /**
     * @brief Checks if a user is currently logged in
     * @return true if someone is logged in
     */
    bool isLoggedIn() const;
    
    /**
     * @brief Gets the number of registered users
     * @return User count
     */
    int getUserCount() const;
    
    /**
     * @brief Reloads user database from file
     * 
     * Useful if users.txt is modified while program is running.
     */
    void reloadUsers();
};

#endif // AUTHENTICATIONMANAGER_H