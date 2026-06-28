#pragma once
#include <string>
#include "Enums.h"

class Transaction {
private:
    std::string transactionId;
    std::string accountNumber;
    TransactionType type;
    double amount;
    double balanceAfter;
    std::string timestamp;
    std::string description;

public:
    Transaction() = default;
    Transaction(const std::string& txId, const std::string& accNo,
                TransactionType type, double amount, double balanceAfter,
                const std::string& timestamp, const std::string& desc = "");

    // Getters
    std::string getTransactionId()  const { return transactionId; }
    std::string getAccountNumber()  const { return accountNumber; }
    TransactionType getType()       const { return type; }
    double getAmount()              const { return amount; }
    double getBalanceAfter()        const { return balanceAfter; }
    std::string getTimestamp()      const { return timestamp; }
    std::string getDescription()    const { return description; }

    // Serialization
    std::string serialize() const;
    static Transaction deserialize(const std::string& line);
};
