#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct InputNode {
    InputNode(int k = 0, int l = -1, int r = -1)
            : key(k), left(l), right(r) {}

    int key;
    int left;
    int right;
};

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
    int size;

    Node* build(vector<InputNode> &data, int i) {
        if (i < 0 || data.empty()) return nullptr;

        Node *n = new Node(data[i].key);

        n->left = build(data, data[i].left);
        n->right = build(data, data[i].right);
        n->height = max(getHeight(n->left), getHeight(n->right)) + 1;

        return n;
    }

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

    Node* balance(Node *n) {
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

    Node* rotateLeft(Node *n) {
        if (n == nullptr)
            return n;

        Node *r = n->right;
        n->right = r->left;
        r->left = n;

        fixHeight(n);
        fixHeight(r);

        return r;
    }
    Node* rotateRight(Node *n) {
        if (n == nullptr)
            return n;

        Node *l = n->left;
        n->left = l->right;
        l->right = n;

        fixHeight(n);
        fixHeight(l);

        return l;
    }

    Node* lastRight(Node *n) {
        if (n->right == nullptr) return n;
        return lastRight(n->right);
    }

    Node* put(int k, Node *n) {
        if (n == nullptr)
        {
            size++;
            return new Node(k);
        }

        if (k > n->key)
            n->right = put(k, n->right);
        else if (k < n->key)
            n->left = put(k, n->left);
        else return n;

        return balance(n);
    }

    Node* get(int k, Node *n) {
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
            }
            else {
                Node *f = lastRight(n->left);
                n->key = f->key;
                n->left = get(f->key, n->left);
            }
        }

        return balance(n);
    }

public:
    AVLTree(vector<InputNode> &data)
            : size(0) {
        root = build(data, 0);
        size = data.size();
    }

    void print() {

        cout << size << endl;

        queue<Node*> q;
        q.push(root);

        if (root == nullptr) return;

        int line = 1;

        while (!q.empty()) {
            int l = 0;
            int r = 0;

            Node *n = q.front();
            q.pop();

            if (n->left != nullptr) {
                q.push(n->left);
                l = ++line;
            }
            if (n->right != nullptr) {
                q.push(n->right);
                r = ++line;
            }

            cout << n->key << " " << l << " " << r << endl;
        }
    }

    void insert(int k) {
        root = put(k, root);
    }

    void eject(int k) {
        if (size == 0) return;
        root = get(k, root);
        size--;
    }
};


int main() {


    freopen("deletion.in", "r", stdin);
    freopen("deletion.out", "w", stdout);

    int count;
    cin >> count;

    vector<InputNode> data(count);

    for (int i = 0; i < count; i++) {
        cin >> data[i].key >> data[i].left >> data[i].right;

        data[i].left--;
        data[i].right--;
    }

    AVLTree tree(data);

    int k;
    cin >> k;

    tree.eject(k);
    tree.print();

    return 0;
}