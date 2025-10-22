#pragma once

#include "Profile.hpp"
#include "Expense.hpp"
#include <iostream>
#include <string>
#include <vector>

class Interface {
    private:
        vector<Profile> profiles;
        Profile activeProfile;

    
    public:
        Interface();
        void addProfile(vector<Expense> expenses, string name, int dailySalary);
        void deleteProfile(string name);
        void setActiveProfile(string profileName);
        void mainMenu();
        void expensesMenu(); // Set expenses here
        void analysisMenu(); 
};