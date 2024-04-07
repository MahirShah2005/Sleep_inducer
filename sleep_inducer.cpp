#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <sstream>
#include<queue>
#include<chrono>
#include<thread>
#include <windows.h>
using namespace std;

 class Inmate{
   public:
       
       string name;
       string earpodID;
       vector<int> sleeptime;
       int timetofallAsleep;
       bool asleep;
       string channel;
       
    public:
       
       Inmate( string m, string id, vector<int> stime, int Time):
       
              name(m),
              earpodID(id),
              sleeptime(stime),
              timetofallAsleep(Time),
              asleep(false),
              channel("")   {}
              
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
       string getchannel() const{
        return channel;
       }
       void setChannel(const string& ch) { 
        channel = ch;
    }

       
 };      
class Dorm {
   
public:
 
    string name;
    vector<string> channels;
    vector<Inmate*> inmates;

public:
   Dorm(){}
    Dorm(string n, vector<string> channels) : name(n), channels(channels) {}

    string getName() const {
        return name;
    }

    vector<string> getchannels() const {
        return channels;
    }


    vector<Inmate*> getInmates() const {
        return inmates;
    }

    void addInmate(Inmate* inmate) {
        inmates.push_back(inmate);
    }
     void addChannel(const string& channel) {
        channels.push_back(channel);
    }

    const vector<string>& getChannels() const {
        return channels;
    }
};
void music(vector<Dorm>& dormslist); //Function declaration
void assigningInmatestoDorms(vector<Inmate>& inmates,vector<Dorm>& dorms) //Function to assign Inmates to Dorm
{
int TotalInmates = inmates.size();  
cout << "Number of Inmates "<< TotalInmates<<endl;
int Totaldorms = dorms.size();
       int inmatesperdorm = TotalInmates/Totaldorms;    
       int remaininginmates = TotalInmates%Totaldorms;
       int j=0; //for inmate
     
       for(int i=0; i<Totaldorms; ++i)  {

        int count = inmatesperdorm + (i < remaininginmates ? 1 : 0);
        cout << "Dorm " << i << " will have " << count << " inmates." << endl;
        for (int k = 0; k < count; ++k) {
            if (j < TotalInmates) {
                dorms[i].addInmate(&inmates[j++]);
                cout << "Assigned Inmate " << j << " to Dorm " << i << endl;
       
        }
       }
}
       for(int i =0; i<Totaldorms;++i){
        const vector<string>& channels = dorms[i].getChannels();
        for (Inmate* inmate : dorms[i].getInmates()) {
            if (j < TotalInmates) {
                inmate->setChannel(channels[j % channels.size()]);
                cout << "Assigned " << inmate->getchannel() << " to Inmate " << inmate->inName() << endl;
                j++;
            }
        }
    }
}
    

    
void Read(string name, vector<Inmate>& inmates, vector<Dorm>& dorms) //Function to read inpur file
{
ifstream file(name);

if(!file){
    cerr<<"File cannot be opened"<< endl;
    exit(1);
}


string fline;
while (getline(file, fline)) {
    istringstream iss(fline);

    string type;
    iss >> type;
    cout << type << endl;
    if (type == "Inmate:") {
        
        string name;
        string earpodID;
        vector<int> sleeptime(7);
        int timetofallAsleep;
        iss >> name >> earpodID;
        for (int i = 0; i < 7; i++) {
            iss >> sleeptime[i];
        }
        iss >> timetofallAsleep;
        cout << "Name: " << name << endl;
        cout << "Earpod ID: " << earpodID << endl;
        cout << "Sleep time: ";
        for (int i = 0; i < 7; i++) {
            cout << sleeptime[i] << " ";
        }
        cout << endl;
        cout << "Time to fall asleep: " << timetofallAsleep << endl;
        Inmate newInmate(name,earpodID,sleeptime,timetofallAsleep);
        inmates.push_back(newInmate);
       
    }


    else if(type == "Dorm:")
    {
        string name;
        int newchannels;
         iss >> name;
        iss >> newchannels;
        Dorm newDorm;
        newDorm.name= name;
        cout << "Name: " << name << endl;
        vector<string>channels(newchannels); 
        for(int i=0;i<newchannels;i++)
        {
            iss >> channels[i];
        } 
       for(int i=0;i<newchannels;++i)
        {
            cout << channels[i]<<" "<<endl;
        } 
        newDorm.channels = channels;
        dorms.push_back(newDorm);
    }
     }
     
     

     
}
void music(vector<Dorm>& dormslist)
{
    int inmateindex = 0;
    for(Dorm& dorm : dormslist)
    {
cout << "Playing sleep inducing music in "<< dorm.getName() <<endl;
cout << "Number of inmates: " << dorm.getInmates().size() << endl;

for(int i=0;i< dorm.getInmates().size();i++){
    Inmate* inmate = dorm.getInmates()[i];
    if(!inmate -> giveAsleep()){
        cout << "Playing music for inmates " << inmate->inName()<<endl;
        const vector<string>& channels = dorm.getChannels();
        inmate->setChannel(channels[inmateindex % channels.size()]);
        cout << "Assigned  " << inmate->getchannel() << " to Inmate " << inmate->inName() << endl;
    std::this_thread::sleep_for(std::chrono::minutes(inmate->getTimeToFallAsleep()));
        inmate->setSleepstatus(true);
        cout<<inmate->inName()<<" fell asleep. Deactivating earpod"<<endl;
         inmateindex++;
    }
}
    }
}

int main()
{   vector<Inmate> inmates;
    vector<Dorm> dorms;
    Read("input.txt",inmates,dorms);
    assigningInmatestoDorms(inmates,dorms);
    music(dorms);

    
    return 0;
}