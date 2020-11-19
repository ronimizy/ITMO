#include <iostream>
#include <vector>

using namespace std;

//template <typename T>
class Node
{
public:
    int key = 0;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *root = this;

    int height = 0;

    void centerPrint() const
    {
        if (left != nullptr) left->centerPrint();
        cout << key << endl;
        if (right != nullptr) right->centerPrint();
    }
    void directPrint() const
    {
        cout << key << endl;
        if (left != nullptr) left->directPrint();
        if (right != nullptr) right->directPrint();
    }
    void indirectPrint() const
    {
        if(left != nullptr) left->indirectPrint();
        if (right != nullptr) right->indirectPrint();
        cout << key << endl;
    }

    Node* search(int k)
    {
        Node *x = this;
        while (x != nullptr && k != x->key) k < x->key ? x = x->left : x = x->right;
        return x;
    }

    Node* minimum()
    {
        Node *x = this;
        while (x->left != nullptr) x = x->left;
        return x;
    }
    Node* maximum()
    {
        Node *x = this;
        while (x->right != nullptr) x = x->right;
        return x;
    }

    Node* successor()
    {
        Node* x = this;
        if (x->right != nullptr) return x->right->minimum();
        while (x->parent != nullptr && x == x->parent->right) x = x->parent;
        return x->parent;
    }

    void insert(Node* z)
    {
        if (this->root == this) z->height = 1;
        else z->height = this->height;

        if (z->key < this->key)
        {
            if (this->left != nullptr) this->left->insert(z);
            else
            {
                this->left = z;
                z->parent = this;
                z->height++;
                if (this->root->height < z->height) this->root->height = z->height;
            }
        }
        else
        {
            if (this->right != nullptr) this->right->insert(z);
            else
            {
                this->right = z;
                z->parent = this;
                z->height++;
                if (this->root->height < z->height) this->root->height = z->height;
            }
        }
    }
    void eject()
    {
        if (this->right != nullptr)
        {
            Node *x = this->right->minimum();

            if (x == x->parent->left) x->parent->left = nullptr;
            else x->parent->right = nullptr;

            if (this->parent != nullptr)
            {
                if (this == this->parent->left) this->parent->left = x;
                else this->parent->right = x;
            }
            if (this->left != nullptr) this->left->parent = x;
            if (this->right != nullptr) this->right->parent = x;

            x->parent = this->parent;
            x->left = this->left;
            x->right = this->right;
        }
        else
        {
            if (this->parent != nullptr)
            {
                if (this == this->parent->left) this->parent->left = this->left;
                else this->parent->right = this->left;
            }
            this->left->parent = this->parent;
        }

        free(this);
    }
};

int main()
{
    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);

    int count;
    cin >> count;

    if (count != 0)
    {

        vector<pair<int, int>> tree(count + 1);

        for (int i = 1; i <= count; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            tree[i] = pair<int, int>(b, c);
        }

        vector<pair<int, int>> heights;
        heights.emplace_back(pair<int, int>(1, 1));
        int maxHeight = 0;

        while (!heights.empty())
        {
            pair<int, int> h = heights.back(); heights.pop_back();
            pair<int, int> n = tree[h.first];
            maxHeight = max(h.second, maxHeight);
            if (n.first != 0) heights.emplace_back(pair<int, int>(n.first, h.second+1));
            if (n.second != 0) heights.emplace_back(pair<int, int>(n.second, h.second+1));
        }

        cout << maxHeight;
    }
    else cout << 0;


    return 0;
}
