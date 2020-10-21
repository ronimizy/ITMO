#include <iostream>
#include <vector>

using namespace std;

class Stack
{
private:
    vector<char> array;

public:
    void push(char a)
    {
        array.push_back(a);
    }

    char pop()
    {
        char a = array.back();
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
    int openedRoundBracket = 0;
    int openedSquareBracket = 0;

    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);

    string line;

    while (cin >> line)
    {
        Stack stack;
        bool no = false;
        for (char i:line)
        {
            if (i == '[' || i == '(') stack.push(i);
            else if (stack.size() == 0 || stack.pop() != (i == ')' ? '(' : '['))
            {
                no = true;
                break;
            }
        }
        if (no || stack.size() != 0) cout << "NO" << endl;
        else cout << "YES" << endl;
    }

    return 0;
}
