#include <iomanip>
#include <vector>

#include "date.h"

using namespace std;

ostream& operator<<(ostream& os, const Date& date)
{
    os << setw(4) << setfill('0') << date.GetYear() << "-" << setw(2)
       << date.GetMonth() << "-" << setw(2) << date.GetDay();
    return os;
}

Date ParseDate(istream& is)
{
    string date;
    is >> date;
    stringstream ss(date);

    int year, month, day;
    char c1, c2;

    ss >> year >> c1 >> month >> c2 >> day;

    if (ss.fail() || ss.peek() != EOF || c1 != '-' || c2 != '-')
    {
        cout << "Wrong date format: " << date << endl;
        throw runtime_error("");
    }

    return Date(year, month, day);
}

istream& operator>>(istream& is, Date& date)
{
    string s;

    if (is)
    {
        date = ParseDate(is);
    }

    return is;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
           vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}
