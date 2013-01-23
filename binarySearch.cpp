
#include <iostream>
#include <vector>

using namespace std;

/** Binary search - find position of x in xs
 *
 *  Precondition: xs is sorted
 *
 *  Idea:   It can be tricky to implement binary search without special cases.
 *          It's important to notice that mid is always rounded down.
 *          If you are left with only two numbers, the mid will be the first one. So if
 *          x > mid, lo must go +1, otherwise it would stuck.
 *
 *          Conditions can be set differently, but the most important is that you don't
 *          get stuck with only two elements.
 *          
 *          
 */
int binarySearch(vector<int>& xs, int x)
{

    int lo = 0;
    int hi = xs.size() - 1;

    while(lo < hi)
    {
        int mid = lo + (hi - lo) / 2;   // This way we avoid having (hi + lo) -> oferflow
        if (x > xs[mid])
            lo = mid + 1;               // Keep lo moving
        else
            hi = mid;                   // hi is moving for sure, as mid is rounded down

    }

    if (xs[lo] == x) return lo;
    return -1;
}

int main(int argc, char const *argv[])
{
    vector<int> xs;
    xs.push_back(1);
    xs.push_back(2);

    cout << binarySearch(xs, 0) << endl;
    cout << binarySearch(xs, 1) << endl;
    cout << binarySearch(xs, 2) << endl;
    cout << binarySearch(xs, 25) << endl;

    return 0;
}
