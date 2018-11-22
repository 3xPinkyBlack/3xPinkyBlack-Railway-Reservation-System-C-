#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;

class loginInformation {

    public:
    	char username[100], SSN[100], creditCard[100];
        int money, PASSWORD;
        time_t t;
       // unsigned srand((unsigned) time(&t));

		
      void getNewUserInfo(char *userSSN) {
          strcpy(SSN, userSSN);
          cout<<"\t\tEnter User Full Name ---------->> ";
          cin.ignore();
          cin.get(username,30);
          PASSWORD = rand() + 1;
      }
     
      void getCreditInfo(char *userSSN) {
          strcpy(SSN, userSSN);
          cout<<endl<<"\n\t\tEnter Your Credit Card Number\n\t\t (e.g 5273 2345 1234 4323) ";
          cin.ignore();
          cin.get(creditCard, 30);
          money = rand() % 30 + 700;
      }

      void displayUserInformation() {
        cout<<SSN<<"\t\t"<<username<<"\t\t\t**********"<<endl;
      }

};

