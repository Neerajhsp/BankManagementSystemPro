#include <iostream>
#include <string>
#include <limits>

#include "Constants.h"
#include "AdminAuth.h"
#include "Bank.h"
#include "FileHandler.h"
#include "UIView.h"
#include "Utils.h"
#include "AccountController.h"
#include "CustomerController.h"
#include "ReportController.h"
#include "InterestCalculator.h"
#include "LoanCalculator.h"

// -------------------------------------------------------
// Login flow
// -------------------------------------------------------
bool performLogin() {
    const int MAX_ATTEMPTS = 3;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        UIView::displayLoginScreen();
        std::cout << "  Username : ";
        std::string username;
        std::getline(std::cin, username);

        std::string password = Utils::getHiddenInput("  Password : ");

if (AdminAuth::getInstance().login(Utils::trim(username), Utils::trim(password))) {            UIView::displaySuccess("Login successful! Welcome, Admin.");
            Utils::pressEnterToContinue();
            return true;
        }

        ++attempts;
        int remaining = MAX_ATTEMPTS - attempts;
        UIView::displayError("Invalid credentials. " +
                              std::to_string(remaining) + " attempt(s) remaining.");
        Utils::pressEnterToContinue();
    }

    UIView::displayError("Maximum login attempts exceeded. System locked.");
    Utils::pressEnterToContinue();
    return false;
}

// -------------------------------------------------------
// Exit confirmation
// -------------------------------------------------------
bool confirmExit() {
    std::cout << "\n  Are you sure you want to exit? (y/n): ";
    std::string choice;
    std::getline(std::cin, choice);
    return (!choice.empty() && (choice[0] == 'y' || choice[0] == 'Y'));
}

// -------------------------------------------------------
// Main menu loop
// -------------------------------------------------------
void runApplication() {
    AccountController  accountCtrl;
    CustomerController customerCtrl;
    ReportController   reportCtrl;
    InterestCalculator interestCalc;
    LoanCalculator     loanCalc;

    bool running = true;
    while (running) {
        UIView::displayMainMenu();
        int choice = Utils::getIntInput("  Enter choice [0-15]: ", 0, 15);

        switch (choice) {
            // ---- Account Operations ----
            case 1:  accountCtrl.createAccount();       break;
            case 2:  accountCtrl.depositMoney();        break;
            case 3:  accountCtrl.withdrawMoney();       break;
            case 4:  accountCtrl.transferMoney();       break;
            case 5:  accountCtrl.balanceInquiry();      break;
            case 6:  accountCtrl.showMiniStatement();   break;
            case 7:  accountCtrl.showTransactionHistory(); break;

            // ---- Customer Operations ----
            case 8:  customerCtrl.updateCustomer();     break;
            case 9:  accountCtrl.deleteAccount();       break;
            case 10: customerCtrl.searchCustomer();     break;
            case 11: customerCtrl.displayAllCustomers(); break;

            // ---- Analytics & Reports ----
            case 12: interestCalc.calculate();          break;
            case 13: loanCalc.calculate();              break;
            case 14: reportCtrl.showMonthlyReport();    break;
            case 15: {
                UIView::displayHeader();
                std::cout << "  === EXPORT OPTIONS ===\n\n";
                std::cout << "   1. Export Monthly Report\n";
                std::cout << "   2. Export Transaction History\n";
                std::cout << "   0. Back\n\n";
                int expChoice = Utils::getIntInput("  Choose [0-2]: ", 0, 2);
                if (expChoice == 1) reportCtrl.exportReport();
                else if (expChoice == 2) reportCtrl.exportTransactionHistory();
                break;
            }

            // ---- Exit ----
            case 0:
                if (confirmExit()) {
                    AdminAuth::getInstance().logout();
                    running = false;
                }
                break;

            default:
                UIView::displayError("Invalid option selected.");
                Utils::pressEnterToContinue();
                break;
        }
    }
}

// -------------------------------------------------------
// Application Entry Point
// -------------------------------------------------------
int main() {
    // Ensure data directories exist and load persisted data
    FileHandler::ensureDirectories();
    FileHandler::loadAccounts();

    // Show splash screen
    Utils::clearScreen();
    Utils::printSeparator('*');
    Utils::printCentered(Constants::BANK_NAME);
    Utils::printCentered("Secure | Reliable | Trusted");
    Utils::printCentered("Version " + Constants::APP_VERSION);
    Utils::printSeparator('*');
    std::cout << "\n  Initializing system...\n";
    Utils::pressEnterToContinue();

    // Authenticate
    if (!performLogin()) {
        return 1;
    }

    // Run main menu
    runApplication();

    // Farewell
    UIView::displayExitConfirmation();
    return 0;
}
