#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    vector<int> stack;
    int n;
    freopen("stack.in", "r", stdin);
    freopen("stack.out", "w", stdout);

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        char command;
        cin >> command;

        if (command == '+')
        {
            int a;
            cin >> a;
            stack.push_back(a);
        }
        else
        {
            cout << stack.back() << endl;
            stack.pop_back();
        }
    }


    return 0;
}
