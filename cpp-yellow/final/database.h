#pragma once

#include "date.h"
#include "node.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Database
{
  public:
    void Add(const Date& date, const string& event);
    void Print(ostream& os) const;
    void Find(const Date& date) const;

    int RemoveIf(std::function<bool(Date, string)> p);
    vector<string> FindIf(std::function<bool(Date, string)> p) const;

    string Last(const Date& date) const;

  private:
    map<Date, vector<string>> db;
    map<Date, set<string>> dbs;
};
