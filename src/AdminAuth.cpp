#include "AdminAuth.h"
#include "Constants.h"

AdminAuth::AdminAuth() : authenticated(false) {}

AdminAuth& AdminAuth::getInstance() {
    static AdminAuth instance;
    return instance;
}

bool AdminAuth::login(const std::string& username, const std::string& password) {
    authenticated = (username == Constants::ADMIN_USERNAME &&
                     password == Constants::ADMIN_PASSWORD);
    return authenticated;
}

void AdminAuth::logout() {
    authenticated = false;
}
