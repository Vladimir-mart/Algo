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
  virtual int RetQuantive() = 0;
  virtual vector<T1> RetAdjacent(T1 ver) = 0;
  virtual void SetV() = 0;
  virtual void SetWay(T1 start, T2 finish) = 0;
  virtual int Start() = 0;
  virtual int Fin() = 0;
};

template <typename T1, typename T2, typename K>
class GraphOnMatrix : public Graph<T1, T2, K> {
public:
  GraphOnMatrix(int ko, int reb);
  int RetQuantive();
  vector<T1> RetAdjacent(T1 ver);
  void SetV();
  void SetWay(T1 start, T2 finish);
  int Start() { return start; }
  int Fin() { return finish; }

  class OnIter {
  public:
    int* fir_point = nullptr;
    int* last_point = nullptr;
    OnIter(int* first, int* last);
    class Iterator {
    public:
      Iterator() : point(nullptr) {}
      Iterator(int* temp_point) { point = temp_point; }
      Iterator(const Iterator& temp_iter) : point(temp_iter.point), pos(temp_iter.pos){}
      Iterator& operator++();
      int& operator*();
      Iterator& operator--();
      Iterator& operator=(const Iterator& other);
      friend bool operator==(Iterator first, Iterator second);
      friend bool operator!=(Iterator first, Iterator second);
    private:
      int* point = nullptr;
      int pos = 0;
    };
    Iterator begin();
    Iterator end() { return Iterator(last_point); }
  };
  OnIter RangeB(T1 ver);

private:
  int quantity_ver = 0;
  int reb = 0;
  T1 start = 0;
  T2 finish = 0;
  int t_from = 0;
  int t_to = 0;
  vector<T1> dist;
  vector<T1> parent;
  vector<vector<T1>> graph_;
};



template <typename T1, typename T2, typename K>
bool operator!=(typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator first, typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator second) {
  return !(first == second);
}


template <typename T1, typename T2, typename K>
bool operator==(typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator first, typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator second) {
  return first.point == second.point;
}

template <typename T1, typename T2, typename K>
typename GraphOnMatrix<T1, T2, K>::OnIter GraphOnMatrix<T1, T2, K>::RangeB(T1 ver) {
  return OnIter(&graph_[ver][0], &graph_[ver][graph_[ver].size() - 1]);
}

template <typename T1, typename T2, typename K>
typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator GraphOnMatrix<T1, T2, K>::OnIter::begin() {
  Iterator temp(fir_point);
  if (*fir_point == 0) {
    ++temp;
  }
  return temp;
}

template <typename T1, typename T2, typename K>
GraphOnMatrix<T1, T2, K>::OnIter::OnIter(int* first, int* last) {
  fir_point = first;
  last_point = last;
}

template <typename T1, typename T2, typename K>
typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator&
GraphOnMatrix<T1, T2, K>::OnIter::Iterator::operator=(const Iterator& other) {
  point = other.point;
  pos = other.pos;
  return *this;
}

template <typename T1, typename T2, typename K>
typename GraphOnMatrix<T1, T2, K>::OnIter::Iterator&
GraphOnMatrix<T1, T2, K>::OnIter::Iterator::operator--() {
  for (int i = 0; pos >= 0; --pos, ++i) {
    if (*point == 1 and i > 0) {
      break;
    }
    else {
      point = (point - 1);
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
  for (int i = 0; *point != -1; ++pos, ++i) {
    if (*point == 1 and i > 0) {
      break;
    }
    else {
      point = (point + 1);
    }
  }
  return *this;
}

template <typename T1, typename T2, typename K>
vector<T1> GraphOnMatrix<T1, T2, K>::RetAdjacent(T1 ver) {
  return graph_[ver];
}

template <typename T1, typename T2, typename K>
void GraphOnMatrix<T1, T2, K>::SetV() {
  graph_.resize(quantity_ver + 1);
  for (int i = 0; i <= quantity_ver; ++i) {
    graph_[i].resize(quantity_ver + 1);
  }
  for (int j = 0; j < reb; ++j) {
    cin >> t_from >> t_to;
    graph_[t_from][t_to] = 1;
    graph_[t_to][t_from] = 1;
  }
  for (int i = 0; i <= quantity_ver; ++i) {
    graph_[i].push_back(-1);
  }
}

template <typename T1, typename T2, typename K>
void GraphOnMatrix<T1, T2, K>::SetWay(T1 start, T2 finish) {
  this->start = start;
  this->finish = finish;
}

template <typename T1, typename T2, typename K>
GraphOnMatrix<T1, T2, K>::GraphOnMatrix(int ko, int reb) {
  this->quantity_ver = ko;
  this->reb = reb;
}

template <typename T1, typename T2, typename K>
int GraphOnMatrix<T1, T2, K>::RetQuantive() {
  return quantity_ver;
}

template <typename T1, typename T2, typename K>
class GraphOnVector : public Graph<T1, T2, K> {
public:
  GraphOnVector(int ko, int reb);
  int RetQuantive();
  vector<T1> RetAdjacent(T1 ver);
  void SetV();
  void SetWay(T1 start, T2 finish);
  int Start() { return start; }
  int Fin() { return finish; }
  class OnIter {
  public:
    int* fir_point = nullptr;
    int* last_point = nullptr;
    OnIter(int* first, int* last);
    class Iterator {
    public:
      int* point = nullptr;
      int pos = 0;
      Iterator() : point(nullptr) {}
      Iterator(int* temp_point) { point = temp_point; }
      Iterator(const Iterator& temp_iter);
      Iterator& operator++();
      int& operator*() { return *point; }
      Iterator& operator--();
      friend bool operator==(Iterator first, Iterator second) {
        return first.point == second.point;
      }
      friend bool operator!=(Iterator first, Iterator second) {
        return !(first == second);
      }
      Iterator& operator=(const Iterator& other);
    };
    Iterator begin();
    Iterator end() { return Iterator(last_point); }
  };
  OnIter RangeB(T1 ver) {
    return OnIter(&graph_[ver][0], &graph_[ver][graph_[ver].size() - 1]);
  }

private:
  int quantity_ver = 0;
  int reb = 0;
  T1 start = 0;
  T2 finish = 0;
  int t_from = 0;
  int t_to = 0;
  vector<T1> dist;
  vector<T1> parent;
  vector<vector<T1>> graph_;
};

template <typename T1, typename T2, typename K>
typename GraphOnVector<T1, T2, K>::OnIter::Iterator GraphOnVector<T1, T2, K>::OnIter::begin() {
  Iterator temp(fir_point);
  if (*fir_point == 0) {
    ++temp;
  }
  return temp;
}

template <typename T1, typename T2, typename K>
typename GraphOnVector<T1, T2, K>::OnIter::Iterator& GraphOnVector<T1, T2, K>::OnIter::Iterator::operator=(const typename GraphOnVector<T1, T2, K>::OnIter::Iterator& other) {
  point = other.point;
  pos = other.pos;
  return *this;
}

template <typename T1, typename T2, typename K>
typename GraphOnVector<T1, T2, K>::OnIter::Iterator& GraphOnVector<T1, T2, K>::OnIter::Iterator::operator--() {
  if (pos >= 0) {
    point = (point - 1);
    pos--;
  }
  return *this;
}

template <typename T1, typename T2, typename K>
typename GraphOnVector<T1, T2, K>::OnIter::Iterator& GraphOnVector<T1, T2, K>::OnIter::Iterator::operator++() {
  if (*point != -1) {
    point = (point + 1);
    pos++;
  }
  return *this;
}

template <typename T1, typename T2, typename K>
GraphOnVector<T1, T2, K>::OnIter::Iterator::Iterator(const typename GraphOnVector<T1, T2, K>::OnIter::Iterator& temp_iter) {
  point = temp_iter.point;
  pos = temp_iter.pos;
}

template <typename T1, typename T2, typename K>
GraphOnVector<T1, T2, K>::OnIter::OnIter(int* first, int* last) {
  fir_point = first;
  last_point = last;
}

template <typename T1, typename T2, typename K>
vector<T1> GraphOnVector<T1, T2, K>::RetAdjacent(T1 ver) {
  return graph_[ver];
}

template <typename T1, typename T2, typename K>
void GraphOnVector<T1, T2, K>::SetV() {
  graph_.resize(quantity_ver + 1);
  for (int j = 0; j < reb; ++j) {
    cin >> t_from >> t_to;
    graph_[t_from].push_back(t_to);
    graph_[t_to].push_back(t_from);
  }
  for (int i = 0; i <= quantity_ver; ++i) {
    graph_[i].push_back(-1);
  }
}

template <typename T1, typename T2, typename K>
void GraphOnVector<T1, T2, K>::SetWay(T1 a, T2 b) {
  this->start = a;
  this->finish = b;
}

template <typename T1, typename T2, typename K>
GraphOnVector<T1, T2, K>::GraphOnVector(int ko, int reb) {
  this->quantity_ver = ko;
  this->reb = reb;
}

template <typename T1, typename T2, typename K>
int GraphOnVector<T1, T2, K>::RetQuantive() {
  return quantity_ver;
}

class Visitor {
public:
  virtual void Pvisit(int vertex, int to) = 0;
  virtual void Dvisit(int dist_on_vertex, int to) = 0;
  virtual int Retperent(int vertex) = 0;
  virtual int Retdist(int vertex) = 0;
};

class HolVisitor : public Visitor {
private:
  vector<int> dist;
  vector<int> perent;
public:
  HolVisitor(int quantity_ver);
  void Pvisit(int vertex, int to) override;
  void Dvisit(int dist_on_vertex, int to) override;
  int Retperent(int vertex) override;
  int Retdist(int vertex) override;
};

void HolVisitor::Dvisit(int dist_on_vertex, int to) { dist[to] = dist_on_vertex; }

int HolVisitor::Retdist(int vertex) { return dist[vertex]; }

int HolVisitor::Retperent(int vertex) { return perent[vertex]; }

HolVisitor::HolVisitor(int quantity_ver) {
  perent.resize(quantity_ver + 1, -1);
  dist.resize(quantity_ver + 1, -1);
}

void HolVisitor::Pvisit(int vertex, int to) { perent[to] = vertex; }

// дополнение к бфс
vector<int> Rez(Visitor* vis, int finish) {
  if (vis->Retperent(finish) == -1) {
    if (vis->Retdist(finish) == 0) {
      vector<int> path(1, finish);
      vis->Dvisit(0,finish);
      return path;
    }
    else {
      vector<int> path(1, -1);
      return path;
    }
  }
  //cout << vis->Retdist(finish)  <<" + "<< finish << '\n';
  vector<int> path(1, finish);
  while (vis->Retperent(finish) != -1) {
    finish = vis->Retperent(finish);
    path.push_back(finish);
  }
  return path;
}
// тут БФС со всем введениями, а так же второй пункт, я сделал без класса, мне так убдобней
// принимает граф и визитор, а возвращать вектор вершин(шаблонных), что лежат на пути.
vector<int> Bfs(Visitor* vis, GraphOnVector<int, int, int>& temp_iter) {
  // из дефолта, сказали как нибудь
  vis->Dvisit(0, temp_iter.Start());
  queue<int> q;
  q.push(temp_iter.Start());
  while (!q.empty()) {
    int vertex = q.front();
    q.pop();

    for (auto it : temp_iter.RangeB(vertex)) {
      if (vis->Retdist(it) == -1) {
        q.push(it);
        vis->Dvisit(vis->Retdist(vertex) + 1, it);
        vis->Pvisit(vertex, it);
      }
    }
  }
  /*
  *   Хитро?
      for (auto iter : temp_iter.RetAdjacent(vertex)) {
        iter = 10; // но это будет не работать
      }
  */
  return Rez(vis, temp_iter.Fin());
}


int main() {
  int vertexes;
  int edges;
  int start;
  int finish;
  cin >> vertexes >> edges;
  cin >> start >> finish;
  GraphOnVector<int, int, int> garph(vertexes, edges);
  // Graph<int, int, int> *B = nullptr;
  // B = &A;
  // B->SetWay(a, b);
  // B->SetV();
  // B->BFS(a);
  // B->Rez();
  garph.SetWay(start, finish);
  garph.SetV();
  Visitor* vertex;
  HolVisitor hv(vertexes);
  vertex = &hv;
  vector<int> path = Bfs(vertex, garph);
  if (path[0] != -1) {
    cout << vertex->Retdist(finish) << '\n';
  }
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
  P.S.S
  вроде стало меньше
*/
