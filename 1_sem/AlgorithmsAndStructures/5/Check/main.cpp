#include <iostream>
#include <vector>

using namespace std;

int main()
{
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);

    int count;
    cin >> count;

    vector<pair<int, pair<int, int>>> tree(count + 1);
    tree[0] = pair<int, pair<int, int> >(0, pair<int, int>(0, 0));

    for (int i = 1; i <= count; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        tree[i] = pair<int, pair<int, int> >(a, pair<int, int>(b, c));
    }

    vector<vector<int>> checks;
    checks.emplace_back(vector<int>{1, INT_MIN, INT_MAX});

    if (count != 0)
    {

        while (!checks.empty())
        {
            int index = checks.back()[0];
            int minimum = checks.back()[1];
            int maximum = checks.back()[2];
            checks.pop_back();

            if (tree[index].first <= minimum || tree[index].first >= maximum)
            {
                cout << "NO";
                exit(0);
            }
            if (tree[index].second.first != 0)
                checks.emplace_back(vector<int>{tree[index].second.first, minimum, tree[index].first});
            if (tree[index].second.second != 0)
                checks.emplace_back(vector<int>{tree[index].second.second, tree[index].first, maximum});
        }
    }


    cout << "YES";

    return 0;
}
