#pragma once
#include <string>

namespace Constants {
    // Admin credentials
    inline const std::string ADMIN_USERNAME = "Neeraj kumar";
    inline const std::string ADMIN_PASSWORD = "Neeraj@123";

    // File paths
    inline const std::string DATA_DIR         = "data/";
    inline const std::string REPORTS_DIR      = "reports/";
    inline const std::string ACCOUNTS_FILE    = "data/accounts.dat";
    inline const std::string CUSTOMERS_FILE   = "data/customers.dat";
    inline const std::string TRANSACTIONS_FILE= "data/transactions.dat";
    inline const std::string COUNTER_FILE     = "data/counter.dat";

    // Account settings
    inline const double MIN_SAVINGS_BALANCE  = 1000.0;
    inline const double MIN_CURRENT_BALANCE  = 5000.0;
    inline const double SAVINGS_INTEREST     = 4.0;   // percent per annum
    inline const double CURRENT_INTEREST     = 0.0;
    inline const double MAX_WITHDRAW_LIMIT   = 100000.0;

    // Loan settings
    inline const double MIN_LOAN_BALANCE     = 10000.0;
    inline const double LOAN_MULTIPLIER      = 5.0;
    inline const double LOAN_INTEREST_RATE   = 8.5;   // percent per annum

    // Display
    inline const int MINI_STATEMENT_COUNT    = 5;
    inline const std::string BANK_NAME       = "SecureBank Pro";
    inline const std::string APP_VERSION     = "1.0.0";
}
