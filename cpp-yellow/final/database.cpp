#include "database.h"
#include <algorithm>

using namespace std;

void Database::Add(const Date& date, const string& event)
{
    if (db.find(date) == db.end() ||
        find(db[date].begin(), db[date].end(), event) == db[date].end())
    {
        // cout << "Adding [" << date << ", " << event << "]" << endl;
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

string Database::Last(const Date& date) const
{
    cout << "db:" << endl;
    Print(cout);

    auto it = upper_bound(
        db.begin(), db.end(), date,
        [](const Date& date, pair<const Date&, const vector<string>> p) {
            cout << "date " << date << " first " << p.first << endl;
            return date < p.first;
        });

    if (it != db.begin())
    {
        ostringstream os;
        --it;
        cout << it->first << " " << it->second.back() << endl;
        os << it->first << " " << it->second.back();
        return os.str();
    }
    else
    {
        return "No entries";
    }
}

int Database::RemoveIf(std::function<bool(Date, string)> p)
{
    // cout << "before" << endl;
    // Print(cout);

    int counter = 0;

    for (auto& d : db)
    {
        Date date = d.first;

        if (date.GetYear() < 0)
            continue;

        vector<string>& events = d.second;

        auto comp = [p, date](const string& event) { return p(date, event); };
        auto it = remove_if(events.begin(), events.end(), comp);

        counter += distance(it, events.end());
        events.erase(it, events.end());
    }

    // cout << "after" << endl;
    // Print(cout);

    return counter;
}

vector<string> Database::FindIf(std::function<bool(Date, string)> p) const
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
