#pragma once
#include <string>
#include <memory>
#include "Account.h"

class AccountController {
public:
    void createAccount();
    void depositMoney();
    void withdrawMoney();
    void transferMoney();
    void balanceInquiry();
    void deleteAccount();
    void showMiniStatement();
    void showTransactionHistory();

private:
    Customer collectCustomerDetails();
    std::shared_ptr<Account> findAndVerifyAccount(const std::string& prompt);
};
