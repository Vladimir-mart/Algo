#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::queue;
using std::vector;

template <typename T1, typename T2, typename K> class Graph {
public:
  virtual int RetV() = 0;
  virtual vector<T1> RetS(T1) = 0;
  virtual void SetV() = 0;
  virtual void SetWay(T1, T2) = 0;
  virtual int stat() = 0;
  virtual int fin() = 0;
};

template <typename T1, typename T2, typename K>
class CraphOnMatrix : public Graph<T1, T2, K> {
public:
  CraphOnMatrix(int ko, int reb);
  int RetV();
  vector<T1> RetS(T1 a);
  void SetV();
  void SetWay(T1, T2);
  void BFS(T1);
  void Rez();
  int stat() { return start; }
  int fin() { return finish; }

private:
  int kolvo = 0;
  int reb = 0;
  T1 start;
  T2 finish;
  int u;
  int v;
  vector<T1> dist, parent;
  vector<vector<T1>> g;
  template <typename T> class Iterator {
  public:
    int *p = nullptr;
    vector<vector<T1>> ggg;
    int v = 0;
    int pos = 0;
    Iterator() : p(nullptr) {}
    Iterator(const Iterator &st) {
      p = st.p;
      ggg = st.ggg;
      pos = st.pos;
      v = st.v;
    }
    explicit Iterator(T t, T poz, vector<vector<T1>> &gg) {
      p = &gg[t][poz];
      ggg = gg;
      pos = poz;
      v = t;
    }
    Iterator &operator++() {
      for (int i = 0; pos < ggg[v].size(); ++pos, ++i) {
        if (*p == -1) {
          break;
        }
        if (*p == 1 and i > 0) {
          break;
        } else {
          p = (p + 1);
        }
      }
      return *this;
    }
    int &operator*() { return pos; }
    Iterator &operator--() {
      for (int i = 0; pos >= 0; --pos, ++i) {
        if (*p == 1 and i > 0) {
          break;
        } else {
          p = (p - 1);
        }
      }
      return *this;
    }
    friend bool operator==(Iterator first, Iterator second) {
      return first.p == second.p;
    }
    friend bool operator!=(Iterator first, Iterator second) {
      return !(first == second);
    }
    Iterator &operator=(const Iterator &other) {
      p = other.p;
      pos = other.pos;
      ggg = other.ggg;
      v = other.v;
      return *this;
    }
  };

public:
  Iterator<T1> begin(T1 t) {
    Iterator<T1> temp(t, 0, g);
    return ++temp;
  }
  Iterator<T1> end(T1 t) { return Iterator<T1>(t, g[t].size() - 1, g); }
};

template <typename T1, typename T2, typename K>
vector<T1> CraphOnMatrix<T1, T2, K>::RetS(T1 a) {
  return g[a];
}

template <typename T1, typename T2, typename K>
void CraphOnMatrix<T1, T2, K>::SetV() {
  g.resize(kolvo + 1);
  for (int i = 0; i <= kolvo; ++i) {
    g[i].resize(kolvo + 1);
  }
  for (int j = 0; j < reb; ++j) {
    cin >> u >> v;
    g[u][v] = 1;
    g[v][u] = 1;
  }
  for (int i = 0; i < kolvo; ++i) {
    g[i].push_back(-1);
  }
}

template <typename T1, typename T2, typename K>
void CraphOnMatrix<T1, T2, K>::SetWay(T1 a, T2 b) {
  this->start = a;
  this->finish = b;
}

template <typename T1, typename T2, typename K>
CraphOnMatrix<T1, T2, K>::CraphOnMatrix(int ko, int reb) {
  this->kolvo = ko;
  this->reb = reb;
}

template <typename T1, typename T2, typename K>
int CraphOnMatrix<T1, T2, K>::RetV() {
  return kolvo;
}

template <typename T1, typename T2, typename K>
class CraphOnVector : public Graph<T1, T2, K> {
  // я не добавлял map к различным типам
public:
  CraphOnVector(int ko, int reb);
  int RetV();
  vector<T1> RetS(T1 a);
  void SetV();
  void SetWay(T1, T2);
  void BFS(T1);
  void Rez();
  int stat() { return start; }
  int fin() { return finish; }

private:
  int kolvo = 0;
  int reb = 0;
  T1 start;
  T2 finish;
  int u;
  int v;
  vector<T1> dist, parent;
  vector<vector<T1>> g;
  // зачем я это делал,? - не знаю
  template <typename T> class Iterator {
  public:
    int *p = nullptr;
    vector<vector<T1>> ggg;
    int v = 0;
    int pos = 0;
    Iterator() : p(nullptr) {}
    Iterator(const Iterator &st) : p(st.p) {}
    explicit Iterator(T t, T poz, vector<vector<T1>> &gg) {
      p = &gg[t][poz];
      ggg = gg;
      pos = poz;
      v = t;
    }
    Iterator &operator++() {
      if (ggg[v].size() > pos) {
        p = (p + 1);
        pos++;
      }
      return *this;
    }
    int &operator*() { return *p; }
    Iterator &operator--() {
      if (pos >= 0) {
        p = (p - 1);
        pos--;
      }
      return *this;
    }
    friend bool operator==(Iterator first, Iterator second) {
      return first.p == second.p;
    }
    friend bool operator!=(Iterator first, Iterator second) {
      return !(first == second);
    }
    Iterator &operator=(const Iterator &other) {
      p = other.p;
      pos = other.pos;
      ggg = other.ggg;
      v = other.v;
      return *this;
    }
  };

public:
  Iterator<T1> begin(T1 t) { return Iterator<T1>(t, 0, g); }
  Iterator<T1> end(T1 t) { return Iterator<T1>(t, g[t].size() - 1, g); }
};

template <typename T1, typename T2, typename K>
vector<T1> CraphOnVector<T1, T2, K>::RetS(T1 a) {
  return g[a];
}

// это не нужный рез, смотрите 335
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

// это не нужный бфс, смотрите 356
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
  for (int i = 0; i <= kolvo; ++i) {
    g[i].push_back(-1);
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

class Visitor {
public:
  virtual void visitP(int v, int to) = 0;
  virtual void visitD(int v, int to) = 0;
  virtual int Retperent(int v) = 0;
  virtual int Retdist(int v) = 0;
};

class HolVisitor : public Visitor {
private:
  vector<int> dist;
  vector<int> perent;

public:
  HolVisitor(int kolvo);
  void visitP(int v, int to) override;
  void visitD(int v, int to) override;
  int Retperent(int v) override;
  int Retdist(int v) override;
};

void HolVisitor::visitD(int v, int to) { dist[to] = v; }

int HolVisitor::Retdist(int v) { return dist[v]; }

int HolVisitor::Retperent(int v) { return perent[v]; }

HolVisitor::HolVisitor(int kolvo) {
  perent.resize(kolvo + 1, -1);
  dist.resize(kolvo + 1, -1);
}

void HolVisitor::visitP(int v, int to) { perent[to] = v; }

// дополнение к бфс
vector<int> Rez(Visitor *vis, int finish) {
  if (vis->Retperent(finish) == -1) {
    if (vis->Retdist(finish) == 0) {
      cout << "0\n" << finish;
    } else {
      vector<int> path(1, -1);
      return path;
      cout << "-1\n";
    }
  } else {
    cout << vis->Retdist(finish) << '\n';
    vector<int> path(1, finish);
    while (vis->Retperent(finish) != -1) {
      finish = vis->Retperent(finish);
      path.push_back(finish);
    }
    return path;
  }
}
// вот БФС со всеми введениями, почему CraphOnVector, ну у меня там класс
// итератора, begin и end до них ни как не достучатся от Craph
vector<int> Bfs(Visitor *vis, CraphOnVector<int, int, int> &st) {
  // из дефолта, сказали как нибудь
  vis->visitD(0, st.stat());
  queue<int> q;
  q.push(st.stat());
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    // знаю, что в векторе есть итератор, но я захотел так, если надо могу
    // переписать(ни надо /\)
    for (auto it = st.begin(v); it != st.end(v); ++it) {
      if (vis->Retdist(*it) == -1) {
        q.push(*it);
        vis->visitD(vis->Retdist(v) + 1, *it);
        vis->visitP(v, *it);
      }
    }
  }
  return Rez(vis, st.fin());
}

int main() {
  int n;
  int m;
  int a;
  int b;
  cin >> n >> m;
  cin >> a >> b;
  Graph<int, int, int> *B = nullptr;
  CraphOnVector<int, int, int> A(n, m);
  A.SetWay(a, b);
  A.SetV();
  Visitor *v;
  HolVisitor hv(n);
  v = &hv;
  vector<int> path = Bfs(v, A);
  for (int i = int(path.size() - 1); i >= 0; i--) {
    cout << path[i] << " ";
  }

  return 0;
}

/*
* P.S
  знаю, много говна и не правильно, но я не понял ревью и не кодил год
*/
