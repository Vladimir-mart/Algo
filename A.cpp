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
class GraphOnMatrix : public Graph<T1, T2, K> {
public:
  GraphOnMatrix(int ko, int reb);
  int RetV();
  vector<T1> RetS(T1 a);
  void SetV();
  void SetWay(T1 a, T2 b);
  int Stat() { return start; }
  int Fin() { return finish; }

  class OnIter {
  public:
    int* sp = nullptr;
    int* fp = nullptr;
    OnIter(int* a, int* b);
    class Iterator {
    public:
      Iterator() : p(nullptr) {}
      Iterator(int* pp) { p = pp; }
      Iterator(const Iterator& st) : p(st.p), pos(st.pos), v(st.pos) {}
      Iterator& operator++();
      int& operator*();
      Iterator& operator--();
      Iterator& operator=(const Iterator& other);
      friend bool operator==(Iterator first, Iterator second);
      friend bool operator!=(Iterator first, Iterator second);
    private:
      int* p = nullptr;
      int v = 0;
      int pos = 0;
    };
    Iterator begin();
    Iterator end() { return Iterator(fp); }
  };
  OnIter RangeB(T1 ver);

private:
  int kolvo = 0;
  int reb = 0;
  T1 start = 0;
  T2 finish = 0;
  int t_from = 0;
  int t_to = 0;
  vector<T1> dist, parent;
  vector<vector<T1>> g;
};



template <typename T1, typename T2, typename K>
bool operator!=(typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator first, typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator second) {
  return !(first == second);
}


template <typename T1, typename T2, typename K>
bool operator==(typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator first, typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator second) {
  return first.p == second.p;
}

template <typename T1, typename T2, typename K>
typename GraphOnMatrix<T1, T2, K>::OnIter GraphOnMatrix<T1, T2, K>::RangeB(T1 ver) {
  return OnIter(&g[ver][0], &g[ver][g[ver].size() - 1]);
}

template <typename T1, typename T2, typename K>
typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator GraphOnMatrix<T1, T2, K>::OnIter::begin() {
  Iterator temp(sp);
  if (*sp == 0) {
    ++temp;
  }
  return temp;
}

template <typename T1, typename T2, typename K>
GraphOnMatrix<T1, T2, K>::OnIter::OnIter(int* a, int* b) {
  sp = a;
  fp = b;
}

template <typename T1, typename T2, typename K>
typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator&
GraphOnMatrix<T1, T2, K>::OnIter::Iterator::operator=(const Iterator& other) {
  p = other.p;
  pos = other.pos;
  v = other.v;
  return *this;
}

template <typename T1, typename T2, typename K>
typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator&
GraphOnMatrix<T1, T2, K>::OnIter::Iterator::operator--() {
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

template <typename T1, typename T2, typename K>
int& GraphOnMatrix<T1, T2, K>::OnIter::Iterator::operator*() {
  return pos;
}

template <typename T1, typename T2, typename K>
typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator&
GraphOnMatrix<T1, T2, K>::OnIter::Iterator::operator++() {
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

template <typename T1, typename T2, typename K>
vector<T1> GraphOnMatrix<T1, T2, K>::RetS(T1 a) {
  return g[a];
}

template <typename T1, typename T2, typename K>
void GraphOnMatrix<T1, T2, K>::SetV() {
  g.resize(kolvo + 1);
  for (int i = 0; i <= kolvo; ++i) {
    g[i].resize(kolvo + 1);
  }
  for (int j = 0; j < reb; ++j) {
    cin >> t_from >> t_to;
    g[t_from][t_to] = 1;
    g[t_to][t_from] = 1;
  }
  for (int i = 0; i <= kolvo; ++i) {
    g[i].push_back(-1);
  }
}

template <typename T1, typename T2, typename K>
void GraphOnMatrix<T1, T2, K>::SetWay(T1 a, T2 b) {
  this->start = a;
  this->finish = b;
}

template <typename T1, typename T2, typename K>
GraphOnMatrix<T1, T2, K>::GraphOnMatrix(int ko, int reb) {
  this->kolvo = ko;
  this->reb = reb;
}

template <typename T1, typename T2, typename K>
int GraphOnMatrix<T1, T2, K>::RetV() {
  return kolvo;
}

template <typename T1, typename T2, typename K>
class GraphOnVector : public Graph<T1, T2, K> {
public:
  GraphOnVector(int ko, int reb);
  int RetV();
  vector<T1> RetS(T1 a);
  void SetV();
  void SetWay(T1 a, T2 b);
  int Stat() { return start; }
  int Fin() { return finish; }
  class OnIter {
  public:
    int* sp = nullptr;
    int* fp = nullptr;
    OnIter(int* a, int* b);
    class Iterator {
    public:
      int* p = nullptr;
      int v = 0;
      int pos = 0;
      Iterator() : p(nullptr) {}
      Iterator(int* pp) { p = pp; }
      Iterator(const Iterator& st);
      Iterator& operator++();
      int& operator*() { return *p; }
      Iterator& operator--();
      friend bool operator==(Iterator first, Iterator second) {
        return first.p == second.p;
      }
      friend bool operator!=(Iterator first, Iterator second) {
        return !(first == second);
      }
      Iterator& operator=(const Iterator& other);
    };
    Iterator begin();
    Iterator end() { return Iterator(fp); }
  };
  OnIter RangeB(T1 ver) {
    return OnIter(&g[ver][0], &g[ver][g[ver].size() - 1]);
  }

private:
  int kolvo = 0;
  int reb = 0;
  T1 start = 0;
  T2 finish = 0;
  int t_from = 0;
  int t_to = 0;
  vector<T1> dist, parent;
  vector<vector<T1>> g;
};

template <typename T1, typename T2, typename K>
typename GraphOnVector<T1, T2, K>::OnIter::Iterator GraphOnVector<T1, T2, K>::OnIter::begin() {
  Iterator temp(sp);
  if (*sp == 0) {
    ++temp;
  }
  return temp;
}

template <typename T1, typename T2, typename K>
typename GraphOnVector<T1, T2, K>::OnIter::Iterator& GraphOnVector<T1, T2, K>::OnIter::Iterator::operator=(const typename GraphOnVector<T1, T2, K>::OnIter::Iterator& other) {
  p = other.p;
  pos = other.pos;
  v = other.v;
  return *this;
}

template <typename T1, typename T2, typename K>
typename GraphOnVector<T1, T2, K>::OnIter::Iterator& GraphOnVector<T1, T2, K>::OnIter::Iterator::operator--() {
  if (pos >= 0) {
    p = (p - 1);
    pos--;
  }
  return *this;
}

template <typename T1, typename T2, typename K>
typename GraphOnVector<T1, T2, K>::OnIter::Iterator& GraphOnVector<T1, T2, K>::OnIter::Iterator::operator++() {
  if (*p != -1) {
    p = (p + 1);
    pos++;
  }
  return *this;
}

template <typename T1, typename T2, typename K>
GraphOnVector<T1, T2, K>::OnIter::Iterator::Iterator(const typename GraphOnVector<T1, T2, K>::OnIter::Iterator& st) {
  p = st.p;
  pos = st.pos;
  v = st.v;
}

template <typename T1, typename T2, typename K>
GraphOnVector<T1, T2, K>::OnIter::OnIter(int* a, int* b) {
  sp = a;
  fp = b;
}

template <typename T1, typename T2, typename K>
vector<T1> GraphOnVector<T1, T2, K>::RetS(T1 a) {
  return g[a];
}

template <typename T1, typename T2, typename K>
void GraphOnVector<T1, T2, K>::SetV() {
  g.resize(kolvo + 1);
  for (int j = 0; j < reb; ++j) {
    cin >> t_from >> t_to;
    g[t_from].push_back(t_to);
    g[t_to].push_back(t_from);
  }
  for (int i = 0; i <= kolvo; ++i) {
    g[i].push_back(-1);
  }
}

template <typename T1, typename T2, typename K>
void GraphOnVector<T1, T2, K>::SetWay(T1 a, T2 b) {
  this->start = a;
  this->finish = b;
}

template <typename T1, typename T2, typename K>
GraphOnVector<T1, T2, K>::GraphOnVector(int ko, int reb) {
  this->kolvo = ko;
  this->reb = reb;
}

template <typename T1, typename T2, typename K>
int GraphOnVector<T1, T2, K>::RetV() {
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
// тут БФС со всем введениями, а так же второй пункт, я сделал без класса, мне так убдобней
// принимает граф и визитор, а возвращать вектор вершин(шаблонных), что лежат на пути.
vector<int> Bfs(Visitor* vis, GraphOnVector<int, int, int>& st) {
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
  GraphOnVector<int, int, int> A(n, m);
  // Graph<int, int, int> *B = nullptr;
  // B = &A;
  // B->SetWay(a, b);
  // B->SetV();
  // B->BFS(a);
  // B->Rez();
  A.SetWay(a, b);
  A.SetV();
  Visitor* v;
  HolVisitor hv(n);
  v = &hv;
  vector<int> path = Bfs(v, A);
  for (int i = int(path.size() - 1); i >= 0; i--) {
    cout << path[i] << " ";
  }
  // Матрица работате
  /*
    GraphOnMatrix<int, int, int> A(n, m);
    A.SetWay(a, b);
    A.SetV();
    for (auto itt : A.RangeB(1)) {
      cout << itt;
    }
  */
  // Список работате
  /*
    GraphOnVector<int, int, int> A(n, m);
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
  знаю, много говна, прошу сильно не бить ♥
*/
