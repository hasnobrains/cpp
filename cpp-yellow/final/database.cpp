#include "database.h"
#include <algorithm>

using namespace std;

void Database::Add(const Date& date, const string& event)
{
    if (db.find(date) == db.end() ||
        find(db[date].begin(), db[date].end(), event) == db[date].end())
    {
        cout << "Adding [" << date << ", " << event << "]" << endl;
        db[date].push_back(event);
    }
}

void Database::Print(ostream& os) const
{
    for (const auto& d : db)
    {
        Date date = d.first;

        if (date.GetYear() < 0)
            continue;

        for (const auto& event : d.second)
        {
            os << date << " " << event << endl;
        }
    }
}

template <class UnaryPredicate> int Database::RemoveIf(UnaryPredicate p)
{
    int counter = 0;

    for (const auto& d : db)
    {
        Date date = d.first;

        if (date.GetYear() < 0)
            continue;

        vector<string> events = d.second;

        auto comp = [p, date](const string& event) { return p(date, event); };
        auto it = remove_if(events.begin(), events.end(), comp);

        counter += distance(it, events.end());
        events.erase(it, events.end());
    }

    return counter;
}

template <class UnaryPredicate>
vector<string> Database::FindIf(UnaryPredicate p)
{
    vector<string> result;

    for (const auto& d : db)
    {
        Date date = d.first;

        if (date.GetYear() < 0)
            continue;

        for (const auto& event : d.second)
        {
            if (p(date, event))
            {
                result.push_back(date.GetDate() + " " + event);
            }
        }
    }

    return result;
}

string Database::Last(const Date& date) const
{
    auto it = upper_bound(db.begin(), db.end(), date);

    if (it != db.begin())
    {
        return (--it)->second.back();
    }
    else
    {
        return "No entries";
    }
}
