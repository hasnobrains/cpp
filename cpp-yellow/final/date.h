#pragma once

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
    string GetDate() const
    {
        stringstream ss;
        ss << setw(4) << setfill('0') << year << "-" << setw(2) << month << "-"
           << setw(2) << day;
        return ss.str();
    }


  private:
    int year;
    int month;
    int day;
};

Date ParseDate(istream& is);

ostream& operator<<(ostream& os, const Date& date);
istream& operator>>(istream& is, Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
