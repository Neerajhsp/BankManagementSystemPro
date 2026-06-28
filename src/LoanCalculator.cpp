#include "LoanCalculator.h"
#include "UIView.h"
#include "Utils.h"
#include "Constants.h"
#include "Bank.h"
#include <cmath>
#include <iostream>

double LoanCalculator::calculateEMI(double principal, double annualRate, int tenureMonths) {
    if (annualRate == 0.0) return principal / tenureMonths;
    double r = annualRate / 100.0 / 12.0;
    double emi = principal * r * std::pow(1 + r, tenureMonths) /
                 (std::pow(1 + r, tenureMonths) - 1);
    return emi;
}

double LoanCalculator::calculateLoanEligibility(double accountBalance) {
    return accountBalance * Constants::LOAN_MULTIPLIER;
}

bool LoanCalculator::isEligible(double accountBalance) {
    return accountBalance >= Constants::MIN_LOAN_BALANCE;
}

void LoanCalculator::calculate() {
    UIView::displayHeader();
    std::cout << "  === LOAN ELIGIBILITY CALCULATOR ===\n\n";

    std::cout << "  Check By:\n";
    std::cout << "   1. Enter Account Number\n";
    std::cout << "   2. Enter Balance Manually\n\n";

    int mode = Utils::getIntInput("  Choose [1-2]: ", 1, 2);

    double balance = 0.0;

    if (mode == 1) {
        std::string accNo = Utils::getStringInput("  Account Number   : ");
        auto acc = Bank::getInstance().findAccount(accNo);
        if (!acc) {
            UIView::displayError("Account not found.");
            Utils::pressEnterToContinue();
            return;
        }
        balance = acc->getBalance();
        std::cout << "  Account Holder   : " << acc->getCustomerConst().getName() << "\n";
        std::cout << "  Current Balance  : " << Utils::formatCurrency(balance) << "\n";
    } else {
        balance = Utils::getDoubleInput("  Enter Balance    : Rs. ", 0.0);
    }

    double loanAmount = calculateLoanEligibility(balance);
    bool eligible     = isEligible(balance);

    int tenureMonths = 0;
    double emi = 0.0;
    if (eligible) {
        tenureMonths = Utils::getIntInput("  Loan Tenure (months) [6-360]: ", 6, 360);
        emi = calculateEMI(loanAmount, Constants::LOAN_INTEREST_RATE, tenureMonths);
    }

    UIView::displayLoanEligibility(balance, loanAmount, emi, eligible);

    if (eligible) {
        double totalPayable = emi * tenureMonths;
        double totalInterest = totalPayable - loanAmount;

        std::cout << "\n  EMI Schedule Summary:\n";
        Utils::printSeparator('-', 55);
        std::cout << "  Loan Amount      : " << Utils::formatCurrency(loanAmount)   << "\n";
        std::cout << "  Interest Rate    : " << Constants::LOAN_INTEREST_RATE       << "% p.a.\n";
        std::cout << "  Tenure           : " << tenureMonths                        << " months\n";
        std::cout << "  Monthly EMI      : " << Utils::formatCurrency(emi)          << "\n";
        std::cout << "  Total Interest   : " << Utils::formatCurrency(totalInterest)<< "\n";
        std::cout << "  Total Payable    : " << Utils::formatCurrency(totalPayable) << "\n";
        Utils::printSeparator('-', 55);
    }
    Utils::pressEnterToContinue();
}
