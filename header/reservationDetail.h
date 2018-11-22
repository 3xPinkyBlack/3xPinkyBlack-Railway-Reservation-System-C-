#include <iostream>
#include <string.h>
using namespace std;

class reservationDetail {

  public:
     int passengerNum, trainNum, passengerAge[100], numberofSeat, day, month, year;
	 char trainName[100], boardingPoint[100], destinationPoint[100], passengerName[20][100], reservedClass[2], userSSN[100];
     float amc;
     
     void getReservationDetail(char *usrSSN, int noSeat, char *reClass, int trNum, char *trName, char *brdPoint, char *dstPoint, int dday, int dmonth, int dyear) {
          strcpy(userSSN, usrSSN);
          strcpy(reservedClass, reClass);              
          strcpy(trainName, trName);              
          strcpy(boardingPoint, brdPoint);    
          strcpy(destinationPoint, dstPoint);     
          numberofSeat = noSeat;               
          trainNum = trNum;       
          day = dday;
          month = dmonth;
          year = dyear; 

            cout<<"Enter The "<<numberofSeat<<" Passengers Detail\n\n";
            for(int i=0; i<numberofSeat; i++) {
                cout<<"Enter The Passanger Name: ";
                cin.ignore();
                cin.get(passengerName[i],100);
                cout<<"Enter The Age of The Passanger: ";
				cin.ignore();
                cin>>passengerAge[i];
            }
     }
    
     void viewReservationDetail() {
	     
         cout<<"\n----------------------------------------------------------------"<<endl;
         cout<<"[ Reserved User SSN \t] : "<<userSSN<<endl;
	     cout<<"[ Passenger Number \t] : "<<passengerNum<<endl;
         cout<<"[ Train Number \t\t] : "<<trainNum<<endl;
         cout<<"[ Trian Name \t\t] : "<<trainName<<endl;
         cout<<"[ Boarding Point  \t] : "<<boardingPoint<<endl;
         cout<<"[ Destination Point \t] : "<<destinationPoint<<endl;
         cout<<"[ Reserved Seats \t] : "<<numberofSeat<<endl;
         cout<<"------------------------------------\n";
           for(int i=0; i<numberofSeat; i++) {
           	    cout<<endl;
                cout<<"[ "<<i+1<<" ] Passenger Name: \t-->> "<<passengerName[i]<<endl;
                cout<<"[ "<<i+1<<" ] Passenger Age: \t-->> "<<passengerAge[i]<<endl;
           }
         cout<<"------------------------------------\n";
         cout<<"[ Reserved Class: \t] : "<<reservedClass<<endl;
         cout<<"[ Date of Travel \t] : "<<day<<"/"<<month<<"/"<<year<<endl;
         cout<<"----------------------------------------------------------------\n"<<endl;
     }
};
