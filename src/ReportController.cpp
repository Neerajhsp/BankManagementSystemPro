#include "ReportController.h"
#include "Bank.h"
#include "UIView.h"
#include "Utils.h"
#include "FileHandler.h"
#include <iostream>

// -------------------------------------------------------
// Monthly Report
// -------------------------------------------------------
void ReportController::showMonthlyReport() {
    UIView::displayHeader();
    std::cout << "  === MONTHLY REPORT ===\n";

    Bank& bank = Bank::getInstance();

    double totalBalance  = bank.getTotalBalance();
    int    totalAccounts = bank.getTotalAccounts();
    auto   highest       = bank.getHighestBalanceAccount();
    auto   lowest        = bank.getLowestBalanceAccount();

    UIView::displayMonthlyReport(totalBalance, totalAccounts, highest, lowest);

    // Per-type breakdown
    int savingsCount = 0, currentCount = 0;
    double savingsTotal = 0.0, currentTotal = 0.0;
    for (const auto& [accNo, acc] : bank.getAllAccounts()) {
        if (!acc->getIsActive()) continue;
        if (acc->getAccountType() == AccountType::SAVINGS) {
            savingsCount++;
            savingsTotal += acc->getBalance();
        } else {
            currentCount++;
            currentTotal += acc->getBalance();
        }
    }

    Utils::printSeparator('-');
    std::cout << "  Account Type Breakdown:\n";
    std::cout << "    Savings Accounts : " << savingsCount
              << " | Total: " << Utils::formatCurrency(savingsTotal) << "\n";
    std::cout << "    Current Accounts : " << currentCount
              << " | Total: " << Utils::formatCurrency(currentTotal) << "\n";
    Utils::printSeparator('=');

    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Export Monthly Report
// -------------------------------------------------------
void ReportController::exportReport() {
    UIView::displayHeader();
    std::cout << "  === EXPORT MONTHLY REPORT ===\n\n";

    std::string filename = "monthly_report_" + Utils::getCurrentDate() + ".txt";
    // Replace : and spaces with _
    for (char& c : filename) if (c == ' ' || c == ':') c = '_';

    if (FileHandler::exportMonthlyReport(filename)) {
        UIView::displaySuccess("Report exported to reports/" + filename);
    } else {
        UIView::displayError("Failed to export report. Check write permissions.");
    }
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Export Transaction History for an Account
// -------------------------------------------------------
void ReportController::exportTransactionHistory() {
    UIView::displayHeader();
    std::cout << "  === EXPORT TRANSACTION HISTORY ===\n\n";

    std::string accNo = Utils::getStringInput("  Account Number   : ");
    auto acc = Bank::getInstance().findAccount(accNo);
    if (!acc) {
        UIView::displayError("Account not found.");
        Utils::pressEnterToContinue();
        return;
    }

    std::string filename = "transactions_" + accNo + "_" + Utils::getCurrentDate() + ".txt";

    if (FileHandler::exportTransactionHistory(accNo, filename)) {
        UIView::displaySuccess("Transaction history exported to reports/" + filename);
    } else {
        UIView::displayError("Failed to export. Check account or write permissions.");
    }
    Utils::pressEnterToContinue();
}
