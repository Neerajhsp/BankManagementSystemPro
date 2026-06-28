#include "CurrentAccount.h"
#include "Utils.h"
#include <sstream>

CurrentAccount::CurrentAccount(const std::string& accNo, double openingBalance,
                               const Customer& cust, const std::string& date)
    : Account(accNo, AccountType::CURRENT, openingBalance, cust, date),
      overdraftLimit(0.0) {}

bool CurrentAccount::deposit(double amount) {
    if (amount <= 0.0) return false;
    balance += amount;
    return true;
}

bool CurrentAccount::withdraw(double amount) {
    if (amount <= 0.0) return false;
    if ((balance - amount) < (Constants::MIN_CURRENT_BALANCE - overdraftLimit)) return false;
    balance -= amount;
    return true;
}

std::string CurrentAccount::serialize() const {
    std::ostringstream oss;
    oss << "CURRENT|"
        << accountNumber << "|"
        << std::fixed << balance << "|"
        << createdDate << "|"
        << (isActive ? "1" : "0") << "|"
        << std::fixed << overdraftLimit << "|"
        << customer.serialize();
    return oss.str();
}

CurrentAccount CurrentAccount::deserialize(const std::string& line) {
    auto parts = Utils::split(line, '|');
    if (parts.size() < 13) {
        return CurrentAccount();
    }
    std::string customerData = Utils::join(
        std::vector<std::string>(parts.begin() + 6, parts.end()), '|');
    Customer cust = Customer::deserialize(customerData);

    CurrentAccount acc(parts[1], std::stod(parts[2]), cust, parts[3]);
    acc.isActive       = (parts[4] == "1");
    acc.overdraftLimit = std::stod(parts[5]);
    return acc;
}
