// Utility.h
// TODO: Implement Utility.h

/**
 * @file Utility.h
 * @brief Template utility functions and helper methods
 * @details Provides generic utility functions demonstrating template usage
 * 
 * OOP Concepts Demonstrated:
 * - Templates (generic programming)
 * - Function templates
 * - Inline functions
 */

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

/**
 * @namespace Utility
 * @brief Contains utility functions for common operations
 */
namespace Utility {

    /**
     * @brief Clamps a value between a minimum and maximum
     * @tparam T Type of the value (must support < operator)
     * @param value The value to clamp
     * @param minVal Minimum allowed value
     * @param maxVal Maximum allowed value
     * @return Clamped value between minVal and maxVal
     * 
     * Template demonstrates generic programming - works with any comparable type
     */
    template <typename T>
    T clamp(T value, T minVal, T maxVal) {
        if (value < minVal) return minVal;
        if (value > maxVal) return maxVal;
        return value;
    }

    /**
     * @brief Converts a string to uppercase
     * @param str String to convert
     * @return Uppercase version of the string
     */
    inline std::string toUpperCase(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }

    /**
     * @brief Converts a string to lowercase
     * @param str String to convert
     * @return Lowercase version of the string
     */
    inline std::string toLowerCase(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    /**
     * @brief Trims whitespace from both ends of a string
     * @param str String to trim
     * @return Trimmed string
     */
    inline std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }

    /**
     * @brief Checks if a string contains a substring (case-insensitive)
     * @param str String to search in
     * @param substr Substring to search for
     * @return true if substring is found, false otherwise
     */
    inline bool containsIgnoreCase(const std::string& str, const std::string& substr) {
        std::string strLower = toLowerCase(str);
        std::string substrLower = toLowerCase(substr);
        return strLower.find(substrLower) != std::string::npos;
    }

    /**
     * @brief Splits a string by a delimiter
     * @param str String to split
     * @param delimiter Character to split by
     * @return Vector of substrings
     */
    inline std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        
        while (std::getline(ss, token, delimiter)) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
        
        return tokens;
    }

    /**
     * @brief Converts an integer to string
     * @param value Integer value
     * @return String representation
     */
    inline std::string toString(int value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    /**
     * @brief Extracts file extension from a file path
     * @param filePath Full file path
     * @return File extension (including the dot, e.g., ".exe")
     */
    inline std::string getFileExtension(const std::string& filePath) {
        size_t dotPos = filePath.find_last_of('.');
        if (dotPos != std::string::npos && dotPos < filePath.length() - 1) {
            return toLowerCase(filePath.substr(dotPos));
        }
        return "";
    }

    /**
     * @brief Extracts filename from a full file path
     * @param filePath Full file path
     * @return Filename without path
     */
    inline std::string getFileName(const std::string& filePath) {
        size_t slashPos = filePath.find_last_of("/\\");
        if (slashPos != std::string::npos && slashPos < filePath.length() - 1) {
            return filePath.substr(slashPos + 1);
        }
        return filePath;
    }

} // namespace Utility

#endif // UTILITY_H