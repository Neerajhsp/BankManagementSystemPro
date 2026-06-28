#include "SavingsAccount.h"
#include "Utils.h"
#include <sstream>
#include <cmath>

SavingsAccount::SavingsAccount(const std::string& accNo, double openingBalance,
                               const Customer& cust, const std::string& date)
    : Account(accNo, AccountType::SAVINGS, openingBalance, cust, date),
      interestRate(Constants::SAVINGS_INTEREST) {}

bool SavingsAccount::deposit(double amount) {
    if (amount <= 0.0) return false;
    balance += amount;
    return true;
}

bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0.0) return false;
    if ((balance - amount) < Constants::MIN_SAVINGS_BALANCE) return false;
    balance -= amount;
    return true;
}

double SavingsAccount::calculateInterest(int months) const {
    // Compound interest monthly
    double r = interestRate / 100.0 / 12.0;
    return balance * (std::pow(1 + r, months) - 1);
}

std::string SavingsAccount::serialize() const {
    std::ostringstream oss;
    oss << "SAVINGS|"
        << accountNumber << "|"
        << std::fixed << balance << "|"
        << createdDate << "|"
        << (isActive ? "1" : "0") << "|"
        << std::fixed << interestRate << "|"
        << customer.serialize();
    return oss.str();
}

SavingsAccount SavingsAccount::deserialize(const std::string& line) {
    // Format: SAVINGS|accNo|balance|date|active|rate|customerSerialized...
    auto parts = Utils::split(line, '|');
    if (parts.size() < 13) {
        return SavingsAccount();
    }
    // Customer data starts at index 6
    std::string customerData = Utils::join(
        std::vector<std::string>(parts.begin() + 6, parts.end()), '|');
    Customer cust = Customer::deserialize(customerData);

    SavingsAccount acc(parts[1], std::stod(parts[2]), cust, parts[3]);
    acc.isActive      = (parts[4] == "1");
    acc.interestRate  = std::stod(parts[5]);
    return acc;
}
