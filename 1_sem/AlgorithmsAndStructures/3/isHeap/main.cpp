#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    freopen("isheap.in","r", stdin);
    freopen("isheap.out", "w", stdout);

    int n, a;
    vector<int> array;
    cin >>n;

    for (int i = 0; i < n; i++)
    {
        cin >> a;
        array.push_back(a);
    }

    for (int i = 0; i < n/2; i++)
    {
        if (2*i+2 < n && (array[i] > array[2*i+1] || array[i] > array[2*i+2]))
        {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}
