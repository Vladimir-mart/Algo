#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Graph {
public:
  vector<int> tin;
  vector<int> tup;
  vector<vector<int>> adj_list;
  vector<int> data;
  Graph(int n) {
    adj_list.resize(n);
    data.resize(n);
    tin.resize(n);
    tup.resize(n);
  }
};

void DFS(int vertex, Graph& graph, int& timer, int& count, vector<pair<int, int>>& result, int parent = -1) {
  graph.data[vertex] = 1;
  timer++;
  graph.tin[vertex] = timer;
  graph.tup[vertex] = timer;

  for (auto u : graph.adj_list[vertex]) {
    if (u == parent) {
      continue;
    }

    if (graph.data[u] == 1) {
      graph.tup[vertex] = min(graph.tup[vertex], graph.tin[u]);
    } else if (graph.data[u] == 0) {
      DFS(u, graph, timer, count, result, vertex);
      graph.tup[vertex] = min(graph.tup[vertex], graph.tup[u]);

      if (graph.tup[u] > graph.tin[vertex]) {
        int cnt = 0;
        for (auto v : graph.adj_list[vertex]) {
          if (v == u) {
            cnt++;
          }
        }

        if (cnt == 1 && vertex != u) {
          result.emplace_back(make_pair(vertex, u));
          count++;
        }
      }
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;

  Graph graph(n);

  map<pair<int, int>, int> edges;
  vector<pair<int, int>> result;

  for (int i = 0; i < m; i++) {
    int vertex1, vertex2;
    cin >> vertex1 >> vertex2;
    vertex1--;
    vertex2--;
    graph.adj_list[vertex1].push_back(vertex2);
    graph.adj_list[vertex2].push_back(vertex1);
    edges[make_pair(vertex1, vertex2)] = i + 1;
    edges[make_pair(vertex2, vertex1)] = i + 1;
  }

  int timer = 0;
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (graph.data[i] == 0) {
      DFS(i, graph, timer, count, result);
    }
  }

  if (count == 0) {
    cout << count << endl;
  } else {
    cout << count << endl;
    vector<int> res;
    for (auto i : result) {
      res.push_back(edges[i]);
    }

    result.clear();
    sort(res.begin(), res.end());
    for (auto i : res) {
      cout << i << endl;
    }
  }

  return 0;
}
