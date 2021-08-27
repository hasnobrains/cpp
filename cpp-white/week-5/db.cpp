#include <iomanip>
#include <iostream>
#include <sstream>


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

istream& operator>>(istream& is, Date& date)
{
    if (is)
    {
        string line;
        is >> line;

        istringstream ss(line);

        int y, m, d;
        char c1, c2;

        ss >> y >> c1 >> m >> c2 >> d;

        if (is)
        {
            if (c1 == '-' && c2 == '-')
            {
                date = Date(y, m, d);
            }
            else
            {
                cout << "Wrong date format: " << line << endl;
                throw runtime_error("");
            }
        }
    }
    return is;
}

bool operator<(const Date& lhs, const Date& rhs);


class Database
{
  public:
    void AddEvent(const Date& date, const string& event);
    bool DeleteEvent(const Date& date, const string& event);
    int DeleteDate(const Date& date);

    void Find(const Date& date) const;

    void Print() const;
};

// - добавление события:                        Add Дата Событие
// - удаление события:                          Del Дата Событие
// - удаление всех событий за конкретную дату:  Del Дата
// - поиск событий за конкретную дату:          Find Дата
// - печать всех событий за все даты:           Print

int main()
{
    Database db;
    string command;

    istringstream input("Add 0-1-2 event1\n"
                        "Add 1-2-3 event2\n"
                        // "Add 0-13-32 event1"
                        "Add 1-1-1 event3\n"
                        "Add -1-1-1 event4\n"
                        // "Add 1--1-1 event5\n"
                        // "Add 1---1-1 event6\n"
                        "Add 1-+1-+1 event7\n");

    while (getline(input, command))
    {
        istringstream ss(command);

        string command_code;

        ss >> command_code;

        cout << command_code << endl;

        try
        {
            if (command_code == "Add")
            {
                Date date;
                string event;
                ss >> date >> event;

                cout << date << " " << event << endl;
            }
            else if (command_code == "Del")
            {
            }
            else if (command_code == "Find")
            {
            }
            else if (command_code == "Print")
            {
            }
            else
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
