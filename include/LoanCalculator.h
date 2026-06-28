#pragma once
#include <string>

class LoanCalculator {
public:
    void calculate();

    static double calculateEMI(double principal, double annualRate, int tenureMonths);
    static double calculateLoanEligibility(double accountBalance);
    static bool   isEligible(double accountBalance);
};
