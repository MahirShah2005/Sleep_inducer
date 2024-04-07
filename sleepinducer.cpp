#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<chrono>
#include<thread>
#include <windows.h>  // Included headers for input/output, string manipulation, and threading
using namespace std;

// Class definition for an Inmate
class Inmate {
public:
    string name;
    string earpodID;
    vector<int> sleeptime;
    int timetofallAsleep;
    bool asleep;
    string channel;

public:
    // Constructor for Inmate class
    Inmate(string m, string id, vector<int> stime, int Time) :
        name(m),
        earpodID(id),
        sleeptime(stime),
        timetofallAsleep(Time),
        asleep(false),
        channel("") {}

    // Accessor methods for Inmate attributes
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

    string getchannel() const {
        return channel;
    }

    void setChannel(const string& ch) {
        channel = ch;
    }
};

// Class definition for a Dorm
class Dorm {
public:
    string name;
    vector<string> channels;
    vector<Inmate*> inmates;

public:
    // Constructor for Dorm class
    Dorm() {}
    
    Dorm(string n, vector<string> channels) : name(n), channels(channels) {}

    // Accessor methods for Dorm attributes
    string getName() const {
        return name;
    }

    vector<string> getchannels() const {
        return channels;
    }

    vector<Inmate*> getInmates() const {
        return inmates;
    }

    // Method to add an inmate to the dorm
    void addInmate(Inmate* inmate) {
        inmates.push_back(inmate);
    }

    // Method to add a music channel to the dorm
    void addChannel(const string& channel) {
        channels.push_back(channel);
    }

    const vector<string>& getChannels() const {
        return channels;
    }
};

// Function declaration for music simulation
void music(vector<Dorm>& dormslist);

// Function to assign inmates to dorms based on input file data
void assigningInmatestoDorms(vector<Inmate>& inmates, vector<Dorm>& dorms) {
    int TotalInmates = inmates.size();
    cout << "Number of Inmates " << TotalInmates << endl;
    int Totaldorms = dorms.size();
    int inmatesperdorm = TotalInmates / Totaldorms;
    int remaininginmates = TotalInmates % Totaldorms;
    int j = 0; // Index for inmates

    // Assign inmates to dorms based on balanced distribution
    for (int i = 0; i < Totaldorms; ++i) {
        int count = inmatesperdorm + (i < remaininginmates ? 1 : 0);
        cout << "Dorm " << i << " will have " << count << " inmates." << endl;
        for (int k = 0; k < count; ++k) {
            if (j < TotalInmates) {
                dorms[i].addInmate(&inmates[j++]);
                cout << "Assigned Inmate " << j << " to Dorm " << i << endl;
            }
        }
    }

    // Assign music channels to inmates within each dorm
    for (int i = 0; i < Totaldorms; ++i) {
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

// Function to read input data from a file and populate vectors of inmates and dorms
void Read(string name, vector<Inmate>& inmates, vector<Dorm>& dorms) {
    ifstream file(name);

    if (!file) {
        cerr << "File cannot be opened" << endl;
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
            Inmate newInmate(name, earpodID, sleeptime, timetofallAsleep);
            inmates.push_back(newInmate);
        }
        else if (type == "Dorm:") {
            string name;
            int newchannels;
            iss >> name;
            iss >> newchannels;
            Dorm newDorm;
            newDorm.name = name;
            cout << "Name: " << name << endl;
            vector<string> channels(newchannels);
            for (int i = 0; i < newchannels; i++) {
                iss >> channels[i];
            }
            for (int i = 0; i < newchannels; ++i) {
                cout << channels[i] << " " << endl;
            }
            newDorm.channels = channels;
            dorms.push_back(newDorm);
        }
    }
}

// Function to simulate playing sleep-inducing music for inmates
void music(vector<Dorm>& dormslist) {
    int inmateindex = 0;
    for (Dorm& dorm : dormslist) {
        cout << "Playing sleep inducing music in " << dorm.getName() << endl;
        cout << "Number of inmates: " << dorm.getInmates().size() << endl;

        for (int i = 0; i < dorm.getInmates().size(); i++) {
            Inmate* inmate = dorm.getInmates()[i];
            if (!inmate->giveAsleep()) {
                cout << "Playing music for inmate " << inmate->inName() << endl;
                const vector<string>& channels = dorm.getChannels();
               
