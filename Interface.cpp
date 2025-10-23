

#include "Interface.hpp"
#include "Expense.hpp"
#include "Profile.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


Interface::Interface() {
    profiles = {};
}




void Interface::addProfile(Profile p) {
    for(int i = 0; i < profiles.size(); i++) {
        if(p.getName() == profiles[i].getName()) {
            cout << "Could not add profile " << p.getName() << ". A profile with that name already exists" << endl;
            return;
        }
    }
    profiles.push_back(p);
    return;

}

void Interface::deleteProfile(string name) {
    for(int i = 0; i < profiles.size(); i++) {
        if(profiles[i].getName() == name) {
            if(name == activeProfile.getName()) {
                cout << "Could not delete profile " << name << ", currently active. Switch to a different profile and try again" << endl;
            }
            profiles.erase(profiles.begin() + i);
            return;
        }
    }
    cout << "Profile " << name << " does not exist." << endl;
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
        string temp = "";
        cout << "> ";
        cin >> temp;
        string command = temp;
        stringstream ss(command);

        string token;
        vector<string> arguments;
        int _temp = 0;
        while (ss >> token) {
            cout << token << endl;
            arguments.push_back(token);
            _temp++;
            cout << _temp << endl;
        }
        for(int i = 0; i < arguments.size(); i++) {
            cout << arguments[i] << ", " << endl;
        }
        if (arguments[0] == "profile" && arguments[1] == "add") {
            if(arguments.size() < 2) {
                cout << "Please provide a name for the new profile (profile add <profile name>)" << endl;
            } else {
                string newProfileName;
                for(int i = 2; i < arguments.size(); i++) {
                    newProfileName += arguments[i];
                }
                Profile p({}, newProfileName, 0);
                addProfile(p);
                cout << "Added profile " << newProfileName << " successfully." << endl;
            }
        } else if(arguments[0] == "help") {
            cout << "    profile" << endl;
            cout << "        profile <profile name>               [switch to existing profile]" << endl;
            cout << "        profile add <profile name>           [adds a profile]" << endl;
            cout << "        profile delete <profile name>        [deletes a profile]" << endl;
            cout << endl;
            cout << "    misc" << endl;
            cout << "        help        [displays this message]" << endl;
            cout << "        quit        [quits application]" << endl;
        } else if(arguments[0] == "quit") {
            cout << "Goodbye" << endl;
            break;
        }
        else {
            cout << "Invalid command, type help for commands list" << endl;
        }
        
    }
    return;
}

void Interface::expensesMenu() {

}

void Interface::analysisMenu() {

}