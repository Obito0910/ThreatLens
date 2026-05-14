/**
 * @file main.cpp
 * @brief Enhanced main entry point with colorful console UI
 */

#include "../include/FileSample.h"
#include "../include/AnalysisResult.h"
#include "../include/User.h"
#include "../include/Analyzer.h"
#include "../include/HashAnalyzer.h"
#include "../include/StringAnalyzer.h"
#include "../include/SignatureAnalyzer.h"
#include "../include/MetadataAnalyzer.h"
#include "../include/AnalysisEngine.h"
#include "../include/Logger.h"
#include "../include/ReportGenerator.h"
#include "../include/AuthenticationManager.h"
#include "../include/QuarantineManager.h"
#include "../include/ConsoleUI.h"
#include "../include/Exceptions.h"
#include <iostream>
#include <string>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Global objects
Logger* globalLogger = NULL;
AuthenticationManager* authManager = NULL;
AnalysisEngine* engine = NULL;
ReportGenerator* reportGen = NULL;
QuarantineManager* quarantineManager = NULL;
AnalysisResult* lastAnalysisResult = NULL;
FileSample* lastAnalyzedFile = NULL;

/**
 * @brief Displays the main menu with colors
 */
void displayMenu(bool loggedIn) {
    ConsoleUI::printHeader(loggedIn ? "MAIN MENU" : "WELCOME");
    
    if (loggedIn) {
        User* user = authManager->getCurrentUser();
        
        ConsoleUI::printKeyValue("User", user->getUsername());
        ConsoleUI::printKeyValue("Role", user->getRole());
        ConsoleUI::printKeyValue("Analyses", to_string(user->getAnalysisCount()));
        
        ConsoleUI::printDivider();
        
        ConsoleUI::printMenuItem(1, "Analyze File");
        ConsoleUI::printMenuItem(2, "View Last Analysis Result");
        ConsoleUI::printMenuItem(3, "Generate Report");
        ConsoleUI::printMenuItem(4, "View Global Statistics");
        ConsoleUI::printMenuItem(5, "View My Analysis History");
        ConsoleUI::printMenuItem(6, "Quarantine Last Analyzed File");
        ConsoleUI::printMenuItem(7, "View Quarantine List");
        ConsoleUI::printMenuItem(8, "Logout");
        ConsoleUI::printMenuItem(9, "Exit");
        
    } else {
        ConsoleUI::printInfo("Please login to access the system");
        
        ConsoleUI::printDivider();
        
        ConsoleUI::printMenuItem(1, "Login");
        ConsoleUI::printMenuItem(2, "Exit");
    }
    
    ConsoleUI::printDivider();
    cout << "Choice: ";
}

/**
 * @brief Initializes system with visual feedback
 */
bool initializeSystem() {
    ConsoleUI::clearScreen();
    ConsoleUI::printBanner();
    
    ConsoleUI::printHeader("SYSTEM INITIALIZATION");
    
    try {
        ConsoleUI::printProgress("Initializing logger...");
        globalLogger = new Logger("logs/analysis.log");
        ConsoleUI::printSuccess("Logger initialized");
        
        ConsoleUI::printProgress("Loading authentication system...");
        authManager = new AuthenticationManager(globalLogger, "data/users.txt");
        ConsoleUI::printSuccess("Loaded " + to_string(authManager->getUserCount()) + " users");
        
        ConsoleUI::printProgress("Initializing analysis engine...");
        engine = new AnalysisEngine();
        
        engine->addAnalyzer(new HashAnalyzer());
        engine->addAnalyzer(new StringAnalyzer());
        engine->addAnalyzer(new SignatureAnalyzer());
        engine->addAnalyzer(new MetadataAnalyzer());
        
        ConsoleUI::printSuccess("Engine initialized with " + to_string(engine->getAnalyzerCount()) + " analyzers");
        
        ConsoleUI::printProgress("Initializing report generator...");
        reportGen = new ReportGenerator("reports/");
        ConsoleUI::printSuccess("Report generator ready");
        
        ConsoleUI::printProgress("Initializing quarantine manager...");
        quarantineManager = new QuarantineManager(globalLogger, "logs/quarantine.log");
        ConsoleUI::printSuccess("Quarantine manager ready");
        
        cout << "\n";
        ConsoleUI::printSuccess("System initialized successfully!");
        
        globalLogger->log("INFO", "System started");
        
        return true;
        
    } catch (const exception& e) {
        ConsoleUI::printError("System initialization failed: " + string(e.what()));
        return false;
    }
}

/**
 * @brief Cleans up system resources
 */
void cleanupSystem() {
    ConsoleUI::printHeader("SYSTEM SHUTDOWN");
    
    if (globalLogger) {
        globalLogger->log("INFO", "System shutting down");
    }
    
    ConsoleUI::printProgress("Cleaning up resources...");
    
    delete lastAnalyzedFile;
    delete lastAnalysisResult;
    delete quarantineManager;
    delete reportGen;
    delete engine;
    delete authManager;
    delete globalLogger;
    
    ConsoleUI::printSuccess("System shutdown complete");
}

/**
 * @brief Handles user login with colored feedback
 */
void handleLogin() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("USER LOGIN");
    
    string username, password;
    
    cout << "Username: ";
    cin >> username;
    
    cout << "Password: ";
    cin >> password;
    
    try {
        User& user = authManager->login(username, password);
        
        cout << "\n";
        ConsoleUI::printSuccess("Login successful!");
        ConsoleUI::printKeyValue("Welcome", user.getUsername());
        ConsoleUI::printKeyValue("Role", user.getRole());
        
        ConsoleUI::pause();
        
    } catch (const AuthenticationException& e) {
        cout << "\n";
        ConsoleUI::printError("Login failed: " + string(e.what()));
        ConsoleUI::pause();
    }
}

/**
 * @brief Handles file analysis with enhanced visual output
 */
void handleAnalyzeFile() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("FILE ANALYSIS");
    
    string filePath;
    cout << "Enter file path: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, filePath);
    
    try {
        delete lastAnalyzedFile;
        delete lastAnalysisResult;
        
        cout << "\n";
        ConsoleUI::printProgress("Loading file...");
        lastAnalyzedFile = new FileSample(filePath);
        lastAnalyzedFile->load();
        
        ConsoleUI::printSuccess("File loaded: " + lastAnalyzedFile->getFileName());
        ConsoleUI::printKeyValue("Size", to_string(lastAnalyzedFile->getFileSize()) + " bytes");
        
        cout << "\n";
        ConsoleUI::printProgress("Running analysis...");
        
        User* user = authManager->getCurrentUser();
        AnalysisResult result = engine->runAnalysis(*lastAnalyzedFile, *user);
        
        lastAnalysisResult = new AnalysisResult(result);
        
        globalLogger->logAnalysis(*user, result);
        
        // Display results with colors
        cout << "\n";
        ConsoleUI::printHeader("ANALYSIS RESULTS");
        
        ConsoleUI::printKeyValue("File", result.getAnalyzedFileName());
        ConsoleUI::printKeyValue("Hash", result.getHashValue());
        
        cout << "Risk Score:          ";
        ConsoleUI::printRiskScore(result.getRiskScore(), true);
        cout << "\n";
        
        cout << "Verdict:             ";
        ConsoleUI::printVerdict(result.getVerdict());
        cout << "\n\n";
        
        ConsoleUI::printDivider();
        cout << "Findings (" << result.getFindingsCount() << "):\n\n";
        
        const vector<string>& findings = result.getFindings();
        for (size_t i = 0; i < findings.size(); ++i) {
            cout << "  " << (i + 1) << ". " << findings[i] << "\n";
        }
        
        ConsoleUI::pause();
        
    } catch (const exception& e) {
        cout << "\n";
        ConsoleUI::printError("Analysis failed: " + string(e.what()));
        ConsoleUI::pause();
    }
}

/**
 * @brief Views last analysis with colored output
 */
void handleViewLastResult() {
    ConsoleUI::clearScreen();
    
    if (lastAnalysisResult == NULL) {
        ConsoleUI::printWarning("No analysis has been performed yet.");
        ConsoleUI::pause();
        return;
    }
    
    ConsoleUI::printHeader("LAST ANALYSIS RESULT");
    
    ConsoleUI::printKeyValue("File", lastAnalysisResult->getAnalyzedFileName());
    ConsoleUI::printKeyValue("Hash", lastAnalysisResult->getHashValue());
    ConsoleUI::printKeyValue("Timestamp", lastAnalysisResult->getTimestamp());
    
    cout << "Risk Score:          ";
    ConsoleUI::printRiskScore(lastAnalysisResult->getRiskScore(), true);
    cout << "\n";
    
    cout << "Verdict:             ";
    ConsoleUI::printVerdict(lastAnalysisResult->getVerdict());
    cout << "\n\n";
    
    ConsoleUI::printDivider();
    cout << "Findings (" << lastAnalysisResult->getFindingsCount() << "):\n\n";
    
    const vector<string>& findings = lastAnalysisResult->getFindings();
    for (size_t i = 0; i < findings.size(); ++i) {
        cout << "  " << (i + 1) << ". " << findings[i] << "\n";
    }
    
    ConsoleUI::pause();
}

/**
 * @brief Generates report with status feedback
 */
void handleGenerateReport() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("REPORT GENERATION");
    
    if (lastAnalysisResult == NULL || lastAnalyzedFile == NULL) {
        ConsoleUI::printWarning("No analysis available to generate report.");
        ConsoleUI::pause();
        return;
    }
    
    try {
        User* user = authManager->getCurrentUser();
        
        ConsoleUI::printProgress("Generating detailed report...");
        
        string reportPath = reportGen->generateReport(*lastAnalyzedFile, 
                                                     *lastAnalysisResult, 
                                                     *user);
        
        cout << "\n";
        ConsoleUI::printSuccess("Report generated successfully!");
        ConsoleUI::printKeyValue("Location", reportPath);
        
        ConsoleUI::pause();
        
    } catch (const exception& e) {
        cout << "\n";
        ConsoleUI::printError("Report generation failed: " + string(e.what()));
        ConsoleUI::pause();
    }
}

/**
 * @brief Displays global statistics with colors
 */
void handleViewStatistics() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("GLOBAL STATISTICS");
    
    ConsoleUI::printKeyValue("Files Analyzed", to_string(AnalysisEngine::getTotalFilesAnalyzed()));
    ConsoleUI::printKeyValue("Threats Detected", to_string(AnalysisEngine::getTotalThreatsDetected()));
    ConsoleUI::printKeyValue("Total Bytes Processed", to_string(FileSample::getTotalBytesProcessed()));
    ConsoleUI::printKeyValue("Log Entries", to_string(Logger::getTotalLogs()));
    ConsoleUI::printKeyValue("Registered Users", to_string(authManager->getUserCount()));
    ConsoleUI::printKeyValue("Quarantined Files", to_string(quarantineManager->getQuarantineCount()));
    
    if (AnalysisEngine::getTotalFilesAnalyzed() > 0) {
        double threatRate = (static_cast<double>(AnalysisEngine::getTotalThreatsDetected()) / 
                            static_cast<double>(AnalysisEngine::getTotalFilesAnalyzed())) * 100.0;
        
        cout << "Threat Rate:         ";
        ConsoleUI::printRiskScore(static_cast<int>(threatRate), false);
        cout << "\n";
    }
    
    ConsoleUI::pause();
}

/**
 * @brief Views user history with colored output
 */
void handleViewHistory() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("MY ANALYSIS HISTORY");
    
    User* user = authManager->getCurrentUser();
    const History<AnalysisResult>& history = user->getHistory();
    
    if (history.isEmpty()) {
        ConsoleUI::printInfo("No analysis history available.");
    } else {
        ConsoleUI::printKeyValue("Total Analyses", to_string(history.size()));
        
        cout << "\n";
        ConsoleUI::printDivider();
        cout << "Recent Analyses:\n\n";
        
        int displayCount = (history.size() < 10) ? history.size() : 10;
        
        for (int i = 0; i < displayCount; ++i) {
            const AnalysisResult& result = history.get(i);
            
            cout << (i + 1) << ". " << result.getAnalyzedFileName() << " - ";
            ConsoleUI::printVerdict(result.getVerdict());
            cout << " (Risk: " << result.getRiskScore() << ")\n";
        }
    }
    
    ConsoleUI::pause();
}

/**
 * @brief Quarantines file with visual feedback
 */
void handleQuarantine() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("QUARANTINE FILE");
    
    if (lastAnalysisResult == NULL || lastAnalyzedFile == NULL) {
        ConsoleUI::printWarning("No analysis available to quarantine.");
        ConsoleUI::pause();
        return;
    }
    
    try {
        User* user = authManager->getCurrentUser();
        
        ConsoleUI::printProgress("Attempting to quarantine file...");
        
        bool success = quarantineManager->quarantine(*lastAnalyzedFile, 
                                                    *lastAnalysisResult, 
                                                    *user);
        
        cout << "\n";
        if (success) {
            ConsoleUI::printSuccess("File has been quarantined successfully!");
            ConsoleUI::printKeyValue("File", lastAnalyzedFile->getFileName());
            ConsoleUI::printKeyValue("Quarantined by", user->getUsername());
        } else {
            ConsoleUI::printWarning("File was not quarantined (not dangerous enough)");
            ConsoleUI::printKeyValue("Verdict", lastAnalysisResult->getVerdict());
            ConsoleUI::printInfo("Only DANGEROUS files can be quarantined");
        }
        
        ConsoleUI::pause();
        
    } catch (const exception& e) {
        cout << "\n";
        ConsoleUI::printError("Quarantine failed: " + string(e.what()));
        ConsoleUI::pause();
    }
}

/**
 * @brief Displays quarantine list with colors
 */
void handleViewQuarantine() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("QUARANTINED FILES");
    
    const vector<string>& files = quarantineManager->getQuarantinedFiles();
    
    if (files.empty()) {
        ConsoleUI::printInfo("No files in quarantine.");
    } else {
        ConsoleUI::printKeyValue("Total Quarantined", to_string(files.size()));
        
        cout << "\n";
        ConsoleUI::printDivider();
        
        for (size_t i = 0; i < files.size(); ++i) {
            cout << (i + 1) << ". " << files[i] << "\n";
        }
    }
    
    ConsoleUI::pause();
}

/**
 * @brief Handles logout with cleanup
 */
void handleLogout() {
    authManager->logout();
    
    delete lastAnalyzedFile;
    delete lastAnalysisResult;
    lastAnalyzedFile = NULL;
    lastAnalysisResult = NULL;
    
    cout << "\n";
    ConsoleUI::printSuccess("Logged out successfully");
    ConsoleUI::pause();
}

/**
 * @brief Main application loop
 */
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);  // Enable UTF-8 output on Windows
#endif
    if (!initializeSystem()) {
        ConsoleUI::printError("Failed to start system. Exiting.");
        return 1;
    }
    
    ConsoleUI::pause();
    
    bool running = true;
    
    while (running) {
        ConsoleUI::clearScreen();
        bool loggedIn = authManager->isLoggedIn();
        displayMenu(loggedIn);
        
        int choice;
        cin >> choice;
        
        if (!loggedIn) {
            switch (choice) {
                case 1:
                    handleLogin();
                    break;
                case 2:
                    running = false;
                    break;
                default:
                    ConsoleUI::printError("Invalid choice!");
                    ConsoleUI::pause();
            }
        } else {
            switch (choice) {
                case 1:
                    handleAnalyzeFile();
                    break;
                case 2:
                    handleViewLastResult();
                    break;
                case 3:
                    handleGenerateReport();
                    break;
                case 4:
                    handleViewStatistics();
                    break;
                case 5:
                    handleViewHistory();
                    break;
                case 6:
                    handleQuarantine();
                    break;
                case 7:
                    handleViewQuarantine();
                    break;
                case 8:
                    handleLogout();
                    break;
                case 9:
                    running = false;
                    break;
                default:
                    ConsoleUI::printError("Invalid choice!");
                    ConsoleUI::pause();
            }
        }
    }
    
    cleanupSystem();
    
    cout << "\n";
    ConsoleUI::printSuccess("Thank you for using Malware Analysis Simulator!");
    cout << "\n";
    
    return 0;
}