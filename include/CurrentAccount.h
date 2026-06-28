#pragma once
#include "Account.h"
#include "Constants.h"

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount() : overdraftLimit(0.0) {}
    CurrentAccount(const std::string& accNo, double openingBalance,
                   const Customer& cust, const std::string& date);

    bool deposit(double amount)             override;
    bool withdraw(double amount)            override;
    double getMinimumBalance()              const override { return Constants::MIN_CURRENT_BALANCE; }
    std::string getAccountTypeName()        const override { return "Current"; }
    double calculateInterest(int /*months*/) const override { return 0.0; }
    std::string serialize()                 const override;

    static CurrentAccount deserialize(const std::string& line);

    double getOverdraftLimit() const { return overdraftLimit; }
    void   setOverdraftLimit(double limit) { overdraftLimit = limit; }
};
