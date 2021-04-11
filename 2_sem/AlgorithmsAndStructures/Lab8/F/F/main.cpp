//
//  main.cpp
//  F
//
//  Created by Георгий Круглов on 11.02.2021.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

struct Cell {
    enum State {
        available = '.', blocked = '#', start = 'S', end = 'T'
    };
    enum Direction {
        left = 'L', right = 'R', up = 'U', down = 'D', none
    };
    
    State state;
    Direction direction = none;
    int distance = -1;
    pair<int, int> previous = pair<int, int>(-1, -1);
    vector<pair<int, int>> connected = {};
    
    Cell() {}
    Cell(char c) {
        switch (c) {
            case '.':
                state = available;
                break;
                
            case '#':
                state = blocked;
                break;
                
            case 'S':
                state = start;
                break;
                
            case 'T':
                state = end;
                break;
                
            default:
                break;
        }
    }
    
    void operator=(Cell rhs) {
        state = rhs.state;
        direction = rhs.direction;
        connected = rhs.connected;
    };
};

int main(int argc, const char * argv[]) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<Cell>> field;
    field.resize(n);
    for (int i = 0; i < n; i++) { field[i].resize(m, Cell()); }
    
    pair<int, int> start;
    pair<int, int> end;
    
    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;
        
        for (int j = 0; j < m; j++) {
            char c = line[j];
            
            if (c == 'S') {
                start = pair<int, int> (i, j);
            }
            if (c == 'T') {
                end = pair<int, int> (i, j);
            }
            
            field[i][j] = Cell(c);
            
            if (i > 0) { field[i][j].connected.emplace_back(i-1, j); }
            if (j > 0) { field[i][j].connected.emplace_back(i, j-1); }
            if (i < n-1) { field[i][j].connected.emplace_back(i+1, j); }
            if (j < m-1) { field[i][j].connected.emplace_back(i, j+1); }
        }
    }
    

    queue<pair<int, int>> q;
    q.push(start);
    
    while (!q.empty()) {
        auto c = q.front();
        q.pop();
        
        Cell viewed = field[c.first][c.second];
        
        for (auto coordinates : viewed.connected) {
            Cell &cell = field[coordinates.first][coordinates.second];
            
            if (cell.state != Cell::blocked && cell.distance == -1) {
                cell.distance = viewed.distance + 1;
                cell.previous = c;
                
                if (coordinates.first < c.first) {
                    cell.direction = Cell::up;
                } else if (coordinates.first > c.first) {
                    cell.direction = Cell::down;
                } else if (coordinates.second < c.second) {
                    cell.direction = Cell::left;
                } else if (coordinates.second > c.second) {
                    cell.direction = Cell::right;
                }
                
                q.push(coordinates);
            }
        }
    }
    
    string path = "";
    pair<int, int> viewed = end;
    
    while (field[viewed.first][viewed.second].direction != Cell::none && field[viewed.first][viewed.second].state != Cell::start) {
        path += field[viewed.first][viewed.second].direction;
        viewed = field[viewed.first][viewed.second].previous;
    }
    
    reverse(path.begin(), path.end());
    
    if (path.empty()) {
        cout << "-1";
        
        return 0;
    }
    
    cout << path.size() << '\n' << path;
    
    
    return 0;
}
