#include "database.h"

using namespace std;

void Database::Add(const Date& date, const string& event)
{
    if (db[date].count(event) == 0)
    {
        db[date].insert(event);
    }
}

bool Database::DeleteEvent(const Date& date, const string& event)
{
    bool erased = false;

    if (db.count(date) > 0)
    {
        erased = db[date].erase(event);
    }

    return erased;
}

int Database::DeleteDate(const Date& date)
{
    int size = 0;

    if (db.count(date) > 0)
    {
        size = db[date].size();
        db.erase(date);
    }

    return size;
}

void Database::Find(const Date& date) const
{
    if (db.count(date) > 0)
    {
        for (const auto& event : db.at(date))
        {
            cout << event << endl;
        }
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
