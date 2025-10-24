#pragma once

#include "Expense.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Profile {
    private:
    vector<Expense> expenses;
    string name; // Must be unique
    int dailySalary; // Convert to per day before adding
    
    public:
        Profile();
        Profile(vector<Expense> expenses, string name, int dailySalary);
        vector<Expense> getExpenses();
        int getDailySalary();
        Expense getExpenseByName(string expenseName);

        void addExpense(int expenseCost, string expenseNname, vector<string> expenseTags);
        void deleteExpense(string expenseName);
        void addDailySalary(int dailySalary);
        string getName();

};