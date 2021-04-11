//
//  main.cpp
//  Lab8
//
//  Created by Георгий Круглов on 11.02.2021.
//

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, const char * argv[]) {
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n;
    
    cin >> n;
    
    vector<vector<int>> array;
    array.resize(n);
    for (int i = 0; i < n; i++) { array[i].resize(n); }
        
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { cin >> array[i][j]; }
    }
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i; j < n; j++) {
            if (array[i][j] != array[j][i] || (i == j && array[i][j] != 0)) {
                cout << "NO";
                exit(0);
            }
        }
    }
    
    cout << "YES";
    
    return 0;
}
