#include "test_runner.h"
#include <cstdint>

#include <numeric>

using namespace std;

class BookingManager
{
  public:
    void Book(uint32_t time, string hotel_name, uint16_t client_id,
              int room_count)
    {
        if (rooms.count(time) > 0 && rooms[time].count(hotel_name) > 0)
        {
            rooms[time][hotel_name] += room_count;
            clients[time][hotel_name].insert(client_id);
        }
        else
        {
            rooms[time][hotel_name] = room_count;
            clients[time][hotel_name] = {client_id};
        }
    }

    int Clients(string hotel_name) const
    {
        // PrintClients();

        if (clients.empty())
        {
            return 0;
        }

        uint32_t current_time = clients.rbegin()->first;

        int64_t from = static_cast<int64_t>(current_time) - 86400;

        if (from < 0)
        {
            from = 0;
        }

        auto it = clients.upper_bound(from);

        // if (it == clients.end())
        // {
        //     cout << "it end" << endl;
        // }
        // else
        // {
        //     cout << "it " << it->first << endl;
        // }
        //
        auto sum_func =
            [hotel_name](int a, pair<uint32_t, map<string, set<uint16_t>>> b) {
                return b.second.count(hotel_name) > 0
                           ? a + b.second[hotel_name].size()
                           : a;
            };

        int sum = accumulate(it, clients.end(), 0, sum_func);
        return sum;
    }

    int Rooms(string hotel_name) const
    {
        // PrintRooms();

        if (rooms.empty())
        {
            return 0;
        }

        uint32_t current_time = rooms.rbegin()->first;

        int64_t from = static_cast<int64_t>(current_time) - 86400;

        if (from < 0)
        {
            from = 0;
        }

        auto it = rooms.upper_bound(from);
        //
        // if (it == rooms.end())
        // {
        //     cout << "it end" << endl;
        // }
        // else
        // {
        //     cout << "it " << it->first << endl;
        // }
        //
        auto sum_func = [hotel_name](int a,
                                     pair<uint32_t, map<string, int>> b) {
            return b.second.count(hotel_name) > 0 ? a + b.second[hotel_name]
                                                  : a;
        };

        int sum = accumulate(it, rooms.end(), 0, sum_func);
        return sum;
    }


  private:
    map<uint32_t, map<string, int>> rooms;
    map<uint32_t, map<string, set<uint16_t>>> clients;

    void PrintRooms() const
    {
        for (auto& [hotel, m] : rooms)
        {
            cout << "rooms in " << hotel << ": ";
            cout << "time:rooms -> ";

            for (auto& [t, r] : m)
            {
                cout << t << ":" << r << ", ";
            }
            cout << endl;
        }
    }

    void PrintClients() const
    {

        for (auto& [hotel, m] : clients)
        {
            cout << "clients in " << hotel << ": ";
            cout << "time:clients -> ";

            for (auto& [t, c] : m)
            {
                cout << t << ":<";
                for (auto& client : c)
                {
                    cout << client << ", ";
                }
                cout << ">";
            }
            cout << endl;
        }
    }
};

void TestEbook()
{
    BookingManager manager;

    ASSERT_EQUAL(manager.Clients("Marriott"), 0);
    ASSERT_EQUAL(manager.Rooms("Marriott"), 0);
    manager.Book(10, "FourSeasons", 1, 2);
    manager.Book(10, "Marriott", 1, 1);
    manager.Book(86409, "FourSeasons", 2, 1);
    ASSERT_EQUAL(manager.Clients("FourSeasons"), 2);
    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 3);
    ASSERT_EQUAL(manager.Clients("Marriott"), 1);
    manager.Book(86410, "Marriott", 2, 10);
    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 1);
    ASSERT_EQUAL(manager.Rooms("Marriott"), 10);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestEbook);

    BookingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK")
        {
            uint32_t time;
            string hotel_name;
            uint16_t client_id;
            int room_count;

            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        }
        else if (query_type == "CLIENTS")
        {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Clients(hotel_name) << endl;
        }
        else if (query_type == "ROOMS")
        {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Rooms(hotel_name) << endl;
        }
    }

    return 0;
}
