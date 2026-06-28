#pragma once

class CustomerController {
public:
    void updateCustomer();
    void searchCustomer();
    void displayAllCustomers();

private:
    void searchByAccountNumber();
    void searchByPhone();
    void searchByAadhar();
    void searchByPAN();
    void searchByName();
};
