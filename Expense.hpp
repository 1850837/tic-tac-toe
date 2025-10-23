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

        void setExpenseCost(int &oldCost, int expenseCost);
        void setExpenseTags(vector<string> &oldTags, vector<string> tags);
        void setName(string &oldName, string name);
};