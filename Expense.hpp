#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Expense {

    private:
        int dailyCost;
        string name;
        vector<string> tags;

    public:
        Expense();
        Expense(int cost, string name, vector<string> tags);

        int getExpenseCost();
        vector<string> getExpenseTags();
        string getName();

};