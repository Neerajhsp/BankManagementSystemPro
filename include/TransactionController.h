#pragma once
#include <string>
#include "Transaction.h"
#include "Enums.h"

class TransactionController {
public:
    static Transaction recordDeposit(const std::string& accNo, double amount, double balanceAfter);
    static Transaction recordWithdrawal(const std::string& accNo, double amount, double balanceAfter);
    static Transaction recordTransferOut(const std::string& accNo, double amount, double balanceAfter,
                                         const std::string& toAccNo);
    static Transaction recordTransferIn(const std::string& accNo, double amount, double balanceAfter,
                                        const std::string& fromAccNo);
    static Transaction recordInterest(const std::string& accNo, double amount, double balanceAfter);
};
