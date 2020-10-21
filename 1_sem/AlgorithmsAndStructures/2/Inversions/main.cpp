#include <iostream>
#include <vector>

using namespace std;

long long inversionsCount = 0;

void compare(long int leftSize, vector<long long>& leftArray, long int rightSize, vector<long long>& rightArray, vector<long long>& result)
{
    long int left = 0, right = 0;
    for (long int i = 0; i < leftSize+rightSize; i++)
    {
        if (left < leftSize && right < rightSize)
        {
            if (leftArray[left] > rightArray[right])
            {
                result[i] = rightArray[right];
                inversionsCount += leftSize-left;
                right++;
            }
            else
            {
                result[i] = leftArray[left];
                left++;
            }
        }
        else if (left == leftSize)
        {
            result[i] = rightArray[right];
            right++;
        }
        else if (right == rightSize)
        {
            result[i] = leftArray[left];
            left++;
        }
    }
}

void divideCompare(long long size, vector<long long>& array)
{
    if (size == 1) { return; }

    long long divideIndex = size/2;

    vector<long long> leftArray(divideIndex), rightArray(size - divideIndex);

    for (long long i = 0; i < divideIndex; i++)
    {
        leftArray[i] = array[i];
    }

    for (long long i = divideIndex; i < size; i++)
    {
        rightArray[i-divideIndex] = array[i];
    }

    divideCompare(divideIndex, leftArray);
    divideCompare(size-divideIndex, rightArray);

    compare(divideIndex, leftArray, size-divideIndex, rightArray, array);
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    freopen("inversions.in", "r", stdin);
    freopen("inversions.out", "w", stdout);

    long long amount;
    cin >> amount;

    vector<long long> array(amount);

    for (long int i = 0; i < amount; i++)
    {
        cin >> array[i];
    }

    divideCompare(amount, array);

    cout << inversionsCount;
    return 0;
}
