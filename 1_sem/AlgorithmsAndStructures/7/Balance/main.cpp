#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    explicit Node(int key = 0, int left = 0, int right = 0)
    :key(key), left(left), right(right)
    {}

    int key;
    int left;
    int right;

    int index;
    bool checked = false;

    int height;

    int balance(vector<Node> &array)
    {
        if (checked) return height;

        int hLeft = 0, hRight = 0;

        if (left != 0) hLeft = array[left].balance(array);
        if (right != 0) hRight = array[right].balance(array);

        index = hRight - hLeft;
        height = (hRight > hLeft ? hRight : hLeft) + 1;
        checked = true;

        return height;
    }
};

int main()
{
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);

    int count; cin >> count;
    vector<Node> array(count+1);
    array[0] = Node();

    for (int i = 1; i <= count; i++)
        cin >> array[i].key >> array[i].left >> array[i].right;

    for (int i = 1; i <= count; i++)
        if (!array[i].checked) array[i].balance(array);

    for (int i = 1; i <= count; i++)
        cout << array[i].index << endl;

    return 0;
}
