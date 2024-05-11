#ifndef PASSMAN_PASSWORD_HPP
#define PASSMAN_PASSWORD_HPP
#include <string>

/**
 * @class Password
 * @brief The Password class represents a password entry.
 *
 * This class encapsulates the information related to a password, including its name, actual password,
 * category, website, and login information.
 */
class Password {
public:
    /**
    * @brief Constructs a new Password object.
    * @param name The name of the password.
    * @param password The actual password.
    * @param category The category of the password.
    * @param website The website associated with the password.
    * @param login The login information associated with the password.
    */
    Password(const std::string& name, const std::string& password, const std::string& category, const std::string& website, const std::string& login);

    std::string getName() const;
    std::string getPassword() const;
    std::string getCategory() const;
    std::string getWebsite() const;
    std::string getLogin() const;
    void setName(const std::string& x);
    void setPassword(const std::string& x);
    void setCategory(const std::string& x);
    void setWebsite(const std::string& x);
    void setLogin(const std::string& x);
     /**
     * @brief Prints all the information about the password entry.
     *
     *These function will be used in searching and sorting passwords to show the user all the information
     */
    void printInfo() const;

private:
    std::string name;
    std::string password;
    std::string category;
    std::string website;
    std::string login;
};



#endif //PASSMAN_PASSWORD_HPP
