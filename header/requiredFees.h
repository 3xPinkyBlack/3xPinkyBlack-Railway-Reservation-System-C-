#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;

class requiredFees {
    
      public:
         int hour, day, userNumberofSeat, userTotalFees, userTrainName, userTrainNum, userPIN;
         char userSSN[100], userReservedClass[100], f[2], s[2];
        
         void getPayingDetail(char *SSN,int numberofSeat,int totalFees, char *reservedClass, int trainNum, int PIN) {
                 time_t now = time(0);
                 tm *ltm = localtime(&now);
            
                strcpy(userSSN, SSN);                      
                strcpy(userReservedClass, reservedClass);
                userPIN = PIN;
                userTrainNum = trainNum;                 
                userTotalFees = totalFees;                
                userNumberofSeat = numberofSeat;        
                hour = ltm ->tm_hour;
                day = ltm ->tm_mday;                    
         }
         
         void viewPayedDetail() {
             cout<<userSSN<<"\t\t "<<userTrainNum<<"\t\t "<<userNumberofSeat<<"\t\t"<<userTotalFees<<"\t  "<<userReservedClass<<"\t "<<day<<"-"<<hour<<"\t"<<userPIN<<endl;
         }
};

