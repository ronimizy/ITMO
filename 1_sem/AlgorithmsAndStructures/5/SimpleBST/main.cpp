#include <iostream>

using namespace std;

struct Node
{
public:
    long long key;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;

    Node (long long key = 0, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
            : key(key), left(left), right(right), parent(parent)
    {}
};

struct Tree
{
public:
    Tree (Node* ptr = nullptr)
            : head(ptr)
    {}

    Node *head;

    void insert(long long value)
    {
        if (head == nullptr)
        {
            head = new Node(value);
            return;
        }

        Node* prev;
        Node* ptr = head;
        while (ptr != nullptr)
        {
            prev = ptr;
            if (value > ptr->key)
            {
                ptr = ptr->right;
                continue;
            }
            if (value < ptr->key)
            {
                ptr = ptr->left;
                continue;
            }
            if (value == ptr->key)
                return;
        }
        ptr = new Node(value, prev);
        if (prev->key > value) prev->left = ptr;
        if (prev->key < value) prev->right = ptr;
    }

    void eject(long long k)
    {
        Node *n = find(k);
        if (n == nullptr) return;

        if (n->left == nullptr && n->right == nullptr)
        {
            if (n == head)
            {
                delete head;
                head = nullptr;
                return;
            }
            if (n->parent->left == n) n->parent->left = nullptr;
            if (n->parent->right == n) n->parent->right = nullptr;

            delete n;
            return;

        }
        if (n->right == nullptr)
        {
            n->left->parent = n->parent;
            if (n->parent != nullptr)
            {
                if (n->parent->left == n) n->parent->left = n->left;
                if (n->parent->right == n) n->parent->right = n->left;
            }
            else head = n->left;

            delete n;
            return;
        }
        if (n->left == nullptr)
        {
            n->right->parent = n->parent;
            if (n->parent != nullptr)
            {
                if (n->parent->left == n) n->parent->left = n->right;
                else n->parent->right = n->right;
            }
            else head = n->right;

            delete n;
            return;
        }
        else
        {
            Node *p = n->left;
            while (p->right != nullptr) p = p->right;

            n->key = p->key;
            if (p == n->left)
            {
                p->parent->left = p->left;
                if (p->left != nullptr) p->left->parent = p->parent;
                delete p;
            }
            else
            {
                p->parent->right = p->left;
                if (p->left != nullptr) p->left->parent = p->parent;
                delete p;
            }
        }
    }

    Node *find(long long k)
    {
        Node *p = head;

        while (p != nullptr)
        {
            if (p->key < k) p = p->right;
            else if (p->key > k) p = p->left;
            else if (p->key == k) break;
        }

        return p;
    }

    Node *successor(long long k)
    {
        if (head == nullptr) return nullptr;

        Node *pr = nullptr;
        Node *p = head;
        while (p != nullptr)
        {
            if (p->key > k)
            {
                pr = p;
                p = p->left;
            } else
            {
                p = p->right;
            }
        }
        return pr;
    }

    Node *predecessor(long long k)
    {
        if (head == nullptr) return nullptr;

        Node *pr = nullptr;
        Node *p = head;
        while (p != nullptr)
        {
            if (p->key < k)
            {
                pr = p;
                p = p->right;
            } else
            {
                p = p->left;
            }
        }
        return pr;
    }
};

int main()
{
    freopen("bstsimple.in", "r", stdin);
    freopen("bstsimple.out", "w", stdout);

    string str;
    Tree tree = Tree();

    while (cin >> str)
    {
        long long value;
        cin >> value;

        if (str == "insert") tree.insert(value);
        else if (str == "exists")
        {
            bool p = tree.find(value) == nullptr;
            cout << (p ? "false" : "true") << endl;
        }
        else if (str == "next")
        {
            Node *p = tree.successor(value);
            if (p == nullptr) cout << "none" << endl;
            else cout << p->key << endl;
        }
        else if (str == "prev")
        {
            Node *p = tree.predecessor(value);
            if (p == nullptr) cout << "none" << endl;
            else cout << p->key << endl;
        }
        else if (str == "delete")
        {
            tree.eject(value);
        }
    }

    return 0;
}
