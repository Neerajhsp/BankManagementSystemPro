#pragma once
#include <string>

enum class AccountType {
    SAVINGS,
    CURRENT
};

enum class TransactionType {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER_IN,
    TRANSFER_OUT,
    INTEREST_CREDIT
};

enum class Gender {
    MALE,
    FEMALE,
    OTHER
};

inline std::string accountTypeToString(AccountType t) {
    switch (t) {
        case AccountType::SAVINGS:  return "Savings";
        case AccountType::CURRENT:  return "Current";
        default:                    return "Unknown";
    }
}

inline std::string transactionTypeToString(TransactionType t) {
    switch (t) {
        case TransactionType::DEPOSIT:       return "Deposit";
        case TransactionType::WITHDRAWAL:    return "Withdrawal";
        case TransactionType::TRANSFER_IN:   return "Transfer In";
        case TransactionType::TRANSFER_OUT:  return "Transfer Out";
        case TransactionType::INTEREST_CREDIT: return "Interest Credit";
        default:                             return "Unknown";
    }
}

inline std::string genderToString(Gender g) {
    switch (g) {
        case Gender::MALE:   return "Male";
        case Gender::FEMALE: return "Female";
        case Gender::OTHER:  return "Other";
        default:             return "Unknown";
    }
}

inline AccountType stringToAccountType(const std::string& s) {
    if (s == "Savings") return AccountType::SAVINGS;
    return AccountType::CURRENT;
}

inline TransactionType stringToTransactionType(const std::string& s) {
    if (s == "Deposit")         return TransactionType::DEPOSIT;
    if (s == "Withdrawal")      return TransactionType::WITHDRAWAL;
    if (s == "Transfer In")     return TransactionType::TRANSFER_IN;
    if (s == "Transfer Out")    return TransactionType::TRANSFER_OUT;
    return TransactionType::INTEREST_CREDIT;
}

inline Gender stringToGender(const std::string& s) {
    if (s == "Male")   return Gender::MALE;
    if (s == "Female") return Gender::FEMALE;
    return Gender::OTHER;
}
