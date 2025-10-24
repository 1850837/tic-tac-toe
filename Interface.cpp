

#include "Interface.hpp"
#include "Expense.hpp"
#include "Profile.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <cmath>
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
    this->profiles.push_back(p);
    cout << "Added profile " << p.getName() << " successfully." << endl;
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
 
}

void Interface::listExpenses(){
    vector<Expense> list = getActiveProfile().getExpenses();
    vector<string> tags;
    for (int i = 0; i < list.size(); i++){
        cout << list[i].getName() << ": $" << list[i].getExpenseCost() << " a day" << endl;
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
                Profile p({}, arguments[2], 0);
                addProfile(p);
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
        else if (arguments[0] == "profile" && arguments.size() > 1){
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
        } else if (arguments[0] == "expense" && arguments[1] == "add") {
            expensesMenu();
        }
        else if (arguments[0] == "expense" && arguments[1] == "delete") {
            if(arguments.size() > 2) {
                Expense e = activeProfile.getExpenseByName(arguments[2]);
            } else {
                cout << "Please include a name of the expense to delete" << endl;
            }
            Expense e = activeProfile.getExpenseByName(arguments[2]);
            activeProfile.deleteExpense(e.getName());
        } else if(arguments[0] == "salary" && arguments.size() == 1) {
            cout << "$" << activeProfile.getDailySalary() << " per day" << endl;
        } else if(arguments[0] == "salary" && arguments.size() == 2) {
            string salaryStr;
            double salary;
            string strDuration;
            double finalSalary;
            int duration;
            string temp;
            string freqString;
            vector<string> salaryArguments;
            while(true) {
                salaryStr = "";
                salary = 0.0;
                strDuration = "";
                finalSalary = 0.0;
                int duration;
                temp = "";
                freqString = "";
                salaryArguments = {};
                cout << "Enter your salary: ";
                if(getline(cin, salaryStr)) {
                    salary = stod(salaryStr);
                    cout << "Type the frequency of this salary (in the format eg. '5 days, 2 months, 1 years, 2 weeks): ";
                    if(getline(cin, freqString)) {
                        for (int i = 0; i < freqString.size(); i++){
                            // case where it's a letter and not the end
                            if (i != freqString.size()-1 && freqString[i] != ' '){
                                temp = temp + freqString[i];
                            }
                            // case where it's a letter and it's the end
                            else if (i == freqString.size()-1 && freqString[i] != ' '){
                                temp = temp + freqString[i];
                                salaryArguments.push_back(temp);
                            }
                            // case where it's a space (end or otherwise)
                            else {
                                salaryArguments.push_back(temp);
                                temp = "";
                            }
                        }
                    }
                    
                    bool argFlag = false;
                    if(salaryArguments.size() == 2) { // Either 1 or 2, 0 can't happen
                        for(int i = 0; i < salaryArguments[0].size(); i++) {
                            if(isdigit(salaryArguments[0][i])) {
                                strDuration += salaryArguments[0][i];
                            } if((i == salaryArguments[0].size()-1 && salaryArguments[1] == "days")) { // Checks if "day" was selected, and also checks if that digit is the last one
                                duration = stoi(strDuration);
                                finalSalary = convertToDays(salary, duration, "days");
                                argFlag = true; 
                                break;

                            } else if ((i == salaryArguments[0].size()-1 && salaryArguments[1] == "weeks")) {
                                duration = stoi(strDuration);
                                finalSalary = convertToDays(salary, duration, "weeks");
                                argFlag = true; 
                                break;

                            } else if((i == salaryArguments[0].size()-1 && salaryArguments[1] == "months")) {
                                duration = stoi(strDuration);
                                finalSalary = convertToDays(salary, duration, "months");
                                argFlag = true; 
                                break;

                            } else if((i == salaryArguments[0].size()-1 && salaryArguments[1] == "years")) {
                                duration = stoi(strDuration);
                                finalSalary = convertToDays(salary, duration, "years");
                                argFlag = true; 
                                break;
                        }
                        } if(argFlag == false) {
                            cout << "Please enter a valid duration in the correct format eg. 5 days, 2 months, 1 years, 2 weeks)." << endl;
                            continue;
                        }
                        this->activeProfile.addDailySalary(finalSalary);
                        cout << "Salary added successfully: $" << finalSalary << " per day." << endl;
                        break;
                    } else {
                        cout << "You must provide more than 1 value eg: 5 days, 2 months, 1 years, 2 weeks" << endl;
                        continue;
                    } 
                } else {
                    cout << "Invalid input" << endl;
                    continue;
                }
            }

        }
        // help
        else if(arguments[0] == "help") {
            cout << "    profile" << endl;
            cout << "        profile <profile name>               [switch to existing profile]" << endl;
            cout << "        profile add <profile name>           [adds a profile]" << endl;
            cout << "        profile delete <profile name>        [deletes a profile]" << endl;
            cout << "        profiles list                         [lists all registered profiles]" << endl;
            cout << endl;
            cout << "    expense" << endl;
            cout << "        expense add                          [add a new expense to this profile]" << endl;
            cout << "        expense delete <expense name>        [deletes the expense <expense name>]" << endl;
            cout << "        expenses list                         [lists all expenses for current profile]" << endl;
            cout << "    salary" << endl;
            cout << "        salary                               [Shows your current salary converted to per day]" << endl;
            cout << "        salary add                           [add a salary to this profile, adding a new salary will replace the old one]" << endl;
            cout << endl;
            cout << "    calculate" << endl;
            cout << "        calculate savings <time (days, int)> <interest rate (%, double)> <current savings ($, double)>" << endl;
            cout << "                                             [calculates the savings after <time>]" << endl;
            cout << "    misc" << endl;
            cout << "        help                                 [displays this message]" << endl;
            cout << "        quit                                 [quits application]" << endl;
        } 
        // list profiles
        else if (arguments[0] == "profiles" && arguments[1] == "list"){
            listProfiles();
        }
        // list expenses
        else if (arguments[0] == "expenses" && arguments[1] == "list"){
            listExpenses();
        }
        // calculate savings <time (days, int)> <interest rate (%, double)> <current savings ($, double)>
        else if (arguments[0] == "calculate" && arguments[1] == "savings"){
            if (arguments.size() < 5){
                cout << "Please include all information!" << endl;
            } else {
                double time = stod(arguments[2]);
                double interest = stod(arguments[3])/100;
                double savings = stod(arguments[4]);
                double timeYears = time/365;

                // checking input vals
                if (time < 0){
                    cout << "Invalid time!" << endl;
                } else if (interest < 0 || interest > 100){
                    cout << "Invalid interest!" << endl;
                } else if (savings < 0) {
                    cout << "Invalid savings!" << endl;
                } else {

                    double totalExpenses = 0;
                    vector<Expense> expense = getActiveProfile().getExpenses();
                    for (int i = 0; i < expense.size(); i++){
                        totalExpenses += expense[i].getExpenseCost();
                    }

                    for (int i = 0; i < time; i++){
                        savings = savings + getActiveProfile().getDailySalary() - totalExpenses + (savings * (interest/365));
                    }

                    cout << "After " << time << " days, you will have saved $" << savings << "!" << endl;
                }
            }
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
    string temp;
    vector<string> arguments;
    string freqString;
    string expenseName;
    string costStr; // cost of the expense, can be in any frequency
    string frequency; // a number and then these options: days (d), weeks (w), months (m), years (y)
    vector<string> tags;
    string strDuration;
    string tagsString;
    double finalCost;
    double cost;
    int duration;
    while(true) {
        vector<Expense> activeExpenses = this->activeProfile.getExpenses();
        cout << "Please name your expense: ";
        temp = "";
        arguments = {};
        freqString = "";  
        expenseName = "";
        costStr = "";
        frequency = "";
        tags = {};
        strDuration = "";
        tagsString = "";
        finalCost = 0.0;
        cost = 0.0;
        duration = 0;
        if(getline(cin, expenseName)) {
            if(expenseName.empty()) {
                cout << "Empty, please try again" << endl;
                continue;
            } else {
                for(int i = 0; i < activeExpenses.size(); i++) {
                    if(activeExpenses[i].getName() == expenseName) {
                        cout << "An expense with that name already exists" << endl;
                        continue;
                    }

                }
                cout << "Please add the cost of the expense (type it as a double eg: 23.6 50.0 91.70): ";
                if(getline(cin, temp)) {
                    cost = stod(temp);
                    temp = "";
                    cout << "Please enter the frequency of the expense (eg, '5 days, 2 months, 1 years, 2 weeks): "; // This bit of the menu could be its own function
                    if(getline(cin, freqString)) {
                        for (int i = 0; i < freqString.size(); i++){
                            // case where it's a letter and not the end
                            if (i != freqString.size()-1 && freqString[i] != ' '){
                                temp = temp + freqString[i];
                            }
                            // case where it's a letter and it's the end
                            else if (i == freqString.size()-1 && freqString[i] != ' '){
                                temp = temp + freqString[i];
                                arguments.push_back(temp);
                            }
                            // case where it's a space (end or otherwise)
                            else {
                                arguments.push_back(temp);
                                temp = "";
                            }
                        }
                        //double expenseCost = stod(costString);
                        bool argFlag = false;
                        if(arguments.size() == 2) { 
                            for(int i = 0; i < arguments[0].size(); i++) {
                                cout << i << endl;
                                if(isdigit(arguments[0][i])) {
                                    strDuration += arguments[0][i];
                                } if((i == arguments[0].size()-1 && arguments[1] == "days")) { // Checks if "day" was selected, and also checks if that digit is the last one
                                    duration = stoi(strDuration);
                                    finalCost = convertToDays(cost, duration, "days");
                                    argFlag = true; 
                                    break;

                                } else if ((i == arguments[0].size()-1 && arguments[1] == "weeks")) {
                                    duration = stoi(strDuration);
                                    finalCost = convertToDays(cost, duration, "weeks");
                                    argFlag = true; 
                                    break;

                                } else if((i == arguments[0].size()-1 && arguments[1] == "months")) {
                                    duration = stoi(strDuration);
                                    finalCost = convertToDays(cost, duration, "months");
                                    argFlag = true; 
                                    break;

                                } else if((i == arguments[0].size()-1 && arguments[1] == "years")) {
                                    duration = stoi(strDuration);
                                    finalCost = convertToDays(cost, duration, "years");
                                    argFlag = true; 
                                    break;
                            }
                            } if(argFlag == false) {
                                cout << "Please enter a valid duration in the correct format eg. 5 days, 2 months, 1 years, 2 weeks or just 5d 2m 3y 2w)." << endl;
                                expensesMenu();
                            }
                            cout << "Any tags? Seperate tags by commas (eg. 'essential, emergency fund, groceries'), or press enter for no tags: ";
                            temp = "";
                            getline(cin, tagsString);
                            for(int i = 0; i < tagsString.size(); i++) {
                                if(tagsString[i] != ',') {
                                    temp += tagsString[i];
                                } else if(tagsString[i] == ',' && tagsString[i+1] == ' ') {
                                    tags.push_back(temp);
                                    temp = "";
                                    i += 1;
                                }
                            }
                            tags.push_back(temp);
                            this->activeProfile.addExpense(finalCost, expenseName, tags); 
                            cout << ("Expense successfully added: ") << endl;
                            cout << finalCost << " per day" << endl;
                            cout << expenseName << endl;
                            cout << "Tags: " << endl;
                            for(int i = 0; i < tags.size(); i++) {
                                cout << tags[i] << ", " << endl;
                            }
                            break;

                        } else {
                            cout << "Please enter a valid duration";
                            continue;
                        }
                    } else {
                        cout << "Please enter a valid expense cost";
                        continue;
                    }


                } else {
                    cout << "Please enter a valid cost" << endl;
                    break;
                }
                cout << "Please enter the tags for this expense, seperated by commas (eg: 'essential, emergency fund, groceries')";
                // TODO add tag

            }
        } else {
            cout << "Please enter an expense name" << endl;
            break;
        }

    }
}

void Interface::analysisMenu() {

}

double Interface::convertToDays(double value, int timeframe, string unit) {
    if(unit == "days") {
        return value / timeframe;
    } if(unit == "weeks") {
        return value / (timeframe * 7);
    } if(unit == "months") {
        return value / (timeframe * 30);
    } if(unit == "years") {
        return value / (timeframe * 365);
    }
} 