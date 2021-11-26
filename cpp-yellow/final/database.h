#pragma once

#include "date.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Database
{
  public:
    void Add(const Date& date, const string& event);
    void Print(ostream& os) const;
    void Find(const Date& date) const;

    template <class UnaryPredicate> int RemoveIf(UnaryPredicate p);
    template <class UnaryPredicate> vector<string> FindIf(UnaryPredicate p);
    string Last(const Date& date) const;

  private:
    map<Date, vector<string>> db;
};
