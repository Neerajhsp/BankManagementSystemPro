#include "Bank.h"
#include "Constants.h"
#include "Utils.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

Bank::Bank() : accountCounter(100000) {
    loadCounter();
}

Bank& Bank::getInstance() {
    static Bank instance;
    return instance;
}

std::string Bank::generateAccountNumber() {
    ++accountCounter;
    saveCounter();
    std::ostringstream oss;
    oss << "SBP" << std::setw(9) << std::setfill('0') << accountCounter;
    return oss.str();
}

bool Bank::addAccount(std::shared_ptr<Account> account) {
    if (!account) return false;
    accounts[account->getAccountNumber()] = account;
    return true;
}

bool Bank::removeAccount(const std::string& accNo) {
    auto it = accounts.find(accNo);
    if (it == accounts.end()) return false;
    it->second->setActive(false);
    return true;
}

std::shared_ptr<Account> Bank::findAccount(const std::string& accNo) {
    auto it = accounts.find(accNo);
    if (it != accounts.end() && it->second->getIsActive())
        return it->second;
    return nullptr;
}

void Bank::addTransaction(const Transaction& tx) {
    transactions.push_back(tx);
}

std::vector<Transaction> Bank::getTransactionsByAccount(const std::string& accNo) const {
    std::vector<Transaction> result;
    for (const auto& tx : transactions) {
        if (tx.getAccountNumber() == accNo) {
            result.push_back(tx);
        }
    }
    return result;
}

std::vector<Transaction> Bank::getRecentTransactions(const std::string& accNo, int count) const {
    auto all = getTransactionsByAccount(accNo);
    if (static_cast<int>(all.size()) <= count) return all;
    return std::vector<Transaction>(all.end() - count, all.end());
}

std::vector<std::shared_ptr<Account>> Bank::searchByName(const std::string& name) const {
    std::vector<std::shared_ptr<Account>> result;
    std::string lname = Utils::toLower(name);
    for (const auto& [accNo, acc] : accounts) {
        if (!acc->getIsActive()) continue;
        if (Utils::toLower(acc->getCustomerConst().getName()).find(lname) != std::string::npos)
            result.push_back(acc);
    }
    return result;
}

std::vector<std::shared_ptr<Account>> Bank::searchByPhone(const std::string& phone) const {
    std::vector<std::shared_ptr<Account>> result;
    for (const auto& [accNo, acc] : accounts) {
        if (!acc->getIsActive()) continue;
        if (acc->getCustomerConst().getPhone() == phone)
            result.push_back(acc);
    }
    return result;
}

std::vector<std::shared_ptr<Account>> Bank::searchByAadhar(const std::string& aadhar) const {
    std::vector<std::shared_ptr<Account>> result;
    for (const auto& [accNo, acc] : accounts) {
        if (!acc->getIsActive()) continue;
        if (acc->getCustomerConst().getAadhar() == aadhar)
            result.push_back(acc);
    }
    return result;
}

std::vector<std::shared_ptr<Account>> Bank::searchByPAN(const std::string& pan) const {
    std::vector<std::shared_ptr<Account>> result;
    std::string upan = Utils::toUpper(pan);
    for (const auto& [accNo, acc] : accounts) {
        if (!acc->getIsActive()) continue;
        if (Utils::toUpper(acc->getCustomerConst().getPAN()) == upan)
            result.push_back(acc);
    }
    return result;
}

double Bank::getTotalBalance() const {
    double total = 0.0;
    for (const auto& [accNo, acc] : accounts) {
        if (acc->getIsActive()) total += acc->getBalance();
    }
    return total;
}

int Bank::getTotalAccounts() const {
    int count = 0;
    for (const auto& [accNo, acc] : accounts) {
        if (acc->getIsActive()) ++count;
    }
    return count;
}

std::shared_ptr<Account> Bank::getHighestBalanceAccount() const {
    std::shared_ptr<Account> best = nullptr;
    double maxBal = -1.0;
    for (const auto& [accNo, acc] : accounts) {
        if (!acc->getIsActive()) continue;
        if (acc->getBalance() > maxBal) {
            maxBal = acc->getBalance();
            best   = acc;
        }
    }
    return best;
}

std::shared_ptr<Account> Bank::getLowestBalanceAccount() const {
    std::shared_ptr<Account> best = nullptr;
    double minBal = std::numeric_limits<double>::max();
    for (const auto& [accNo, acc] : accounts) {
        if (!acc->getIsActive()) continue;
        if (acc->getBalance() < minBal) {
            minBal = acc->getBalance();
            best   = acc;
        }
    }
    return best;
}

void Bank::loadCounter() {
    std::ifstream f(Constants::COUNTER_FILE);
    if (f.is_open()) {
        f >> accountCounter;
    }
}

void Bank::saveCounter() {
    std::ofstream f(Constants::COUNTER_FILE);
    if (f.is_open()) {
        f << accountCounter;
    }
}

void Bank::clearAll() {
    accounts.clear();
    transactions.clear();
}
