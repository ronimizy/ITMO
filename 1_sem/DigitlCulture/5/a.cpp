#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int INF = 1e9;
vector<vector<int> > graph;
vector<pair<int, int> > deg; /// {Степень вершины, номер вершины}
vector<int> color; /// Посещена вершина или нет
vector<int> pr; /// Предыдущая вершина в обходе в ширину
vector<vector<int> > dist;

int dfs(int v, int cnt) { /// Поиск наибольшей компоненты связности исходного графа
    color[v] = 1;
    for (int i = 0; i < graph[v].size(); i++) {
        int to = graph[v][i];
        if (!color[to]) {
            return dfs(to, cnt + 1);
        }
    }
    return cnt;
}

void bfs(int v) { /// Расчёт расстояний от вершины v до остальных вершин из той же компоненты связности
    queue<int> q;
    q.push(v);
    dist[v][v] = 0;
    pr[v] = -1;
    while (!q.empty()) {
        int vv = q.front();
        q.pop();
        for (int i = 0; i < graph[vv].size(); i++) {
            int to = graph[vv][i];
            if (dist[v][to] > dist[v][vv] + 1) {
                dist[v][to] = dist[v][vv] + 1;
            }
        }
    }
    pr[to] = vv;
    q.push(to);
}

void find_way(int a, int b) { /// Восстановление пути от вершины а до b
    pr.clear();
    pr.resize(1000);
    dist.clear();
    dist.resize(1000, vector<int>(1000, INF));
    bfs(a);
    cout << dist[a][b] << '\n'; /// Расстояние между а и b
    while (b != -1) {
        cout << b << ' ';
        b = pr[b];
    }
    cout << '\n';
    return;
}

int NOTmain() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int a;
    int cntEdges = 0; /// Число рёбер
    graph.resize(1000);
    pr.resize(1000);
    for (int i = 0; i < 1000; i++) {
        deg.push_back({0, i});
    }
    while (cin >> a) {
        int b;
        cin >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
        deg[a].first++;
        deg[b].first++;
        cntEdges++;
    }
    cout << cntEdges << '\n';
    vector<int> leaf; /// Изолированные вершины
    sort(deg.begin(), deg.end());
    for (int i = 0; i < 1000; i++) {
        if (deg[i].first == 0) {
            leaf.push_back(deg[i].second);
        }
    }
    sort(leaf.begin(), leaf.end());
    cout << leaf.size() << '\n'; /// Число изолированных вершин
    for (auto &i : leaf) {
        cout << i << ' '; /// Вывод изолированных вершин }
        cout << '\n';
        vector<int> maxx; /// Вершины с наибольшей степенью
        for (int i = 999; i >= 0; i--) {
            if (deg[i].first == deg[999].first) {
                maxx.push_back(deg[i].second);
            }
            cout << deg[999].first << '\n'; /// Наибольшая степень вершины
            sort(maxx.begin(), maxx.end());
            for (auto &i : maxx) {
                cout << i << ' '; /// Вывод вершин с наибольшей степенью
            }
            cout << '\n';
/////////////////////////////////////
            color.resize(1000);
            int mx = 0;
            int v = -1;
            for (int i = 0; i < 1000; i++) { /// Разбитие на компоненты связности и поиск наибольшей
                if (!color[i]) {
                    int cnt = dfs(i, 0);
                    if (cnt > mx) {
                        v = i;
                        mx = cnt;
                    }
                }
            }
            color.clear();
            color.resize(1000);
            dist.resize(1000, vector<int>(1000, INF));

            for (int i = 0; i < 1000; i++) {
                bfs(i); /// Расчёт расстояний от каждой вершины до каждой из той же компоненты связности, до вершин издругих компонент по умолчанию INF
            }
            int diameter = -1; /// Диаметр графа
            int vv;
            for (int i = 0; i < 1000; i++) {
                for (int j = 0; j < 1000; j++) {
                    if (dist[i][j] == INF) {
                        dist[i][j] = -INF;
                    }
                    if (dist[i][j] > diameter) {
                        diameter = dist[i][j];
                        v = i; /// Один конец самого длинного кратчайшего пути графа
                        vv = j; /// Другой конец
                    }
                }
            }
            find_way(v, vv); /// Восстановление наидлиннейшего пути графа find_way(395, 800); ///
            find_way(464,
                     find_way(384,
                              cout << '\n';
            set<int> del;
            del.insert(217);
            del.insert(203);
            del.insert(749);
            del.insert(398);
            del.insert(927);
            del.insert(377);
            del.insert(799);
            for (int i = 0; i < 1000; i++) {
                for (int j = 0; j < graph[i].size(); j++) {
                    auto it = del.find(graph[i][j]);
                    int to = graph[i][j];
                    if (to % 17 == 0 || it != del.end()) {
                        graph[i].erase(graph[i].begin() + j, graph[i].begin() + j + 1); /// Удаление вершин
                        graph[to].clear(); ///
                        j--;
                    }
                    778); /// Пути между вершинами 682); ///
                }
            }
/// Удалённые вершины
/// Пересчёт всех значений
            cntEdges = 0;
            deg.clear();
            for (int i = 0; i < 1000; i++) {
                deg.push_back({0, i});
            }
            for (int i = 0; i < 1000; i++) {
                cntEdges += graph[i].size();
                deg[i].first = graph[i].size();
            }
            cout << cntEdges / 2 << '\n';
            leaf.clear();
            sort(deg.begin(), deg.end());
            for (int i = 0; i < 1000; i++) {
                auto it = del.find(deg[i].second);
                if (deg[i].first == 0 && it == del.end() && deg[i].second % 17 != 0) {
                    leaf.push_back(deg[i].second);
                }
            }

            sort(leaf.begin(), leaf.end());
            cout << leaf.size() << '\n';
            for (auto &i : leaf) {
                cout << i << ' ';
            }
            cout << '\n';
            maxx.clear();
            for (int i = 999; i >= 0; i--) {
                if (deg[i].first == deg[999].first) {
                    maxx.push_back(deg[i].second);
                }
            }
            cout << deg[999].first << '\n';
            sort(maxx.begin(), maxx.end());
            for (auto &i : maxx) {
                cout << i << ' ';
            }
            cout << '\n';
            color.resize(1000);
            mx = 0;
            v = -1;
            for (int i = 0; i < 1000; i++) {
                if (!color[i]) {
                    int cnt = dfs(i, 0);
                    if (cnt > mx) {
                        v = i;
                        mx = cnt;
                    }
                }
            }
            color.clear();
            color.resize(1000);
            dist.resize(1000, vector<int>(1000, INF));
            for (int i = 0; i < 1000; i++) {
                bfs(i);
            }
            diameter = -1;
            vv = -1;
            for (int i = 0; i < 1000; i++) {
                for (int j = 0; j < 1000; j++) {
                    if (dist[i][j] == INF) {
                        dist[i][j] = -INF;
                    }
                    if (dist[i][j] > diameter) {
                        diameter = dist[i][j];
                        v = i;
                        vv = j;
                    }
                }
            }
            find_way(v, vv);
            find_way(395, 800);
            find_way(464, 778);
            find_way(384, 682);
        }