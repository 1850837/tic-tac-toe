

#include "Interface.hpp"
#include "Expense.hpp"
#include "Profile.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


Interface::Interface() {
    profiles = {};
}




void Interface::addProfile(Profile p) {
    profiles.push_back(p);
}

void Interface::deleteProfile(string name) {
    for(int i = 0; i < profiles.size(); i++) {
        if(profiles[i].getName() == name) {
            profiles.erase(profiles.begin() + i);
            return;
        }
    }
}

void Interface::setActiveProfile(string profileName) {
    for(int i = 0; i < profiles.size(); i++) {
        if(profiles[i].getName() == profileName) {
            activeProfile = profiles[i];
            return;
        }
    } 
}

Profile Interface::getActiveProfile() {
    return this->activeProfile;
}


vector<Profile> Interface::getProfiles() {
    return this->profiles;
}
void Interface::mainMenu() {
    while(true) {
        if(profiles.size() == 0) {
            string firstProfileName;
            cout << "Enter profile name: ";
            cin >> firstProfileName;
            Profile p({}, firstProfileName, 0);
            addProfile(p);
            cout << "Welcome " << firstProfileName << ". Type help for commands" << endl;
        }
        string command = "";
        cout << "> ";
        cin >> command;


        if(command == "help") {
            cout << "    profile" << endl;
            cout << "        profile [profile name]               [switch to existing profile]" << endl;
            cout << "        profile add [profile name]           [adds a profile]" << endl;
            cout << "        profile delete [profile name]        [deletes a profile]" << endl;
            cout << endl;
            cout << "    misc" << endl;
            cout << "        quit        [quits application]" << endl;
        } else if(command == "quit") {
            cout << "Goodbye" << endl;
            break;
        }
        else {
            cout << "Invalid command, type help for commands" << endl;
        }
        
    }
    return;
}

void Interface::expensesMenu() {

}

void Interface::analysisMenu() {

}