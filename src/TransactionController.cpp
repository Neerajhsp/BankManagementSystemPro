#include "TransactionController.h"
#include "Bank.h"
#include "Utils.h"

Transaction TransactionController::recordDeposit(const std::string& accNo, double amount,
                                                   double balanceAfter) {
    Transaction tx(Utils::generateTransactionId(), accNo, TransactionType::DEPOSIT,
                   amount, balanceAfter, Utils::getCurrentTimestamp(), "Cash Deposit");
    Bank::getInstance().addTransaction(tx);
    return tx;
}

Transaction TransactionController::recordWithdrawal(const std::string& accNo, double amount,
                                                      double balanceAfter) {
    Transaction tx(Utils::generateTransactionId(), accNo, TransactionType::WITHDRAWAL,
                   amount, balanceAfter, Utils::getCurrentTimestamp(), "Cash Withdrawal");
    Bank::getInstance().addTransaction(tx);
    return tx;
}

Transaction TransactionController::recordTransferOut(const std::string& accNo, double amount,
                                                      double balanceAfter, const std::string& toAccNo) {
    Transaction tx(Utils::generateTransactionId(), accNo, TransactionType::TRANSFER_OUT,
                   amount, balanceAfter, Utils::getCurrentTimestamp(),
                   "Transfer to " + toAccNo);
    Bank::getInstance().addTransaction(tx);
    return tx;
}

Transaction TransactionController::recordTransferIn(const std::string& accNo, double amount,
                                                     double balanceAfter, const std::string& fromAccNo) {
    Transaction tx(Utils::generateTransactionId(), accNo, TransactionType::TRANSFER_IN,
                   amount, balanceAfter, Utils::getCurrentTimestamp(),
                   "Transfer from " + fromAccNo);
    Bank::getInstance().addTransaction(tx);
    return tx;
}

Transaction TransactionController::recordInterest(const std::string& accNo, double amount,
                                                   double balanceAfter) {
    Transaction tx(Utils::generateTransactionId(), accNo, TransactionType::INTEREST_CREDIT,
                   amount, balanceAfter, Utils::getCurrentTimestamp(), "Interest Credit");
    Bank::getInstance().addTransaction(tx);
    return tx;
}
