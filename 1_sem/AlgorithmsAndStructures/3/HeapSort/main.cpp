#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void heapify(vector<T> &array, int n, int root) {
    int largest = root, left = 2 * root + 1, right = left + 1;

    if (left < n && array[largest] < array[left]) { largest = left; }
    if (right < n && array[largest] < array[right]) { largest = right; }

    if (largest != root) {
        swap(array[root], array[largest]);

        heapify(array, n, largest);
    }
}

template<typename T>
void heapSort(vector<T> &array) {
    for (int i = array.size() / 2 - 1; i >= 0; i--) { heapify(array, array.size(), i); }

    for (int i = array.size() - 1; i >= 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    vector<int> array;
    int n, a;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a;
        array.push_back(a);
    }

    heapSort(array);

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }

    return 0;
}
