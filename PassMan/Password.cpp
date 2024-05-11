#include <iostream>
#include "Password.hpp"
Password::Password(const std::string& name, const std::string& password, const std::string& category, const std::string& website, const std::string& login)
        : name(name), password(password), category(category), website(website), login(login) {}

std::string Password::getName() const {
    return name;
}
void Password::setName(const std::string& x){
    name = x;
}
void Password::setPassword(const std::string& x){
    password = x;
}
void Password::setCategory(const std::string& x){
    category = x;
}
void Password::setWebsite(const std::string& x){
    website = x;
}
void Password::setLogin(const std::string& x){
    login = x;
}
std::string Password::getPassword() const {
    return password;
}

std::string Password::getCategory() const {
    return category;
}

std::string Password::getWebsite() const {
    return website;
}

std::string Password::getLogin() const {
    return login;
}
void Password::printInfo() const{
    std::cout << "\nNAME: " + getName();
    std::cout << "\nPASSWORD: " + getPassword();
    std::cout << "\nCATEGORY: " + getCategory();
    std::cout << "\nWEBSITE: " + getWebsite();
    std::cout << "\nLOGIN: " + getLogin();
    std::cout << "\n";
}