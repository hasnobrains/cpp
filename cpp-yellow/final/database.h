#pragma once

#include "date.h"
#include "node.h"
#include <algorithm>
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

    int RemoveIf(std::function<bool(Date, string)> p);
    vector<string> FindIf(std::function<bool(Date, string)> p) const;

    // template <class UnaryPredicate> int RemoveIf(UnaryPredicate p);
    // template <class UnaryPredicate> vector<string> FindIf(UnaryPredicate p);
    string Last(const Date& date) const;

  private:
    map<Date, vector<string>> db;
};
//
// template <class UnaryPredicate> int Database::RemoveIf(UnaryPredicate p)
// {
//     int counter = 0;
//
//     for (const auto& d : db)
//     {
//         Date date = d.first;
//
//         if (date.GetYear() < 0)
//             continue;
//
//         vector<string> events = d.second;
//
//         auto comp = [p, date](const string& event) { return p(date, event);
//         }; auto it = remove_if(events.begin(), events.end(), comp);
//
//         counter += distance(it, events.end());
//         events.erase(it, events.end());
//     }
//
//     return counter;
// }
//
// template <class UnaryPredicate>
// vector<string> Database::FindIf(UnaryPredicate p)
// {
//     vector<string> result;
//
//     for (const auto& d : db)
//     {
//         Date date = d.first;
//
//         if (date.GetYear() < 0)
//             continue;
//
//         for (const auto& event : d.second)
//         {
//             if (p(date, event))
//             {
//                 result.push_back(date.GetDate() + " " + event);
//             }
//         }
//     }
//
//     return result;
// }
