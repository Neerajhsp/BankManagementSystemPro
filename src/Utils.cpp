#include "Utils.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <limits>
#include <regex>
#include <random>

namespace Utils {

std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm* tm_info = std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(tm_info, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm* tm_info = std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(tm_info, "%Y-%m-%d");
    return oss.str();
}

std::string generateTransactionId() {
    static std::mt19937 rng(
        static_cast<unsigned int>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        )
    );

    std::uniform_int_distribution<int> dist(100000, 999999);
    return "TXN" + std::to_string(dist(rng));
}

std::string getHiddenInput(const std::string& prompt) {
    std::cout << prompt;
    std::cout.flush();

    std::string password;
    std::getline(std::cin >> std::ws, password);

    return password;
}

std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";

    size_t end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string toUpper(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

bool isValidEmail(const std::string& email) {
    std::regex pattern(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    return std::regex_match(email, pattern);
}

bool isValidPhone(const std::string& phone) {
    std::regex pattern(R"(^[6-9]\d{9}$)");
    return std::regex_match(phone, pattern);
}

bool isValidAadhar(const std::string& aadhar) {
    std::regex pattern(R"(^\d{12}$)");
    return std::regex_match(aadhar, pattern);
}

bool isValidPAN(const std::string& pan) {
    std::regex pattern(R"(^[A-Z]{5}[0-9]{4}[A-Z]{1}$)");
    return std::regex_match(toUpper(pan), pattern);
}

bool isValidAmount(double amount) {
    return amount > 0.0;
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> parts;
    std::istringstream ss(s);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        parts.push_back(token);
    }

    return parts;
}

std::string join(const std::vector<std::string>& parts, char delimiter) {
    std::string result;

    for (size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) result += delimiter;
        result += parts[i];
    }

    return result;
}

std::string formatCurrency(double amount) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << amount;

    std::string s = oss.str();
    size_t dotPos = s.find('.');

    std::string intPart = s.substr(0, dotPos);
    std::string decPart = s.substr(dotPos);

    std::string result;
    int len = static_cast<int>(intPart.size());

    if (len <= 3) {
        result = intPart;
    } else {
        int first = len % 2;
        if (first == 0) first = 2;

        result = intPart.substr(0, first);

        for (int i = first; i < len; i += 2) {
            result += "," + intPart.substr(i, 2);
        }
    }

    return "Rs. " + result + decPart;
}

std::string formatDouble(double value, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}

void clearScreen() {
#if defined(__APPLE__) || defined(__linux__)
    (void)system("clear");
#else
    (void)system("cls");
#endif
}

void pressEnterToContinue() {
    std::cout << "\n  Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getIntInput(const std::string& prompt, int min, int max) {
    int value;

    while (true) {
        std::cout << prompt;

        std::string line;
        std::getline(std::cin, line);

        try {
            value = std::stoi(trim(line));

            if (value >= min && value <= max) {
                break;
            }

            std::cout << "  [!] Please enter a value between "
                      << min << " and " << max << ".\n";
        } catch (...) {
            std::cout << "  [!] Invalid input. Please enter a number.\n";
        }
    }

    return value;
}

double getDoubleInput(const std::string& prompt, double min) {
    double value;

    while (true) {
        std::cout << prompt;

        std::string line;
        std::getline(std::cin, line);

        try {
            value = std::stod(trim(line));

            if (value >= min) {
                break;
            }

            std::cout << "  [!] Please enter a value >= " << min << ".\n";
        } catch (...) {
            std::cout << "  [!] Invalid input. Please enter a number.\n";
        }
    }

    return value;
}

std::string getStringInput(const std::string& prompt, bool allowEmpty) {
    std::string value;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);

        value = trim(value);

        if (!value.empty() || allowEmpty) {
            break;
        }

        std::cout << "  [!] Input cannot be empty.\n";
    }

    return value;
}

void printSeparator(char ch, int width) {
    std::cout << "  " << std::string(width, ch) << "\n";
}

void printCentered(const std::string& text, int width) {
    int padding = (width - static_cast<int>(text.size())) / 2;
    if (padding < 0) padding = 0;

    std::cout << "  " << std::string(padding, ' ') << text << "\n";
}

}