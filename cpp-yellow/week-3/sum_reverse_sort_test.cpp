#include "sum_reverse_sort.h"
#include "test_runner.h"

void Test()
{
    AssertEqual(Sum(2, 3), 5, "Sum");
    AssertEqual(Reverse("help"), "pleh", "Reverse");
    // vector<int> v = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    // vector<int> r = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // AssertEqual(v, r, "Sort");
}

int main()
{
    TestRunner tr;
    tr.RunTest(Test, "Test");
    return 0;
}
