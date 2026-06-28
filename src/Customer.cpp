#include "Customer.h"
#include "Utils.h"
#include <sstream>

Customer::Customer(const std::string& n, int a, Gender g,
                   const std::string& p, const std::string& e,
                   const std::string& addr, const std::string& aadhar,
                   const std::string& pan)
    : name(n), age(a), gender(g), phone(p), email(e),
      address(addr), aadharNumber(aadhar), panNumber(pan) {}

std::string Customer::serialize() const {
    // Encode address to avoid pipe conflicts: replace | with \|
    std::string safeAddr = address;
    for (char& c : safeAddr) if (c == '|') c = '^';

    std::ostringstream oss;
    oss << name << "|"
        << age << "|"
        << genderToString(gender) << "|"
        << phone << "|"
        << email << "|"
        << safeAddr << "|"
        << aadharNumber << "|"
        << panNumber;
    return oss.str();
}

Customer Customer::deserialize(const std::string& line) {
    auto parts = Utils::split(line, '|');
    if (parts.size() < 8) return Customer();
    std::string addr = parts[5];
    for (char& c : addr) if (c == '^') c = '|';

    return Customer(
        parts[0],
        std::stoi(parts[1]),
        stringToGender(parts[2]),
        parts[3],
        parts[4],
        addr,
        parts[6],
        parts[7]
    );
}
