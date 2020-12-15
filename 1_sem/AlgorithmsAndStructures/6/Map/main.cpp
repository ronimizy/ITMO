#include <iostream>
#include <string>
#include <ctime>

using namespace std;

#define SIZE 100000

struct Cell
{
    string key;
    string value;

    Cell *prev;
    Cell* next = nullptr;

    Cell(string key, string value, Cell *prev = nullptr)
    :key(key), value(value), prev(prev)
    {}
};

struct Map
{
    Cell *table[SIZE];
    long a = rand() + 1, b = rand();
    int primes[10] = { 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 };

    long hashify(string key)
    {
        long sum = 0;
        for (int i = 0; i < key.size(); i++ ) sum += primes[abs(key[i] - 'a') % 10] * primes[i % 10];

        return sum % SIZE;
    }

    void put(string key, string value)
    {
        long hash = hashify(key);
        if (table[hash] == nullptr) table[hash] = new Cell(key, value);
        else
        {
            Cell *ptr = table[hash];
            while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;
            if (ptr->key != key) ptr->next = new Cell(key, value, ptr);
            else ptr->value = value;
        }
    }

    string get(string key)
    {
        long hash = hashify(key);
        if (table[hash] == nullptr) return "none";
        else
        {
            Cell *ptr = table[hash];
            while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;
            if (ptr->key == key) return ptr->value;
            else return "none";
        }
    }

    void eject(string key)
    {
        long hash = hashify(key);
        if (table[hash] == nullptr) return;
        else
        {
            Cell *ptr = table[hash];
            while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;
            if (ptr->key == key)
            {
                if (table[hash] == ptr) table[hash] = ptr->next;
                if (ptr->prev != nullptr) ptr->prev->next = ptr->next;
                if (ptr->next != nullptr) ptr->next->prev = ptr->prev;
                free(ptr);
            }
        }
    }
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);

    srand((unsigned int) time(nullptr));

    Map *map = new Map();

    string s;
    while (cin >> s)
    {
        string key; cin >> key;

        if (s == "put")
        {
            string value; cin >> value;
            map->put(key, value);
        }
        if (s == "get") cout << (map->get(key)) << endl;
        if (s == "delete") map->eject(key);
    }

    return 0;
}
