#include <iostream>
#include <string>
#include <vector>
using namespace std;

   class inmates{
   private:
       
       string name;
       string earpodID;
       vector<int> sleeptime;
       int timetofallAsleep;
       bool asleep;
       
    public:
       
       inmates( string m, string id, vector<int> stime, int Time):
       
              name(m),
              earpodID(id),
              sleeptime(stime),
              timetofallAsleep(Time),
              asleep(false)   {}
              
       string inName() const {
           
             return name;
       }
       string getEarpodID() const {
       
             return earpodID;
       }

       vector<int> getSleeptime() const {
           
             return sleeptime;
       }

       int getTimeToFallAsleep() const {
       
             return timetofallAsleep;
       }

       bool giveAsleep() const {
        
             return asleep;
       }

       void setSleepstatus(bool status) {
        
             asleep = status;
       }
       
       
   };
