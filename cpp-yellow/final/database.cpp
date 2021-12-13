#include "database.h"
#include <algorithm>

using namespace std;

void Database::Add(const Date& date, const string& event)
{
    if (dbs[date].count(event) == 0)
    {
        // cout << "Adding [" << date << ", " << event << "]" << endl;
        db[date].push_back(event);
        dbs[date].insert(event);
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
    auto it = db.upper_bound(date);

    if (it == db.begin())
    {
        return "No entries";
    }

    --it;

    ostringstream os;
    os << it->first << " " << it->second.back();

    return os.str();
}

int Database::RemoveIf(std::function<bool(Date, string)> p)
{
    int counter = 0;

    for (auto it = db.begin(); it != db.end();)
    {
        Date date = it->first;
        vector<string>& events = it->second;

        auto comp = [p, date](const string& event) { return !p(date, event); };
        auto from = stable_partition(events.begin(), events.end(), comp);

        counter += distance(from, events.end());
        for (auto i = from; i != events.end();)
        {
            dbs[date].erase(*i);
            i = events.erase(i);
        }

        if (events.empty())
        {
            it = db.erase(it);
            dbs.erase(date);
        }
        else
        {
            ++it;
        }
    }

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
