/**
 * @file ConsoleUI.cpp
 * @brief Implementation of ConsoleUI class
 */

#include "../include/ConsoleUI.h"
#include <iostream>
#include <iomanip>
#include <limits>

// Initialize ANSI color codes
const std::string ConsoleUI::RESET = "\033[0m";
const std::string ConsoleUI::BOLD = "\033[1m";

const std::string ConsoleUI::BLACK = "\033[30m";
const std::string ConsoleUI::RED = "\033[31m";
const std::string ConsoleUI::GREEN = "\033[32m";
const std::string ConsoleUI::YELLOW = "\033[33m";
const std::string ConsoleUI::BLUE = "\033[34m";
const std::string ConsoleUI::MAGENTA = "\033[35m";
const std::string ConsoleUI::CYAN = "\033[36m";
const std::string ConsoleUI::WHITE = "\033[37m";

const std::string ConsoleUI::BRIGHT_RED = "\033[91m";
const std::string ConsoleUI::BRIGHT_GREEN = "\033[92m";
const std::string ConsoleUI::BRIGHT_YELLOW = "\033[93m";
const std::string ConsoleUI::BRIGHT_BLUE = "\033[94m";
const std::string ConsoleUI::BRIGHT_MAGENTA = "\033[95m";
const std::string ConsoleUI::BRIGHT_CYAN = "\033[96m";
const std::string ConsoleUI::BRIGHT_WHITE = "\033[97m";

const std::string ConsoleUI::BG_RED = "\033[41m";
const std::string ConsoleUI::BG_GREEN = "\033[42m";
const std::string ConsoleUI::BG_YELLOW = "\033[43m";
const std::string ConsoleUI::BG_BLUE = "\033[44m";

// ==================== Banner ====================

void ConsoleUI::printBanner() {
    std::cout << BRIGHT_CYAN << BOLD;
    std::cout << "\n";
    std::cout << "  *********************************************************************************************\n";
    std::cout << " ████████╗██╗  ██╗██████╗ ███████╗ █████╗ ████████╗    ██╗     ███████╗███╗   ██╗███████╗ "<< "\n";
    std::cout << " ╚══██╔══╝██║  ██║██╔══██╗██╔════╝██╔══██╗╚══██╔══╝    ██║     ██╔════╝████╗  ██║██╔════╝ "<< "\n";
    std::cout << "    ██║   ███████║██████╔╝█████╗  ███████║   ██║       ██║     █████╗  ██╔██╗ ██║███████╗ "<< "\n";
    std::cout << "    ██║   ██╔══██║██╔══██╗██╔══╝  ██╔══██║   ██║       ██║     ██╔══╝  ██║╚██╗██║╚════██║ "<< "\n";
    std::cout << "    ██║   ██║  ██║██║  ██║███████╗██║  ██║   ██║       ███████╗███████╗██║ ╚████║███████║ "<< "\n";
    std::cout << "    ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝       ╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝ "<< "\n";
                                                                                        
    std::cout << "  *********************************************************************************************\n";
    std::cout << RESET;
    std::cout << BRIGHT_WHITE;
    std::cout << "  +-------------------------------------------------------+\n";
    std::cout << "  |        MALWARE ANALYSIS SIMULATOR  v1.0               |\n";
    std::cout << "  |        OOP Lab Semester Project                       |\n";
    std::cout << "  +-------------------------------------------------------+\n";
    std::cout << RESET << "\n";
}

// ==================== Headers & Dividers ====================

void ConsoleUI::printHeader(const std::string& title, int width) {
    std::string line(width, '=');
    
    std::cout << BRIGHT_CYAN << line << RESET << "\n";
    printCentered(title, width);
    std::cout << BRIGHT_CYAN << line << RESET << "\n";
}

void ConsoleUI::printDivider(int width) {
    std::cout << CYAN << std::string(width, '-') << RESET << "\n";
}

void ConsoleUI::printCentered(const std::string& text, int width) {
    int padding = (width - static_cast<int>(text.length())) / 2;
    if (padding > 0) {
        std::cout << std::string(padding, ' ');
    }
    std::cout << BOLD << WHITE << text << RESET << "\n";
}

void ConsoleUI::printBox(const std::string& text, int width) {
    std::string line(width - 2, '=');
    
    std::cout << CYAN << "╔" << line << "╗" << RESET << "\n";
    std::cout << CYAN << "║ " << RESET << text;
    
    int padding = width - static_cast<int>(text.length()) - 4;
    if (padding > 0) {
        std::cout << std::string(padding, ' ');
    }
    std::cout << CYAN << " ║" << RESET << "\n";
    std::cout << CYAN << "╚" << line << "╝" << RESET << "\n";
}

// ==================== Status Messages ====================

void ConsoleUI::printSuccess(const std::string& message) {
    std::cout << BRIGHT_GREEN << "[✓] " << message << RESET << "\n";
}

void ConsoleUI::printWarning(const std::string& message) {
    std::cout << BRIGHT_YELLOW << "[!] " << message << RESET << "\n";
}

void ConsoleUI::printError(const std::string& message) {
    std::cout << BRIGHT_RED << "[✗] " << message << RESET << "\n";
}

void ConsoleUI::printInfo(const std::string& message) {
    std::cout << BRIGHT_BLUE << "[i] " << message << RESET << "\n";
}

void ConsoleUI::printProgress(const std::string& message) {
    std::cout << BRIGHT_CYAN << "[>] " << message << RESET << "\n";
}

// ==================== Verdict Display ====================

std::string ConsoleUI::getVerdictColor(const std::string& verdict) {
    if (verdict == "SAFE") {
        return BRIGHT_GREEN;
    } else if (verdict == "SUSPICIOUS") {
        return BRIGHT_YELLOW;
    } else if (verdict == "DANGEROUS") {
        return BRIGHT_RED;
    }
    return WHITE;
}

void ConsoleUI::printVerdict(const std::string& verdict) {
    std::string color = getVerdictColor(verdict);
    std::cout << color << BOLD << verdict << RESET;
}

// ==================== Risk Score Display ====================

std::string ConsoleUI::getRiskColor(int riskScore) {
    if (riskScore <= 29) {
        return BRIGHT_GREEN;
    } else if (riskScore <= 69) {
        return BRIGHT_YELLOW;
    } else {
        return BRIGHT_RED;
    }
}

void ConsoleUI::printRiskScore(int score, bool showMeter) {
    std::string color = getRiskColor(score);
    std::cout << color << BOLD << score << " / 100" << RESET;
    
    if (showMeter) {
        std::cout << "  ";
        printRiskMeter(score, 30);
    }
}

void ConsoleUI::printRiskMeter(int score, int width) {
    int filledWidth = (score * width) / 100;
    std::string color = getRiskColor(score);
    
    std::cout << "[";
    
    // Filled portion
    std::cout << color;
    for (int i = 0; i < filledWidth; ++i) {
        std::cout << "█";
    }
    std::cout << RESET;
    
    // Empty portion
    for (int i = filledWidth; i < width; ++i) {
        std::cout << "░";
    }
    
    std::cout << "]";
}

// ==================== Menu & Formatting ====================

void ConsoleUI::printMenuItem(int number, const std::string& text) {
    std::cout << BRIGHT_WHITE << "  " << number << ". " 
              << RESET << text << "\n";
}

void ConsoleUI::printKeyValue(const std::string& key, const std::string& value, int keyWidth) {
    std::cout << CYAN << std::left << std::setw(keyWidth) << key << ": " 
              << RESET << value << "\n";
}

// ==================== Screen Control ====================

void ConsoleUI::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void ConsoleUI::pause(const std::string& message) {
    std::cout << "\n" << BRIGHT_YELLOW << message << RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}