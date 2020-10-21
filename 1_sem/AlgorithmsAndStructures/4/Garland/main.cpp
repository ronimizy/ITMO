#include <iostream>
#include <vector>

using namespace std;

int main()
{
    freopen("garland.in", "r", stdin);
    freopen("garland.out", "w", stdout);

    int n;
    double A;
    cin >> n >> A;
    vector<double> array(n);
    array[0] = A;

    double left = 0, right = A;

    while (right - left > 0.00000001)
    {
        array[1] = (left + right) / 2;
        bool _ = true;

        for (int i = 2; i < array.size(); i++)
        {
            array[i] = 2 * array[i - 1] + 2 - array[i-2];
            if (array[i] < 0)
            {
                _ = false;
                break;
            }
        }
        _ ? right = array[1] : left = array[1];
    }

    printf("%.2lf", array.back());

    return 0;
}
