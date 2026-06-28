#pragma once
#include <string>
#include <vector>
#include <memory>

class Account;
class Transaction;

class FileHandler {
public:
    static void ensureDirectories();

    // Account persistence
    static void saveAccounts();
    static void loadAccounts();

    // Transaction persistence
    static void saveTransactions();
    static void loadTransactions();

    // Report export
    static bool exportMonthlyReport(const std::string& filename);
    static bool exportTransactionHistory(const std::string& accNo, const std::string& filename);
};
