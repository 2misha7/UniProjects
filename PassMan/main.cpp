#include <iostream>
#include "PasswordManager.hpp"
//key password for source.txt is "123"
using namespace std;
auto main() -> int {
    PasswordManager pm;
    pm.chooseSourceFile();
    pm.enterPassword();
    bool run = true;
    int x;
    while(run){
        cout << "\nSELECT THE NUMBER OF A FUNCTION TO EXECUTE:"
              "\n1.SEARCH PASSWORDS\n2.SORT PASSWORDS\n3.ADD PASSWORD"
              "\n4.EDIT PASSWORD\n5.DELETE PASSWORD(s)\n6.ADD CATEGORY\n7.DELETE CATEGORY\n";
        cin >> x;
        if (x == 1) {
          pm.searchPasswords();
          run = false;
        }else if (x == 2) {
          pm.sortPasswords();
          run = false;
        }else if (x == 3) {
          pm.addPassword();
           run = false;
        }else if (x == 4) {
             pm.editPassword();
          run = false;
      }else if (x == 5) {
          pm.deletePassword();
          run = false;
      }else if (x == 6) {
          pm.addCategory();
          run = false;
      }else if (x == 7) {
          pm.deleteCategory();
          run = false;
      }else if(x == 8){
          run = false;
      }else{
          cout << "THIS FUNCTION DOES NOT EXIST\n";
          run = false;
      }
      cout << "IF YOU WANT TO CONTINUE, TYPE 1\nELSE, TYPE 0\n";
      cin >> x;
      if(x == 1){
          run = true;
      }
  }

}
