#include <iostream>
#include <vector>

using namespace std;

using result_type = unsigned long long;

template<typename T>
class InversionsCounter {
    static void compare(std::vector<T> &leftArray, std::vector<T> &rightArray, std::vector<T> &result, result_type &count) {
        result_type left = 0, right = 0;
        for (long int i = 0; i < leftArray.size() + rightArray.size(); i++) {
            if (left < leftArray.size() && right < rightArray.size()) {
                if (leftArray[left] > rightArray[right]) {
                    result[i] = rightArray[right];
                    count += leftArray.size() - left;
                    right++;
                } else {
                    result[i] = leftArray[left];
                    left++;
                }
            } else if (left == leftArray.size()) {
                result[i] = rightArray[right];
                right++;
            } else if (right == rightArray.size()) {
                result[i] = leftArray[left];
                left++;
            }
        }
    }

    static void divideCompare(std::vector<T> &array, result_type &count) {
        if (array.size() == 1) { return; }

        result_type divideIndex = array.size() / 2;

        std::vector<T> leftArray, rightArray;

        for (result_type i = 0; i < divideIndex; i++) {
            leftArray.push_back(array[i]);
        }

        for (result_type i = divideIndex; i < array.size(); i++) {
            rightArray.push_back(array[i]);
        }

        divideCompare(leftArray, count);
        divideCompare(rightArray, count);

        compare(leftArray, rightArray, array, count);
    }

public:
    static result_type Count(const std::vector<T> &vector) {
        std::vector<T> array(vector);
        result_type count = 0;

        divideCompare(array, count);

        return count;
    }
};

int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

#ifndef __APPLE__
    freopen("inversions.in", "r", stdin);
    freopen("inversions.out", "w", stdout);
#endif

    long long amount;
    cin >> amount;

    vector<long long> array(amount);

    for (long int i = 0; i < amount; i++) {
        cin >> array[i];
    }

    cout << InversionsCounter<long long>::Count(array);

    return 0;
}