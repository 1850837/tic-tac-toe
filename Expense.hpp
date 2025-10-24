#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Expense {

    private:
        double dailyCost;
        string name;
        vector<string> tags;

    public:
        Expense();
        Expense(double cost, string name, vector<string> tags);

        double getExpenseCost();
        vector<string> getExpenseTags();
        string getName();

        void setExpenseCost(double &oldCost, double expenseCost);
        void setExpenseTags(vector<string> &oldTags, vector<string> tags);
        void setName(string &oldName, string name);
};