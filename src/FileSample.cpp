// FileSample.cpp
// TODO: Implement FileSample.cpp

/**
 * @file FileSample.cpp
 * @brief Implementation of FileSample class
 */

#include "../include/FileSample.h"
#include "../include/Exceptions.h"
#include "../include/Utility.h"
#include <fstream>
#include <iostream>
#include <cstring>

// Initialize static members
int FileSample::totalFilesAnalyzed = 0;
long FileSample::totalBytesProcessed = 0;

// ==================== Constructors & Destructor ====================

FileSample::FileSample() 
    : filePath(""), fileName(""), extension(""), fileSize(0), isLoaded(false) {
    // Default constructor initializes all members to default values
}

FileSample::FileSample(const std::string& path) 
    : filePath(path), fileName(""), extension(""), fileSize(0), isLoaded(false) {
    // Constructor with path - file not loaded until load() is called
    fileName = Utility::getFileName(path);
    extension = Utility::getFileExtension(path);
}

FileSample::FileSample(const FileSample& other) 
    : filePath(other.filePath), 
      fileName(other.fileName),
      extension(other.extension),
      fileSize(other.fileSize),
      extractedStrings(other.extractedStrings),
      isLoaded(other.isLoaded) {
    // Deep copy constructor - vector handles deep copy automatically
}

FileSample& FileSample::operator=(const FileSample& other) {
    if (this != &other) {  // Self-assignment check
        filePath = other.filePath;
        fileName = other.fileName;
        extension = other.extension;
        fileSize = other.fileSize;
        extractedStrings = other.extractedStrings;
        isLoaded = other.isLoaded;
    }
    return *this;
}

FileSample::~FileSample() {
    // Destructor - no dynamic memory to clean up (vector handles itself)
}

// ==================== Core Methods ====================

void FileSample::load() {
    // Check if file exists and can be opened
    std::ifstream file(filePath.c_str(), std::ios::binary | std::ios::ate);
    
    if (!file.is_open()) {
        throw FileOpenException("Cannot open file: " + filePath);
    }
    
    // Get file size (ate flag puts cursor at end)
    fileSize = static_cast<long>(file.tellg());
    file.seekg(0, std::ios::beg);  // Reset to beginning
    
    if (fileSize < 0) {
        file.close();
        throw InvalidFileException("Cannot determine file size: " + filePath);
    }
    
    // Validate file size (reject files > 500MB for safety)
    const long MAX_FILE_SIZE = 500L * 1024L * 1024L;  // 500 MB
    if (fileSize > MAX_FILE_SIZE) {
        file.close();
        throw InvalidFileException("File too large (max 500MB): " + filePath);
    }
    
    file.close();
    
    // Extract filename and extension if not already set
    if (fileName.empty()) {
        fileName = Utility::getFileName(filePath);
    }
    if (extension.empty()) {
        extension = Utility::getFileExtension(filePath);
    }
    
    isLoaded = true;
    
    // Update static counters
    incrementAnalyzedCount();
    totalBytesProcessed += fileSize;
    
    std::cout << "[FileSample] Loaded: " << fileName 
              << " (" << fileSize << " bytes)" << std::endl;
}

void FileSample::extractStrings(int minLength) {
    if (!isLoaded) {
        throw InvalidFileException("File must be loaded before extracting strings");
    }
    
    extractedStrings.clear();  // Clear any previous strings
    
    std::ifstream file(filePath.c_str(), std::ios::binary);
    if (!file.is_open()) {
        throw FileOpenException("Cannot open file for string extraction: " + filePath);
    }
    
    std::string currentString;
    char ch;
    
    // Read file byte by byte
    while (file.get(ch)) {
        // Check if character is printable ASCII
        if (ch >= 32 && ch <= 126) {
            currentString += ch;
        } else {
            // Non-printable character - end of string
            if (static_cast<int>(currentString.length()) >= minLength) {
                extractedStrings.push_back(currentString);
            }
            currentString.clear();
        }
    }
    
    // Don't forget the last string if file ends with printable chars
    if (static_cast<int>(currentString.length()) >= minLength) {
        extractedStrings.push_back(currentString);
    }
    
    file.close();
    
    std::cout << "[FileSample] Extracted " << extractedStrings.size() 
              << " strings (min length: " << minLength << ")" << std::endl;
}

void FileSample::displayInfo() const {
    std::cout << "\n========== File Information ==========\n";
    std::cout << "File Name:  " << fileName << "\n";
    std::cout << "File Path:  " << filePath << "\n";
    std::cout << "Extension:  " << extension << "\n";
    std::cout << "File Size:  " << fileSize << " bytes\n";
    std::cout << "Loaded:     " << (isLoaded ? "Yes" : "No") << "\n";
    std::cout << "Strings:    " << extractedStrings.size() << " extracted\n";
    std::cout << "======================================\n\n";
}

// ==================== Getters ====================

const std::string& FileSample::getFilePath() const {
    return filePath;
}

const std::string& FileSample::getFileName() const {
    return fileName;
}

const std::string& FileSample::getExtension() const {
    return extension;
}

long FileSample::getFileSize() const {
    return fileSize;
}

const std::vector<std::string>& FileSample::getExtractedStrings() const {
    return extractedStrings;
}

bool FileSample::getIsLoaded() const {
    return isLoaded;
}

// ==================== Setters ====================

void FileSample::setFilePath(const std::string& path) {
    filePath = path;
    fileName = Utility::getFileName(path);
    extension = Utility::getFileExtension(path);
    isLoaded = false;  // Reset loaded status when path changes
    extractedStrings.clear();
}

// ==================== Static Methods ====================

int FileSample::getTotalFilesAnalyzed() {
    return totalFilesAnalyzed;
}

long FileSample::getTotalBytesProcessed() {
    return totalBytesProcessed;
}

void FileSample::incrementAnalyzedCount() {
    totalFilesAnalyzed++;
}

void FileSample::resetCounters() {
    totalFilesAnalyzed = 0;
    totalBytesProcessed = 0;
    std::cout << "[FileSample] Static counters reset." << std::endl;
}

// ==================== Operator Overloading ====================

bool FileSample::operator==(const FileSample& other) const {
    // Two files are equal if they have the same path
    return filePath == other.filePath;
}

bool FileSample::operator!=(const FileSample& other) const {
    return !(*this == other);
}