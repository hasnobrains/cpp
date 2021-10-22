#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class QueryType
{
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query
{
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q)
{
    string operation_code;
    is >> operation_code;

    if (operation_code == "NEW_BUS")
    {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops)
        {
            is >> stop;
        }
    }
    else if (operation_code == "BUSES_FOR_STOP")
    {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (operation_code == "STOPS_FOR_BUS")
    {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (operation_code == "ALL_BUSES")
    {
        q.type = QueryType::AllBuses;
    }

    return is;
}

struct BusesForStopResponse
{
    vector<string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r)
{
    if (r.buses.empty())
    {
        os << "No stop";
    }
    else
    {
        for (const string& bus : r.buses)
        {
            os << bus << " ";
        }
    }

    return os;
}

struct StopsForBusResponse
{
    vector<string> stops;
    map<string, vector<string>> stops_to_buses;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r)
{
    if (r.stops.empty())
    {
        os << "No bus";
    }
    else
    {
        for (size_t i = 0; i < r.stops.size(); ++i)
        {
            os << "Stop " << r.stops[i] << ": ";
            for (const string& other_bus : r.stops_to_buses.at(r.stops[i]))
            {
                os << other_bus << " ";
            }
            os << (i == r.stops.size() - 1 ? "" : "\n");
        }
    }

    return os;
}

struct AllBusesResponse
{
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r)
{
    if (r.buses_to_stops.empty())
    {
        os << "No buses";
    }
    else
    {
        size_t i = 0;
        for (const auto& bus_item : r.buses_to_stops)
        {
            os << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second)
            {
                os << stop << " ";
            }
            os << (++i == r.buses_to_stops.size() ? "" : "\n");
        }
    }
    return os;
}

class BusManager
{
  public:
    void AddBus(const string& bus, const vector<string>& stops)
    {
        for (const string& stop : stops)
        {
            buses_to_stops[bus].push_back(stop);
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const
    {
        BusesForStopResponse r;
        if (stops_to_buses.count(stop) != 0)
        {
            r.buses = stops_to_buses.at(stop);
        }
        return r;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const
    {
        StopsForBusResponse r;
        if (buses_to_stops.count(bus) != 0)
        {
            r.stops = buses_to_stops.at(bus);

            for (const string& stop : r.stops)
            {
                if (stops_to_buses.at(stop).size() == 1)
                {
                    r.stops_to_buses[stop].push_back("no interchange");
                }
                else
                {
                    for (const string& other_bus : stops_to_buses.at(stop))
                    {
                        if (bus != other_bus)
                        {
                            r.stops_to_buses[stop].push_back(other_bus);
                        }
                    }
                }
            }
        }
        return r;
    }

    AllBusesResponse GetAllBuses() const
    {
        AllBusesResponse r = {buses_to_stops, stops_to_buses};
        return r;
    }

    const map<string, vector<string>>& GetBuses() const
    {
        return buses_to_stops;
    }

    const map<string, vector<string>>& GetStops() const
    {
        return stops_to_buses;
    }

  private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

void TestQuery()
{
    {
        istringstream ss("NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo");
        Query q;
        ss >> q;
        Query expected = {QueryType::NewBus,
                          "32",
                          "",
                          {"Tolstopaltsevo", "Marushkino", "Vnukovo"}};
        assert(q.type == expected.type);
        assert(q.bus == expected.bus);
        assert(q.stop == expected.stop);
        assert(q.stops == expected.stops);
    }
    {
        istringstream ss("BUSES_FOR_STOP Marushkino");
        Query q;
        ss >> q;
        Query expected = {QueryType::BusesForStop, "", "Marushkino", {}};
        assert(q.type == expected.type);
        assert(q.bus == expected.bus);
        assert(q.stop == expected.stop);
        assert(q.stops == expected.stops);
    }
    {
        istringstream ss("STOPS_FOR_BUS 32K");
        Query q;
        ss >> q;
        Query expected = {QueryType::StopsForBus, "32K", "", {}};
        assert(q.type == expected.type);
        assert(q.bus == expected.bus);
        assert(q.stop == expected.stop);
        assert(q.stops == expected.stops);
    }
    {
        istringstream ss("ALL_BUSES");
        Query q;
        ss >> q;
        Query expected = {QueryType::AllBuses, "", "", {}};
        assert(q.type == expected.type);
        assert(q.bus == expected.bus);
        assert(q.stop == expected.stop);
        assert(q.stops == expected.stops);
    }

    cout << "TestQuery OK" << endl;
}

void TestAddBus()
{
    BusManager bm;
    bm.AddBus("32", {"Tolstopaltsevo", "Marushkino", "Vnukovo"});

    map<string, vector<string>> buses_to_stops = bm.GetBuses();
    map<string, vector<string>> stops_to_buses = bm.GetStops();

    map<string, vector<string>> buses_expected = {
        {"32", {"Tolstopaltsevo", "Marushkino", "Vnukovo"}}};

    assert(buses_to_stops == buses_expected);

    map<string, vector<string>> stops_expected = {{"Tolstopaltsevo", {"32"}},
                                                  {"Marushkino", {"32"}},
                                                  {"Vnukovo", {"32"}}};
    assert(stops_to_buses == stops_expected);

    cout << "TestAddBus OK" << endl;
}

void TestGetBusesForStop()
{
    BusManager bm;
    BusesForStopResponse r;

    bm.AddBus("32", {"Tolstopaltsevo", "Marushkino", "Vnukovo"});
    r = bm.GetBusesForStop("Tolstopaltsevo");

    vector<string> expected;

    expected = {"32"};

    assert(r.buses == expected);

    r = bm.GetBusesForStop("Yoyo");

    expected = {};

    assert(r.buses == expected);

    cout << "TestGetBusesForStop OK" << endl;
}

void TestGetStopsForBus()
{
    BusManager bm;

    bm.AddBus("32", {"Tolstopaltsevo", "Marushkino", "Vnukovo"});
    bm.AddBus("32K", {"Tolstopaltsevo", "Marushkino", "Vnukovo", "Peredelkino",
                      "Solntsevo", "Skolkovo"});
    bm.AddBus("950", {"Kokoshkino", "Marushkino", "Vnukovo", "Peredelkino",
                      "Solntsevo", "Troparyovo"});
    bm.AddBus("272", {"Vnukovo", "Moskovsky", "Rumyantsevo", "Troparyovo"});

    StopsForBusResponse r;

    r = bm.GetStopsForBus("272");

    vector<string> expected;
    expected = {"Vnukovo", "Moskovsky", "Rumyantsevo", "Troparyovo"};

    assert(r.stops == expected);

    map<string, vector<string>> stops_to_buses = {
        {"Vnukovo", {"32", "32K", "950"}}, {"Troparyovo", {"950"}}};

    assert(r.stops_to_buses == stops_to_buses);

    cout << "TestGetStopsForBus OK" << endl;
}

void TestAll()
{
    TestQuery();
    TestAddBus();
    TestGetBusesForStop();
    TestGetStopsForBus();
}

// Не меняя тела функции main, реализуйте функции и классы выше

int main()
{
    // TestAll();
    // return 0;

    istringstream ss(
        "10\n"
        "ALL_BUSES\n"
        "BUSES_FOR_STOP Marushkino\n"
        "STOPS_FOR_BUS 32K\n"
        "NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo\n"
        "NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo "
        "Skolkovo\n"
        "BUSES_FOR_STOP Vnukovo\n"
        "NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo "
        "Troparyovo\n"
        "NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo\n"
        "STOPS_FOR_BUS 272\n"
        "ALL_BUSES");

    int query_count;
    Query q;

    ss >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i)
    {
        ss >> q;
        switch (q.type)
        {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
