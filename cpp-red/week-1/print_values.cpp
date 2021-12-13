#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y)                                                \
    do                                                                         \
    {                                                                          \
        out << (x) << endl;                                                    \
        out << (y) << endl;                                                    \
    } while (0)

void TestUpdate()
{
    {
        ostringstream output;
        PRINT_VALUES(output, 5, "red belt");
        ASSERT_EQUAL(output.str(), "5\nred belt\n");
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
    return 0;
}
