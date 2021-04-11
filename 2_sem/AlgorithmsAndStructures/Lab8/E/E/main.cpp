//
//  main.cpp
//  E
//
//  Created by Георгий Круглов on 11.02.2021.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct Node {
    vector<int> connected = {};
    unsigned int distance = -1;
    
    bool seen = false;
};

int main(int argc, const char * argv[]) {
    freopen("pathbge1.in", "r", stdin);
    freopen("pathbge1.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    
    vector<Node> graph;
    graph.resize(n, Node());
    
    for (int i = 0; i < m; i++) {
        int begin, end;
        cin >> begin >> end;
        begin--; end--;
        
        graph[begin].connected.push_back(end);
        graph[end].connected.push_back(begin);
    }
    
    graph[0].distance = 0;
    
    queue<int> q;
    q.push(0);
    
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        
        if (!graph[i].seen) {
            graph[i].seen = true;
            for (auto &k : graph[i].connected) {
                graph[k].distance = fmin(graph[k].distance, graph[i].distance + 1);
                q.push(k);
            }
        }
    }
    
    for (auto &i : graph) {
        cout << i.distance << ' ';
    }
    
    return 0;
}
