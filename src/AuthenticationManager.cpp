// AuthenticationManager.cpp
// TODO: Implement AuthenticationManager.cpp

/**
 * @file AuthenticationManager.cpp
 * @brief Implementation of AuthenticationManager class
 */

#include "../include/AuthenticationManager.h"
#include "../include/Exceptions.h"
#include "../include/Utility.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

// ==================== Constructor & Destructor ====================

AuthenticationManager::AuthenticationManager(Logger* log, const std::string& userFile)
    : currentUser(NULL), logger(log), usersLoaded(false), userFilePath(userFile) {
    
    std::cout << "[AuthenticationManager] Initializing..." << std::endl;
    
    try {
        loadUsersFromFile();
    } catch (const FileOpenException& e) {
        std::cerr << "[AuthenticationManager] Warning: " << e.what() << std::endl;
        std::cerr << "[AuthenticationManager] System will run with no users" << std::endl;
    }
}

AuthenticationManager::~AuthenticationManager() {
    if (currentUser != NULL) {
        logout();
    }
    std::cout << "[AuthenticationManager] Destroyed" << std::endl;
}

// ==================== Core Authentication Methods ====================

User& AuthenticationManager::login(const std::string& username, const std::string& password) {
    // Check if user exists
    if (users.find(username) == users.end()) {
        throw AuthenticationException("User not found: " + username);
    }
    
    // Get user reference
    User& user = users[username];
    
    // Authenticate
    if (!user.authenticate(password)) {
        if (logger) {
            logger->logError("Failed login attempt for user: " + username);
        }
        throw AuthenticationException("Invalid password for user: " + username);
    }
    
    // Set current session
    currentUser = &user;
    
    // Update login timestamp
    std::string timestamp = getCurrentTimestamp();
    currentUser->setLoginTimestamp(timestamp);
    
    // Log successful login
    if (logger) {
        logger->logLogin(username);
    }
    
    std::cout << "[AuthenticationManager] User logged in: " << username 
              << " (" << user.getRole() << ")" << std::endl;
    
    return *currentUser;
}

void AuthenticationManager::logout() {
    if (currentUser == NULL) {
        std::cout << "[AuthenticationManager] No user is currently logged in" << std::endl;
        return;
    }
    
    std::string username = currentUser->getUsername();
    
    // Log logout
    if (logger) {
        logger->logLogout(username);
    }
    
    std::cout << "[AuthenticationManager] User logged out: " << username << std::endl;
    
    currentUser = NULL;
}

// ==================== User Management ====================

bool AuthenticationManager::userExists(const std::string& username) const {
    return users.find(username) != users.end();
}

User* AuthenticationManager::getCurrentUser() const {
    return currentUser;
}

bool AuthenticationManager::isLoggedIn() const {
    return currentUser != NULL;
}

int AuthenticationManager::getUserCount() const {
    return static_cast<int>(users.size());
}

void AuthenticationManager::reloadUsers() {
    users.clear();
    usersLoaded = false;
    loadUsersFromFile();
}

// ==================== Private Helper Methods ====================

void AuthenticationManager::loadUsersFromFile() {
    std::ifstream file(userFilePath.c_str());
    
    if (!file.is_open()) {
        throw FileOpenException("Cannot open user database: " + userFilePath);
    }
    
    users.clear();
    std::string line;
    int lineNumber = 0;
    
    while (std::getline(file, line)) {
        lineNumber++;
        line = Utility::trim(line);
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Parse: username,password,role
        std::vector<std::string> parts = Utility::split(line, ',');
        
        if (parts.size() < 3) {
            std::cerr << "[AuthenticationManager] Warning: Invalid format at line " 
                      << lineNumber << std::endl;
            continue;
        }
        
        std::string username = Utility::trim(parts[0]);
        std::string password = Utility::trim(parts[1]);
        std::string role = Utility::trim(parts[2]);
        
        // Create and store user
        User user(username, password, role);
        users[username] = user;
    }
    
    file.close();
    usersLoaded = true;
    
    std::cout << "[AuthenticationManager] Loaded " << users.size() 
              << " users from " << userFilePath << std::endl;
}

std::string AuthenticationManager::getCurrentTimestamp() const {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    
    std::stringstream ss;
    ss << (1900 + timeinfo->tm_year) << "-"
       << std::setw(2) << std::setfill('0') << (1 + timeinfo->tm_mon) << "-"
       << std::setw(2) << std::setfill('0') << timeinfo->tm_mday << " "
       << std::setw(2) << std::setfill('0') << timeinfo->tm_hour << ":"
       << std::setw(2) << std::setfill('0') << timeinfo->tm_min << ":"
       << std::setw(2) << std::setfill('0') << timeinfo->tm_sec;
    
    return ss.str();
}