#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Person {

    public:

        void ChangeFirstName(int year, const string& first_name) {
            // добавить факт изменения имени на first_name в год year
            if (history[year].size() == 0)
            {
                vector<string> v(2);
                v[0] = first_name;
                history[year] = v;
            }
            else if (history[year][0].size() == 0)
            {
                history[year][0] = first_name;
            }
        }

        void ChangeLastName(int year, const string& last_name) {
            // добавить факт изменения фамилии на last_name в год year
            if (history[year].size() == 0)
            {
                vector<string> v(2);
                v[1] = last_name;
                history[year] = v;
            }
            else if (history[year][1].size() == 0)
            {
                history[year][1] = last_name;
            }
        }

        string GetFullName(int year) {
            // получить имя и фамилию по состоянию на конец года year

            string first_name, last_name;

            for (auto& item: history)
            {
                int y = item.first;

                if (y > year) break;

                if (item.second[0].size() > 0)
                {
                    first_name = item.second[0];
                }

                if (item.second[1].size() > 0)
                {
                    last_name = item.second[1];
                }
            }

            if (first_name.size() == 0 && last_name.size() == 0)
            {
                return "Incognito";
            }

            if (first_name.size() != 0 && last_name.size() == 0)
            {
                return first_name + " with unknown last name";
            }

            if (first_name.size() == 0 && last_name.size() != 0)
            {
                return last_name + " with unknown first name";
            }

            return first_name + " " + last_name;

        }

    private:

        // приватные поля
        map<int, vector<string>> history;
};


int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}

