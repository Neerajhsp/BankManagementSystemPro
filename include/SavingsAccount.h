#pragma once
#include "Account.h"
#include "Constants.h"

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount() : interestRate(Constants::SAVINGS_INTEREST) {}
    SavingsAccount(const std::string& accNo, double openingBalance,
                   const Customer& cust, const std::string& date);

    bool deposit(double amount)             override;
    bool withdraw(double amount)            override;
    double getMinimumBalance()              const override { return Constants::MIN_SAVINGS_BALANCE; }
    std::string getAccountTypeName()        const override { return "Savings"; }
    double calculateInterest(int months)    const override;
    std::string serialize()                 const override;

    static SavingsAccount deserialize(const std::string& line);

    double getInterestRate() const { return interestRate; }
};
