#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::queue;
using std::vector;


template <typename T1, typename T2, typename K>
class Graph {
public:
  virtual int RetV() = 0;
  virtual vector<T1> RetS(T1) = 0;
  virtual void SetV() = 0;
  virtual void SetWay(T1, T2) = 0;
  virtual void BFS(T1) = 0;
  virtual void Rez() = 0;
private:
};

template <typename T1, typename T2, typename K>
class CraphOnVector : public Graph<T1, T2, K> {
public:
  CraphOnVector(int ko, int reb);
  int RetV();
  vector<T1> RetS(T1 a);
  void SetV();
  void SetWay(T1, T2);
  void BFS(T1);
  void Rez();
private:
  int kolvo = 0;
  int reb = 0;
  T1 start;
  T2 finish;
  int u;
  int v;
  vector<int> dist, parent;
  vector<vector<int>> g;
  public:
  // тестовый итератор для списка, для матрицы будет масло мажу маслом
  template <typename T>
  class Iterator : public std::iterator<std::input_iterator_tag, T> {
    int* p = nullptr; 
    int v = 0;
    int pos = 0;
    Iterator() : p(nullptr) {}
    Iterator(const Iterator& st) : p(st.p) {}
    Iterator(T1 t) : p(&g[t][0]), v(t) {}
    Iterator &operator++() {
      if(g[v].size() > pos) {
        *p = *(p+1);
        pos++;
      }
      return *this;
    }
    Iterator &operator--() {
      if(pos >= 0) {
        *p = *(p-1);
        pos--;
      }
      return *this;
    }
    friend bool operator==(Iterator first, Iterator second) {
      return first.it_ == second.it_;
    }
    friend bool operator!=(Iterator first, Iterator second) {
      return !(first == second);
    }
    Iterator &operator=(const Iterator &other) {
      p = other.p;
      return *this;
    }
  };
 public:
  Iterator<T1> begin(int t) {
    return Iterator<T1>(g[t]);
  }
  Iterator<T1> end(int t) {
    return Iterator<T1>(g[t][g[t].size()-1]);
  }
};

template <typename T1, typename T2, typename K>
vector<T1> CraphOnVector<T1, T2, K>::RetS(T1 a) {
  return g[a];
}

template <typename T1, typename T2, typename K>
void CraphOnVector<T1, T2, K>::Rez() {
  if (parent[finish] == -1) {
    if (dist[finish] == 0) {
      cout << "0\n" << finish;
    } else {
      cout << "-1\n";
    }
  } else {
    cout << dist[finish] << '\n';
    vector<int> path(1, finish);
    while (parent[finish] != -1) {
      finish = parent[finish];
      path.push_back(finish);
    }
    for (int i = int(path.size() - 1); i >= 0; i--) {
      cout << path[i] << " ";
    }
  }
}

template <typename T1, typename T2, typename K>
void CraphOnVector<T1, T2, K>::BFS(T1 start) {
  parent = vector<T1>(kolvo + 1, -1);
  dist = vector<T1>(kolvo + 1, -1);
  dist[start] = 0;
  queue<T1> q;
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

template <typename T1, typename T2, typename K>
void CraphOnVector<T1, T2, K>::SetV() {
  g.resize(kolvo + 1);
  for (int j = 0; j < reb; ++j) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
}

template <typename T1, typename T2, typename K>
void CraphOnVector<T1, T2, K>::SetWay(T1 a, T2 b) {
  this->start = a;
  this->finish = b;
}

template <typename T1, typename T2, typename K>
CraphOnVector<T1, T2, K>::CraphOnVector(int ko, int reb) {
  this->kolvo = ko;
  this->reb = reb;
}

template <typename T1, typename T2, typename K>
int CraphOnVector<T1, T2, K>::RetV() {
  return kolvo;
}

int main(void) {
  int n;
  int m;
  int a;
  int b;
  cin >> n >> m;
  cin >> a >> b;
  Graph<int, int, int> *B = nullptr;
  CraphOnVector<int, int, int> A(n, m);
  B = &A;
  B->SetWay(a, b);
  B->SetV();
  B->BFS(a);
  B->Rez();
  A.begin(1);
  return 0;
}