

#include "Interface.hpp"
#include "Expense.hpp"
#include "Profile.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
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
    cout << "Added profile " << p.getName() << " successfully." << endl;
    return;

}

void Interface::deleteProfile(string name) {
    for(int i = 0; i < profiles.size(); i++) {
        if(profiles[i].getName() == name) {
            if(name == activeProfile.getName()) {
                cout << "Could not delete profile " << name << ", currently active. Switch to a different profile and try again" << endl;
                return;
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

    // lil bit more of Maddy tinkering
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
            cout << "Welcome " << firstProfileName << ". Type help for commands" << endl;
            cin.ignore();
        }
        // string temp = "";
        // cout << "> ";
        // cin >> temp;
        // string command = temp;
        // stringstream ss(command);

        // string token;
        // vector<string> arguments;
        // int _temp = 0;
        // while (ss >> token) {
        //     cout << token << endl;
        //     arguments.push_back(token);
        //     _temp++;
        //     cout << _temp << endl;
        // }

        // Maddy testing non-sstream option
        cout << "> ";
        temp = "";
        arguments = {};
        fullArg = "";
        // cin.ignore();
        getline(cin, fullArg);

        // cout << "fullArg = " << fullArg << "\n";

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
    string temp;
    vector<string> arguments;
    string costString;
    string expenseName;
    bool existingNameFlag;
    int cost; // cost of the expense, can be in any frequency
    string frequency; // options: days (d), weeks (w), months (m), years (y)
    while(true) {
        vector<Expense> activeExpenses = this->activeProfile.getExpenses();
        cout << "Please name your expense: ";
        temp = "";
        arguments = {};
        costString = "";  
        expenseName = "";
        if(getline(cin, expenseName)) {
            for(int i = 0; i < activeExpenses.size(); i++) {
                if(activeExpenses[i].getName() == expenseName) {
                    cout << "An expense with that name already exists" << endl;
                    continue;
                }

            }
            cout << "Please add the cost of the expense: ";
            // TODO add cost
            cout << "Please enter the tags for this expense, seperated by commas (eg: 'essential, emergency fund, groceries')";
            // TODO add tag
            cout << "Please enter the frequency of the expense (eg, '5 days, 2 months, 3 years, 2 weeks or just 5d 2m 3y 2w)";
            if(getline(cin, costString)) {
                for (int i = 0; i < costString.size(); i++){
                    // case where it's a letter and not the end
                    if (i != costString.size()-1 && costString[i] != ' '){
                        temp = temp + costString[i];
                    }
                    // case where it's a letter and it's the end
                    else if (i == costString.size()-1 && costString[i] != ' '){
                        temp = temp + costString[i];
                        arguments.push_back(temp);
                    }
                    // case where it's a space (end or otherwise)
                    else {
                        arguments.push_back(temp);
                        temp = "";
                    }
                }
                double expenseCost = stod(costString);
                if(arguments.size() == 1) { // Case where its the shorthand "5d 2m 3y 2w etc"
                    string strDuration = "";
                    for(int i = 0; i < arguments.size(); i++) {
                        if(isdigit(arguments[0][i])) {
                            strDuration += arguments[0][i];
                        } else if(arguments[0][i] == 'd') {
                            int duration = stoi(strDuration);
                            int finalCost = expenseCost / duration;
                            this->activeProfile.addExpense(finalCost, expenseName, {}); // To add tags here soon
                            cout << ("Expense successfully added: ") << endl;
                            cout << finalCost << " per day" << endl;
                            cout << expenseName << endl;
                            break;
                        } else if(arguments[0][i] == 'w') {
                            // Convert cost to every day and then add
                        } else if(arguments[0][i] == 'm') {
                            // Convert cost to every day and then add
                        } else if(arguments[0][i] == 'y') {
                            // Convert cost to every day and then add
                        }
                    }
                } else {
                    cout << "Please enter a valid duration";
                }
            } else {
                cout << "Please enter a valid expense cost";
            }

        } else {
            cout << "Please enter an expense name" << endl;
            break;
        }

    }
}

void Interface::analysisMenu() {

}