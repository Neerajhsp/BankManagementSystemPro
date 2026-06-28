#pragma once
#include <string>
#include "Enums.h"

class Customer {
private:
    std::string name;
    int age;
    Gender gender;
    std::string phone;
    std::string email;
    std::string address;
    std::string aadharNumber;
    std::string panNumber;

public:
    Customer() = default;
    Customer(const std::string& name, int age, Gender gender,
             const std::string& phone, const std::string& email,
             const std::string& address, const std::string& aadhar,
             const std::string& pan);

    // Getters
    std::string getName()        const { return name; }
    int         getAge()         const { return age; }
    Gender      getGender()      const { return gender; }
    std::string getPhone()       const { return phone; }
    std::string getEmail()       const { return email; }
    std::string getAddress()     const { return address; }
    std::string getAadhar()      const { return aadharNumber; }
    std::string getPAN()         const { return panNumber; }

    // Setters
    void setName(const std::string& n)    { name = n; }
    void setAge(int a)                    { age = a; }
    void setGender(Gender g)              { gender = g; }
    void setPhone(const std::string& p)   { phone = p; }
    void setEmail(const std::string& e)   { email = e; }
    void setAddress(const std::string& a) { address = a; }
    void setAadhar(const std::string& a)  { aadharNumber = a; }
    void setPAN(const std::string& p)     { panNumber = p; }

    // Serialization
    std::string serialize() const;
    static Customer deserialize(const std::string& line);
};
