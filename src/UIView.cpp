#include "UIView.h"
#include "Constants.h"
#include "Utils.h"
#include "Enums.h"
#include <iostream>
#include <iomanip>

void UIView::displayHeader() {
    Utils::clearScreen();
    Utils::printSeparator('=');
    Utils::printCentered(Constants::BANK_NAME);
    Utils::printCentered("Banking Management System v" + Constants::APP_VERSION);
    Utils::printSeparator('=');
    std::cout << "\n";
}

void UIView::displayFooter() {
    std::cout << "\n";
    Utils::printSeparator('-');
}

void UIView::displayLoginScreen() {
    displayHeader();
    Utils::printCentered("[ ADMIN LOGIN ]");
    std::cout << "\n";
}

void UIView::displayMainMenu() {
    displayHeader();
    Utils::printCentered("[ MAIN MENU ]");
    std::cout << "\n";
    std::cout << "  ACCOUNT OPERATIONS\n";
    Utils::printSeparator('-', 50);
    std::cout << "   1. Create New Account\n";
    std::cout << "   2. Deposit Money\n";
    std::cout << "   3. Withdraw Money\n";
    std::cout << "   4. Transfer Money\n";
    std::cout << "   5. Balance Inquiry\n";
    std::cout << "   6. Mini Statement\n";
    std::cout << "   7. Transaction History\n";
    std::cout << "\n  CUSTOMER OPERATIONS\n";
    Utils::printSeparator('-', 50);
    std::cout << "   8. Update Customer Details\n";
    std::cout << "   9. Delete Account\n";
    std::cout << "  10. Search Customer\n";
    std::cout << "  11. View All Accounts\n";
    std::cout << "\n  ANALYTICS & REPORTS\n";
    Utils::printSeparator('-', 50);
    std::cout << "  12. Interest Calculator\n";
    std::cout << "  13. Loan Eligibility Calculator\n";
    std::cout << "  14. Monthly Report\n";
    std::cout << "  15. Export Report\n";
    std::cout << "\n  SYSTEM\n";
    Utils::printSeparator('-', 50);
    std::cout << "   0. Logout & Exit\n";
    std::cout << "\n";
    Utils::printSeparator('=');
}

void UIView::displayExitConfirmation() {
    std::cout << "\n";
    Utils::printSeparator('*');
    Utils::printCentered("Thank you for using " + Constants::BANK_NAME);
    Utils::printCentered("Have a great day!");
    Utils::printSeparator('*');
    std::cout << "\n";
}

void UIView::displayAccountDetails(const std::shared_ptr<Account>& acc) {
    if (!acc) return;
    const Customer& c = acc->getCustomerConst();
    std::cout << "\n";
    Utils::printSeparator('-');
    Utils::printCentered("ACCOUNT DETAILS");
    Utils::printSeparator('-');
    std::cout << "  Account Number   : " << acc->getAccountNumber()       << "\n";
    std::cout << "  Account Type     : " << acc->getAccountTypeName()      << "\n";
    std::cout << "  Status           : " << (acc->getIsActive() ? "Active" : "Closed") << "\n";
    std::cout << "  Balance          : " << Utils::formatCurrency(acc->getBalance()) << "\n";
    std::cout << "  Date Opened      : " << acc->getCreatedDate()          << "\n";
    Utils::printSeparator('-');
    Utils::printCentered("CUSTOMER INFORMATION");
    Utils::printSeparator('-');
    std::cout << "  Name             : " << c.getName()                    << "\n";
    std::cout << "  Age              : " << c.getAge()                     << "\n";
    std::cout << "  Gender           : " << genderToString(c.getGender())  << "\n";
    std::cout << "  Phone            : " << c.getPhone()                   << "\n";
    std::cout << "  Email            : " << c.getEmail()                   << "\n";
    std::cout << "  Address          : " << c.getAddress()                 << "\n";
    std::cout << "  Aadhar Number    : " << c.getAadhar()                  << "\n";
    std::cout << "  PAN Number       : " << c.getPAN()                     << "\n";
    Utils::printSeparator('-');
}

void UIView::displayAccountList(const std::vector<std::shared_ptr<Account>>& accounts) {
    if (accounts.empty()) {
        displayInfo("No accounts found.");
        return;
    }
    std::cout << "\n";
    Utils::printSeparator('-');
    std::cout << "  " << std::left
              << std::setw(16) << "Account No"
              << std::setw(10) << "Type"
              << std::setw(25) << "Name"
              << std::setw(18) << "Balance"
              << "Phone\n";
    Utils::printSeparator('-');
    for (const auto& acc : accounts) {
        if (!acc->getIsActive()) continue;
        std::cout << "  " << std::left
                  << std::setw(16) << acc->getAccountNumber()
                  << std::setw(10) << acc->getAccountTypeName()
                  << std::setw(25) << acc->getCustomerConst().getName()
                  << std::setw(18) << Utils::formatCurrency(acc->getBalance())
                  << acc->getCustomerConst().getPhone() << "\n";
    }
    Utils::printSeparator('-');
}

void UIView::displayBalance(const std::shared_ptr<Account>& acc) {
    std::cout << "\n";
    Utils::printSeparator('-');
    Utils::printCentered("BALANCE INQUIRY");
    Utils::printSeparator('-');
    std::cout << "  Account Number   : " << acc->getAccountNumber()        << "\n";
    std::cout << "  Account Holder   : " << acc->getCustomerConst().getName() << "\n";
    std::cout << "  Account Type     : " << acc->getAccountTypeName()       << "\n";
    std::cout << "  Available Balance: " << Utils::formatCurrency(acc->getBalance()) << "\n";
    std::cout << "  As of            : " << Utils::getCurrentTimestamp()    << "\n";
    Utils::printSeparator('-');
}

void UIView::displayTransaction(const Transaction& tx) {
    std::cout << "  " << std::left
              << std::setw(15) << tx.getTransactionId()
              << std::setw(22) << tx.getTimestamp()
              << std::setw(18) << transactionTypeToString(tx.getType())
              << std::setw(16) << Utils::formatCurrency(tx.getAmount())
              << Utils::formatCurrency(tx.getBalanceAfter()) << "\n";
}

void UIView::displayTransactionHistory(const std::vector<Transaction>& txs,
                                        const std::string& accNo) {
    std::cout << "\n";
    Utils::printSeparator('-');
    Utils::printCentered("TRANSACTION HISTORY - " + accNo);
    Utils::printSeparator('-');
    if (txs.empty()) {
        displayInfo("No transactions found.");
        return;
    }
    std::cout << "  " << std::left
              << std::setw(15) << "TxID"
              << std::setw(22) << "Timestamp"
              << std::setw(18) << "Type"
              << std::setw(16) << "Amount"
              << "Balance After\n";
    Utils::printSeparator('-');
    for (const auto& tx : txs) {
        displayTransaction(tx);
    }
    Utils::printSeparator('-');
}

void UIView::displayMiniStatement(const std::vector<Transaction>& txs,
                                   const std::string& accNo, double currentBalance) {
    std::cout << "\n";
    Utils::printSeparator('-');
    Utils::printCentered("MINI STATEMENT - " + accNo);
    Utils::printSeparator('-');
    std::cout << "  Current Balance : " << Utils::formatCurrency(currentBalance) << "\n";
    Utils::printSeparator('-');
    if (txs.empty()) {
        displayInfo("No recent transactions.");
        return;
    }
    std::cout << "  Last " << txs.size() << " Transactions:\n\n";
    std::cout << "  " << std::left
              << std::setw(22) << "Date/Time"
              << std::setw(18) << "Type"
              << std::setw(16) << "Amount"
              << "Balance\n";
    Utils::printSeparator('-');
    for (const auto& tx : txs) {
        displayTransaction(tx);
    }
    Utils::printSeparator('-');
}

void UIView::displayMonthlyReport(double totalBalance, int totalAccounts,
                                   const std::shared_ptr<Account>& highest,
                                   const std::shared_ptr<Account>& lowest) {
    std::cout << "\n";
    Utils::printSeparator('=');
    Utils::printCentered(Constants::BANK_NAME + " - MONTHLY REPORT");
    Utils::printSeparator('=');
    std::cout << "  Generated On     : " << Utils::getCurrentTimestamp() << "\n\n";
    std::cout << "  Total Accounts   : " << totalAccounts << "\n";
    std::cout << "  Total Balance    : " << Utils::formatCurrency(totalBalance) << "\n";

    if (highest) {
        Utils::printSeparator('-');
        std::cout << "  Highest Balance Account:\n";
        std::cout << "    Account No   : " << highest->getAccountNumber()         << "\n";
        std::cout << "    Holder Name  : " << highest->getCustomerConst().getName() << "\n";
        std::cout << "    Balance      : " << Utils::formatCurrency(highest->getBalance()) << "\n";
    }
    if (lowest) {
        Utils::printSeparator('-');
        std::cout << "  Lowest Balance Account:\n";
        std::cout << "    Account No   : " << lowest->getAccountNumber()          << "\n";
        std::cout << "    Holder Name  : " << lowest->getCustomerConst().getName() << "\n";
        std::cout << "    Balance      : " << Utils::formatCurrency(lowest->getBalance()) << "\n";
    }
    Utils::printSeparator('=');
}

void UIView::displayInterestResult(double principal, double rate,
                                    double interest, double maturity, int months) {
    std::cout << "\n";
    Utils::printSeparator('-');
    Utils::printCentered("INTEREST CALCULATION RESULT");
    Utils::printSeparator('-');
    std::cout << "  Principal Amount : " << Utils::formatCurrency(principal)  << "\n";
    std::cout << "  Annual Rate      : " << Utils::formatDouble(rate) << "%\n";
    std::cout << "  Period           : " << months << " months\n";
    Utils::printSeparator('-');
    std::cout << "  Interest Earned  : " << Utils::formatCurrency(interest)   << "\n";
    std::cout << "  Maturity Amount  : " << Utils::formatCurrency(maturity)   << "\n";
    Utils::printSeparator('-');
}

void UIView::displayLoanEligibility(double balance, double loanAmount,
                                     double emi, bool eligible) {
    std::cout << "\n";
    Utils::printSeparator('-');
    Utils::printCentered("LOAN ELIGIBILITY RESULT");
    Utils::printSeparator('-');
    std::cout << "  Account Balance  : " << Utils::formatCurrency(balance)    << "\n";
    std::cout << "  Eligible Amount  : " << Utils::formatCurrency(loanAmount) << "\n";
    if (eligible) {
        std::cout << "  Estimated EMI    : " << Utils::formatCurrency(emi) << " / month\n";
        std::cout << "\n  Status           : [ELIGIBLE] Congratulations!\n";
    } else {
        std::cout << "\n  Status           : [NOT ELIGIBLE]\n";
        std::cout << "  Reason           : Minimum balance required is "
                  << Utils::formatCurrency(Constants::MIN_LOAN_BALANCE) << "\n";
    }
    Utils::printSeparator('-');
}

void UIView::displaySearchMenu() {
    std::cout << "\n  Search Customer By:\n";
    Utils::printSeparator('-', 40);
    std::cout << "   1. Account Number\n";
    std::cout << "   2. Phone Number\n";
    std::cout << "   3. Aadhar Number\n";
    std::cout << "   4. PAN Number\n";
    std::cout << "   5. Name\n";
    std::cout << "   0. Back\n";
}

void UIView::displaySearchResults(const std::vector<std::shared_ptr<Account>>& results) {
    if (results.empty()) {
        displayError("No matching records found.");
        return;
    }
    std::cout << "\n  Found " << results.size() << " record(s):\n";
    displayAccountList(results);
}

void UIView::displaySuccess(const std::string& message) {
    std::cout << "\n  [SUCCESS] " << message << "\n";
}

void UIView::displayError(const std::string& message) {
    std::cout << "\n  [ERROR]   " << message << "\n";
}

void UIView::displayInfo(const std::string& message) {
    std::cout << "\n  [INFO]    " << message << "\n";
}
