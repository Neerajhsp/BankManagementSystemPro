#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "Account.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "Transaction.h"

class Bank {
private:
    std::unordered_map<std::string, std::shared_ptr<Account>> accounts;
    std::vector<Transaction> transactions;
    long long accountCounter;

    Bank();
    Bank(const Bank&)            = delete;
    Bank& operator=(const Bank&) = delete;

public:
    static Bank& getInstance();

    // Account management
    std::string generateAccountNumber();
    bool addAccount(std::shared_ptr<Account> account);
    bool removeAccount(const std::string& accNo);
    std::shared_ptr<Account> findAccount(const std::string& accNo);

    // Transaction management
    void addTransaction(const Transaction& tx);
    std::vector<Transaction> getTransactionsByAccount(const std::string& accNo) const;
    std::vector<Transaction> getRecentTransactions(const std::string& accNo, int count) const;

    // Search methods
    std::vector<std::shared_ptr<Account>> searchByName(const std::string& name)   const;
    std::vector<std::shared_ptr<Account>> searchByPhone(const std::string& phone)  const;
    std::vector<std::shared_ptr<Account>> searchByAadhar(const std::string& aadhar) const;
    std::vector<std::shared_ptr<Account>> searchByPAN(const std::string& pan)      const;

    // Report data
    double getTotalBalance()    const;
    int    getTotalAccounts()   const;
    std::shared_ptr<Account> getHighestBalanceAccount() const;
    std::shared_ptr<Account> getLowestBalanceAccount()  const;

    // Getters
    const std::unordered_map<std::string, std::shared_ptr<Account>>& getAllAccounts() const { return accounts; }
    const std::vector<Transaction>& getAllTransactions() const { return transactions; }

    // Persistence
    void loadCounter();
    void saveCounter();
    long long getCounter() const { return accountCounter; }
    void setCounter(long long c) { accountCounter = c; }
    void clearAll();
};
