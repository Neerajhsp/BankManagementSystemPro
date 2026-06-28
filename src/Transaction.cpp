#include "Transaction.h"
#include "Utils.h"
#include <sstream>

Transaction::Transaction(const std::string& txId, const std::string& accNo,
                         TransactionType t, double amt, double bal,
                         const std::string& ts, const std::string& desc)
    : transactionId(txId), accountNumber(accNo), type(t),
      amount(amt), balanceAfter(bal), timestamp(ts), description(desc) {}

std::string Transaction::serialize() const {
    // Format: txId|accNo|type|amount|balanceAfter|timestamp|description
    std::ostringstream oss;
    oss << transactionId << "|"
        << accountNumber << "|"
        << transactionTypeToString(type) << "|"
        << std::fixed << amount << "|"
        << std::fixed << balanceAfter << "|"
        << timestamp << "|"
        << description;
    return oss.str();
}

Transaction Transaction::deserialize(const std::string& line) {
    auto parts = Utils::split(line, '|');
    if (parts.size() < 7) return Transaction();
    Transaction tx;
    tx.transactionId  = parts[0];
    tx.accountNumber  = parts[1];
    tx.type           = stringToTransactionType(parts[2]);
    tx.amount         = std::stod(parts[3]);
    tx.balanceAfter   = std::stod(parts[4]);
    tx.timestamp      = parts[5];
    tx.description    = parts[6];
    return tx;
}
