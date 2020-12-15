#include <iostream>
#include <string>

using namespace std;

#define SIZE 100000

struct LinkedMapCell
{
    string key;
    string value;

    LinkedMapCell *prev;
    LinkedMapCell* next = nullptr;

    LinkedMapCell *before;
    LinkedMapCell *after = nullptr;

    LinkedMapCell(string key, string value, LinkedMapCell *b = nullptr, LinkedMapCell *prev = nullptr)
            :key(key), value(value), prev(prev), before(b)
    {}
};

struct LinkedMap
{
    LinkedMapCell *table[SIZE];
    int primes[10] = { 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 };

    LinkedMapCell *lastAdded = nullptr;

    long hashify(string key)
    {
        long sum = 0;
        for (int i = 0; i < key.size(); i++ ) sum += primes[abs(key[i] - 'a') % 10] * primes[i % 10];

        return sum % SIZE;
    }

    void put(string key, string value)
    {
        long hash = hashify(key);
        if (table[hash] == nullptr)
        {
            LinkedMapCell *c = new LinkedMapCell(key, value, lastAdded);
            table[hash] = c;

            if (lastAdded != nullptr) lastAdded->after = c;
            lastAdded = c;
        }
        else
        {
            LinkedMapCell *ptr = table[hash];
            while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;
            if (ptr->key != key)
            {
                LinkedMapCell *c = new LinkedMapCell(key, value, lastAdded, ptr);
                ptr->next = c;
                if (lastAdded != nullptr) lastAdded->after = c;
                lastAdded = c;
            }
            else
            {
                ptr->value = value;
            }
        }
    }

    LinkedMapCell* find(string key)
    {
        long hash = hashify(key);
        if (table[hash] == nullptr) return nullptr;
        else
        {
            LinkedMapCell *ptr = table[hash];
            while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;
            if (ptr->key == key) return ptr;
            else return nullptr;
        }
    }

    string get(string key)
    {
        LinkedMapCell *c = find(key);
        return c == nullptr ? "none" : c->value;
    }

    string after(string key)
    {
        LinkedMapCell *c = find(key);
        if (c == nullptr || c->after == nullptr) return "none";
        return c->after->value;
    }

    string before(string key)
    {
        LinkedMapCell *c = find(key);
        if (c == nullptr || c->before == nullptr) return "none";
        return c->before->value;
    }

    void eject(string key)
    {
        long hash = hashify(key);
        if (table[hash] == nullptr) return;
        else
        {
            LinkedMapCell *ptr = table[hash];
            while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;
            if (ptr->key == key)
            {
                if (table[hash] == ptr) table[hash] = ptr->next;

                if (ptr->prev != nullptr) ptr->prev->next = ptr->next;
                if (ptr->next != nullptr) ptr->next->prev = ptr->prev;

                if (ptr->before != nullptr) ptr->before->after = ptr->after;
                if (ptr->after != nullptr) ptr->after->before = ptr->before;

                if (lastAdded == ptr) lastAdded = ptr->before;

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

    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);

    LinkedMap *map = new LinkedMap();

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
        if (s == "prev") cout << (map->before(key)) << endl;
        if (s == "next") cout << (map->after(key)) << endl;
    }

    return 0;
}
