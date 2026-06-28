#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Account.h"
#include "Transaction.h"

class UIView {
public:
    // Application chrome
    static void displayHeader();
    static void displayFooter();
    static void displayLoginScreen();
    static void displayMainMenu();
    static void displayExitConfirmation();

    // Account views
    static void displayAccountDetails(const std::shared_ptr<Account>& acc);
    static void displayAccountList(const std::vector<std::shared_ptr<Account>>& accounts);
    static void displayBalance(const std::shared_ptr<Account>& acc);

    // Transaction views
    static void displayTransaction(const Transaction& tx);
    static void displayTransactionHistory(const std::vector<Transaction>& txs,
                                          const std::string& accNo);
    static void displayMiniStatement(const std::vector<Transaction>& txs,
                                     const std::string& accNo, double currentBalance);

    // Report views
    static void displayMonthlyReport(double totalBalance, int totalAccounts,
                                     const std::shared_ptr<Account>& highest,
                                     const std::shared_ptr<Account>& lowest);

    // Calculator views
    static void displayInterestResult(double principal, double rate,
                                      double interest, double maturity, int months);
    static void displayLoanEligibility(double balance, double loanAmount,
                                       double emi, bool eligible);

    // Search views
    static void displaySearchMenu();
    static void displaySearchResults(const std::vector<std::shared_ptr<Account>>& results);

    // Success / Error
    static void displaySuccess(const std::string& message);
    static void displayError(const std::string& message);
    static void displayInfo(const std::string& message);
};
