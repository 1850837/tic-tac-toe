

#include "Expense.hpp"
#include "Profile.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Profile::Profile() {
    this->name = "";
    this->dailySalary = 0;
    this->expenses = {};
}
Profile::Profile(vector<Expense> expenses, string name, int dailySalary) {
    this->name = name;
    this->dailySalary = dailySalary;
    this->expenses = expenses;
}
vector<Expense> Profile::getExpenses() {
    return this->expenses;
}


int Profile::getDailySalary() {
    return this->dailySalary;
}


Expense Profile::getExpenseByName(string expenseName) {
    for(int i = 0; i < expenses.size(); i++) {
        if(expenses[i].getName() == expenseName) {
            return expenses[i];
        }
    }
}
void Profile::addExpense(int cost, string name, vector<string> tags) {
    Expense e = Expense(cost, name, tags);
    expenses.push_back(e);
}

void Profile::deleteExpense(string name) {
    for(int i = 0; i < expenses.size(); i++) {
        if(expenses[i].getName() == name) {
            expenses.erase(expenses.begin() + i);
            return;
        }
    }
}

string Profile::getName() {
    return this->name;
}