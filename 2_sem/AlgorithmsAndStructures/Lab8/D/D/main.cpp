//
//  main.cpp
//  D
//
//  Created by Георгий Круглов on 11.02.2021.
//

#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    vector<int> connected = {};
    int component = 0;
    
    
    enum COLOR {
        white = 0, gray, black
    };
    
    COLOR color = white;
};

void Visit(int &g, vector<Node> &graph, int &count) {
    graph[g].color = Node::gray;
    
    for (auto &i : graph[g].connected) {
        if (graph[i].color == Node::white) {
            Visit(i, graph, count);
        }
    }
    
    graph[g].color = Node::black;
    graph[g].component = count;
}


int main(int argc, const char * argv[]) {
    freopen("components.in", "r", stdin);
    freopen("components.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    
    vector<Node> array;
    array.resize(n, Node());
    int count = 0;
    
    for (int i = 0; i < m; i++) {
        int node, connected;
        cin >> node >> connected;
        
        array[node-1].connected.push_back(connected-1);
        array[connected-1].connected.push_back(node-1);
    }
    
    for (int i = 0; i < n; i++) {
        if (array[i].color == Node::white) {
            count++;
            Visit(i, array, count);
        }
    }
    
    cout << count << '\n';
    for (auto &i : array) {
        cout << i.component << ' ';
    }
    
    return 0;
}
