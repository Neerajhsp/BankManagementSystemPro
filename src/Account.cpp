#include "Account.h"

Account::Account(const std::string& accNo, AccountType type, double openingBalance,
                 const Customer& cust, const std::string& date)
    : accountNumber(accNo), accountType(type), balance(openingBalance),
      customer(cust), createdDate(date), isActive(true) {}
