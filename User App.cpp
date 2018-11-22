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

void userAccount(char*,int);                  
void registerNewUser();             
void userViewTrainDetail();      
void redirectReserveTrain(char*);              
void reserveTrain(char*,int);            
void deleteFeeAfterReserve(char*,int);     //Delete Paid Fee After Reservation
void cancelReservation(char*);             //Cancel Reservation
void updateAfterCancel();                  //Update Paid Fee After Cancellation
void updateReservation(int, char*);
void checkFee(char*);
void messageBox(char*);
void cancelPayment(char*);
void cancellAllPayment(char*);
void cancelSinglePayment(char*,int);
void wallet(char*);

int main() {
     system("color 00");
     int ch, userPassword;
     char userSSN[100];
     
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
		  cout<<"\tWellcome To The User Account Menu\n";
		  cout<<"\n\t\t[ 1 ] To Register New Account\n\t\t[ 2 ] To Login\n\t\t[ 3 ] To Exit The Application\n\t\tEnter Your Choice -->> ";
		  cin>>ch;

			  if(ch == 1) {
				  registerNewUser();
			  } else if(ch == 2) {
                   system("cls");
                   cout<<"\n\tEnter Your SSN ------->> ";
                   cin.ignore();
                   cin.get(userSSN, 30);
                   cout<<"\n\tEnter Your Password -->> ";
                   cin>>userPassword;
				   userAccount(userSSN, userPassword);
			  }
			  getch();
    }
}

void registerNewUser() {
	system("cls");
    loginInformation LI;      
    fstream userFileLogin, wallet;
    userFileLogin.open("userFileLogin.GROUP-10",ios::in | ios::binary);
    wallet.open("userWallet.GROUP-10", ios::app | ios::out | ios::binary);
    char userSSN[100];
    flag = 0;
    int userPassword;

    cout<<"\n\n\t\tEnter Social Security Number -->> ";
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
         userPassword = LI.PASSWORD;
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
       getch();
       system("cls");
       userAccount(userSSN,userPassword);
     }

     if(flag == 1) {
         cout<<"\n\t"<<userSSN<<" is Already Registered Please Try Another User";   
     }

    getch();
    getch();
}

void userAccount(char *userSSN, int userPassword) {
  system("cls");
  loginInformation LI;
  fstream userFileLogin;
  int passengerNum;
  userFileLogin.open("userFileLogin.GROUP-10",ios::app | ios::in | ios::out | ios::binary);

     while(userFileLogin.read((char *)&LI, sizeof(LI))) {
        if((strcmp(LI.SSN,userSSN) == 0)){
          if((LI.PASSWORD == userPassword)) {
	          int ch;
             h:
              system("cls");
	          cout<<"\n\t"<<LI.username<<" Welcome To Your Account\n"<<endl;
              cout<<"\t\t[ 1 ] Check The Required Fee\n\t\t[ 2 ] Reserve Train\n\t\t[ 3 ] Cancell Reservation";
              cout<<"\n\t\t[ 4 ] Update Reservation\n\t\t[ 5 ] View Train Informations\n\t\t[ 6 ] View Messages";
              cout<<"\n\t\t[ 7 ] Cancell Payment\n\t\t[ 8 ] My Wallet\n\t\t[ 9 ] Return to Main Menu\n";
              cout<<"\t\tEnter your choice -->> ";
              cin>>ch;
              cout<<endl;
              switch(ch) {
              case 1:
                  checkFee(LI.SSN);
                  goto h;
                  break;
              case 2:
                  redirectReserveTrain(LI.SSN);
                  goto h;
                  break;
              case 3:
                  cancelReservation(LI.SSN);
                  goto h;
                  break;
              case 4:
                  cout<<"Enter The Passenger Number -->> ";
                  cin>>passengerNum;
                  
                  updateReservation(passengerNum, LI.SSN);    
                  goto h;
                  break;
              case 5:
                  userViewTrainDetail();
                  goto h;
                  break;
              case 6:
                  messageBox(LI.SSN);
				  goto h;
                  break;
              case 7:
                  cancelPayment(LI.SSN);
                  goto h;
                  break;
              case 8:
                  wallet(LI.SSN);
                  goto h;
                  break;
              }
          } 
        }
     }
}

void userViewTrainDetail(){
    system("cls");
    fstream trainInfo;
    trainInfo.open("trainInfo.GROUP-10",ios::in | ios::out | ios::binary);
    trainInformation TI;
    cout<<"\n\tAvailable Trains For Now\n\n";
    while(trainInfo.read((char *) & TI,sizeof(TI))){
        TI.viewTrainDetail();
    }
    getch();
}

void reserveTrain(char *SSN, int PIN) {
   system("cls");
    requiredFees RF;
    trainInformation TI;
    reservationDetail RD;
    fstream trainInfo, passengerDetail, payFee;

    time_t t, now = time(0);
    tm *ltm = localtime(&now);
	
    int hour, day, mis, checkGet = 0;
    hour = ltm ->tm_hour; 
    day = ltm ->tm_mday;     
    
    flag = 0;  

   payFee.open("payRequiredFee.GROUP-10",ios::app | ios::in | ios::out | ios::binary);   
   
   payFee.seekg(0);
   payFee.read((char *)&RF, sizeof(RF));
  
     while(!payFee.eof()) {
        if((strcmp(SSN, RF.userSSN) == 0) && (PIN == RF.userPIN)) {  //Check User SSN and User PIN are The Same
           if((RF.day == day)) {
               if((hour - RF.hour) >= 3) {
                   flag = 2;
                   break;
               } else {
                 flag = 1;
                 mis = RF.hour;
               }
           }

           if((RF.day != day)) {
               flag = 2;
               break;
           }
        }
        payFee.read((char *)&RF, sizeof(RF));
     }

       if(flag == 0) {  
            cout<<"\n\tYou Are Not Allowed To Reserve You Must Pay The Required Fee First\n";
       } else if(flag == 1) {
            cout<<"\n\tYou Have To Wait "<<3 - (hour - mis)<<" or Less Hour Before Reservation"<<endl;
       } else if(flag == 2) { 
            trainInfo.open("trainInfo.GROUP-10",ios::in | ios::out | ios::binary);
            passengerDetail.open("passengerDetail.GROUP-10",ios::in | ios::out | ios::binary | ios::app);
            int ch;

            while(trainInfo.read((char *)&TI,sizeof(TI))) {
                if(TI.trainNum == RF.userTrainNum) {   //If The Train Number is Same us User Train Number
                   RD.getReservationDetail(SSN,RF.userNumberofSeat, RF.userReservedClass, RF.userTrainNum, TI.trainName, TI.boardingPoint, TI.destinationPoint, TI.day, TI.month, TI.year);
                   srand((unsigned) time(&t));
                   RD.passengerNum = rand();         
                   passengerDetail.write((char *)&RD,sizeof(RD));  
                   RD.viewReservationDetail();                      
                   cout<<"--------------Your Ticket is Reserved-----------\n";
                   cout<<"-----------------End of Reservation Menu-------\n";
                 }
              } 
       }

       payFee.close();
       trainInfo.close();
       passengerDetail.close();

       if(flag == 2) {
            deleteFeeAfterReserve(SSN, PIN);
       }
      getch();
}

void deleteFeeAfterReserve(char *SSN,int PIN) {
       requiredFees RF;
       ifstream payFee;
	   ofstream deleteFee;
       payFee.open("payRequiredFee.GROUP-10",ios::binary);
       deleteFee.open("deleteFee.GROUP-10",ios::out | ios::binary);
       
       payFee.seekg(0,ios::beg);
           while(payFee.read((char *)&RF,sizeof(RF))) {
               if((strcmp(RF.userSSN, SSN) != 0) || ((strcmp(RF.userSSN, SSN) == 0) && (RF.userPIN != PIN))) {
                   deleteFee.write((char *)&RF, sizeof(RF));
               }
           }
        payFee.close();
        deleteFee.close();
        
        remove("payRequiredFee.GROUP-10");
        rename("deleteFee.GROUP-10","payRequiredFee.GROUP-10");
}

void cancelReservation(char *SSN) {
    system("cls");
    fstream payFee;
    ifstream passengerDetail, trainInfo;
	ofstream cancelReserveFile;
	reservationDetail RD;
    trainInformation TI;
	requiredFees RF;
    int passengerNum,totalFees, check = 0;
    char userSSN[100];
    strcpy(userSSN, SSN);
    flag = 0;

    cout<<"\tCancellation Menu\n\n";
    cout<<"Enter The Passenger Number -->> ";
    cin>>passengerNum;

    trainInfo.open("trainInfo.GROUP-10",ios::binary);
    passengerDetail.open("passengerDetail.GROUP-10",ios::binary);
    cancelReserveFile.open("cancelReserve.GROUP-10",ios::out | ios::binary);
    payFee.open("payRequiredFee.GROUP-10",ios::in | ios::out | ios::app | ios::binary);

    passengerDetail.seekg(0,ios::beg);
      while(passengerDetail.read((char *)&RD,sizeof(RD))) {
           if(RD.passengerNum != passengerNum || ((strcmp(RD.userSSN, userSSN) != 0) && (RD.passengerNum == passengerNum))) {
                cancelReserveFile.write((char *)&RD, sizeof(RD));
           }
           if(RD.passengerNum == passengerNum && (strcmp(RD.userSSN, userSSN) == 0)) {
                  while(trainInfo.read((char *)&TI, sizeof(TI)) && check == 0) {
                       if(RD.trainNum == TI.trainNum) {
                           if(strcmp(RD.reservedClass, f) == 0) {
                               totalFees = RD.numberofSeat * TI.feesPerTicketIn1Class;
                           }

                           if(strcmp(RD.reservedClass, s) == 0) {
                               totalFees = RD.numberofSeat * TI.feesPerTicketIn2Class;
                           }
								check = 1;
                       }
                  }

                  time_t t;
                  srand((unsigned) time(&t));
                  PIN = rand() / 10;
                  RF.getPayingDetail(RD.userSSN, RD.numberofSeat, totalFees, RD.reservedClass, RD.trainNum, PIN);
                  payFee.write((char *)&RF, sizeof(RF));
                  cout<<"  Your Reservation Cancelled Sucessfully With "<<passengerNum<<" Passenger Number \n";
            }
       }
        
    if(flag == 0) {
        cout<<"  You Entered Invalid Passenger Number\n";
    }
        payFee.close();
        passengerDetail.close();
        cancelReserveFile.close();
 
        remove("passengerDetail.GROUP-10");
        rename("cancelReserve.GROUP-10","passengerDetail.GROUP-10");
}

void updateReservation(int passengerNum, char *SSN) {
    fstream passengerDetail, trainInfo;
    reservationDetail RD;
    flag = 0;
    passengerDetail.open("passengerDetail.GROUP-10",ios::in | ios::out | ios::binary);
    trainInfo.open("trainInfo.GROUP-10",ios::in | ios::binary);
    int foundPassNum = 0, pos;     

     while(passengerDetail.read((char *)&RD,sizeof(RD))) {
        if((RD.passengerNum == passengerNum) && (strcmp(RD.userSSN, SSN) == 0) && (foundPassNum == 0)){
               cout<<"\n\tYour Reservation Detail\n";
               RD.viewReservationDetail();

               cout<<"\n\tEnter The New Detail\n";
               RD.getReservationDetail(SSN,RD.numberofSeat, RD.reservedClass, RD.trainNum, RD.trainName, RD.boardingPoint, RD.destinationPoint,RD.day,RD.month,RD.year);
               pos = -1 * sizeof(RD);
               passengerDetail.seekp(pos, ios::cur);
            
               passengerDetail.write((char *)&RD, sizeof(RD));
               cout<<"\n\tYour Reservation Updated Sucessfully\n";
               foundPassNum = 1;
               flag = 1;
        }
    }

    if(flag==0) {
        cout<<"\nEnter The Correct Passenger Number\n";
    }
    
    passengerDetail.close();
    getch();
}

void checkFee(char *SSN) {
    trainInformation TI;
    requiredFees RF;
    loginInformation LI;
	fstream trainInfo, payFee, wallet;

    payFee.open("payRequiredFee.GROUP-10",ios::app | ios::in | ios::out | ios::binary);
	trainInfo.open("trainInfo.GROUP-10",ios::in | ios::out | ios::binary);
    wallet.open("userWallet.GROUP-10",ios::in | ios::binary);
    
    PIN = 0;
    int numberofSeat, totalFees, trainNum, check = 0, pos, checkMoney = 0;
    char reservedClass[2], s[2] = "S", f[2] = "F";

    cout<<"\n\tEnter The Train Number  -->> ";
    cin>>trainNum;
    cout<<"\tEnter The Number of Seats -->> ";
    cin>>numberofSeat;
    cout<<"\tEnter The Class To Reserve [ F / S ]  -->> ";
    cin>>reservedClass;
       
     while(trainInfo.read((char *)&TI, sizeof(TI)) && check == 0) {
           if(trainNum == TI.trainNum) {
                if((strcmp(reservedClass, f) == 0) && (numberofSeat <= TI.numberofSeatsIn1Class)) {
                    totalFees = numberofSeat * TI.feesPerTicketIn1Class;
                    while(wallet.read((char *)&LI, sizeof(LI))) {
                        if(strcmp(SSN, LI.SSN) == 0) {
                            if(LI.money >= totalFees) {
                                cout<<"\n  Goto RailPay.com and Pay "<<totalFees<<" Birr For This Address headeratanon@gmail.com\n";
                                RF.getPayingDetail(SSN, numberofSeat, totalFees, reservedClass, trainNum, PIN);
                                payFee.write((char *)&RF, sizeof(RF));
                                TI.numberofSeatsIn1Class -= numberofSeat;
                                pos = trainInfo.tellg();
                                trainInfo.seekp(pos - (4 * (sizeof(TI.numberofSeatsIn1Class))));
                                trainInfo.write((char *)&TI.numberofSeatsIn1Class, sizeof(TI.numberofSeatsIn1Class));
                                checkMoney = 0;
                            } else {
                                checkMoney = 1;
                            }
                        }
                    }
                    flag = 1;
                }

                if((strcmp(reservedClass, s) == 0) && (numberofSeat <= TI.numberofSeatsIn2Class)) {
                    totalFees = numberofSeat * TI.feesPerTicketIn2Class;
                    while(wallet.read((char *)&LI, sizeof(LI))) {
                        if(strcmp(SSN, LI.SSN) == 0) {
                            if(LI.money >= totalFees) {
                                cout<<"\n  Goto RailPay.com and Pay "<<totalFees<<" Birr For This Address headeratanon@gmail.com\n";
                                RF.getPayingDetail(SSN, numberofSeat, totalFees, reservedClass, trainNum, PIN);
                                payFee.write((char *)&RF, sizeof(RF));
                                TI.numberofSeatsIn2Class -= numberofSeat;
                                pos = trainInfo.tellg();
                                trainInfo.seekp(pos - (3 * (sizeof(TI.numberofSeatsIn2Class))));
                                trainInfo.write((char *)&TI.numberofSeatsIn2Class, sizeof(TI.numberofSeatsIn2Class));
                                checkMoney = 0;
                            } else {
                                checkMoney = 1;
                            }
                        }
                    }
                    flag = 1;
                } 
                check = 1;
            }
        }

      if(check == 0) {
          cout<<"\n\t\tYou Entered a Wrong Train Number\n";
      } else if(flag == 0) {
          cout<<"\n\t\tThe Number of Seats is Not Available\n";
      }

      if(checkMoney == 1) {
          cout<<"\n\n\tYou Dont Have Enough Money In Your Wallet\n";
      }
    getch();
}

void redirectReserveTrain(char *SSN) {
    int check = 0;
    requiredFees RF;
    fstream payFee;
    payFee.open("payRequiredFee.GROUP-10", ios::in | ios::binary);
    cout<<"Enter Your PIN Number -->> ";
    cin>>PIN;
    
     while(payFee.read((char *)&RF, sizeof(RF))) {
          if(strcmp(SSN, RF.userSSN) == 0) {
              if(RF.userPIN == 0) {
                  check = 1;
              }

              if(PIN == RF.userPIN) {
                  check = 2;
              }
          }
     }
      payFee.close();

        if(check == 0 || check == 1) {
            cout<<"\n\t\tInvalid PIN Number You Did Not Pay The Required Fee\n";
        }

        if(check == 2) {
           reserveTrain(SSN,PIN);
        }
        getch();
}

void messageBox(char *SSN) {
      system("cls");
      requiredFees RF;
      fstream payFee;
      flag = 0;
      
      payFee.open("payRequiredFee.GROUP-10",ios::in | ios::binary);
      
      cout<<"\tTrain Number\tNumber of Seat\tTotal Fee\tClass\tPIN Number"<<endl;
      cout<<"\t------------\t--------------\t---------\t-----\t--- ------"<<endl;

      payFee.seekg(0,ios::beg);
      while(payFee.read((char *)&RF, sizeof(RF))) {
          if(strcmp(SSN, RF.userSSN) == 0) {
              if(RF.userPIN != 0) {
                  cout<<"\t "<<RF.userTrainNum<<"\t\t "<<RF.userNumberofSeat<<"\t\t"<<RF.userTotalFees<<"\t\t"<<RF.userReservedClass<<"\t"<<RF.userPIN<<endl;
                  flag = 1;
              }

              if(RF.userPIN == 0) {
              	  cout<<"\t "<<RF.userTrainNum<<"\t\t "<<RF.userNumberofSeat<<"\t\t"<<RF.userTotalFees<<"\t\t"<<RF.userReservedClass<<"\t"<<"Pending..."<<endl;
       
                  flag = 2;
              }
          }
      }

       if(flag == 0) {
           cout<<"\n\t\tYou Don\'t Have Any Message Yet\n";
       }
    getch();
}

void cancelPayment(char *SSN) {
    requiredFees RF;
    fstream payFee, trainInfo, tempo1, tempo2;
	int check = 0, choice, aabb = 0;
    char ch;

    payFee.open("payRequiredFee.GROUP-10",ios::in | ios::binary);

    cout<<"\tTrain Number\tNumber of Seat\tTotal Fee\tClass\tPIN Number"<<endl;
    cout<<"\t------------\t--------------\t---------\t-----\t--- ------"<<endl;
      while(payFee.read((char *)&RF, sizeof(RF))) {
          if(strcmp(SSN, RF.userSSN) == 0) {
             if(RF.userPIN != 0) {
                  cout<<"\t "<<RF.userTrainNum<<"\t\t "<<RF.userNumberofSeat<<"\t\t"<<RF.userTotalFees<<"\t\t"<<RF.userReservedClass<<"\t"<<RF.userPIN<<endl;
                  flag = 1;
              }

              if(RF.userPIN == 0) {
              	  cout<<"\t "<<RF.userTrainNum<<"\t\t "<<RF.userNumberofSeat<<"\t\t"<<RF.userTotalFees<<"\t\t"<<RF.userReservedClass<<"\t"<<"Pending..."<<endl;
                  flag = 1;
              }
              check = 1;
              aabb++;
          }
      }
      payFee.close();

      if(check == 0) {
          cout<<"\n\t\tYou Dont Have Any Payment Yet";
      }
      
      if(flag == 1) {
          cout<<"\n\t\t[ 1 ] Cancell All Payment\n\t\t[ 2 ] Cancell A Single Payment\n";
          cout<<"\n\t\tEnter Your Choice -->> ";
          cin>>choice;
              if(choice == 1) {
                  cout<<"\n\tDo Yo Want To Cancel All Payment [ Y ]-Yes [ N ]-No ";
                  cin>>ch;
                   if(ch == 'Y' || ch == 'y') {
                      cancellAllPayment(SSN);
                   }
              } else if(choice == 2) {
                  cout<<"\n\tEnter The PIN Number You Want To Cancel \n\t(If You Didnt Pay The Fee Press 0 and Enter) ";
                  cin>>PIN;
                      cancelSinglePayment(SSN, PIN);
              }
      }
      
      if(check == 1) {
          
      }
}

void cancellAllPayment(char *SSN) {
    requiredFees RF;
    trainInformation TI;
    loginInformation LI;
    fstream payFee, trainInfo, tempo1, wallet;
    int totalFees = 0, check = 0, pos, pos1;

    payFee.open("payRequiredFee.GROUP-10",ios::in | ios::binary);
    tempo1.open("pay.GROUP-10",ios::app | ios::out | ios::binary);

     while(payFee.read((char *)&RF, sizeof(RF))) {
            if(strcmp(SSN, RF.userSSN) != 0) {
                tempo1.write((char *)&RF, sizeof(RF));
            }

            if(strcmp(SSN, RF.userSSN) == 0) {
             
              wallet.open("userWallet.GROUP-10", ios::in | ios::out | ios::binary);
              wallet.seekg(0,ios::beg);
              while(wallet.read((char *)&LI, sizeof(LI))) {
                   if(strcmp(LI.SSN, RF.userSSN) == 0) {
                       LI.money += RF.userTotalFees;
                       pos1 = wallet.tellg();
                       wallet.seekp(pos1 -(2 * (sizeof(LI.money))));
                       wallet.write((char *)&LI.money, sizeof(LI.money));
                       totalFees += LI.money;
                   }
              }

              wallet.close();

               trainInfo.open("trainInfo.GROUP-10", ios::in | ios::out | ios::binary);
               trainInfo.seekg(0,ios::beg);
               while(trainInfo.read((char *)&TI, sizeof(TI))) {
                   if(RF.userTrainNum == TI.trainNum) {
                      if(strcmp(RF.userReservedClass, f) == 0) {
                          TI.numberofSeatsIn1Class += RF.userNumberofSeat;
				          pos = trainInfo.tellg();
                          trainInfo.seekp(pos - (4 * (sizeof(TI.numberofSeatsIn1Class))));
                          trainInfo.write((char *)&TI.numberofSeatsIn1Class, sizeof(TI.numberofSeatsIn1Class));
                          cout<<"\n\tCancelling Reservation in The First Class [ Sucessfull... ]";
                      } 
                      
                      if(strcmp(RF.userReservedClass, s) == 0) {
                          TI.numberofSeatsIn2Class += RF.userNumberofSeat;
                          pos = trainInfo.tellg();
                          trainInfo.seekp(pos - (3 * (sizeof(TI.numberofSeatsIn2Class))));
                          trainInfo.write((char *)&TI.numberofSeatsIn2Class, sizeof(TI.numberofSeatsIn2Class));
                          cout<<"\n\tCancelling Reservation in The Second Class [ Sucessfull... ]";
                      } 
                   }
               }
              trainInfo.close();
         }
    }
    
    payFee.close();
    tempo1.close();

    remove("payRequiredFee.GROUP-10");
    rename("pay.GROUP-10","payRequiredFee.GROUP-10");

    cout<<"\n\n\t\tYour Payment Cancelled Successfully and Now You Have "<<totalFees<<" Birr\n";
    getch();
}

void cancelSinglePayment(char *SSN,int PIN) {
    requiredFees RF;
    trainInformation TI;
    loginInformation LI;
    fstream payFee, trainInfo, tempo1, wallet;
    int totalFees = 0, check = 0, pos, pos1;
    char ch;

    payFee.open("payRequiredFee.GROUP-10",ios::in | ios::binary);
    tempo1.open("pay.GROUP-10",ios::app | ios::out | ios::binary);
    trainInfo.open("trainInfo.GROUP-10", ios::in | ios::out | ios::binary);
    wallet.open("userWallet.GROUP-10", ios::in | ios::out | ios::binary);

     while(payFee.read((char*)&RF, sizeof(RF))) {
          if((strcmp(RF.userSSN, SSN) != 0) || ((strcmp(RF.userSSN, SSN) == 0) && (RF.userPIN != PIN))) {
                 tempo1.write((char *)&RF, sizeof(RF));
          } 
          
          if((strcmp(RF.userSSN, SSN) == 0) && (RF.userPIN == PIN)) {

              wallet.seekg(0,ios::beg);
              while(wallet.read((char *)&LI, sizeof(LI))) {
                   if(strcmp(LI.SSN, RF.userSSN) == 0) {
                       LI.money += RF.userTotalFees;
                       pos1 = wallet.tellg();
                       wallet.seekp(pos1 -(2 * (sizeof(LI.money))));
                       wallet.write((char *)&LI.money, sizeof(LI.money));
                       totalFees += LI.money;
                   }
              }

               trainInfo.seekg(0,ios::beg);
               while(trainInfo.read((char *)&TI, sizeof(TI))) {
                   if(RF.userTrainNum == TI.trainNum) {
                      if(strcmp(RF.userReservedClass, f) == 0) {
                          TI.numberofSeatsIn1Class += RF.userNumberofSeat;
				          pos = trainInfo.tellg();
                          trainInfo.seekp(pos - (4 * (sizeof(TI.numberofSeatsIn1Class))));
                          trainInfo.write((char *)&TI.numberofSeatsIn1Class, sizeof(TI.numberofSeatsIn1Class));
                          cout<<"\n\tCancelling Reservation in The First Class [ Sucessfull... ]";
                      } 
                      
                      if(strcmp(RF.userReservedClass, s) == 0) {
                          TI.numberofSeatsIn2Class += RF.userNumberofSeat;
                          pos = trainInfo.tellg();
                          trainInfo.seekp(pos - (3 * (sizeof(TI.numberofSeatsIn2Class))));
                          trainInfo.write((char *)&TI.numberofSeatsIn2Class, sizeof(TI.numberofSeatsIn2Class));
                          cout<<"\n\tCancelling Reservation in The Second Class [ Sucessfull... ]";
                      } 
                   }
               }

               check = 1;
          }
         
          if((strcmp(RF.userSSN, SSN) != 0) && (RF.userPIN == PIN)) {
              cout<<"\n\tFailed To Cancel This Reservation ";
          }

     }
    wallet.close();
    trainInfo.close();
    payFee.close();
    tempo1.close();

    remove("payRequiredFee.GROUP-10");
    rename("pay.GROUP-10","payRequiredFee.GROUP-10");
    
    if(check == 1) {
        cout<<"\n\n\t\tYour Payment Cancelled Successfully and Now You Have "<<totalFees<<" Birr in Your Wallet\n";
    }
    getch();
}

void wallet(char *SSN) {
    system("cls");
    loginInformation LI;
    fstream wallet;
     
    wallet.open("userWallet.GROUP-10",ios::in | ios::binary);

    cout<<"\n\t\tCredit Card Number\tMoney On Credit Card\n";
    cout<<"\t\t------------------\t--------------------\n";
    while(wallet.read((char *)&LI, sizeof(LI))) {
        if(strcmp(SSN, LI.SSN) == 0) {
            cout<<"\t\t"<<LI.creditCard<<"\t\t"<<LI.money<<" Birr"<<endl;
        }
    }
    getch();
}

