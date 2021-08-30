#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>


using namespace std;

class Date
{
  public:
    Date()
    {
        year = 0;
        month = 0;
        day = 0;
    };

    Date(int y, int m, int d)
    {
        if (m < 1 || m > 12)
        {
            cout << "Month value is invalid: " << m << endl;
            throw runtime_error("");
        }

        if (d < 1 || d > 31)
        {
            cout << "Day value is invalid: " << d << endl;
            throw runtime_error("");
        }

        year = y;
        month = m;
        day = d;
    }

    int GetYear() const { return year; }
    int GetMonth() const { return month; }
    int GetDay() const { return day; }

  private:
    int year;
    int month;
    int day;
};


ostream& operator<<(ostream& os, const Date& date)
{
    os << setw(4) << setfill('0') << date.GetYear() << "-" << setw(2)
       << date.GetMonth() << "-" << setw(2) << date.GetDay();
    return os;
}


Date ParseDate(const string& s)
{
    stringstream ss(s);

    int year, month, day;
    char c1, c2;

    ss >> year >> c1 >> month >> c2 >> day;

    if (ss.fail() || ss.peek() != EOF || c1 != '-' || c2 != '-')
    {
        cout << "Wrong date format: " << s << endl;
        throw runtime_error("");
    }

    return Date(year, month, day);
}

istream& operator>>(istream& is, Date& date)
{
    string s;

    if (is)
    {
        is >> s;
        date = ParseDate(s);
    }

    return is;
}


bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.GetYear() == rhs.GetYear())
    {
        if (lhs.GetMonth() == rhs.GetMonth())
        {
            if (lhs.GetDay() == rhs.GetDay())
            {
                return false;
            }
            else
            {
                return lhs.GetDay() < rhs.GetDay();
            }
        }
        else
        {
            return lhs.GetMonth() < rhs.GetMonth();
        }
    }
    else
    {
        return lhs.GetYear() < rhs.GetYear();
    }


    // воспользуемся тем фактом, что векторы уже можно сравнивать на <:
    // создадим вектор из года, месяца и дня для каждой даты и сравним их
    // return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
    //     vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}


class Database
{
  public:
    void AddEvent(const Date& date, const string& event)
    {
        if (db[date].count(event) == 0)
        {
            db[date].insert(event);
        }
    }

    bool DeleteEvent(const Date& date, const string& event)
    {
        bool erased = false;

        if (db.count(date) > 0)
        {
            erased = db[date].erase(event);
        }

        return erased;
    }

    int DeleteDate(const Date& date)
    {
        int size = 0;

        if (db.count(date) > 0)
        {
            size = db[date].size();
            db.erase(date);
        }

        return size;
    }

    void Find(const Date& date) const
    {
        if (db.count(date) > 0)
        {
            for (const auto& event : db.at(date))
            {
                cout << event << endl;
            }
        }
    }

    void Print() const
    {
        for (const auto& d : db)
        {
            Date date = d.first;

            if (date.GetYear() < 0)
                continue;

            for (const auto& event : d.second)
            {
                cout << date << " " << event << endl;
            }
        }
    }

  private:
    map<Date, set<string>> db;
};


int main()
{
    Database db;
    string command;

    // istringstream input("BadCommand\n"
    //                     "Add 1-+-1-666 event1\n"
    //                     "Print\n");
    // istringstream input("Add 1 1 1 a\n"
    //                     "Add 1-1-1 b\n"
    //                     "Find 1-1-1\n"
    //                     "Print\n");
    // istringstream input("Add 1-3-1 event\n"
    //                     "Add 2-2-1 event1\n"
    //                     "Add 3-1-1 event2\n"
    //                     "Print\n");
    // istringstream input("Add 1-0- event1\n");
    // while (getline(input, command))
    //
    while (getline(cin, command))
    {
        istringstream ss(command);

        string command_code;

        ss >> command_code;

        try
        {
            if (command_code == "Add")
            {
                Date date;
                string event;
                ss >> date >> event;
                // cout << "Command: " << command << endl;
                // cout << "Date: " << date << " event: " << event << endl;
                db.AddEvent(date, event);
            }
            else if (command_code == "Del")
            {
                Date date;
                string event;
                ss >> date >> event;

                if (event.size() > 0)
                {
                    bool ok = db.DeleteEvent(date, event);
                    cout << (ok ? "Deleted successfully" : "Event not found")
                         << endl;
                }
                else
                {
                    cout << "Deleted " << db.DeleteDate(date) << " events"
                         << endl;
                }
            }
            else if (command_code == "Find")
            {
                Date date;
                ss >> date;
                db.Find(date);
            }
            else if (command_code == "Print")
            {
                db.Print();
            }
            else if (ss)
            {
                cout << "Unknown command: " << command_code << endl;
            }
        }
        catch (exception&)
        {
            return 1;
        }
    }

    return 0;
}
