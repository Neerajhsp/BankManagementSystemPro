#include "AccountController.h"
#include "Bank.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "UIView.h"
#include "Utils.h"
#include "Constants.h"
#include "FileHandler.h"
#include "TransactionController.h"
#include <iostream>
#include <memory>

// -------------------------------------------------------
// Helper: collect customer information from console
// -------------------------------------------------------
Customer AccountController::collectCustomerDetails() {
    std::cout << "\n  === Customer Details ===\n\n";

    std::string name = Utils::getStringInput("  Full Name        : ");

    int age = Utils::getIntInput("  Age              : ", 18, 120);

    std::cout << "  Gender (1=Male, 2=Female, 3=Other): ";
    int gChoice = Utils::getIntInput("", 1, 3);
    Gender gender = (gChoice == 1) ? Gender::MALE :
                    (gChoice == 2) ? Gender::FEMALE : Gender::OTHER;

    std::string phone;
    while (true) {
        phone = Utils::getStringInput("  Phone (10 digits): ");
        if (Utils::isValidPhone(phone)) break;
        UIView::displayError("Invalid phone number. Must be 10 digits starting with 6-9.");
    }

    std::string email;
    while (true) {
        email = Utils::getStringInput("  Email Address    : ");
        if (Utils::isValidEmail(email)) break;
        UIView::displayError("Invalid email address format.");
    }

    std::string address = Utils::getStringInput("  Address          : ");

    std::string aadhar;
    while (true) {
        aadhar = Utils::getStringInput("  Aadhar Number    : ");
        if (Utils::isValidAadhar(aadhar)) break;
        UIView::displayError("Invalid Aadhar number. Must be 12 digits.");
    }

    std::string pan;
    while (true) {
        pan = Utils::getStringInput("  PAN Number       : ");
        pan = Utils::toUpper(pan);
        if (Utils::isValidPAN(pan)) break;
        UIView::displayError("Invalid PAN number. Format: ABCDE1234F");
    }

    return Customer(name, age, gender, phone, email, address, aadhar, pan);
}

// -------------------------------------------------------
// Helper: find account by number from user input
// -------------------------------------------------------
std::shared_ptr<Account> AccountController::findAndVerifyAccount(const std::string& prompt) {
    std::string accNo = Utils::getStringInput(prompt);
    auto acc = Bank::getInstance().findAccount(accNo);
    if (!acc) {
        UIView::displayError("Account not found or account is closed.");
        return nullptr;
    }
    return acc;
}

// -------------------------------------------------------
// Create New Account
// -------------------------------------------------------
void AccountController::createAccount() {
    UIView::displayHeader();
    std::cout << "  === CREATE NEW ACCOUNT ===\n\n";
    std::cout << "  Account Type:\n";
    std::cout << "   1. Savings Account (Min balance: "
              << Utils::formatCurrency(Constants::MIN_SAVINGS_BALANCE) << ")\n";
    std::cout << "   2. Current Account (Min balance: "
              << Utils::formatCurrency(Constants::MIN_CURRENT_BALANCE) << ")\n\n";

    int typeChoice = Utils::getIntInput("  Choose type [1-2]: ", 1, 2);

    Customer customer = collectCustomerDetails();

    double minBalance = (typeChoice == 1) ? Constants::MIN_SAVINGS_BALANCE
                                          : Constants::MIN_CURRENT_BALANCE;
    double openingBalance = 0.0;
    while (true) {
        openingBalance = Utils::getDoubleInput("\n  Opening Balance  : Rs. ");
        if (openingBalance >= minBalance) break;
        UIView::displayError("Opening balance must be at least " +
                              Utils::formatCurrency(minBalance));
    }

    std::string accNo = Bank::getInstance().generateAccountNumber();
    std::string date  = Utils::getCurrentDate();
    std::shared_ptr<Account> account;

    if (typeChoice == 1) {
        account = std::make_shared<SavingsAccount>(accNo, openingBalance, customer, date);
    } else {
        account = std::make_shared<CurrentAccount>(accNo, openingBalance, customer, date);
    }

    Bank::getInstance().addAccount(account);
    TransactionController::recordDeposit(accNo, openingBalance, openingBalance);
    FileHandler::saveAccounts();
    FileHandler::saveTransactions();

    UIView::displaySuccess("Account created successfully!");
    std::cout << "\n  New Account Number : " << accNo << "\n";
    std::cout << "  Account Holder     : " << customer.getName() << "\n";
    std::cout << "  Account Type       : "
              << (typeChoice == 1 ? "Savings" : "Current") << "\n";
    std::cout << "  Opening Balance    : " << Utils::formatCurrency(openingBalance) << "\n";

    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Deposit Money
// -------------------------------------------------------
void AccountController::depositMoney() {
    UIView::displayHeader();
    std::cout << "  === DEPOSIT MONEY ===\n\n";

    auto acc = findAndVerifyAccount("  Account Number   : ");
    if (!acc) { Utils::pressEnterToContinue(); return; }

    UIView::displayBalance(acc);

    double amount = Utils::getDoubleInput("\n  Deposit Amount   : Rs. ", 1.0);

    if (acc->deposit(amount)) {
        TransactionController::recordDeposit(acc->getAccountNumber(), amount, acc->getBalance());
        FileHandler::saveAccounts();
        FileHandler::saveTransactions();
        UIView::displaySuccess("Deposit successful!");
        std::cout << "  Deposited Amount  : " << Utils::formatCurrency(amount) << "\n";
        std::cout << "  New Balance       : " << Utils::formatCurrency(acc->getBalance()) << "\n";
    } else {
        UIView::displayError("Deposit failed. Invalid amount.");
    }
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Withdraw Money
// -------------------------------------------------------
void AccountController::withdrawMoney() {
    UIView::displayHeader();
    std::cout << "  === WITHDRAW MONEY ===\n\n";

    auto acc = findAndVerifyAccount("  Account Number   : ");
    if (!acc) { Utils::pressEnterToContinue(); return; }

    UIView::displayBalance(acc);

    double amount = Utils::getDoubleInput("\n  Withdraw Amount  : Rs. ", 1.0);

    if (amount > Constants::MAX_WITHDRAW_LIMIT) {
        UIView::displayError("Amount exceeds maximum withdrawal limit of " +
                              Utils::formatCurrency(Constants::MAX_WITHDRAW_LIMIT));
        Utils::pressEnterToContinue();
        return;
    }

    if (acc->withdraw(amount)) {
        TransactionController::recordWithdrawal(acc->getAccountNumber(), amount, acc->getBalance());
        FileHandler::saveAccounts();
        FileHandler::saveTransactions();
        UIView::displaySuccess("Withdrawal successful!");
        std::cout << "  Withdrawn Amount  : " << Utils::formatCurrency(amount) << "\n";
        std::cout << "  Remaining Balance : " << Utils::formatCurrency(acc->getBalance()) << "\n";
    } else {
        UIView::displayError("Insufficient balance! Minimum balance of " +
                              Utils::formatCurrency(acc->getMinimumBalance()) + " must be maintained.");
    }
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Transfer Money
// -------------------------------------------------------
void AccountController::transferMoney() {
    UIView::displayHeader();
    std::cout << "  === TRANSFER MONEY ===\n\n";

    auto fromAcc = findAndVerifyAccount("  From Account No  : ");
    if (!fromAcc) { Utils::pressEnterToContinue(); return; }

    UIView::displayBalance(fromAcc);

    auto toAcc = findAndVerifyAccount("  To Account No    : ");
    if (!toAcc) { Utils::pressEnterToContinue(); return; }

    if (fromAcc->getAccountNumber() == toAcc->getAccountNumber()) {
        UIView::displayError("Cannot transfer to the same account.");
        Utils::pressEnterToContinue();
        return;
    }

    double amount = Utils::getDoubleInput("\n  Transfer Amount  : Rs. ", 1.0);

    if (fromAcc->withdraw(amount)) {
        toAcc->deposit(amount);

        TransactionController::recordTransferOut(fromAcc->getAccountNumber(), amount,
                                                  fromAcc->getBalance(), toAcc->getAccountNumber());
        TransactionController::recordTransferIn(toAcc->getAccountNumber(), amount,
                                                 toAcc->getBalance(), fromAcc->getAccountNumber());
        FileHandler::saveAccounts();
        FileHandler::saveTransactions();

        UIView::displaySuccess("Transfer successful!");
        std::cout << "  Amount Transferred: " << Utils::formatCurrency(amount)              << "\n";
        std::cout << "  From Account      : " << fromAcc->getAccountNumber()                << " ("
                  << fromAcc->getCustomerConst().getName() << ")\n";
        std::cout << "  To Account        : " << toAcc->getAccountNumber()                  << " ("
                  << toAcc->getCustomerConst().getName() << ")\n";
        std::cout << "  Sender Balance    : " << Utils::formatCurrency(fromAcc->getBalance()) << "\n";
    } else {
        UIView::displayError("Transfer failed! Insufficient balance or minimum balance violation.");
    }
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Balance Inquiry
// -------------------------------------------------------
void AccountController::balanceInquiry() {
    UIView::displayHeader();
    std::cout << "  === BALANCE INQUIRY ===\n\n";

    auto acc = findAndVerifyAccount("  Account Number   : ");
    if (!acc) { Utils::pressEnterToContinue(); return; }

    UIView::displayBalance(acc);
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Delete Account
// -------------------------------------------------------
void AccountController::deleteAccount() {
    UIView::displayHeader();
    std::cout << "  === DELETE ACCOUNT ===\n\n";

    auto acc = findAndVerifyAccount("  Account Number   : ");
    if (!acc) { Utils::pressEnterToContinue(); return; }

    UIView::displayAccountDetails(acc);

    std::cout << "\n  WARNING: This action cannot be undone!\n";
    std::string confirm = Utils::getStringInput("  Type 'DELETE' to confirm: ");

    if (confirm == "DELETE") {
        Bank::getInstance().removeAccount(acc->getAccountNumber());
        FileHandler::saveAccounts();
        UIView::displaySuccess("Account " + acc->getAccountNumber() + " has been deleted.");
    } else {
        UIView::displayInfo("Deletion cancelled.");
    }
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Mini Statement
// -------------------------------------------------------
void AccountController::showMiniStatement() {
    UIView::displayHeader();
    std::cout << "  === MINI STATEMENT ===\n\n";

    auto acc = findAndVerifyAccount("  Account Number   : ");
    if (!acc) { Utils::pressEnterToContinue(); return; }

    auto txs = Bank::getInstance().getRecentTransactions(
        acc->getAccountNumber(), Constants::MINI_STATEMENT_COUNT);

    UIView::displayMiniStatement(txs, acc->getAccountNumber(), acc->getBalance());
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Transaction History
// -------------------------------------------------------
void AccountController::showTransactionHistory() {
    UIView::displayHeader();
    std::cout << "  === TRANSACTION HISTORY ===\n\n";

    auto acc = findAndVerifyAccount("  Account Number   : ");
    if (!acc) { Utils::pressEnterToContinue(); return; }

    auto txs = Bank::getInstance().getTransactionsByAccount(acc->getAccountNumber());
    UIView::displayTransactionHistory(txs, acc->getAccountNumber());
    Utils::pressEnterToContinue();
}
