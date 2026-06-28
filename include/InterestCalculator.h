#pragma once

class InterestCalculator {
public:
    void calculate();

    static double simpleInterest(double principal, double rate, int months);
    static double compoundInterest(double principal, double rate, int months);
    static double maturityAmount(double principal, double rate, int months, bool compound = true);
};
