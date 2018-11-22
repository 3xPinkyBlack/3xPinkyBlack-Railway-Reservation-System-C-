#include <iostream>
using namespace std;

class trainInformation {

   public:
	   int trainNum;
	   char trainName[15];
	   char boardingPoint[15];
	   char destinationPoint[15];
	   int month, day, year;
       int numberofSeatsIn1Class, numberofSeatsIn2Class, feesPerTicketIn1Class, feesPerTicketIn2Class;
       
       //This Function Used To Get The Train Informations That Are Ready To Reserved From The Administrator
	   void getTrainInformation() {
          cout<<"Enter The Train Number: ";
		      cin>>trainNum;
          cout<<"Enter The Train Name: ";
          cin.ignore();
          cin.get(trainName,14);
          cout<<"Enter The Boarding Point: ";
          cin.ignore();
          cin.get(boardingPoint,14);
          cout<<"Enter The Destination Point: ";
          cin.ignore();
          cin.get(destinationPoint,14);
          cout<<"Number of Seats In First Class: ";
          cin>>numberofSeatsIn1Class;
          cout<<"Fees Per Ticket In The First Class: ";
          cin>>feesPerTicketIn1Class;
          cout<<"Number of Seats In The Second Class: ";
          cin>>numberofSeatsIn2Class;
          cout<<"Fees Per Ticket In The Second Class: ";
          cin>>feesPerTicketIn2Class;
          cout<<"Enter The Date of Travel(day/month/year): ";
          cout<<"\tDay----->> ";
          cin>>day;
          cout<<"\tMonth--->> ";
          cin>>month;
          cout<<"\tYear---->> ";
          cin>>year;
	   }
      
    //Displays The Available Train Information Which We Get Its Information From The getTrainInformation() Function
	 void viewTrainDetail() {
         cout<<"\n----------------------------------------------------------------"<<endl;
         cout<<"[ Train Number \t\t] : "<<trainNum<<endl;
         cout<<"[ Trian Name \t\t] : "<<trainName<<endl;
         cout<<"[ Boarding Point  \t] : "<<boardingPoint<<endl;
         cout<<"[ Destination Point \t] : "<<destinationPoint<<endl;
         cout<<"[ Seat In First Class \t] : "<<numberofSeatsIn1Class<<endl;
         cout<<"[ Fees In First Class \t] : "<<feesPerTicketIn1Class<<endl;
         cout<<"[ Seat In Second Class \t] : "<<numberofSeatsIn2Class<<endl;
         cout<<"[ Fees In Second Class \t] : "<<feesPerTicketIn2Class<<endl;
         cout<<"----------------------------------------------------------------"<<endl;
     }
};

