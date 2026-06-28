#include "FileHandler.h"
#include "Bank.h"
#include "Constants.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

void FileHandler::ensureDirectories() {
    fs::create_directories(Constants::DATA_DIR);
    fs::create_directories(Constants::REPORTS_DIR);
}

void FileHandler::saveAccounts() {
    ensureDirectories();
    std::ofstream f(Constants::ACCOUNTS_FILE);
    if (!f.is_open()) return;

    for (const auto& [accNo, acc] : Bank::getInstance().getAllAccounts()) {
        f << acc->serialize() << "\n";
    }
}

void FileHandler::loadAccounts() {
    std::ifstream f(Constants::ACCOUNTS_FILE);
    if (!f.is_open()) return;

    Bank::getInstance().clearAll();
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        // Peek at type
        if (line.substr(0, 7) == "SAVINGS") {
            auto acc = std::make_shared<SavingsAccount>(
                SavingsAccount::deserialize(line));
            if (!acc->getAccountNumber().empty())
                Bank::getInstance().addAccount(acc);
        } else if (line.substr(0, 7) == "CURRENT") {
            auto acc = std::make_shared<CurrentAccount>(
                CurrentAccount::deserialize(line));
            if (!acc->getAccountNumber().empty())
                Bank::getInstance().addAccount(acc);
        }
    }
    // Reload transactions
    loadTransactions();
}

void FileHandler::saveTransactions() {
    ensureDirectories();
    std::ofstream f(Constants::TRANSACTIONS_FILE);
    if (!f.is_open()) return;

    for (const auto& tx : Bank::getInstance().getAllTransactions()) {
        f << tx.serialize() << "\n";
    }
}

void FileHandler::loadTransactions() {
    std::ifstream f(Constants::TRANSACTIONS_FILE);
    if (!f.is_open()) return;

    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        Transaction tx = Transaction::deserialize(line);
        if (!tx.getTransactionId().empty())
            Bank::getInstance().addTransaction(tx);
    }
}

bool FileHandler::exportMonthlyReport(const std::string& filename) {
    ensureDirectories();
    std::ofstream f(Constants::REPORTS_DIR + filename);
    if (!f.is_open()) return false;

    Bank& bank = Bank::getInstance();
    f << "========================================================\n";
    f << "          " << Constants::BANK_NAME << " - Monthly Report\n";
    f << "========================================================\n";
    f << "Generated On : " << Utils::getCurrentTimestamp() << "\n";
    f << "--------------------------------------------------------\n\n";
    f << "Summary:\n";
    f << "  Total Accounts       : " << bank.getTotalAccounts() << "\n";
    f << "  Total Bank Balance   : " << Utils::formatCurrency(bank.getTotalBalance()) << "\n\n";

    auto highest = bank.getHighestBalanceAccount();
    auto lowest  = bank.getLowestBalanceAccount();

    if (highest) {
        f << "  Highest Balance Account:\n";
        f << "    Account No : " << highest->getAccountNumber() << "\n";
        f << "    Name       : " << highest->getCustomerConst().getName() << "\n";
        f << "    Balance    : " << Utils::formatCurrency(highest->getBalance()) << "\n\n";
    }
    if (lowest) {
        f << "  Lowest Balance Account:\n";
        f << "    Account No : " << lowest->getAccountNumber() << "\n";
        f << "    Name       : " << lowest->getCustomerConst().getName() << "\n";
        f << "    Balance    : " << Utils::formatCurrency(lowest->getBalance()) << "\n\n";
    }

    f << "--------------------------------------------------------\n";
    f << "Account Details:\n\n";
    f << std::left
      << std::setw(16) << "Account No"
      << std::setw(10) << "Type"
      << std::setw(25) << "Name"
      << std::setw(18) << "Balance"
      << "Status\n";
    f << std::string(80, '-') << "\n";

    for (const auto& [accNo, acc] : bank.getAllAccounts()) {
        f << std::left
          << std::setw(16) << acc->getAccountNumber()
          << std::setw(10) << acc->getAccountTypeName()
          << std::setw(25) << acc->getCustomerConst().getName()
          << std::setw(18) << Utils::formatCurrency(acc->getBalance())
          << (acc->getIsActive() ? "Active" : "Closed") << "\n";
    }
    f << "\n========================================================\n";
    return true;
}

bool FileHandler::exportTransactionHistory(const std::string& accNo, const std::string& filename) {
    ensureDirectories();
    std::ofstream f(Constants::REPORTS_DIR + filename);
    if (!f.is_open()) return false;

    auto acc = Bank::getInstance().findAccount(accNo);
    if (!acc) return false;

    auto txs = Bank::getInstance().getTransactionsByAccount(accNo);

    f << "========================================================\n";
    f << "       " << Constants::BANK_NAME << " - Transaction History\n";
    f << "========================================================\n";
    f << "Account No   : " << accNo << "\n";
    f << "Account Name : " << acc->getCustomerConst().getName() << "\n";
    f << "Generated On : " << Utils::getCurrentTimestamp() << "\n";
    f << "--------------------------------------------------------\n\n";
    f << std::left
      << std::setw(15) << "TxID"
      << std::setw(22) << "Timestamp"
      << std::setw(18) << "Type"
      << std::setw(16) << "Amount"
      << "Balance After\n";
    f << std::string(80, '-') << "\n";

    for (const auto& tx : txs) {
        f << std::left
          << std::setw(15) << tx.getTransactionId()
          << std::setw(22) << tx.getTimestamp()
          << std::setw(18) << transactionTypeToString(tx.getType())
          << std::setw(16) << Utils::formatCurrency(tx.getAmount())
          << Utils::formatCurrency(tx.getBalanceAfter()) << "\n";
    }
    f << "\n========================================================\n";
    return true;
}
