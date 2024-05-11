#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "PasswordManager.hpp"
PasswordManager::PasswordManager()  {
}
void PasswordManager::getCAT(){
    for(const std::string& s : categories){
        std::cout << s << "\n";
    }
}
void PasswordManager::writeToFile(){
    std::vector<char> data;
    for (const std::string& cat: categories) {
        for (char c: cat) {
            data.push_back(c);
        }
        data.push_back('\n');
    }
    data.push_back('!');

    int a = 0;
    for (int i = 0; i < password.size(); i++) {
        a += static_cast<int>(password[i]);
    }
    for (int i = 0; i < hh.size(); ++i) {
        int ascii = static_cast<int>(hh[i]);
        ascii -= a;
        hh[i] = static_cast<char>(ascii);
    }
    for (int i = 0; i < mm.size(); ++i) {
        int ascii = static_cast<int>(mm[i]);
        ascii -= a;
        mm[i] = static_cast<char>(ascii);
    }
    for (int i = 0; i < ss.size(); ++i) {
        int ascii = static_cast<int>(ss[i]);
        ascii -= a;
        ss[i] = static_cast<char>(ascii);
    }
    for (int i = 0; i < date.size(); ++i) {
        int ascii = static_cast<int>(date[i]);
        ascii -= a;
        date[i] = static_cast<char>(ascii);
    }

    for (const char& c: hh) {
        data.push_back(c);
    }
    std::string toAdd = "\nRIGHT_DATA";
    for (const char& c: toAdd) {
        data.push_back(c);
    }
    for (const char& c: mm) {
        data.push_back(c);
    }
    for (const char& c: date) {
        data.push_back(c);
    }
    data.push_back('\n');
    data.push_back('\n');
    for (const Password& p: passwords) {
        std::string name1 = p.getName();
        std::string password1 = p.getPassword();
        std::string category1 = p.getCategory();
        std::string website1 = p.getWebsite();
        std::string login1 = p.getLogin();
        data.push_back(':');
        for (const char& c: name1) {
            data.push_back(c);
        }
        data.push_back('\n');
        data.push_back(':');
        for (const char& c: password1) {
            data.push_back(c);
        }
        data.push_back('\n');
        data.push_back(':');
        for (const char& c: category1) {
            data.push_back(c);
        }
        data.push_back('\n');
        data.push_back(':');
        for (const char& c: website1) {
            data.push_back(c);
        }
        data.push_back('\n');
        data.push_back(':');
        for (const char& c: login1) {
            data.push_back(c);
        }
        data.push_back('\n');
        data.push_back('\n');
    }
    data.push_back('.');
    for (const char& c: ss) {
        data.push_back(c);
    }
    for (int i = 0; i < data.size(); ++i) {
        int ascii = static_cast<int>(data[i]);
        ascii += a;
        data[i] = static_cast<char>(ascii);
    }
    std::ofstream outFile(sourceFile);
    outFile.write((data.data()), data.size());
    outFile.close();
}
void PasswordManager::readCategoriesFromFile(){
    std::vector<char> data = DecData();
    std::size_t endIndex = std::find(data.begin(), data.end(), '!') - data.begin();
    std::vector<char> categoriesData(data.begin(), data.begin() + endIndex);

    std::size_t startPos = 0;
    std::size_t newlinePos = std::find(categoriesData.begin(), categoriesData.end(), '\n') - categoriesData.begin();
    while (newlinePos != categoriesData.size()) {
        std::string category(categoriesData.begin() + startPos, categoriesData.begin() + newlinePos);
        categories.insert(category);

        startPos = newlinePos + 1;
        newlinePos = std::find(categoriesData.begin() + startPos, categoriesData.end(), '\n') - categoriesData.begin();
    }
}
std::vector<char> PasswordManager::DecData(){
    std::ifstream inFile(sourceFile);
    std::vector<char> data;
    char c;
    while (inFile.get(c)) {
        data.push_back(c);
    }
    inFile.close();

    int a = 0;
    for(int i = 0; i < password.size(); i++){
        a+=static_cast<int>(password[i]);
    }

    for (int i = 0; i < data.size(); ++i) {
        int ascii = static_cast<int>(data[i]);
        ascii -= a;
        data[i] = static_cast<char>(ascii);
    }
    return data;
}
void PasswordManager::chooseSourceFile() {
    std::cout << "ENTER A PATH TO YOUR ENCRYPTED FILE:\n";
    std::cin >> sourceFile;
}
void PasswordManager::enterPassword() {
    std::cout << "ENTER YOUR PASSWORD:\n";
    std::cin >> password;
    timeNow();
    bool wrong = false;
    if(isPasswordCorrect()){
        std::cout << "RIGHT PASSWORD";
        readCategoriesFromFile();
        allPasswords();
    }else{
        std::cout << "WRONG PASSWORD. PLEASE RUN THE PROGRAM ONE MORE TIME:\n";
        wrong = true;
    }
    std::ifstream inFile(sourceFile);
    // Read the file contents
    std::vector<char> data;
    char c;
    while (inFile.get(c)) {
        data.push_back(c);
    }
    inFile.close();
    std::vector<char> data1;
    for (const char& c : data) {
        if (std::isdigit(c)) {
            break;
        }
        data1.push_back(c);
    }
    for(const char& c : hh){
        data1.push_back(c);
    }
    auto digitFound = false;
    auto it = data.begin();
    while (it != data.end()) {
        if (std::isdigit(*it)) {
            digitFound = true;
            break;
        }
        ++it;
    }

    if (digitFound) {
        data.erase(data.begin(), it + 2);
    }
    for(int i = 0; i < 11; i++){
        data1.push_back(data[i]);
    }
    for(const char& c : date){
        data1.push_back(c);
    }
    data1.push_back(' ');
    for(const char& c : mm){
        data1.push_back(c);
    }
    data.erase(data.begin(), data.begin() + 20);
    for (std::size_t i = 0; i < data.size() - 2; ++i) {
        data1.push_back(data[i]);
    }
    for(const char& c : ss){
        data1.push_back(c);
    }
    std::ofstream outFile(sourceFile);
    outFile.write(reinterpret_cast<const char*>(data1.data()), data1.size());
    outFile.close();

    if(wrong == true){
        std::exit(EXIT_SUCCESS);
    }
}
bool PasswordManager::isPasswordCorrect(){
    std::vector<char> data = DecData();
    std::string toCheck = "RIGHT_DATA";
    auto it = std::find(data.begin(), data.end(), '!');
    if (it != data.end()) {
        auto startIndex = std::distance(data.begin(), it) + 4;
        // Check if the next 10 characters match "RIGHT_DATA"
        if (data.size() >= startIndex + 10 && std::equal(data.begin() + startIndex, data.begin() + startIndex + 10, toCheck.begin())) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }

}
void PasswordManager::allPasswords(){
    std::vector<char> data = DecData();
    for(int i = 0; i < data.size(); i++){
        if(data[i] ==  ':'){
            std::string name = "";
            std::string password = "";
            std::string category = "";
            std::string website = "";
            std::string login = "";
            i++;
            while(data[i] != '\n'){
                name+=data[i];
                i++;
            }
            i++;
            i++;
            while(data[i] != '\n'){
                password+=data[i];
                i++;
            }
            i++;
            i++;
            while(data[i] != '\n'){
                category+=data[i];
                i++;
            }
            i++;
            i++;
            while(data[i] != '\n'){
                website+=data[i];
                i++;
            }
            i++;
            i++;
            while(data[i] != '\n' && i < data.size()){
                login+=data[i];
                i++;
            }
            Password p(name, password, category, website,login);
            passwords.push_back(p);
        }
    }
}
void PasswordManager::searchPasswords() {
    int parNum;
    std::cout << "ENTER A NUMBER OF A PARAMETER:\n1. NAME\n2. PASSWORD\n3. CATEGORY\n4. WEBSITE\n5. LOGIN\n";
    std::cin >> parNum;
    std::cout << "ENTER YOUR PARAMETER:\n";
    std::string parameter;
    std::cin >> parameter;
    std::vector<Password> suchPasswords;
    for (const auto& password : passwords) {
        switch (parNum) {
            case 1:
                if (password.getName().find(parameter) != std::string::npos) {
                    suchPasswords.push_back(password);
                }
                break;
            case 2:
                if (password.getPassword().find(parameter) != std::string::npos) {
                    suchPasswords.push_back(password);
                }
                break;
            case 3:
                if (password.getCategory().find(parameter) != std::string::npos) {
                    suchPasswords.push_back(password);
                }
                break;
            case 4:
                if (password.getWebsite().find(parameter) != std::string::npos) {
                    suchPasswords.push_back(password);
                }
                break;
            case 5:
                if (password.getLogin().find(parameter) != std::string::npos) {
                    suchPasswords.push_back(password);
                }
                break;
            default:
                break;
        }
    }
    for (const Password& p : suchPasswords) {
        p.printInfo();
    }

}
bool PasswordManager::comparePasswords(const Password& password1, const Password& password2) {
    if (password1.getCategory() == password2.getCategory()) {
        return password1.getName() < password2.getName();
    } else {
        return password1.getCategory() < password2.getCategory();
    }
}
void PasswordManager::sortPasswords(){
    std::vector<Password> sorted = passwords;
    std::sort(sorted.begin(), sorted.end(), [&](const Password& password1, const Password& password2) {
        return comparePasswords(password1, password2);
    });
    for(const Password& p : sorted){
        p.printInfo();
        std::cout<<"\n";
    }
}
void PasswordManager::addCategory() {
    std::cout << "TYPE THE NAME OF A CATEGORY, IF IT IS NOT IN THE LIST\n";
    for(const std::string& c : categories){
        std::cout << c << "\n";
    }
    std::cout << "\nNEW CATEGORY:\n";
    std::string newCategory;
    std::cin >> newCategory;
    int x = 0;
    for(const std::string& c : categories){
        if(c == newCategory){
            std::cout << "YOU HAVE SUCH A CATEGORY IN YOUR LIST\n";
            x++;
        }
    }
    if(x == 0){
        categories.insert(newCategory);
        std::vector<char> data = DecData();
        data.insert(data.begin(), newCategory.begin(), newCategory.end());
        data.insert(data.begin() + newCategory.size(), '\n');

        // Encrypt the data
        int a = 0;
        for (int i = 0; i < password.size(); i++) {
            a += static_cast<int>(password[i]);
        }
        for (int i = 0; i < data.size(); ++i) {
            int ascii = static_cast<int>(data[i]);
            ascii += a;
            data[i] = static_cast<char>(ascii);
        }

        std::ofstream outFile(sourceFile);
        outFile.write(reinterpret_cast<const char*>(data.data()), data.size());
        outFile.close();
    }

}
void PasswordManager::deleteCategory(){
    std::cout << "\nTYPE A NAME OF A CATEGORY FOR DELETION:\n";
    for(std::string c : categories){
        std::cout << c << "\n";
    }
    std::string delC;
    std::cin >> delC;
    categories.erase(delC);

    passwords.erase(std::remove_if(passwords.begin(), passwords.end(),
                                   [&delC](const Password& p) {
                                       return p.getCategory() == delC;
                                   }),
                    passwords.end());

    writeToFile();
}
void PasswordManager::addPassword() {
    std::cout << "\nCREATING A NEW PASSWORD\n";
    std::string newName;
    std::string newPass;
    std::string newCategory;
    std::string newWebsite;
    std::string newLogin;
    std::cout << "TYPE A NAME:\n";
    std::cin >> newName;
    std::cout << "CATEGORIES TO CHOOSE FROM\n";
    getCAT();
    std::cout << "TYPE A CATEGORY:\n";
    std::cin >> newCategory;
    std::cout << "TYPE A WEBSITE\nIF YOU DO NOT WANT TO INSERT THE WEBSITE, TYPE 'null':\n";
    std::cin >> newWebsite;
    std::cout << "TYPE A LOGIN\nIF YOU DO NOT WANT TO INSERT YOUR LOGIN, TYPE 'null':\n";
    std::cin >> newLogin;

    //choosing password
    std::cout
            << "TYPE '0' IF YOU WANT TO RECEIVE A GENERATED PASSWORD\nTYPE '1' IF YOU WANT TO ENTER YOUR OWN PASSWORD\n";
    int x;
    std::cin >> x;
    if (x == 0) {
        std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
        std::string specialChars = "!@#$%^&*()?~:№";
        std::cout << "ENTER A NUMBER OF CHARACTERS YOU WANT:\n";
        int numChar;
        std::cin >> numChar;
        std::cout << "DO YOU WANT TO INCLUDE UPPERCASE LETTERS.\nTYPE '1' IF YOU WANT.\nTYPE '0' IF YOU DO NOT WANT\n";
        int up;
        std::cin >> up;
        std::cout << "DO YOU WANT TO INCLUDE LOWERCASE LETTERS.\nTYPE '1' IF YOU WANT.\nTYPE '0' IF YOU DO NOT WANT\n";
        int low;
        std::cin >> low;
        std::cout << "DO YOU WANT TO INCLUDE SPECIAL CHARACTERS.\nTYPE '1' IF YOU WANT.\nTYPE '0' IF YOU DO NOT WANT\n";
        int special;
        std::cin >> special;
        std::string allCharacters = "";
        if (low == 1)
            allCharacters += lowercase;
        if (up == 1)
            allCharacters += uppercase;
        if (special == 1)
            allCharacters += specialChars;
        for (int i = 0; i < numChar; ++i) {
            int index = rand() % allCharacters.length();
            newPass += allCharacters[index];
        }
        int q = 0;
        for(const Password& p : passwords){
            if(p.getPassword() == newPass){
                q++;
            }
        }
        while(q != 0){
            newPass = "";
            for (int i = 0; i < numChar; ++i) {
                int index = rand() % allCharacters.length();
                newPass += allCharacters[index];
            }
            q = 0;
            for(const Password& p : passwords){
                if(p.getPassword() == newPass){
                    q++;
                }
            }
        }

        std::cout << "YOUR NEW PASSWORD: " << newPass << "\n";
        Password addNewP(newName, newPass, newCategory, newWebsite, newLogin);
        passwords.push_back(addNewP);
        writeToFile();
    }else if (x == 1) {
        std::cout << "YOUR PASSWORD WILL BE SECURE IF\n"
                     "1.IT INCLUDES:\nUPPERCASE LETTERS\nLOWERCASE LETTERS\nNUMBERS\nSPECIAL CHARACTERS\n"
                     "2.YOU DO NOT USE THE SAME PASSWORD IN OTHER SERVICES\n"
                     "3.THE LENGTH OF YOUR PASSWORD SHOULD IS AT LEAST 8 CHARACTERS\n";
        std::cin >> newPass;
        int safety = 0;
        bool safe = true;
        int typeNEW = 0;
        for (const char& c: newPass) {
            if (std::islower(c)) {
                safety++;
            }
        }
        if (safety == 0) {
            std::cout << "\nYOUR PASSWORD IS NOT SECURE. IT DOES NOT INCLUDE LOWERCASE LETTERS\n";
            safe = false;
            typeNEW++;
        }
        safety = 0;
        for (const char& c: newPass) {
            if (std::isupper(c)) {
                safety++;
            }
        }
        if (safety == 0) {
            std::cout << "\nYOUR PASSWORD IS NOT SECURE. IT DOES NOT INCLUDE UPPERCASE LETTERS\n";
            safe = false;
            typeNEW++;
        }
        safety = 0;
        for (const char& c: newPass) {
            if (std::isdigit(c)) {
                safety++;
            }
        }
        if (safety == 0) {
            std::cout << "\nYOUR PASSWORD IS NOT SECURE. IT DOES NOT INCLUDE NUMBERS\n";
            safe = false;
            typeNEW++;
        }
        safety = 0;
        for (const Password& p: passwords) {
            if (newPass == p.getPassword()) {
                safety++;
            }
        }
        if (safety != 0) {
            std::cout << "\nYOUR PASSWORD IS NOT SECURE. YOU HAVE ALREADY USED IT\n";
            safe = false;
            typeNEW++;
        }
        safety = 0;
        if (newPass.size() < 8) {
            std::cout << "\nYOUR PASSWORD IS NOT SECURE. IT IS TOO SHORT\n";
            safe = false;
            typeNEW++;
        }
        if(safe == false) {
            std::cout << "\nDO YOU WANT TO ENTER NEW PASSWORD\nTYPE '0' IF NO\nTYPE '1' IF YES\n";
            int y;
            std::cin >> y;
            if (y == 1) {
                std::cout << "ENTER A PASSWORD:\n";
                std::cin >> newPass;
                while (safe != true) {
                    safety = 0;
                    for (const char &c: newPass) {
                        if (std::islower(c)) {
                            safety++;
                        }
                    }
                    if (safety == 0) {
                        std::cout << "\nYOUR PASSWORD IS NOT SECURE. IT DOES NOT INCLUDE LOWERCASE LETTERS\n";
                        safe = false;
                        typeNEW++;
                    } else {
                        safe = true;
                    }
                    safety = 0;
                    for (const char &c: newPass) {
                        if (std::isupper(c)) {
                            safety++;
                        }
                    }
                    if (safety == 0) {
                        std::cout << "\nYOUR PASSWORD IS NOT SECURE. IT DOES NOT INCLUDE UPPERCASE LETTERS\n";
                        safe = false;
                        typeNEW++;
                    } else {
                        safe = true;
                    }
                    safety = 0;
                    for (const char &c: newPass) {
                        if (std::isdigit(c)) {
                            safety++;
                        }
                    }
                    if (safety == 0) {
                        std::cout << "\nYOUR PASSWORD IS NOT SECURE. IT DOES NOT INCLUDE NUMBERS\n";
                        safe = false;
                        typeNEW++;
                    } else {
                        safe = true;
                    }
                    safety = 0;
                    for (const Password &p: passwords) {
                        if (newPass == p.getPassword()) {
                            safety++;
                        }
                    }
                    if (safety != 0) {
                        std::cout << "\nYOUR PASSWORD IS NOT SECURE. YOU HAVE ALREADY USED IT\n";
                        safe = false;
                        typeNEW++;
                    } else {
                        safe = true;
                    }
                    safety = 0;
                    if (newPass.size() < 8) {
                        std::cout << "\nYOUR PASSWORD IS NOT SECURE. IT IS TOO SHORT\n";
                        safe = false;
                        typeNEW++;
                    } else {
                        safe = true;
                    }
                    if (safe == false) {
                        std::cout << "\nDO YOU WANT TO ENTER NEW PASSWORD\nTYPE '0' IF NO\nTYPE '1' IF YES\n";
                        int a;
                        std::cin >> a;
                        if (a == 0) {
                            Password addNewP(newName, newPass, newCategory, newWebsite, newLogin);
                            passwords.push_back(addNewP);
                            safe = true;
                        } else {
                            std::cout << "ENTER A PASSWORD:\n";
                            std::cin >> newPass;
                        }
                    } else {
                        Password addNewP(newName, newPass, newCategory, newWebsite, newLogin);
                        passwords.push_back(addNewP);
                        safe = true;
                    }
                }
                writeToFile();
            } else {
                Password addNewP(newName, newPass, newCategory, newWebsite, newLogin);
                passwords.push_back(addNewP);
                writeToFile();
            }

        }else{
            Password addNewP(newName, newPass, newCategory, newWebsite, newLogin);
            passwords.push_back(addNewP);
            writeToFile();
        }
    }
}
void PasswordManager::editPassword() {
    std::cout << "NAMES OF PASSWORDS:\n";
    int i = 1;
    for (const Password &p: passwords) {
        std::cout << i << ". " << p.getName() << "\n";
        i++;
    }
    std::cout << "TYPE THE NUMBER OF PASSWORD TO EDIT:\n";
    int numToEdit;
    std::cin >> numToEdit;
    std::cout << "\nTYPE THE NUMBER OF A PARAMETER TO EDIT:\n1. NAME\n2. PASSWORD\n3. CATEGORY\n4. WEBSITE\n5. LOGIN\n";
    int numCat;
    std::cin >> numCat;
    std::string toEdit;
    std::cout << "TYPE NEW:";
    std::cin >> toEdit;
    if(numCat == 1){
        passwords[numToEdit - 1].setName(toEdit);
    }else if(numCat == 2){
        passwords[numToEdit - 1].setPassword(toEdit);
    }else if(numCat == 3){
        passwords[numToEdit - 1].setCategory(toEdit);
    }else if(numCat == 4){
        passwords[numToEdit - 1].setWebsite(toEdit);
    }else if(numCat == 5){
        passwords[numToEdit - 1].setLogin(toEdit);
    }
    passwords[numToEdit - 1].setName(toEdit);
    writeToFile();
 }
void PasswordManager::deletePassword() {
    std::cout << "CRITERIA FOR DELETION\nTYPE NUMBER OF A CRITERIA: \n1. NAME\n2. CATEGORY\n3. WEBSITE\n";
    int numCat;
    std::cin >> numCat;
    if(numCat == 1){
        std::cout << "NAMES OF PASSWORDS:\n";
        int i = 1;
        for(const Password& p : passwords){
            std::cout << i << ". " << p.getName() << "\n";
            i++;
        }
        std::cout << "TYPE THE NAME TO DELETE:";
        std::string nameDel;
        std::cin >> nameDel;
        int all = 0;
        for(const Password& p : passwords){
             if(p.getName() == nameDel){
                 all++;
             }
        }
        if(all != 0){
            std::cout << all << " PASSWORD(S) WILL BE DELETED\nIF YOU AGREE, TYPE '1', ELSE, TYPE '0'\n";
            int w;
            std::cin >> w;
            if(w == 1){
                passwords.erase(std::remove_if(passwords.begin(), passwords.end(),
                                               [&nameDel](const Password& p) {
                                                   return p.getName() == nameDel;
                                               }),
                                passwords.end());
                writeToFile();
            }
        }
    }else if(numCat == 2){
        std::cout << "\nDELETE CATEGORY:\n";
        for(std::string c : categories){
            std::cout << c << "\n";
        }
        std::string delC;
        std::cin >> delC;
        int all = 0;
        for(const Password& p : passwords){
            if(p.getCategory() == delC){
                all++;
            }
        }
        if(all != 0){
            std::cout << all << " PASSWORD(S) WILL BE DELETED\nIF YOU AGREE, TYPE '1', ELSE, TYPE '0'\n";
            int w;
            std::cin >> w;
            if(w == 1){
                passwords.erase(std::remove_if(passwords.begin(), passwords.end(),
                                               [&delC](const Password& p) {
                                                   return p.getCategory() == delC;
                                               }),
                                passwords.end());
                writeToFile();
            }
        }
    }else if(numCat == 3) {
        std::cout << "WEBSITES:\n";
        int i = 1;
        for (const Password &p: passwords) {
            std::cout << i << ". " << p.getWebsite() << "\n";
            i++;
        }
        std::cout << "TYPE THE NAME OF A WEBSITE TO DELETE:\n";
        std::string webDel;
        std::cin >> webDel;
        int all = 0;
        for(const Password& p : passwords){
            if(p.getWebsite() == webDel){
                all++;
            }
        }
        if(all != 0){
            std::cout << all << " PASSWORD(S) WILL BE DELETED\nIF YOU AGREE, TYPE '1', ELSE, TYPE '0'\n";
            int w;
            std::cin >> w;
            if(w == 1){
                passwords.erase(std::remove_if(passwords.begin(), passwords.end(),
                                               [&webDel](const Password& p) {
                                                   return p.getWebsite() == webDel;
                                               }),
                                passwords.end());
                writeToFile();
            }
        }
    }

}
void PasswordManager::timeNow(){
    std::time_t currentTime = std::time(nullptr);
    std::string time = std::ctime(&currentTime);
    timestamp = time;
    hh=timestamp.substr(11, 2);
    mm=timestamp.substr(14, 2);
    ss=timestamp.substr(17, 2);
    std::string month = timestamp.substr(4, 3);
    std::string day = timestamp.substr(8, 2);
    date = month + " " + day;
}