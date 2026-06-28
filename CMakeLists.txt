cmake_minimum_required(VERSION 3.16)
project(BankManagementSystemPro VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/Account.cpp
    src/SavingsAccount.cpp
    src/CurrentAccount.cpp
    src/Customer.cpp
    src/Transaction.cpp
    src/Bank.cpp
    src/AdminAuth.cpp
    src/AccountController.cpp
    src/CustomerController.cpp
    src/ReportController.cpp
    src/TransactionController.cpp
    src/FileHandler.cpp
    src/UIView.cpp
    src/Utils.cpp
    src/InterestCalculator.cpp
    src/LoanCalculator.cpp
)

add_executable(BankManagementSystemPro ${SOURCES})

target_compile_options(BankManagementSystemPro PRIVATE
    -Wall
    -Wextra
    -O2
)

# Create data and reports directories on build
add_custom_command(TARGET BankManagementSystemPro POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/data
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/reports
    COMMENT "Creating data and reports directories"
)
