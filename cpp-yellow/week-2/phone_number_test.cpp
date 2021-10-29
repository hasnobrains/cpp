#include "phone_number.h"
#include "test_runner.h"

void Test()
{
    {
        PhoneNumber phone_number("+7-495-111-22-33");
        AssertEqual(phone_number.GetInternationalNumber(), "+7-495-111-22-33",
                    "+7-495-111-22-33");
    }
    {
        PhoneNumber phone_number("+7-495-1112233");
        AssertEqual(phone_number.GetInternationalNumber(), "+7-495-1112233",
                    "+7-495-1112233");
    }
    {
        PhoneNumber phone_number("+323-22-460002");
        AssertEqual(phone_number.GetInternationalNumber(), "+323-22-460002",
                    "+323-22-460002");
    }
    {
        PhoneNumber phone_number("+1-2-coursera-cpp");
        AssertEqual(phone_number.GetInternationalNumber(), "+1-2-coursera-cpp",
                    "+1-2-coursera-cpp");
    }
    // {
    //     PhoneNumber phone_number("1-2-333");
    //     AssertEqual(phone_number.GetInternationalNumber(), "1-2-333",
    //                 "1-2-333");
    // }
    {
        PhoneNumber phone_number("+7-1233");
        AssertEqual(phone_number.GetInternationalNumber(), "+7-1233",
                    "+7-1233");
    }
}

int main()
{
    TestRunner tr;
    tr.RunTest(Test, "Test");
    return 0;
}
