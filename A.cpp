
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
  virtual vector<T1> RetS(T1 a) = 0;
  virtual void SetV() = 0;
  virtual void SetWay(T1 a, T2 b) = 0;

  virtual int Stat() = 0;
  virtual int Fin() = 0;
};

template <typename T1, typename T2, typename K>
class CraphOnMatrix : public Graph<T1, T2, K> {
public:
  CraphOnMatrix(int ko, int reb);
  int RetV();
  vector<T1> RetS(T1 a);
  void SetV();
  void SetWay(T1 a, T2 b);
  int Stat() { return start; }
  int Fin() { return finish; }

  class OnIter {
    //std::iterator<std::input_iterator_tag>
  public:
    int* sp = nullptr;
    int* fp = nullptr;
    OnIter(int* a, int* b) {
      sp = a;
      fp = b;
    }
    class Iterator {
    public:
      int* p = nullptr;
      int v = 0;
      int pos = 0;
      Iterator() : p(nullptr) {}
      Iterator(int* pp) {
        p = pp;
      }
      Iterator(const Iterator& st) {
        p = st.p;
        pos = st.pos;
        v = st.v;
      }
      Iterator& operator++() {
        for (int i = 0; *p != -1; ++pos, ++i) {
          if (*p == 1 and i > 0) {
            break;
          }
          else {
            p = (p + 1);
          }
        }
        return *this;
      }
      int& operator*() { return pos; }
      Iterator& operator--() {
        for (int i = 0; pos >= 0; --pos, ++i) {
          if (*p == 1 and i > 0) {
            break;
          }
          else {
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
      Iterator& operator=(const Iterator& other) {
        p = other.p;
        pos = other.pos;
        v = other.v;
        return *this;
      }
    };
    Iterator begin() {
      Iterator temp(sp);
      if (*sp == 0) {
        ++temp;
      }
      return temp;
    }
    Iterator end() {
      return Iterator(fp);
    }
  };
  OnIter RangeB(T1 ver) {
    return OnIter(&g[ver][0], &g[ver][g[ver].size() - 1]);
  }
private:
  int kolvo = 0;
  int reb = 0;
  T1 start;
  T2 finish;
  int u;
  int v;
  vector<T1> dist, parent;
  vector<vector<T1>> g;
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
  for (int i = 0; i <= kolvo; ++i) {
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
  void SetWay(T1 a, T2 b);
  int Stat() { return start; }
  int Fin() { return finish; }
  class OnIter {
    //std::iterator<std::input_iterator_tag>
  public:
    int* sp = nullptr;
    int* fp = nullptr;
    OnIter(int* a, int* b) {
      sp = a;
      fp = b;
    }
    class Iterator {
    public:
      int* p = nullptr;
      int v = 0;
      int pos = 0;
      Iterator() : p(nullptr) {}
      Iterator(int* pp) {
        p = pp;
      }
      Iterator(const Iterator& st) {
        p = st.p;
        pos = st.pos;
        v = st.v;
      }
      Iterator& operator++() {
        if (*p != -1) {
          p = (p + 1);
          pos++;
        }
        return *this;
      }
      int& operator*() { return *p; }
      Iterator& operator--() {
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
      Iterator& operator=(const Iterator& other) {
        p = other.p;
        pos = other.pos;
        v = other.v;
        return *this;
      }
    };
    Iterator begin() {
      Iterator temp(sp);
      if (*sp == 0) {
        ++temp;
      }
      return temp;
    }
    Iterator end() {
      return Iterator(fp);
    }
  };
  OnIter RangeB(T1 ver) {
    return OnIter(&g[ver][0], &g[ver][g[ver].size() - 1]);
  }
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
};

template <typename T1, typename T2, typename K>
vector<T1> CraphOnVector<T1, T2, K>::RetS(T1 a) {
  return g[a];
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
  virtual void Pvisit(int v, int to) = 0;
  virtual void Dvisit(int v, int to) = 0;
  virtual int Retperent(int v) = 0;
  virtual int Retdist(int v) = 0;
};

class HolVisitor : public Visitor {
private:
  vector<int> dist;
  vector<int> perent;

public:
  HolVisitor(int kolvo);
  void Pvisit(int v, int to) override;
  void Dvisit(int v, int to) override;
  int Retperent(int v) override;
  int Retdist(int v) override;
};

void HolVisitor::Dvisit(int v, int to) { dist[to] = v; }

int HolVisitor::Retdist(int v) { return dist[v]; }

int HolVisitor::Retperent(int v) { return perent[v]; }

HolVisitor::HolVisitor(int kolvo) {
  perent.resize(kolvo + 1, -1);
  dist.resize(kolvo + 1, -1);
}

void HolVisitor::Pvisit(int v, int to) { perent[to] = v; }

// дополнение к бфс
vector<int> Rez(Visitor* vis, int finish) {
  if (vis->Retperent(finish) == -1) {
    if (vis->Retdist(finish) == 0) {
      vector<int> path(1, finish);
      cout << "0\n";
      return path;
    }
    else {
      vector<int> path(1, -1);
      return path;
    }
  }
  cout << vis->Retdist(finish) << '\n';
  vector<int> path(1, finish);
  while (vis->Retperent(finish) != -1) {
    finish = vis->Retperent(finish);
    path.push_back(finish);
  }
  return path;
}
// вот БФС со всеми введениями, почему CraphOnVector, ну у меня там класс
// итератора, begin и end до них ни как не достучатся от Craph
vector<int> Bfs(Visitor* vis, CraphOnVector<int, int, int>& st) {
  // из дефолта, сказали как нибудь
  vis->Dvisit(0, st.Stat());
  queue<int> q;
  q.push(st.Stat());
  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (auto it : st.RangeB(v)) {
      if (vis->Retdist(it) == -1) {
        q.push(it);
        vis->Dvisit(vis->Retdist(v) + 1, it);
        vis->Pvisit(v, it);
      }
    }
  }
/*
*   Хитро?
    for (auto iter : st.RetS(v)) {
      iter = 10; // но это будет не работать
    }
*/
  return Rez(vis, st.Fin());
}

int main() {
  int n;
  int m;
  int a;
  int b;
  cin >> n >> m;
  cin >> a >> b;
  // Graph<int, int, int> *B = nullptr;
  // CraphOnVector<int, int, int> A(n, m);
  // B = &A;
  // B->SetWay(a, b);
  // B->SetV();
  // B->BFS(a);
  // B->Rez();
  // A.SetWay(a, b);
  // 
  // Visitor *v;
  // HolVisitor hv(n);
  // v = &hv;
  // vector<int> path = Bfs(v, A);
  // for (int i = int(path.size() - 1); i >= 0; i--) {
  //   cout << path[i] << " ";
  // }
// Матрица работате
/*
  CraphOnMatrix<int, int, int> A(n, m);
  A.SetWay(a, b);
  A.SetV();
  for (auto itt : A.RangeB(1)) {
    cout << itt;
  }
*/
// Список работате
/*
  CraphOnVector<int, int, int> A(n, m);
  A.SetWay(a, b);
  A.SetV();
  for (auto itt : A.RangeB(1)) {
    cout << itt;
  }
*/
  return 0;
}

/*
* P.S
  знаю, много говна и не правильно, но я не понял ревью и не кодил год
*/

