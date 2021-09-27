#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int n;
    int64_t r;

    cin >> n >> r;

    int64_t weight = 0;

    for (int i = 0; i < n; i++)
    {
        int w, h, d;
        cin >> w >> h >> d;

        weight += w * h * d * r;
    }

    cout << weight << endl;

    return 0;
}
