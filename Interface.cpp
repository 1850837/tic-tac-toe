#pragma once

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




void Interface::addProfile(vector<Expense> expenses, string name, int dailySalary) {
    Profile p(expenses, name, dailySalary);
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

void Interface::mainMenu() {

}

void Interface::expensesMenu() {

}

void Interface::analysisMenu() {

}