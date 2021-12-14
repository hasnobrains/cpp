#include "test_runner.h"

using namespace std;

template <typename T> class Deque
{
  public:
    Deque() {}

    bool Empty() const { return front.empty() && back.empty(); }
    size_t Size() const { return front.size() + back.size(); }

    void PushFront(const T& t) { front.push_back(t); }
    void PushBack(const T& t) { back.push_back(t); }

    T& operator[](size_t index) { return GetItem(index); }
    const T& operator[](size_t index) const { return GetItem(index); }

    T& At(size_t index)
    {
        if (index < 0 || index >= Size())
        {
            throw out_of_range("");
        }

        return GetItem(index);
    }

    const T& At(size_t index) const
    {
        if (index < 0 || index >= Size())
        {
            throw out_of_range("");
        }

        return GetItem(index);
    }

    T& Front() { return front.empty() ? back.front() : front.back(); }

    const T& Front() const
    {
        return front.empty() ? back.front() : front.back();
    }

    T& Back() { return back.empty() ? front.front() : back.back(); }
    const T& Back() const { return back.empty() ? front.front() : back.back(); }

  private:
    const T& GetItem(size_t index) const
    {
        if (index >= front.size())
        {
            return back[index - front.size()];
        }
        else
        {
            return front[front.size() - 1 - index];
        }
    }

    T& GetItem(size_t index)
    {
        if (index >= front.size())
        {
            return back[index - front.size()];
        }
        else
        {
            return front[front.size() - 1 - index];
        }
    }

    vector<T> front;
    vector<T> back;
};

#ifdef DEBUG
void TestDeque()
{
    {
        Deque<int> d;

        ASSERT(d.Empty());
        ASSERT_EQUAL(d.Size(), 0);

        d.PushFront(3);
        d.PushFront(2);
        d.PushFront(1);
        d.PushBack(4);
        d.PushBack(5);
        d.PushBack(6);

        ASSERT_EQUAL(d.Front(), 1);
        ASSERT_EQUAL(d.Back(), 6);
        ASSERT_EQUAL(d.At(0), 1);
        ASSERT_EQUAL(d.At(2), 3);
        ASSERT_EQUAL(d.At(3), 4);
        ASSERT_EQUAL(d.At(5), 6);
        ASSERT_EQUAL(d[0], 1);
        ASSERT_EQUAL(d[2], 3);
        ASSERT_EQUAL(d[3], 4);
        ASSERT_EQUAL(d[5], 6);
        ASSERT_EQUAL(d.Size(), 6);

        d[3] = 3;
        ASSERT_EQUAL(d[3], 3);

        d.At(3) = 9;
        ASSERT_EQUAL(d.At(3), 9);
    }
    {
        Deque<int> d;

        d.PushFront(3);
        d.PushFront(2);
        d.PushFront(1);

        ASSERT_EQUAL(d.Front(), 1);
        ASSERT_EQUAL(d.Back(), 3);
        ASSERT_EQUAL(d.At(0), 1);
        ASSERT_EQUAL(d.At(2), 3);
        ASSERT_EQUAL(d[0], 1);
        ASSERT_EQUAL(d[2], 3);
        ASSERT_EQUAL(d.Size(), 3);
    }
    {
        Deque<int> d;

        d.PushBack(1);
        d.PushBack(2);
        d.PushBack(3);

        ASSERT_EQUAL(d.Front(), 1);
        ASSERT_EQUAL(d.Back(), 3);
        ASSERT_EQUAL(d.At(0), 1);
        ASSERT_EQUAL(d.At(2), 3);
        ASSERT_EQUAL(d[0], 1);
        ASSERT_EQUAL(d[2], 3);
        ASSERT_EQUAL(d.Size(), 3);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestDeque);
    return 0;
}
#endif
