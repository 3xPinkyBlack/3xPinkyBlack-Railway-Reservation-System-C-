#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include "header/requiredFees.h"
#include "header/loginInformation.h"
#include "header/trainInformation.h"
#include "header/reservationDetail.h"
using namespace std;

int flag, PIN = 0;
char s[2] = "S", f[2] = "F";

void adminMenu();                   
void registerNewUser();               
void userManagement();   
void userViewTrainDetail();           
void viewPayedUser();  
void displayPassangerDetail();    


int main() {
     system("color 00");
     int choise;
     string adminPassword= "GROUP-10", password;
     
    for(;;) {
      system("cls");
          cout<<"          *######a            ,###    ,##########,   *####           "<<endl;
          cout<<"           *##   *#          ,#**##  *#^  *##*  ^#*   *##            "<<endl;
          cout<<"            ##    *#        ,#*  ##        ##          ##            "<<endl;
          cout<<"            #####*#        ,#*   ##        ##          ##            "<<endl;
          cout<<"            ##  ##        ,#*****##        ##          ##            "<<endl;
          cout<<"            ##   ##      ,#*     ##        ##          ##            "<<endl;
          cout<<"           ,##    ##    ,#*      ##  ,#,  ,##,  ,#,  ,###,    ,*#,  "<<endl;
          cout<<"          *###     ##* ,#*       ##   *##########*    *#########*    "<<endl;

	      cout<<"\n\t\tWelcome To The Railway Reservation system\n\n";
          cout<<"\n\t\tEnter The Administrator Password -->> ";
          cin>>password;

                if(password == adminPassword) {
     	           adminMenu();
                } else {
                    cout<<"\n\tYou Password is Incorrect\n\t\tLogging Out...";
                    getch();
                }
    }
}

void adminMenu() {
	system("cls");
	loginInformation LI;  
	trainInformation TI;  
	int choose;
    char reAdd;
    fstream trainInfo;   

      system("cls");
      cout<<"\n\tWelcome To The Administrator Menu\n\n";
      cout<<"\t\t[ 1 ] User Management Menu\n\t\t[ 2 ] Add Train Details\n\t\t[ 3 ] Display Passangers Detail\n\t";
      cout<<"\t[ 4 ] Display Train Details\n\t\t[ 5 ] Return To Main Menu\n\n\t\tEnter Your choice -->> ";
      cin>>choose;

       switch(choose) {
       	case 1:
       	      userManagement();
              break;
        case 2:
              trainInfo.open("trainInfo.GROUP-10",ios::out | ios::binary | ios::app);
          do {
              TI.getTrainInformation();                        
              trainInfo.write((char *) & TI, sizeof(TI));  
              cout<<"Do You Want to Add one More Record Y/N: ";
              cin>>reAdd;
          } while(reAdd == 'y' || reAdd == 'Y');

              trainInfo.close();   
              break;
        case 3:
               displayPassangerDetail();
               break;
        case 4: 
                system("cls");
                cout<<"\nTrains Available To Go\n\n";
                trainInfo.open("trainInfo.GROUP-10",ios::in); 
                trainInfo.seekg(0);    
                  
                  while(trainInfo.read((char *)&TI,sizeof(TI))) {
                      TI.viewTrainDetail();
                  }
                trainInfo.close();
                getch();
                break;
        case 5: 
            return;
        default:
          break;
       }
    adminMenu();
}

void registerNewUser() {
	system("cls");
    loginInformation LI;      
    fstream userFileLogin, wallet;
    userFileLogin.open("userFileLogin.GROUP-10",ios::in | ios::binary);
    wallet.open("userWallet.GROUP-10", ios::app | ios::out | ios::binary);
    char userSSN[100];
    flag = 0;

    cout<<"\n\n\t\tEnter User SSN -->> ";
    cin.ignore();
    cin.get(userSSN, 30);
    
        userFileLogin.seekg(0,ios::beg);             
        while(userFileLogin.read((char *)&LI,sizeof(LI)) && flag == 0) {
            if(strcmp(LI.SSN, userSSN) == 0) {      
                   flag = 1;
            }
        }

     userFileLogin.close();  
     userFileLogin.open("userFileLogin.GROUP-10",ios::app | ios::out | ios::binary);

     if(flag == 0) {        
         LI.getNewUserInfo(userSSN);   
         userFileLogin.write((char *)&LI, sizeof(LI));
         userFileLogin.close();
         cout<<"\n\t\tPassword For This Account "<<LI.PASSWORD<<endl;
         cout<<"\n\t\tKeep Your Password In Safe Place";   
         cout<<"\n\t\tDear "<<LI.username<<" You Are Sucessfully Registered ";
     }

     if(flag == 0) {
        cout<<"\n\tBut One Last Step Enter Your Credit Information\n";
        LI.getCreditInfo(userSSN);
        wallet.write((char *)&LI, sizeof(LI));
        wallet.close();
        cout<<"\n\t\tYou Have "<<LI.money<<" Birr on Your Wallet\n";
     }

     if(flag == 1) {
         cout<<"\n\t"<<userSSN<<" is Already Registered Please Try Another User";   
     }

    getch();
    getch();
    getch();
}

void userManagement() {
    fstream userManage;
    loginInformation LI;
    char c;
    int ch;
	
    do {
	    system("cls");
    	cout<<"\n\tWelcome To The User Administration Menu\n";
        cout<<"\n\t\t[ 1 ] Add New Users\n";
        cout<<"\t\t[ 2 ] View All Users\n\t\t[ 3 ] View Paid Users\n\t\t[ 4 ] Return to Main Menu\n";
        cout<<"\t\tEnter your choice -->> ";
        cin>>ch;
        cout<<endl;
        switch(ch) {
         case 1:
            do {
                registerNewUser();
                cout<<"\n\t\tDo You Want To Add One More Record Y-Yes N-No -->>";
                cin>>c;
            } while(c=='Y' || ch == 'y');
              break;
         case 2:
            userManage.open("userFileLogin.GROUP-10",ios::in | ios::binary);
            userManage.seekg(0);
            cout<<"SSN\t\tName\t\t\t\tPassword\n";
            cout<<"--\t\t----\t\t\t\t--------\n";
             while(userManage.read((char *) & LI,sizeof(LI))) {
                LI.displayUserInformation();
             }
            getch();
            userManage.close();
            break;
         case 3:
           viewPayedUser();
           break;
        }
    }
    while(ch<=3);
    adminMenu();
}

void viewPayedUser() {
    requiredFees RF;
    fstream payFee;
    payFee.open("payRequiredFee.GROUP-10",ios::in);
      cout<<"User SSN\tTrain Number\tNumber of Seat\tFees\tClass\tDate\tPIN"<<endl;
      cout<<"--------\t------------\t--------------\t----\t-----\t---\t----"<<endl;
      
         while(payFee.read((char *)&RF, sizeof(RF))) {
             RF.viewPayedDetail();
         }
    getch();
}

void displayPassangerDetail() {
  system("cls");
  fstream passengerDetail;
  reservationDetail RD;
  passengerDetail.open("passengerDetail.GROUP-10",ios::in | ios::out | ios::binary);
  passengerDetail.seekg(0);

    if(passengerDetail == NULL) { 
         cout<<"No Passenger Details Available";
    } else {
        cout<<"\n\tAvailable Passengers Detail\n";
         while(passengerDetail.read((char *) & RD,sizeof(RD))) {
           RD.viewReservationDetail();
         }
       passengerDetail.close();
    }
   getch();
}



