#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class Stack
{
private:
    vector<T> array;

public:
    void push(T a)
    {
        array.push_back(a);
    }

    T pop()
    {
        T a = array.back();
        array.pop_back();
        return a;
    }

    int size()
    {
        return array.size();
    }
};

int main()
{
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    freopen("postfix.in", "r", stdin);
    freopen("postfix.out", "w", stdout);

    string line;
    Stack<int> stack;

    while (cin >> line)
    {
        if (line == "+")
        {
            int a = stack.pop(), b = stack.pop();
            stack.push(a + b);
        } else if (line == "-")
        {
            int a = stack.pop(), b = stack.pop();
            stack.push(b - a);
        } else if (line == "*")
        {
            int a = stack.pop(), b = stack.pop();
            stack.push(a * b);
        } else stack.push(stoi(line));
    }

    cout << stack.pop();

    return 0;
}
