#include "test_runner.h"

using namespace std;

// Реализуйте здесь шаблонный класс Table
template <typename T> class Table
{
  public:
    Table(size_t num_rows, size_t num_cols)
    {
        table = vector<vector<T>>(num_rows, vector<T>(num_cols));
    }

    pair<size_t, size_t> Size() const
    {
        if (!table.empty() && !table[0].empty())
        {
            return {table.size(), table[0].size()};
        }
        return {0, 0};
    }

    void Resize(size_t new_rows, size_t new_columns)
    {
        table.resize(new_rows);
        for (auto& r : table)
        {
            r.resize(new_columns);
        }
    }

    const vector<T>& operator[](size_t i) const { return table[i]; }
    vector<T>& operator[](size_t i) { return table[i]; }

  private:
    vector<vector<T>> table;
};

void TestTable()
{
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
