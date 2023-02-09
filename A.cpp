#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::queue;
using std::vector;

int n;
int m;
int a;
int b;
int u;
int v;

vector<int> dist, parent;

vector<vector<int> > g;

void Bfs(int start) {
  parent = vector<int>(n + 1, -1);
  dist = vector<int>(n + 1, -1);
  dist[start] = 0;
  queue<int> q;
  q.push(start);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < int(g[v].size()); i++) {
      int to = g[v][i];
      if (dist[to] == -1) {
        q.push(to);
        dist[to] = dist[v] + 1;
        parent[to] = v;
      }
    }
  }
}

int main(void) {
  cin >> n >> m;
  cin >> a >> b;
  g.resize(n + 1);
  for (int j = 0; j < m; ++j) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  Bfs(a);
  if (parent[b] == -1) {
    if (dist[b] == 0) {
      cout << "0\n" << b;
    } else {
      cout << "-1\n";
    }
  } else {
    cout << dist[b] << '\n';
    vector<int> path(1, b);
    while (parent[b] != -1) {
      b = parent[b];
      path.push_back(b);
    }
    for (int i = int(path.size() - 1); i >= 0; i--) {
      cout << path[i] << " ";
    }
  }
  return 0;
}