#include <iostream>
#include <vector>

using namespace std;

template <typename T>
T binSearchFirst(vector<T> &array, T element)
{
    if (array.front() > element || array.back() < element) return -1;

    long long int left = -1, right = (long long int) array.size();

    while (right - left > 1)
    {
        long long int mid = (left + right) / 2;
        if (array[mid] < element) left = mid;
        else right = mid;
    }

    if (array[right] == element) return right + 1;

    return -1;
}

template <typename T>
T binSearchLast(vector<T> &array, T element)
{
    if (array.front() > element || array.back() < element) return -1;

    long long int left = -1, right = (long long int) array.size();

    while (right - left > 1)
    {
        long long int mid = (left + right) / 2;
        if (array[mid] <= element) left = mid;
        else right = mid;
    }

    if (array[right - 1] == element) return right;

    return -1;
}

int main()
{
    freopen("binsearch.in", "r", stdin);
    freopen("binsearch.out", "w", stdout);

    long long int length, count, element;

    cin >> length;
    vector<long long int> array(length);
    for (long long int i = 0; i < length; i++)
    {
        cin >> array[i];
    }

    cin >> count;
    for (long long int i = 0; i < count; i++)
    {
        cin >> element;
        cout << binSearchFirst(array, element) << " " << binSearchLast(array, element) << "\n";
    }

    return 0;
}
