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
    
    int n, m;
    
    cin >> n >> m;
    
    vector<vector<int>> array;
    array.resize(n);
    for (int i = 0; i < n; i++) { array[i].resize(n); }

    for (int i = 0; i < m; i++) {
        int b, e;
        
        cin >> b >> e;
        b--;
        e--;
        
        if (array[b][e] == 1 || array[e][b] == 1) {
            cout << "YES";
            exit(0);
        }
        
        array[b][e]++;
        array[e][b]++;
    }
    
    cout << "NO";
    
    return 0;
}
