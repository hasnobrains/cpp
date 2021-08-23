#include <iostream>
#include <map>
#include <string>

using namespace std;

class Person
{
    public:

        void ChangeFirstName(int year, const string& _first_name)
        {
            // добавить факт изменения имени на first_name в год year
            first_name[year] = _first_name;
        }

        void ChangeLastName(int year, const string& _last_name) {
            // добавить факт изменения фамилии на last_name в год year
           last_name[year] = _last_name;
        }

        string GetName(int year, map<int, string>& name)
        {
            string _name = "";

            for (auto& n: name)
            {
                if (n.first > year) break;

                if (n.second.size() > 0)
                {
                    _name = n.second;
                }
            }

            return _name;
        }

        string GetFullName(int year)
        {
            // получить имя и фамилию по состоянию на конец года year
            string _first_name = GetName(year, first_name);
            string _last_name = GetName(year, last_name);

            if (_first_name.size() == 0 && _last_name.size() == 0)
            {
                return "Incognito";
            }

            if (_first_name.size() != 0 && _last_name.size() == 0)
            {
                return _first_name + " with unknown last name";
            }

            if (_first_name.size() == 0 && _last_name.size() != 0)
            {
                return _last_name + " with unknown first name";
            }

            return _first_name + " " + _last_name;
        }

        string GetFullNameWithHistory(int year)
        {
            // получить все имена и фамилии по состоянию на конец года year
            for (int i = first_name.size(); i > 0; i--)
            {

            }
        }

    private:
        // приватные поля

        map<int, string> first_name;
        map<int, string> last_name;

};


int test1()
{
    Person person;

    person.ChangeFirstName(1900, "Eugene");
    person.ChangeLastName(1900, "Sokolov");
    person.ChangeLastName(1910, "Sokolov");
    person.ChangeFirstName(1920, "Evgeny");
    person.ChangeLastName(1930, "Sokolov");
    cout << person.GetFullNameWithHistory(1940) << endl;

    return 0;
}


int test2()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}


int test3()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeFirstName(1965, "Appolinaria");

    person.ChangeLastName(1965, "Sergeeva");
    person.ChangeLastName(1965, "Volkova");
    person.ChangeLastName(1965, "Volkova-Sergeeva");

    for (int year : {1964, 1965, 1966}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}


int main()
{
    test1();

    cout << endl;

    test2();

    cout << endl;

    test3();

    cout << endl;

    return 0;
}

