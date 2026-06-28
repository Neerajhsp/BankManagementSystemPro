#pragma once
#include <string>
#include <vector>
#include "Customer.h"
#include "Transaction.h"
#include "Enums.h"

class Account {
protected:
    std::string accountNumber;
    AccountType accountType;
    double balance;
    Customer customer;
    std::string createdDate;
    bool isActive;

public:
    Account() : balance(0.0), isActive(true) {}
    Account(const std::string& accNo, AccountType type, double openingBalance,
            const Customer& cust, const std::string& date);
    virtual ~Account() = default;

    // Pure virtual methods
    virtual bool deposit(double amount)                         = 0;
    virtual bool withdraw(double amount)                        = 0;
    virtual double getMinimumBalance()                          const = 0;
    virtual std::string getAccountTypeName()                    const = 0;
    virtual double calculateInterest(int months)                const = 0;
    virtual std::string serialize()                             const = 0;

    // Getters
    std::string  getAccountNumber() const { return accountNumber; }
    AccountType  getAccountType()   const { return accountType; }
    double       getBalance()       const { return balance; }
    Customer&    getCustomer()            { return customer; }
    const Customer& getCustomerConst()  const { return customer; }
    std::string  getCreatedDate()   const { return createdDate; }
    bool         getIsActive()      const { return isActive; }

    // Setters
    void setBalance(double b)         { balance = b; }
    void setActive(bool a)            { isActive = a; }
    void setCustomer(const Customer& c) { customer = c; }
};
