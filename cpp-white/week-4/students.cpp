#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student
{
    string first_name;
    string last_name;
    int day;
    int month;
    int year;
};

int main()
{
    vector<Student> studens;

    int n, m;

    cin >> n;

    while (n-- > 0)
    {
        string first_name, last_name;
        cin >> first_name >> last_name;

        int day, month, year;
        cin >> day >> month >> year;

        studens.push_back({first_name, last_name, day, month, year});
    }

    cin >> m;

    while (m-- > 0)
    {
        string request;
        cin >> request;

        int id;
        cin >> id;

        if (request == "name")
        {
            if (id < 1 || id > studens.size())
            {
                cout << "bad request" << endl;
                continue;
            }

            Student student = studens.at(id - 1);
            cout << student.first_name << " " << student.last_name << endl;
        }
        else if (request == "date")
        {
            if (id < 1 || id > studens.size())
            {
                cout << "bad request" << endl;
                continue;
            }

            Student student = studens.at(id - 1);
            cout << student.day << "." << student.month << "." << student.year
                 << endl;
        }
        else
        {
            cout << "bad request" << endl;
        }
    }
}
