#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void swap(vector<T> &array, int first, int second)
{
    T tmp = array[first];
    array[first] = array[second];
    array[second] = tmp;
}

template <typename T>
T kTh(vector<T> array, int k)
{
    int left = 0, right = array.size()-1;

    while (true)
    {
        if (left+1 >= right)
        {
            if (left+1 == right && array[left] > array[right]) { swap(array, left, right); }
            return array[k];
        }

        int center = (left + right) / 2;
        swap(array, left+1, center);
        if (array[left] > array[right]) { swap(array, left, right); }
        if (array[left+1] > array[right]) {swap(array, left+1, right); }
        if (array[left] > array[left+1]) {swap(array, left, left+1); }


        int leftLocal = left+1, rightLocal = right;
        T value = array[leftLocal];

        while (true)
        {
            do
            {
                leftLocal++;
            } while (array[leftLocal] < value);
            do
            {
                rightLocal--;
            } while (array[rightLocal] > value);
            if (leftLocal > rightLocal) { break; }

            swap(array, leftLocal, rightLocal);
        }

        array[left+1] = array[rightLocal];
        array[rightLocal] = value;

        if (rightLocal >= k) { right = rightLocal-1; }
        if (rightLocal <= k) { left = leftLocal; }
    }
}


int main()
{
    //clock_t begin = clock();

    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);

    int n, k, A, B, C, var;
    vector<int> array;

    cin >> n >> k >> A >> B >> C >> var;
    array.push_back(var);

    if (n > 1) { cin >> var; array.push_back(var); }

    for (int i = 2; i < n; i++)
    {
        array.push_back((A*array[i-2]) + (B*array[i-1]) + C);
    }

    printf("%d\n", kTh(array, k-1));
    //clock_t end = clock();

    //printf("%f", (double)(end-begin)/CLOCKS_PER_SEC);

    return 0;
}
