/**
 * @file ConsoleUI.h
 * @brief Console UI utilities for colorful, professional output
 * @details Provides ANSI color codes and formatting functions
 * 
 * ANSI Color Codes:
 * - Work in most modern terminals (PowerShell, VS Code, Linux)
 * - Format: \033[CODEm where CODE is the color/style
 * - Reset with: \033[0m
 */

#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <string>
#include <iostream>

/**
 * @class ConsoleUI
 * @brief Static utility class for console formatting and colors
 * 
 * Provides methods for:
 * - Colored output (success, warning, error, info)
 * - Formatted headers and banners
 * - Progress indicators
 * - Risk meters
 * - Status icons
 */
class ConsoleUI {
private:
    // ANSI Color Codes
    static const std::string RESET;
    static const std::string BOLD;
    
    // Text Colors
    static const std::string BLACK;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;
    
    // Bright Colors
    static const std::string BRIGHT_RED;
    static const std::string BRIGHT_GREEN;
    static const std::string BRIGHT_YELLOW;
    static const std::string BRIGHT_BLUE;
    static const std::string BRIGHT_MAGENTA;
    static const std::string BRIGHT_CYAN;
    static const std::string BRIGHT_WHITE;
    
    // Background Colors
    static const std::string BG_RED;
    static const std::string BG_GREEN;
    static const std::string BG_YELLOW;
    static const std::string BG_BLUE;
    
    /**
     * @brief Gets color code for a verdict
     * @param verdict Verdict string (SAFE, SUSPICIOUS, DANGEROUS)
     * @return ANSI color code
     */
    static std::string getVerdictColor(const std::string& verdict);
    
    /**
     * @brief Gets color code for risk score
     * @param riskScore Score 0-100
     * @return ANSI color code
     */
    static std::string getRiskColor(int riskScore);
    
public:
    /**
     * @brief Displays the application banner with ASCII art
     */
    static void printBanner();
    
    /**
     * @brief Prints a formatted header
     * @param title Header title
     * @param width Width of the header box (default: 60)
     */
    static void printHeader(const std::string& title, int width = 60);
    
    /**
     * @brief Prints a section divider
     * @param width Width of divider (default: 60)
     */
    static void printDivider(int width = 60);
    
    /**
     * @brief Prints a success message with [✓] icon
     * @param message Message to display
     */
    static void printSuccess(const std::string& message);
    
    /**
     * @brief Prints a warning message with [!] icon
     * @param message Message to display
     */
    static void printWarning(const std::string& message);
    
    /**
     * @brief Prints an error message with [✗] icon
     * @param message Message to display
     */
    static void printError(const std::string& message);
    
    /**
     * @brief Prints an info message with [i] icon
     * @param message Message to display
     */
    static void printInfo(const std::string& message);
    
    /**
     * @brief Prints a progress message with [>] icon
     * @param message Message to display
     */
    static void printProgress(const std::string& message);
    
    /**
     * @brief Prints a colored verdict
     * @param verdict Verdict string (SAFE, SUSPICIOUS, DANGEROUS)
     */
    static void printVerdict(const std::string& verdict);
    
    /**
     * @brief Prints a colored risk score with visual meter
     * @param score Risk score (0-100)
     * @param showMeter Display graphical meter (default: true)
     */
    static void printRiskScore(int score, bool showMeter = true);
    
    /**
     * @brief Prints a visual risk meter bar
     * @param score Risk score (0-100)
     * @param width Width of the meter (default: 40)
     */
    static void printRiskMeter(int score, int width = 40);
    
    /**
     * @brief Prints a formatted menu item
     * @param number Menu number
     * @param text Menu text
     */
    static void printMenuItem(int number, const std::string& text);
    
    /**
     * @brief Prints a key-value pair with alignment
     * @param key Key name
     * @param value Value
     * @param keyWidth Width for key column (default: 20)
     */
    static void printKeyValue(const std::string& key, const std::string& value, int keyWidth = 20);
    
    /**
     * @brief Clears the console screen
     */
    static void clearScreen();
    
    /**
     * @brief Pauses execution and waits for Enter
     * @param message Custom message (default: "Press Enter to continue...")
     */
    static void pause(const std::string& message = "Press Enter to continue...");
    
    /**
     * @brief Prints centered text
     * @param text Text to center
     * @param width Total width (default: 60)
     */
    static void printCentered(const std::string& text, int width = 60);
    
    /**
     * @brief Prints a box with text inside
     * @param text Text content
     * @param width Box width (default: 60)
     */
    static void printBox(const std::string& text, int width = 60);
};

#endif // CONSOLEUI_H