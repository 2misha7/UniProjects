
#ifndef PASSMAN_PASSWORDMANAGER_HPP
#define PASSMAN_PASSWORDMANAGER_HPP


#include <vector>
#include <set>
#include "Password.hpp"
/**
 * @class PasswordManager
 * @brief Manages passwords and categories.
 *
 * The PasswordManager class provides functionality for managing passwords and categories of passwords.
 * It allows adding, editing, deleting, searching, and sorting passwords. It also provides
 * methods for adding and deleting categories. It is able to modify the encrypted file.
 * PasswordManager updates the timestamp in the very beginning of a program, when the user enters main "key" password to an encrypted file, even if an attempt to get an access to a file was failed.
 */
class PasswordManager {
public:
    PasswordManager();
    /**
     * @brief Retrieves the current time and stores it in the timestamp member variable.
     * Creates a string, which represents a timestamp of a last attempt to open a file(both successful and failed).
     * This function retrieves the current system time and extracts the hour, minute, second,
     * and date components (from a string with a timestamp). It then assigns these values to the corresponding member variables
     * in the PasswordManager class.
     */
    void timeNow();
    /**
    * @brief Writes the data to a file.
    *
    * This function saves the password manager data to a file. It performs the following steps:
    *
    * 1. Constructs a vector `data` to store the data to be written.
    * 2. Writes the categories to `data`, separating each category with a newline character ('\n').
    * 3. Appends an exclamation mark ('!') as a delimiter after the categories.
    * 4. Calculates the checksum `a` by summing the ASCII values of the characters in the `password` string.
    * 5. Encrypts the `hh`, `mm`, `ss`, and `date` strings by subtracting the checksum `a` from their ASCII values.
    * 6. Appends the encrypted `hh` string to `data`.
    * 7. Appends the string "\nRIGHT_DATA" to `data` as an indicator.
    * 8. Appends the encrypted `mm` and `date` strings to `data`.
    * 9. Appends two newline characters ('\n') to `data`.
    * 10. Appends the individual password data to `data` for each password in the `passwords` vector.
    *    - Adds a colon (':') as a separator.
    *    - Appends the name, password, category, website, and login strings to `data`, each followed by a newline character.
    *    - Appends two newline characters ('\n') to separate each password entry.
    * 11. Appends a period ('.') as a delimiter after the password entries. Appends the encrypted `mm`.
    * 12. Encrypts the entire `data` vector by adding the checksum `a` to the ASCII values of each character.
    * As a result 'hh', 'mm', 'ss', 'date' will be decrypted in a file.
    * 13. Writes the contents of the `data` vector to a source file.
    */
    void writeToFile();
    /**
    * @brief Retrieves all passwords from the decrypted data and populates the passwords vector.
    *
    *This function iterates over the decrypted data and extracts individual password entries.
    *The function parses the data and creates a Password object for each entry.
    *These Password objects are then added to the passwords vector in the PasswordManager class.
    *The function will be called immediately after the user enters the correct key password.
    *
    *@see PasswordManager::DecData()
    */
    void allPasswords();
    /**
     * @brief Decrypts the contents of the source file and returns the decrypted data.
     *
     * This function reads the contents of the source file and stores them in a vector of characters.
     * It then performs a decryption process on the data by subtracting a computed value from each
     * character's ASCII code. The computed value is based on the characters of the password(sum of all characters ASCII codes in a key password).
     * The decrypted data is returned as a vector of characters.
     *
     * @return The decrypted data as a vector of characters.
     */
    std::vector<char> DecData();
    /**
    * @brief Checks if the password enters by the user is correct.
    *
    * This function retrieves the decrypted data by calling the DecData() function.
    * It searches for a specific pattern in the decrypted data to determine if the password is correct.
    * The pattern to check is "RIGHT_DATA", which should be present in the decrypted data after a '!' character.
    *
    * @return True if the password is correct, false otherwise.
    */
    bool isPasswordCorrect();
    /**
     * @brief Allows the user to choose the source file by inputting the path to the encrypted file.
     *
     * This function prompts the user to enter a path to their encrypted file.
     * The entered path is stored in the member variable 'sourceFile' of the PasswordManager class.
     */
    void chooseSourceFile();
    /**
    * @brief Prompts the user to enter their password and performs operations based on the password's correctness.
    *
    * This function prompts the user to enter their password.
    * It calls the 'timeNow()' function to get the current timestamp and date.
    *
    * If the entered password is correct, it reads categories from the file using 'readCategoriesFromFile()',
    * and retrieves all passwords from the file using 'allPasswords()'.
    *
    * If the password is incorrect, it prints "WRONG PASSWORD. PLEASE RUN THE PROGRAM ONE MORE TIME".
    *
    * The function then opens the source file for reading and reads its contents into a vector.
    * It modifies the vector with data from a source file according to a nen timestamp.
    * Finally, the function opens the source file for writing and writes the contents of the new vector to the file.
    *
    * @see  Password::readCategoriesFromFile()
    * @see  Password::allPasswords()
    * @see  Password::timeNow();
    */
    void enterPassword();
    /**
    * @brief Allows the user to search for passwords based on a selected parameter.
    *
    * This function prompts the user to enter a number corresponding to a parameter:
    * It iterates over each password in the 'passwords' vector and checks if the password matches the search criteria based on the selected parameter.
    * Finally, it prints the information of each password in 'suchPasswords' by calling the 'printInfo()' function.
    *
    * @see PasswordManager::printInfo()
    */
    void searchPasswords();
    /**
 * @brief Compares two Password objects based on category and name.
 *
 * This function compares two Password objects based on their category and name. It is used as a custom comparison criteria for sorting passwords in the `sortPasswords()` function. The comparison is performed as follows:
 * - If the categories of both passwords are equal, the comparison is based on the names of the passwords.
 * - If the categories are different, the comparison is based on the categories of the passwords.
 *
 * @param password1 The first Password object to compare.
 * @param password2 The second Password object to compare.
 * @return True if password1 is less than password2 based on the comparison criteria, False otherwise.
 *
 * @see PasswordManager::sortPasswords()
 */
    bool comparePasswords(const Password &password1, const Password &password2);
    /**
    * @brief Sorts and displays the passwords based on a custom comparison criteria.
    *
    * This function sorts the passwords stored in the `passwords` vector based on a custom comparison criteria defined by the `comparePasswords()` function. The sorted passwords are then printed by calling the `printInfo()` function for each password.
    * @see PasswordManager::comparePasswords()
    * @see Password::printInfo()
    */
    void sortPasswords();
    /**
    * @brief Adds a new password.
    *
    * This function prompts the user to enter details for a new password, such as name, category,
    * website, and login. The user can choose to either generate a password automatically or enter
    * their own password. The user-entered password is then validated for security.
    * If the password meets the security requirements, it is added to the PasswordManager's list
    * of passwords and saved to the data file, using writeToFile(). If it does not, a user have an opportunity to create a better password.
    * @see PasswordManager::writeToFile()
    */
    void addPassword();
    /**
    * @brief Allows the user to edit an existing password.
    *
    * This function displays the list of password names and prompts the user to choose a password
    * to edit by entering the corresponding number. Then, the function presents a menu of parameters
    * (name, password, category, website, login) that can be edited. The user selects the parameter
    * to edit by entering the corresponding number and provides the new value for that parameter.
    * Finally, the function updates the password with the edited information and saves the changes
    * to the data file, using writeToFile().
    *
    * @see PasswordManager::writeToFile()
    */
    void editPassword();
    /** @brief Deletes passwords based on user-specified criteria.
    *
    * This function allows the user to delete passwords based on different criteria such as name, category, or website.
    * The function updates the `passwords` vector and the associated data file with the modified password information.
    * Passwords are erased from the `passwords` vector based on the selected criteria, and the updated data is encrypted and written back to the file, using writeToFile().
    *
    * @see PasswordManager::writeToFile()
    */
    void deletePassword();
    /**
    * @brief Adds a new category to the password manager.
    *
    * This function allows the user to add a new category to the password manager.
    * The function prompts the user to enter the name of the new category and then saves it.
    */
    void addCategory();
    /**
    * @brief Deletes a category and passwords belonging to this category.
    *
    * This function allows the user to delete passwords that are associated with a particular category.
    * The function prompts the user to enter the category to be deleted and removes it from the list of categories.
    * Passwords associated with the specified category are also removed from the `passwords` vector.
    * The function updates the encrypted data file with the modified category and password information.
    */
    void deleteCategory();
    /**
    * @brief Reads categories from the data file and populates the categories set.
    *
    * This function reads the encrypted data from the data file, decrypts it, and retrieves the category information.
    * The categories are stored as a sequence of characters separated by newline characters. Categories are separated from the rest information in a file by "!"
    * The function splits the category data and inserts each category into the `categories` set.
    */
    void readCategoriesFromFile();
    /**
    * @brief Prints the list of categories stored in the password manager.
    *
    * This function iterates over the categories stored in the `categories` set and prints them to the standard output.
    */
    void getCAT();
private:
    std::set<std::string> categories;
    std::string sourceFile;
    std::string timestamp;
    std::string hh;
    std::string mm;
    std::string ss;
    std::string date;
    std::vector<Password> passwords;
    std::string password;
};


#endif //PASSMAN_PASSWORDMANAGER_HPP
