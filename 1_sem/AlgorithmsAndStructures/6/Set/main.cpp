#include <iostream>
#include <vector>

#define size 1000000

using namespace std;

struct Cell
{
    long value;
    Cell* next = nullptr;

    Cell(long value)
            :value(value)
    {}
};

struct Set
{
    Cell *table[size];

    long h(long a)
    {
        return abs(a)%size;
    }

    void insert(long a)
    {
        long hash = h(a);
        if (table[hash] == nullptr) table[hash] = new Cell(a);
        else
        {
            Cell *ptr = table[hash];
            while (ptr->next != nullptr && ptr->value != a) ptr = ptr->next;
            if (ptr->next == nullptr && ptr->value != a) ptr->next = new Cell(a);
        }
    }

    void eject(long a)
    {
        long hash = h(a);
        if (table[hash] == nullptr) return;
        else if (table[hash]->value == a) table[hash] = table[hash]->next;
        else
        {
            Cell *prev = table[hash];
            if (prev->next == nullptr) return;
            Cell *ptr = prev->next;
            while (ptr->next != nullptr && ptr->value != a) ptr = ptr->next;
            if (ptr->value == a) prev->next = ptr->next;
        }
    }

    int exists(long a)
    {
        long hash = h(a);
        if (table[hash] == nullptr) return false;
        else
        {
            Cell *ptr = table[hash];
            while (ptr->next != nullptr && ptr->value != a) ptr = ptr->next;
            if (ptr->value == a) return true;
            return false;
        }
    }
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);

    Set *set = new Set();
    string s;

    while (cin >> s)
    {
        long value;
        cin >> value;
        if (s == "insert") set->insert(value);
        else if (s == "delete") set->eject(value);
        else if (s == "exists") cout << (set->exists(value) ? "true" : "false") << endl;
    }

    return 0;
}
