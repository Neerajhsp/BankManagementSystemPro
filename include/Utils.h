#pragma once
#include <string>
#include <vector>

namespace Utils {
    std::string getCurrentTimestamp();
    std::string getCurrentDate();
    std::string generateTransactionId();

    std::string getHiddenInput(const std::string& prompt);
    std::string trim(const std::string& s);
    std::string toLower(const std::string& s);
    std::string toUpper(const std::string& s);

    bool isValidEmail(const std::string& email);
    bool isValidPhone(const std::string& phone);
    bool isValidAadhar(const std::string& aadhar);
    bool isValidPAN(const std::string& pan);
    bool isValidAmount(double amount);

    std::vector<std::string> split(const std::string& s, char delimiter);
    std::string join(const std::vector<std::string>& parts, char delimiter);

    std::string formatCurrency(double amount);
    std::string formatDouble(double value, int precision = 2);

    void clearScreen();
    void pressEnterToContinue();
    int  getIntInput(const std::string& prompt, int min, int max);
    double getDoubleInput(const std::string& prompt, double min = 0.0);
    std::string getStringInput(const std::string& prompt, bool allowEmpty = false);

    void printSeparator(char ch = '=', int width = 70);
    void printCentered(const std::string& text, int width = 70);
}
