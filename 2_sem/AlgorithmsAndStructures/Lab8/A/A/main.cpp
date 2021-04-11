//
//  main.cpp
//  Lab8
//
//  Created by Георгий Круглов on 11.02.2021.
//

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, m;
    
    cin >> n >> m;
    
    vector<vector<int>> arr;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        arr[i].resize(n, 0);
    }
    
    for (int i = 0; i < m; i++) {
        int s, e;
        
        cin >> s >> e;
        
        arr[s-1][e-1]++;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
    
    return 0;
}
