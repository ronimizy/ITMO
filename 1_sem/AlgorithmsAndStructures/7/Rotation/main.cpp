#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    explicit Node(int k = 0, int l = 0, int r = 0, int h = 0)
            : key(k), left(l), right(r), height(h) {}

    int key;
    int left;
    int right;
    int height;
};

struct AVLTree {

    explicit AVLTree(vector<Node> t)
            : tree(std::move(t)) {}

    vector<Node> tree;

    int calcHeight(int i) {
        if (i < 0) return 0;

        int hR = calcHeight(tree[i].left);
        int hL = calcHeight(tree[i].right);

        tree[i].height = (hR > hL ? hR : hL) + 1;

        return tree[i].height;
    }

    int rotateLeft(int i) {
        int r = tree[i].right;
        tree[i].right = tree[r].left;
        tree[r].left = i;

        calcHeight(i);
        calcHeight(r);

        return r;
    }

    int rotateRight(int i) {
        int l = tree[i].left;
        tree[i].left = tree[l].right;
        tree[l].right = i;

        calcHeight(i);
        calcHeight(l);

        return l;
    }

    int bigRotateLeft(int i) {
        tree[i].right = rotateRight(tree[i].right);

        return rotateLeft(i);
    }

    int rotate(int i) {
        int r = tree[i].right;
        int lH = getHeight(tree[r].left);
        int rH = getHeight(tree[r].right);

        if (rH - lH == -1) return bigRotateLeft(i);

        return rotateLeft(i);
    }

    int getHeight(int i) {
        if (i < 0) return 0;

        return tree[i].height;
    }

    void print(int root) {
        int line = 1;
        queue<int> q;

        q.push(root);
        cout << tree.size() << endl;

        while (!q.empty()) {
            int i = q.front();
            q.pop();
            int l = 0, r = 0;

            if (tree[i].left >= 0) {
                q.push(tree[i].left);
                l = ++line;
            }
            if (tree[i].right >= 0) {
                q.push(tree[i].right);
                r = ++line;
            }
            cout << tree[i].key << " " << l << " " << r << endl;
        }
    }
};


int main() {
    freopen("rotation.in", "r", stdin);
    freopen("rotation.out", "w", stdout);

    int count;
    cin >> count;

    vector<Node> line(count);

    for (int i = 0; i < count; i++) {
        cin >> line[i].key >> line[i].left >> line[i].right;

        line[i].left--;
        line[i].right--;
    }

    auto *tree = new AVLTree(line);

    tree->calcHeight(0);

    int root = tree->rotate(0);

    tree->print(root);

    return 0;
}
