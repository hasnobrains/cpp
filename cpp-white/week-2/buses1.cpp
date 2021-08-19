#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

void print_buses_for_stop(const map<string, vector<string>>& stops, string stop)
{
    for (const auto& bus: stops.at(stop))
    {
        cout << bus << " ";
    }

    cout << endl;
}

int main()
{
    map<string, vector<string>> buses;
    map<string, vector<string>> stops;

    int q;

    cin >> q;

    while (q > 0)
    {
        string command_code;
        cin >> command_code;

        if ("NEW_BUS" == command_code)
        {
            string bus;
            int stop_count;

            cin >> bus >> stop_count;

            while (stop_count > 0)
            {
                string stop;
                cin >> stop;

               buses[bus].push_back(stop);
               stops[stop].push_back(bus);

               stop_count--;
            }
        }
        else if ("BUSES_FOR_STOP" == command_code)
        {
            string stop;
            cin >> stop;

            if (stops.count(stop) == 0)
            {
                cout << "No stop" << endl;
            }
            else
            {
                print_buses_for_stop(stops, stop);
            }
        }
        else if ("STOPS_FOR_BUS" == command_code)
        {
            string bus;
            cin >> bus;

            if (buses.count(bus) == 0)
            {
                cout << "No bus" << endl;
            }
            else
            {
                for (const auto& stop: buses[bus])
                {
                    cout << "Stop " << stop << ": ";

                    if (stops[stop].size() == 1)
                    {
                        cout << "no interchange" << endl;
                    }
                    else
                    {
                        for (const auto& b: stops.at(stop))
                        {
                            if (bus != b)
                            {
                                cout << b << " ";
                            }
                        }

                        cout << endl;
                    }
                }
            }
        }
        else if ("ALL_BUSES" == command_code)
        {
            if (buses.size() == 0)
            {
                cout << "No buses" << endl;
            }
            else
            {
                for (const auto& bus: buses)
                {
                    cout << "Bus " << bus.first << ": ";

                    for (const auto& stop: bus.second)
                    {
                        cout << stop << " ";
                    }

                    cout << endl;
                }
            }
        }

        q--;
    }

    return 0;
}
