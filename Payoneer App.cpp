#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include "header/requiredFees.h"
#include "header/loginInformation.h"
using namespace std;

int flag, PIN = 0;
char s[2] = "S", f[2] = "F";

void payRequiredFee(char*);
void RailPay();

int main() {
      system("cls");
	  char ch;
          cout<<"          *######a            ,###    ,##########,   *####           "<<endl;
          cout<<"           *##   *#          ,#**##  *#^  *##*  ^#*   *##            "<<endl;
          cout<<"            ##    *#        ,#*  ##        ##          ##            "<<endl;
          cout<<"            #####*#        ,#*   ##        ##          ##            "<<endl;
          cout<<"            ##  ##        ,#*****##        ##          ##            "<<endl;
          cout<<"            ##   ##      ,#*     ##        ##          ##            "<<endl;
          cout<<"           ,##    ##    ,#*      ##  ,#,  ,##,  ,#,  ,###,    ,*#,  "<<endl;
          cout<<"          *###     ##* ,#*       ##   *##########*    *#########*    "<<endl;

	    cout<<"\n\t\tWelcome To The Railway Reservation system\n\n";
		cout<<"\n\t\tGo To RailPay Y/N-->> ";
		cin>>ch;
		  switch(ch) {
		     case 'Y':
			    RailPay();
				break;
			 case 'y':
			    RailPay();
				break;
		  }
	return 0;
}

void RailPay() {
    system("cls");
    requiredFees RF;
    fstream payFee;
    char SSN[100];
    int check = 0;
	  payFee.open("payRequiredFee.GROUP-10", ios::in | ios::out | ios::binary);
    cout<<"\n\tWelcome To RailPay.com The Safest Way To Shop Online\n";
    cout<<"\n\t\tEnter Your SSN You Used To Signup -->> ";
    cin.ignore();
    cin.get(SSN, 30);
       while(payFee.read((char *)&RF, sizeof(RF))) {
          if((strcmp(SSN, RF.userSSN) == 0) && (RF.userPIN == 0)) {
              check = 1;
              break;
          }
		  
		  if((strcmp(SSN, RF.userSSN) == 0) && (RF.userPIN != 0)) {
		      check = 2;
		  }
      }

      if(check == 0) {
          cout<<"\n\tYou Entered an Invalid Social Security Number\n";
      } else if(check == 1) {
         payRequiredFee(SSN);
      } else if(check == 2) {
	     cout<<"\n\tYou Have Already Pay The Required Fee\n";
	  }
	getch();
}

void payRequiredFee(char* SSN) {
    requiredFees RF;
    loginInformation LI;
    fstream payFee, wallet;
    payFee.open("payRequiredFee.GROUP-10",ios::in | ios::out | ios::binary);

    char choice;
    int check = 0, pos, pos1;

     while(payFee.read((char *)&RF, sizeof(RF))) {
         if((strcmp(SSN, RF.userSSN) == 0) && (RF.userPIN == 0)) {
             time_t t;
             srand((unsigned) time(&t));
             PIN = rand() / 10;

                RF.getPayingDetail(SSN, RF.userNumberofSeat, RF.userTotalFees, RF.userReservedClass, RF.userTrainNum, PIN);
                cout<<"\n\tDo You Want To Pay "<<RF.userTotalFees<<" Birr For "<<RF.userNumberofSeat<<" Seats? Yes [ Y ] No [ N ] -->> ";
                cin>>choice;

                     if(choice == 'Y' || choice == 'y') {
                         wallet.open("userWallet.GROUP-10",ios::in | ios::out | ios::binary);
                         wallet.seekg(0, ios::beg);
                         while(wallet.read((char *)&LI, sizeof(LI))) {
                             if(strcmp(SSN, LI.SSN) == 0) {
                                LI.money -= RF.userTotalFees;
                                pos = wallet.tellg();
                                wallet.seekp(pos - (2 * (sizeof(LI.money))));
                                wallet.write((char *)&LI.money, sizeof(LI.money));
                             }
                         } 
                         wallet.close();     
                                cout<<"\n\t\tThank\'s For Paying The Required Fee\n\t\tNow You Can Reserve "<<RF.userNumberofSeat<<" Seats After 3 Hours"<<endl;
                                cout<<"\tYou Will Get A PIN Number and Other Informations In Your Message Box\n";
                                pos1 = -1 * sizeof(RF); 
                                payFee.seekp(pos1, ios::cur);
                                payFee.write((char *)&RF, sizeof(RF));
                                payFee.close();
                     } else {
                          cout<<"\n   You Didn\'t Accept To Pay The Required Fee Thank\'s For Using Our System\n";
                     }
             check = 1;
         }
     }
    getch();
}
     

