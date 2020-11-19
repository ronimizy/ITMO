#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define SIZE 1000

struct LinkedMapCell
{
    string key;

    LinkedMapCell *prev;
    LinkedMapCell* next = nullptr;

    LinkedMapCell *before;
    LinkedMapCell *after = nullptr;

    LinkedMapCell(string key, LinkedMapCell *b = nullptr, LinkedMapCell *prev = nullptr)
            :key(key), prev(prev), before(b)
    {}
};

struct LinkedMap
{
    LinkedMapCell *table[SIZE];
    int primes[10] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

    LinkedMapCell *lastAdded = nullptr;

    long hash(string key)
    {
        long sum = 0;
        for (int i = 0; i < key.size(); i++) sum += primes[abs(key[i] - 'a') % 10] * primes[i % 10];

        return sum % SIZE;
    }

    void put(string key)
    {
        long h = hash(key);
        if (table[h] == nullptr)
        {
            table[h] = new LinkedMapCell(key, lastAdded);

            if (lastAdded != nullptr) lastAdded->after = table[h];
            table[h]->before = lastAdded;
            lastAdded = table[h];
        }
        else
        {
            LinkedMapCell *ptr = table[h];
            while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;

            if (ptr->key != key)
            {
                ptr->next = new LinkedMapCell(key, lastAdded, ptr);

                if (lastAdded != nullptr) lastAdded->after = ptr->next;
                lastAdded = ptr->next;
            }
            else if (ptr->key == key)
            {
                if (ptr->before != nullptr && ptr != lastAdded) ptr->before->after = ptr->after;
                if (ptr->after != nullptr) ptr->after->before = ptr->before;

                if (lastAdded != ptr)
                {
                    if (lastAdded != nullptr) lastAdded->after = ptr;
                    ptr->before = lastAdded;
                    ptr->after = nullptr;
                }

                lastAdded = ptr;
            }
        }
    }

    void eject(string key)
    {
        long h = hash(key);
        if (table[h] == nullptr) return;

        LinkedMapCell *ptr = table[h];
        while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;

        if (ptr->key == key)
        {
            if (ptr->prev != nullptr) ptr->prev->next = ptr->next;
            else
            {
                table[h] = ptr->next;
            }
            if (ptr->next != nullptr) ptr->next->prev = ptr->prev;

            if (ptr->before != nullptr) ptr->before->after = ptr->after;
            if (ptr->after != nullptr) ptr->after->before = ptr->before;
            else
            {
                lastAdded = ptr->before;
            }

            delete ptr;
        }
    }
};

struct MultimapCell
{
    string key;
    LinkedMap *value;

    MultimapCell *prev;
    MultimapCell *next = nullptr;

    MultimapCell(string key, string value, MultimapCell *prev = nullptr)
    :key(key), prev(prev)
    {
        this->value = new LinkedMap();
        this->value->put(value);
    }
};

struct MultiMap
{
    MultimapCell *table[SIZE];

    int primes[10] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    long hash(string key)
    {
        long sum = 0;
        for (int i = 0; i < key.size(); i++) sum += primes[abs(key[i] - 'a') % 10] * primes[i % 10];

        return sum % SIZE;
    }

    void put(string key, string value)
    {
        long h = hash(key);

        if (table[h] == nullptr) table[h] = new MultimapCell(key, value);
        else
        {
            MultimapCell *ptr = table[h];
            while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;

            if (ptr->key == key) ptr->value->put(value);
            else ptr->next = new MultimapCell(key, value, ptr);
        }
    }

    void eject(string key, string value)
    {
        long h = hash(key);
        if (table[h] == nullptr) return;

        MultimapCell *ptr = table[h];
        while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;

        if (ptr->key == key) ptr->value->eject(value);
        else return;
    }

    void ejectAll(string key)
    {
        long h = hash(key);
        if (table[h] == nullptr) return;

        MultimapCell *ptr = table[h];
        while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;

        if (ptr->key == key)
        {
            if (ptr->prev != nullptr) ptr->prev->next = ptr->next;
            else
            {
                table[h] = ptr->next;
            }
            if (ptr->next != nullptr) ptr->next->prev = ptr->prev;

            delete ptr;
        }
        else return;
    }

    void get(string key)
    {
        long h = hash(key);
        if (table[h] == nullptr)
        {
            cout << "0" << endl;
            return;
        }

        MultimapCell *ptr = table[h];
        while (ptr->next != nullptr && ptr->key != key) ptr = ptr->next;

        if (ptr->key == key)
        {
            vector<string> s;
            LinkedMapCell *lp = ptr->value->lastAdded;

            while (lp != nullptr)
            {
                s.push_back(lp->key);
                lp = lp->before;
            }

            cout << s.size() << " ";
            for (int i = 0; i < s.size(); i++) cout << s[i] << " ";

            cout << endl;
        }
        else
        {
            cout << "0" << endl;
            return;
        }
    }
};



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);

    MultiMap *map = new MultiMap();

    string s;
    while (cin >> s)
    {
        string key; cin >> key;

        if (s == "put")
        {
            string value; cin >> value;
            map->put(key, value);
        }
        if (s == "get") map->get(key);
        if (s == "delete")
        {
            string value; cin >> value;
            map->eject(key, value);
        }
        if (s == "deleteall") map->ejectAll(key);
    }

    return 0;
}
