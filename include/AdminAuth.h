#pragma once
#include <string>

class AdminAuth {
private:
    bool authenticated;

    AdminAuth();
    AdminAuth(const AdminAuth&)            = delete;
    AdminAuth& operator=(const AdminAuth&) = delete;

public:
    static AdminAuth& getInstance();

    bool login(const std::string& username, const std::string& password);
    void logout();
    bool isAuthenticated() const { return authenticated; }
};
