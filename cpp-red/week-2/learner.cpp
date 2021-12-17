#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "profile.h"
#include "test_runner.h"

using namespace std;

class Learner
{
  private:
    vector<string> dict;
    set<string> d;

  public:
    int Learn(const vector<string>& words)
    {
        LOG_DURATION("Learn")
        int newWords = 0;
        for (const auto& word : words)
        {
            if (d.insert(word).second)
            {
                ++newWords;
            }
        }
        return newWords;
    }

    vector<string> KnownWords()
    {
        LOG_DURATION("KnownWords")
        return {d.begin(), d.end()};
    }
};

void TestLearner()
{
    Learner learner;

    vector<string> words{
        "lorem",        "ipsum",       "dolor",      "sit",
        "amet",         "consectetur", "adipiscing", "elit",
        "sed",          "do",          "eiusmod",    "tempor",
        "incididunt",   "ut",          "labore",     "et",
        "dolore",       "magna",       "aliqua",     "ultricies",
        "mi",           "quis",        "hendrerit",  "dolor",
        "magna",        "eget",        "lectus",     "sit",
        "amet",         "est",         "placerat",   "in",
        "egestas",      "erat",        "imperdiet",  "pulvinar",
        "pellentesque", "habitant",    "morbi",      "tristique",
        "odio",         "eu",          "feugiat",    "pretium",
        "nibh",         "ipsum",       "dui",        "ut",
        "ornare",       "lectus",      "sit",        "amet",
        "est",          "placerat",    "tellus",     "in",
        "hac",          "habitasse",   "platea",     "dictumst",
        "vestibulum",   "rhoncus",     "est",        "magna",
        "etiam",        "tempor",      "orci",       "eu",
        "lobortis",     "elementum",   "nibh",       "tellus",
        "mi",           "quis",        "hendrerit",  "dolor",
        "magna",        "eget",        "est",        "laoreet",
        "sit",          "amet",        "cursus",     "sit",
        "risus",        "quis",        "varius",     "quam",
        "quisque",      "cras",        "semper",     "auctor",
        "neque",        "vitae",       "tempus",     "non",
        "pulvinar",     "neque",       "laoreet",    "suspendisse",
        "interdum",     "consectetur", "elit",       "ullamcorper",
        "dignissim",    "cras",        "tincidunt",
    };

    vector<string> expected{
        "adipiscing",  "aliqua",    "amet",        "auctor",
        "consectetur", "cras",      "cursus",      "dictumst",
        "dignissim",   "do",        "dolor",       "dolore",
        "dui",         "egestas",   "eget",        "eiusmod",
        "elementum",   "elit",      "erat",        "est",
        "et",          "etiam",     "eu",          "feugiat",
        "habitant",    "habitasse", "hac",         "hendrerit",
        "imperdiet",   "in",        "incididunt",  "interdum",
        "ipsum",       "labore",    "laoreet",     "lectus",
        "lobortis",    "lorem",     "magna",       "mi",
        "morbi",       "neque",     "nibh",        "non",
        "odio",        "orci",      "ornare",      "pellentesque",
        "placerat",    "platea",    "pretium",     "pulvinar",
        "quam",        "quis",      "quisque",     "rhoncus",
        "risus",       "sed",       "semper",      "sit",
        "suspendisse", "tellus",    "tempor",      "tempus",
        "tincidunt",   "tristique", "ullamcorper", "ultricies",
        "ut",          "varius",    "vestibulum",  "vitae",
    };

    ASSERT_EQUAL(learner.Learn(words), 72);
    ASSERT_EQUAL(learner.KnownWords(), expected);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestLearner);
    return 0;
}
