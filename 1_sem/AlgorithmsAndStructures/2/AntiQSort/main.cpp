#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    freopen("antiqs.in", "r", stdin);
    freopen("antiqs.out", "w", stdout);

    int n;
    cin >> n;

    vector<int> array(n);

    for (int i = 0; i < n; i++)
    {
        array[i] = i+1;
    }

    for (int i = 0; i < n; i++)
    {
        int temp = array[i];
        array[i] = array[i/2];
        array[i/2] = temp;
    }

    for (int i = 0; i < n; i++)
    {
        cout << array[i] << " ";
    }

    return 0;
}
