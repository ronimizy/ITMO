#include <iostream>
#include <vector>

using namespace std;

class PriorityQueue
{
private:
    vector<int> queue;
    vector<int> rows;

public:
    void push(int a, int row)
    {
        queue.push_back(a);
        rows.push_back(row);
    }

    void extractMin()
    {
        if (!queue.empty())
        {
            int m = queue[0], index = 0;
            for (int i = 1; i < queue.size(); i++)
            {
                if (queue[i] < m)
                {
                    m = queue[i];
                    index = i;
                }
            }
            int tmp = queue[index];
            queue[index] = queue.back();
            rows[index] = rows.back();
            queue.pop_back();
            rows.pop_back();
            printf("%d\n", tmp);
        } else
        {
            printf("*\n");
        }
    }

    void decreaseKey(int key, int value)
    {
        int index = 0;
        for (int i = 0; i < rows.size(); i++)
        {
            if (rows[i] == key)
            {index = i; break;}
        }
        queue[index] = value;
    }
};

int main()
{
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    freopen("priorityqueue.in", "r", stdin);
    freopen("priorityqueue.out", "w", stdout);

    string command;
    int row = 1;
    PriorityQueue queue;

    while (cin >> command)
    {
        if (command == "push")
        {
            int value;
            cin >> value;
            queue.push(value, row++);
        }
        else if (command == "extract-min")
        {
            queue.extractMin();
            row++;
        }
        else if (command == "decrease-key")
        {
            int key, value;
            cin >> key >> value;
            queue.decreaseKey(key, value);
            row++;
        }
    }

    return 0;
}
