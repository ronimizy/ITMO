#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);

    vector<int> queue;
    int n, outputIterator = 0;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        char command;
        cin >> command;
        if (command == '+')
        {
            int a;
            cin >> a;
            queue.push_back(a);
        }
        else
        {
            cout << queue[outputIterator++] << endl;
        }
    }

    return 0;
}
