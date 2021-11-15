#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Person
{
  public:
    void ChangeFirstName(int year, const string& first_name)
    {
        // добавить факт изменения имени на first_name в год year
        if (first_name_history.count(year) == 0)
        {
            first_name_history[year] = first_name;
        }
    }
    void ChangeLastName(int year, const string& last_name)
    {
        // добавить факт изменения фамилии на last_name в год year
        if (last_name_history.count(year) == 0)
        {
            last_name_history[year] = last_name;
        }
    }
    string GetFullName(int year)
    {
        // получить имя и фамилию по состоянию на конец года year
        // с помощью двоичного поиска
        string first_name, last_name;

        auto first_name_it = first_name_history.upper_bound(year);
        auto last_name_it = last_name_history.upper_bound(year);

        if (first_name_it != first_name_history.begin())
        {
            first_name = (--first_name_it)->second;
        }

        if (last_name_it != last_name_history.begin())
        {
            last_name = (--last_name_it)->second;
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
    map<int, string> first_name_history;
    map<int, string> last_name_history;
};

int main()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990})
    {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullName(year) << endl;
    }

    // Incognito
    // Polina with unknown last name
    // Polina Sergeeva
    // Polina Sergeeva
    // Appolinaria Sergeeva
    // Polina Volkova
    // Appolinaria Volkova

    return 0;
}
