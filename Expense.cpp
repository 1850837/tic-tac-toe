
#include <iostream>
#include <string>
#include <vector>
#include "Expense.hpp"
using namespace std;

Expense::Expense() {
    this->dailyCost = 0;
    this->name = "";
    this->tags = {};
}
Expense::Expense(int cost, string name, vector<string> tags) {
    this->dailyCost = cost;
    this->name = name;
    this->tags = tags;
}


int Expense::getExpenseCost() {
    return this->dailyCost;
}
vector<string> Expense::getExpenseTags() {
    return this->tags;
}

string Expense::getName() {
    return this->name;
}


void Expense::setExpenseCost(int &oldCost, int expenseCost) {
    oldCost = expenseCost;
}
void Expense::setExpenseTags(vector<string> &oldTags, vector<string> tags) {
    oldTags.insert(oldTags.end(), tags.begin(), tags.end());
}
void Expense::setName(string &oldName, string name) {
    oldName = name;
}
