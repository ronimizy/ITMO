#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void mergeBalanced(vector<T> &leftArray, vector<T> &rightArray, vector<T> &resultArray, int key)
{
    int left = 0, right = 0;
    for (int i = 0; i < leftArray.size() + rightArray.size(); ++i)
    {
        if (left < leftArray.size() && right < rightArray.size())
        {
            if (leftArray[left][key] < rightArray[right][key])
            {
                resultArray[i] = leftArray[left];
                left++;
            } else if (leftArray[left][key] > rightArray[right][key])
            {
                resultArray[i] = rightArray[right];
                right++;
            } else
            {
                if (leftArray[left].compare(rightArray[right]) > 0)
                {
                    resultArray[i] = rightArray[right];
                    right++;
                } else
                {
                    resultArray[i] = leftArray[left];
                    left++;
                }
            }
        } else if (left == leftArray.size())
        {
            resultArray[i] = rightArray[right];
            right++;
        } else if (right == rightArray.size())
        {
            resultArray[i] = leftArray[left];
            left++;
        }
    }
}

template<typename T>
void mergeSortBalanced(vector<T> &array, int key)
{
    if (array.size() == 1)
    { return; }

    int divideIndex = array.size() / 2;
    vector<T> leftArray(divideIndex), rightArray(array.size() - divideIndex);
    for (int i = 0; i < divideIndex; ++i)
    {
        leftArray[i] = array[i];
    }
    for (int i = divideIndex; i < array.size(); ++i)
    {
        rightArray[i - divideIndex] = array[i];
    }

    mergeSortBalanced(leftArray, key);
    mergeSortBalanced(rightArray, key);
    mergeBalanced(leftArray, rightArray, array, key);
}

void numbersSort(vector<string> &array, int key)
{
    vector<vector<string>> c(206);
    for (int i = 0; i < array.size(); i++)
    {
        c[(int)array[i][key]].push_back(array[i]);
    }

    int index = 0;
    for (int i = 0; i < 206; i++)
    {
        for (int j = 0; j < c[i].size(); j++)
        {
            array[index] = c[i][j];
            index++;
        }
    }
}

int main()
{
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    freopen("radixsort.in", "r", stdin);
    freopen("radixsort.out", "w", stdout);

    int lineCount, lineLength, phaseCount;
    vector<string> array;

    cin >> lineCount >> lineLength >> phaseCount;

    for (int i = 0; i < lineCount; ++i)
    {
        string a;
        cin >> a;
        array.push_back(a);
    }

    for (int phase = lineLength - 1; phase > lineLength - 1 - phaseCount; phase--)
    {
        //mergeSortBalanced(array, phase);
        numbersSort(array, phase);
    }

    for (int i = 0; i < lineCount; ++i)
    {
        cout << array[i] << endl;
    }

    return 0;
}
