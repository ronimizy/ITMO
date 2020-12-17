#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    Node(int k = 0, Node *l = nullptr, Node *r = nullptr, int h = 1)
            : key(k), left(l), right(r), height(h) {}

    int key;
    Node *left;
    Node *right;

    int height;
};

class AVLTree {
    Node *root;

    int getHeight(Node *n) {
        if (n == nullptr)
            return 0;

        return n->height;
    }

    void fixHeight(Node *n) {
        if (n == nullptr)
            return;

        n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
    }

    int getBalance(Node *n) {
        if (n == nullptr)
            return 0;

        return getHeight(n->right) - getHeight(n->left);
    }

    Node *balance(Node *n) {
        if (n == nullptr)
            return n;

        fixHeight(n);

        if (getBalance(n) > 1) {
            if (getBalance(n->right) < 0)
                n->right = rotateRight(n->right);

            return rotateLeft(n);
        }

        if (getBalance(n) < -1) {
            if (getBalance(n->left) > 0)
                n->left = rotateLeft(n->left);

            return rotateRight(n);
        }

        return n;
    }

    Node *rotateLeft(Node *n) {
        if (n == nullptr)
            return n;

        Node *r = n->right;
        n->right = r->left;
        r->left = n;

        fixHeight(n);
        fixHeight(r);

        return r;
    }

    Node *rotateRight(Node *n) {
        if (n == nullptr)
            return n;

        Node *l = n->left;
        n->left = l->right;
        l->right = n;

        fixHeight(n);
        fixHeight(l);

        return l;
    }

    Node *lastRight(Node *n) {
        if (n->right == nullptr) return n;
        return lastRight(n->right);
    }

    Node *put(int k, Node *n) {
        if (n == nullptr) {
            return new Node(k);
        }

        if (k > n->key)
            n->right = put(k, n->right);
        else if (k < n->key)
            n->left = put(k, n->left);
        else
            return n;

        return balance(n);
    }

    Node *get(int k, Node *n) {
        if (n == nullptr)
            return n;

        if (n->key < k)
            n->right = get(k, n->right);
        else if (n->key > k)
            n->left = get(k, n->left);
        else {
            if (n->left == nullptr && n->right == nullptr) {
                return nullptr;
            }
            if (n->left == nullptr) {
                n = n->right;
                return balance(n);
            } else {
                Node *f = lastRight(n->left);
                n->key = f->key;
                n->left = get(f->key, n->left);
            }
        }

        return balance(n);
    }

    bool check(int k, Node *n) {
        if (n == nullptr) return false;

        if (n->key < k)
            return check(k, n->right);
        if (n->key > k)
            return check(k, n->left);

        return true;
    }

public:
    AVLTree()
            : root(nullptr) {}


    int insert(int k) {
        root = put(k, root);

        return getBalance(root);
    }

    int eject(int k) {
        root = get(k, root);

        return getBalance(root);
    }

    bool exists(int k) {
        return check(k, root);
    }
};


int main() {


    freopen("avlset.in", "r", stdin);
    freopen("avlset.out", "w", stdout);

    int count;
    cin >> count;

    AVLTree tree;

    string action;
    int value;

    for (int i = 0; i < count; i++) {
        cin >> action >> value;

        if (action == "A") {
            cout << tree.insert(value) << endl;
        }
        if (action == "D") {
            cout << tree.eject(value) << endl;
        }
        if (action == "C") {
            cout << (tree.exists(value) ? "Y" : "N") << endl;
        }
    }

    return 0;
}