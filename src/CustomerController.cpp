#include "CustomerController.h"
#include "Bank.h"
#include "UIView.h"
#include "Utils.h"
#include "FileHandler.h"
#include "Enums.h"
#include <iostream>
#include <vector>
#include <memory>

// -------------------------------------------------------
// Update Customer Details
// -------------------------------------------------------
void CustomerController::updateCustomer() {
    UIView::displayHeader();
    std::cout << "  === UPDATE CUSTOMER DETAILS ===\n\n";

    std::string accNo = Utils::getStringInput("  Account Number   : ");
    auto acc = Bank::getInstance().findAccount(accNo);
    if (!acc) {
        UIView::displayError("Account not found or account is closed.");
        Utils::pressEnterToContinue();
        return;
    }

    UIView::displayAccountDetails(acc);

    Customer& c = acc->getCustomer();

    std::cout << "\n  Leave field EMPTY to keep existing value.\n\n";

    // Name
    std::cout << "  Name [" << c.getName() << "]: ";
    std::string input;
    std::getline(std::cin, input);
    input = Utils::trim(input);
    if (!input.empty()) c.setName(input);

    // Age
    std::cout << "  Age [" << c.getAge() << "]: ";
    std::getline(std::cin, input);
    input = Utils::trim(input);
    if (!input.empty()) {
        try { c.setAge(std::stoi(input)); } catch (...) {}
    }

    // Phone
    while (true) {
        std::cout << "  Phone [" << c.getPhone() << "]: ";
        std::getline(std::cin, input);
        input = Utils::trim(input);
        if (input.empty()) break;
        if (Utils::isValidPhone(input)) { c.setPhone(input); break; }
        UIView::displayError("Invalid phone number.");
    }

    // Email
    while (true) {
        std::cout << "  Email [" << c.getEmail() << "]: ";
        std::getline(std::cin, input);
        input = Utils::trim(input);
        if (input.empty()) break;
        if (Utils::isValidEmail(input)) { c.setEmail(input); break; }
        UIView::displayError("Invalid email format.");
    }

    // Address
    std::cout << "  Address [" << c.getAddress() << "]: ";
    std::getline(std::cin, input);
    input = Utils::trim(input);
    if (!input.empty()) c.setAddress(input);

    FileHandler::saveAccounts();
    UIView::displaySuccess("Customer details updated successfully.");
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Display All Accounts
// -------------------------------------------------------
void CustomerController::displayAllCustomers() {
    UIView::displayHeader();
    std::cout << "  === ALL ACCOUNTS ===\n";

    const auto& allAccounts = Bank::getInstance().getAllAccounts();
    std::vector<std::shared_ptr<Account>> active;
    for (const auto& [accNo, acc] : allAccounts) {
        if (acc->getIsActive()) active.push_back(acc);
    }

    if (active.empty()) {
        UIView::displayInfo("No accounts found in the system.");
    } else {
        std::cout << "  Total Active Accounts: " << active.size() << "\n";
        UIView::displayAccountList(active);
    }
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Search Customer (menu dispatch)
// -------------------------------------------------------
void CustomerController::searchCustomer() {
    bool searching = true;
    while (searching) {
        UIView::displayHeader();
        std::cout << "  === SEARCH CUSTOMER ===\n";
        UIView::displaySearchMenu();

        int choice = Utils::getIntInput("\n  Enter choice [0-5]: ", 0, 5);
        switch (choice) {
            case 1: searchByAccountNumber(); break;
            case 2: searchByPhone();         break;
            case 3: searchByAadhar();        break;
            case 4: searchByPAN();           break;
            case 5: searchByName();          break;
            case 0: searching = false;       break;
        }
    }
}

// -------------------------------------------------------
// Search by Account Number
// -------------------------------------------------------
void CustomerController::searchByAccountNumber() {
    UIView::displayHeader();
    std::cout << "  === SEARCH BY ACCOUNT NUMBER ===\n\n";

    std::string accNo = Utils::getStringInput("  Account Number   : ");
    auto acc = Bank::getInstance().findAccount(accNo);
    if (acc) {
        UIView::displayAccountDetails(acc);
    } else {
        UIView::displayError("No account found with number: " + accNo);
    }
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Search by Phone
// -------------------------------------------------------
void CustomerController::searchByPhone() {
    UIView::displayHeader();
    std::cout << "  === SEARCH BY PHONE ===\n\n";

    std::string phone = Utils::getStringInput("  Phone Number     : ");
    auto results = Bank::getInstance().searchByPhone(phone);
    UIView::displaySearchResults(results);
    if (!results.empty()) {
        std::string view = Utils::getStringInput(
            "\n  View full details? Enter account no or press ENTER to skip: ", true);
        if (!view.empty()) {
            auto acc = Bank::getInstance().findAccount(view);
            if (acc) UIView::displayAccountDetails(acc);
        }
    }
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Search by Aadhar
// -------------------------------------------------------
void CustomerController::searchByAadhar() {
    UIView::displayHeader();
    std::cout << "  === SEARCH BY AADHAR NUMBER ===\n\n";

    std::string aadhar = Utils::getStringInput("  Aadhar Number    : ");
    auto results = Bank::getInstance().searchByAadhar(aadhar);
    UIView::displaySearchResults(results);
    if (!results.empty()) {
        std::string view = Utils::getStringInput(
            "\n  View full details? Enter account no or press ENTER to skip: ", true);
        if (!view.empty()) {
            auto acc = Bank::getInstance().findAccount(view);
            if (acc) UIView::displayAccountDetails(acc);
        }
    }
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Search by PAN
// -------------------------------------------------------
void CustomerController::searchByPAN() {
    UIView::displayHeader();
    std::cout << "  === SEARCH BY PAN NUMBER ===\n\n";

    std::string pan = Utils::getStringInput("  PAN Number       : ");
    auto results = Bank::getInstance().searchByPAN(pan);
    UIView::displaySearchResults(results);
    if (!results.empty()) {
        std::string view = Utils::getStringInput(
            "\n  View full details? Enter account no or press ENTER to skip: ", true);
        if (!view.empty()) {
            auto acc = Bank::getInstance().findAccount(view);
            if (acc) UIView::displayAccountDetails(acc);
        }
    }
    Utils::pressEnterToContinue();
}

// -------------------------------------------------------
// Search by Name
// -------------------------------------------------------
void CustomerController::searchByName() {
    UIView::displayHeader();
    std::cout << "  === SEARCH BY NAME ===\n\n";

    std::string name = Utils::getStringInput("  Customer Name    : ");
    auto results = Bank::getInstance().searchByName(name);
    UIView::displaySearchResults(results);
    if (!results.empty()) {
        std::string view = Utils::getStringInput(
            "\n  View full details? Enter account no or press ENTER to skip: ", true);
        if (!view.empty()) {
            auto acc = Bank::getInstance().findAccount(view);
            if (acc) UIView::displayAccountDetails(acc);
        }
    }
    Utils::pressEnterToContinue();
}
