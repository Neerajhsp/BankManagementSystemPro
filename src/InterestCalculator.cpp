#include "InterestCalculator.h"
#include "UIView.h"
#include "Utils.h"
#include "Constants.h"
#include <cmath>
#include <iostream>

double InterestCalculator::simpleInterest(double principal, double rate, int months) {
    return principal * (rate / 100.0) * (months / 12.0);
}

double InterestCalculator::compoundInterest(double principal, double rate, int months) {
    double r = rate / 100.0 / 12.0;
    return principal * (std::pow(1.0 + r, months) - 1.0);
}

double InterestCalculator::maturityAmount(double principal, double rate, int months, bool compound) {
    if (compound)
        return principal + compoundInterest(principal, rate, months);
    else
        return principal + simpleInterest(principal, rate, months);
}

void InterestCalculator::calculate() {
    UIView::displayHeader();
    std::cout << "  === INTEREST CALCULATOR ===\n\n";

    std::cout << "  Calculation Type:\n";
    std::cout << "   1. Savings Account Interest (Compound, 4% p.a.)\n";
    std::cout << "   2. Fixed Deposit Calculator (Custom Rate)\n";
    std::cout << "   3. Simple Interest Calculator\n\n";

    int type = Utils::getIntInput("  Choose [1-3]: ", 1, 3);

    double principal = Utils::getDoubleInput("  Principal Amount : Rs. ", 1.0);
    double rate;
    bool compound = true;

    if (type == 1) {
        rate = Constants::SAVINGS_INTEREST;
        std::cout << "  Interest Rate    : " << rate << "% p.a. (Compound)\n";
    } else if (type == 2) {
        rate = Utils::getDoubleInput("  Annual Rate (%)  : ", 0.1);
        compound = true;
    } else {
        rate = Utils::getDoubleInput("  Annual Rate (%)  : ", 0.1);
        compound = false;
    }

    int months = Utils::getIntInput("  Period (months)  : ", 1, 600);

    double interest = compound ? compoundInterest(principal, rate, months)
                               : simpleInterest(principal, rate, months);
    double maturity = principal + interest;

    UIView::displayInterestResult(principal, rate, interest, maturity, months);

    // Yearly breakdown
    std::cout << "\n  Yearly Breakdown:\n";
    Utils::printSeparator('-', 50);
    std::cout << "  " << "Year" << "\t" << "Interest" << "\t" << "Maturity\n";
    Utils::printSeparator('-', 50);
    for (int y = 1; y <= (months / 12); ++y) {
        int m = y * 12;
        double iv = compound ? compoundInterest(principal, rate, m)
                             : simpleInterest(principal, rate, m);
        std::cout << "  Year " << y
                  << "\t" << Utils::formatCurrency(iv)
                  << "\t" << Utils::formatCurrency(principal + iv) << "\n";
    }
    int rem = months % 12;
    if (rem > 0) {
        std::cout << "  +" << rem << " mo"
                  << "\t" << Utils::formatCurrency(interest)
                  << "\t" << Utils::formatCurrency(maturity) << "\n";
    }
    Utils::printSeparator('-', 50);
    Utils::pressEnterToContinue();
}
