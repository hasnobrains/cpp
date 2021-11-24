#pragma once

#include <iostream>

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

ostream& operator<<(ostream& os, const Date& date);
Date ParseDate(istream& is);
istream& operator>>(istream& is, Date& date);
bool operator<(const Date& lhs, const Date& rhs);
