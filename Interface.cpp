

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

bool Interface::deleteProfile(string name) {
    for(int i = 0; i < profiles.size(); i++) {
        if(profiles[i].getName() == name) {
            if(name == activeProfile.getName()) {
                cout << "Could not delete profile " << name << ", currently active. Switch to a different profile and try again" << endl;
                return false;
            }
            profiles.erase(profiles.begin() + i);
            return true;
        }
    }
    cout << "Profile " << name << " does not exist." << endl;
    return false;
}

bool Interface::setActiveProfile(string profileName) {
    for(int i = 0; i < profiles.size(); i++) {
        if(profiles[i].getName() == profileName) {
            activeProfile = profiles[i];
            return true;
        }
    } 
    return false;
}

Profile Interface::getActiveProfile() {
    return this->activeProfile;
}


vector<Profile> Interface::getProfiles() {
    return this->profiles;
}

void Interface::listProfiles(){
    vector<Profile> profs = getProfiles();

    for (int i = 0; i < profs.size(); i++){
        cout << "        " << profs[i].getName() << "\n";
    }

    return;
}

void Interface::listExpenses(){
    vector<Expense> list = getActiveProfile().getExpenses();
    vector<string> tags;
    for (int i = 0; i < list.size(); i++){
        cout << list[i].getName() << ": $" << list[i].getExpenseCost() << endl;
        tags = list[i].getExpenseTags();
        for (int j = 0; j < tags.size(); j++){
            cout << "   " << tags[j] << endl;
        }
    }
}

void Interface::mainMenu() {

    string temp;
    vector<string> arguments;
    string fullArg;

    while(true) {
        if(profiles.size() == 0) {
            string firstProfileName;
            cout << "Enter profile name: ";
            cin >> firstProfileName;
            Profile p({}, firstProfileName, 0);
            addProfile(p);
            setActiveProfile(firstProfileName);
            cout << "Welcome " << firstProfileName << ". Type help for commands" << endl;
            cin.ignore();
        }

        cout << "> ";
        temp = "";
        arguments = {};
        fullArg = "";
        getline(cin, fullArg);

        for (int i = 0; i < fullArg.size(); i++){
            // case where it's a letter and not the end
            if (i != fullArg.size()-1 && fullArg[i] != ' '){
                temp = temp + fullArg[i];
            }
            // case where it's a letter and it's the end
            else if (i == fullArg.size()-1 && fullArg[i] != ' '){
                temp = temp + fullArg[i];
                arguments.push_back(temp);
            }
            // case where it's a space (end or otherwise)
            else {
                arguments.push_back(temp);
                temp = "";
            }
        }

        // profile add <profile name>
        if (arguments[0] == "profile" && arguments[1] == "add") {
            if(arguments.size() <= 2) {
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
        } 
        // profile delete <profile name>
        else if (arguments[0] == "profile" && arguments[1] == "delete"){
            if (arguments.size() <= 2){
                cout << "Please provide a name for the profile to delete (profile delete <profile name>)" << endl;
            } else {
                string newProfileName;
                for(int i = 2; i < arguments.size(); i++) {
                    newProfileName += arguments[i];
                }
                bool check = deleteProfile(newProfileName);
                if (check == true){
                    cout << "Deleted profile " << newProfileName << " successfully." << endl;
                }
            }
        } 
        // profile <profile name>
        else if (arguments[0] == "profile"){
            if (arguments.size() <= 1){
                cout << "Please provide a name for the profile to switch to (profile <profile name>)" << endl;
            } else {
                string newProfileName;
                for(int i = 1; i < arguments.size(); i++) {
                    newProfileName += arguments[i];
                }
                // check if it's the current profile
                if (newProfileName == getActiveProfile().getName()){
                    cout << "Already using this profile!\n";
                }
                else {
                    bool check = setActiveProfile(newProfileName);
                    if (check){
                        cout << "Switched to profile " << newProfileName << " successfully." << endl;
                    } else {
                        cout << "Not an existing profile!\n";
                    }
                }
            }
        } 
        // help
        else if(arguments[0] == "help") {
            cout << "    profile" << endl;
            cout << "        profile <profile name>               [switch to existing profile]" << endl;
            cout << "        profile add <profile name>           [adds a profile]" << endl;
            cout << "        profile delete <profile name>        [deletes a profile]" << endl;
            cout << "        list profiles                        [lists all registered profiles]" << endl;
            cout << "        list expenses                        [lists all expenses for current profile]" << endl;
            cout << endl;
            cout << "    misc" << endl;
            cout << "        help                                 [displays this message]" << endl;
            cout << "        quit                                 [quits application]" << endl;
        } 
        // list profiles
        else if (arguments[0] == "list" && arguments[1] == "profiles"){
            listProfiles();
        }
        // list expenses
        else if (arguments[0] == "list" && arguments[1] == "expenses"){
            listExpenses();
        }
        // quit
        else if(arguments[0] == "quit") {
            cout << "Goodbye" << endl;
            break;
        }
        // anything else
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