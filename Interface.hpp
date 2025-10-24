#pragma once


#include "Expense.hpp"
#include "Profile.hpp"
#include <iostream>
#include <string>
#include <vector>

class Interface {
    private:
        vector<Profile> profiles;
        Profile activeProfile;

    
    public:
        Interface();
        void addProfile(Profile p);
        bool deleteProfile(string name);
        bool setActiveProfile(string profileName);
        Profile getActiveProfile();
        vector<Profile> getProfiles();
        void listProfiles();
        void listExpenses();
        void mainMenu(); 
        void expensesMenu(); // Set expenses here
        void analysisMenu(); 
        double convertToDays(double value, int timeframe, string unit);
};