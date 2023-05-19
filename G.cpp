#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

// все основные измение в классе на сиписке смежности и в визиторе
using std::sort;
using std::map;
using std::min;
using std::pair;
using std::cin;
using std::cout;
using std::queue;
using std::vector;
using std::make_pair;

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
  GraphOnMatrix(int ko, int edge);
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
      Iterator(const Iterator& temp_iter) : point(temp_iter.point), pos(temp_iter.pos) {}
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
  int edge = 0;
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
  for (int j = 0; j < edge; ++j) {
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
GraphOnMatrix<T1, T2, K>::GraphOnMatrix(int ko, int edge) {
  this->quantity_ver = ko;
  this->edge = edge;
}

template <typename T1, typename T2, typename K>
int GraphOnMatrix<T1, T2, K>::RetQuantive() {
  return quantity_ver;
}

template <typename T1, typename T2, typename K>
class GraphOnVector : public Graph<T1, T2, K> {
public:
  GraphOnVector(int ko, int edge);
  int RetQuantive();
  vector<T1> RetAdjacent(T1 ver);
  void SetV();
  void SetWay(T1 start, T2 finish);
  int Start() { return start; }
  int Fin() { return finish; }
  int RetVer(pair<int, int> ver) { return edges[ver]; }
  class OnIter {
  public:
    K* fir_point = nullptr;
    K* last_point = nullptr;
    OnIter(K* first, K* last);
    class Iterator {
    public:
      K* point = nullptr;
      int pos = 0;
      Iterator() : point(nullptr) {}
      Iterator(K* temp_point) { point = temp_point; }
      Iterator(const Iterator& temp_iter);
      Iterator& operator++();
      K& operator*() { return *point; }
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
  map<pair<int, int>, int> edges;
  int quantity_ver = 0;
  int edge = 0;
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
GraphOnVector<T1, T2, K>::OnIter::OnIter(K* first, K* last) {
  fir_point = first;
  last_point = last;
}

template <typename T1, typename T2, typename K>
vector<T1> GraphOnVector<T1, T2, K>::RetAdjacent(T1 ver) {
  return graph_[ver];
}

template <typename T1, typename T2, typename K>
void GraphOnVector<T1, T2, K>::SetV() {
  for (int i = 0; i < this->edge; i++) {
    int vertex1, vertex2;
    cin >> vertex1 >> vertex2;
    vertex1--;
    vertex2--;
    graph_[vertex1].push_back(vertex2);
    graph_[vertex2].push_back(vertex1);
    edges[make_pair(vertex1, vertex2)] = i + 1;
    edges[make_pair(vertex2, vertex1)] = i + 1;
  }
  for (int i = 0; i < quantity_ver; ++i) {
    graph_[i].push_back(-1);
  }
}

template <typename T1, typename T2, typename K>
void GraphOnVector<T1, T2, K>::SetWay(T1 a, T2 b) {
  this->start = a;
  this->finish = b;
}

template <typename T1, typename T2, typename K>
GraphOnVector<T1, T2, K>::GraphOnVector(int ver, int edge) {
  this->quantity_ver = ver;
  this->edge = edge;
  graph_.resize(ver);
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
  virtual void UseVertex(int vertex) = 0;
  virtual int QuesData(int vertex) = 0;
  virtual int RetQuantityVer() = 0;
  virtual void PushRes(const pair<int, int>& res_p) = 0;
  virtual vector<pair<int, int>> RetRes() = 0;
};

class SpecificVisitor : public Visitor {
public:
  SpecificVisitor(int quantity_ver);
  void Pvisit(int vertex, int to) override;
  void Dvisit(int dist_on_vertex, int to) override;
  int Retperent(int vertex) override;
  int Retdist(int vertex) override;
  void UseVertex(int vertex) override;
  int QuesData(int vertex) override;
  int RetQuantityVer() override;
  void PushRes(const pair<int, int>& res_p) override;
  vector<pair<int, int>> RetRes();
private:
  int quantity_ver;
  vector<int> dist;
  vector<int> perent;

  vector<int> data;
  map<pair<int, int>, int> edges;
  vector<pair<int, int>> result;
};

int SpecificVisitor::RetQuantityVer() {
  return quantity_ver;
}

vector<pair<int, int>> SpecificVisitor::RetRes() {
  return result;
}

void SpecificVisitor::PushRes(const pair<int, int>& res_p) {
  result.emplace_back(res_p);
}

int SpecificVisitor::QuesData(int vertex) {
  return data[vertex];
}

void SpecificVisitor::Dvisit(int dist_on_vertex, int to) { dist[to] = dist_on_vertex; }

int SpecificVisitor::Retdist(int vertex) { return dist[vertex]; }

int SpecificVisitor::Retperent(int vertex) { return perent[vertex]; }

void SpecificVisitor::UseVertex(int vertex) {
  data[vertex] = 1;
}

SpecificVisitor::SpecificVisitor(int quantity_ver) {
  this->quantity_ver = quantity_ver;
  perent.resize(quantity_ver + 1, -1);
  dist.resize(quantity_ver + 1, -1);
  data.resize(quantity_ver);
}

void SpecificVisitor::Pvisit(int vertex, int to) { perent[to] = vertex; }

struct TimeUpIn
{
  vector<int> tin;
  vector<int> tup;
  int timer;
  int count;
};

// я в визиторе все изменил, возвращать вектор не имеет смысла
void DFS(pair<int, int> ver_par, GraphOnVector<int, int, int>& graph, TimeUpIn& Time, Visitor* vis) {
  vis->UseVertex(ver_par.first);
  Time.timer++;
  
  Time.tup[ver_par.first] = Time.timer;
  Time.tin[ver_par.first] = Time.timer;
  // этот злодей и тут есть(range-based for)
  for (auto ver_u : graph.RangeB(ver_par.first)) {
    if (ver_u == ver_par.second) {
      continue;
    }
    if (vis->QuesData(ver_u) == 1) {
      Time.tup[ver_par.first] = min(Time.tup[ver_par.first], Time.tin[ver_u]);
    }
    else if (vis->QuesData(ver_u) == 0) {
      DFS(make_pair(ver_u, ver_par.first), graph, Time, vis);
      Time.tup[ver_par.first] = min(Time.tup[ver_par.first], Time.tup[ver_u]);
      if (Time.tup[ver_u] > Time.tin[ver_par.first]) {
        int cnt = 0;
        for (auto ver_v : graph.RangeB(ver_par.first)) {
          if (ver_v == ver_u) {
            cnt++;
          }
        }

        if (cnt == 1 && ver_par.first != ver_u) {
          vis->PushRes(make_pair(ver_par.first, ver_u));
          Time.count++;
        }
      }
    }
  }
}


int main() {
  int num;
  int edge;
  cin >> num >> edge;

  GraphOnVector<int, int, int> graph(num, edge);
  graph.SetV();
  Visitor* vertex;
  SpecificVisitor hv(num);
  vertex = &hv;
  TimeUpIn Time;
  Time.tin.resize(vertex->RetQuantityVer());
  Time.tup.resize(vertex->RetQuantityVer());
  Time.timer = 0;
  Time.count = 0;
  for (int i = 0; i < num; i++) {
    if (vertex->QuesData(i) == 0) {
      DFS(make_pair(i, -1), graph, Time, vertex);
    }
  }

  if (Time.count == 0) {
    cout << Time.count << '\n';
  }
  else {
    cout << Time.count << '\n';
    vector<int> res;
    for (auto i : vertex->RetRes()) {
      res.push_back(graph.RetVer(i));
    }
    sort(res.begin(), res.end());
    for (auto i : res) {
      cout << i << '\n';
    }
  }

  return 0;
}

/*
6 7
1 2
2 3
3 4
1 3
4 5
4 6
5 6

*/
