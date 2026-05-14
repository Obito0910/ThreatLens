/**
 * @file User.cpp
 * @brief Implementation of User class
 */

#include "../include/User.h"
#include <iostream>

// ==================== Constructors & Destructor ====================

User::User() 
    : username("guest"), password(""), role("Guest"), 
      loginTimestamp(""), analysisCount(0), analysisHistory(50) {
    // Default guest user
}

User::User(const std::string& user, const std::string& pass, const std::string& r)
    : username(user), password(pass), role(r), 
      loginTimestamp(""), analysisCount(0), analysisHistory(50) {
    // Parameterized constructor with 50 history entries max
}

User::User(const User& other)
    : username(other.username), password(other.password), role(other.role),
      loginTimestamp(other.loginTimestamp), analysisCount(other.analysisCount),
      analysisHistory(other.analysisHistory) {
    // Deep copy constructor
}

User& User::operator=(const User& other) {
    if (this != &other) {
        username = other.username;
        password = other.password;
        role = other.role;
        loginTimestamp = other.loginTimestamp;
        analysisCount = other.analysisCount;
        analysisHistory = other.analysisHistory;
    }
    return *this;
}

User::~User() {
    // Destructor
}

// ==================== Core Methods ====================

bool User::authenticate(const std::string& pass) const {
    return password == pass;
}

void User::addToHistory(const AnalysisResult& result) {
    analysisHistory.add(result);
    analysisCount++;
}

void User::setLoginTimestamp(const std::string& timestamp) {
    loginTimestamp = timestamp;
}

void User::incrementAnalysisCount() {
    analysisCount++;
}

void User::displayInfo() const {
    std::cout << "\n========== User Information ==========\n";
    std::cout << "Username:       " << username << "\n";
    std::cout << "Role:           " << role << "\n";
    std::cout << "Last Login:     " << (loginTimestamp.empty() ? "Never" : loginTimestamp) << "\n";
    std::cout << "Analyses Done:  " << analysisCount << "\n";
    std::cout << "History Size:   " << analysisHistory.size() << " / " 
              << analysisHistory.getMaxSize() << "\n";
    std::cout << "======================================\n\n";
}

// ==================== Getters ====================

const std::string& User::getUsername() const {
    return username;
}

const std::string& User::getRole() const {
    return role;
}

const std::string& User::getLoginTimestamp() const {
    return loginTimestamp;
}

int User::getAnalysisCount() const {
    return analysisCount;
}

const History<AnalysisResult>& User::getHistory() const {
    return analysisHistory;
}

const std::string& User::getPassword() const {
    return password;
}