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
  virtual void SetTup(int vertex, int timer) = 0;
  virtual void SetTin(int vertex, int timer) = 0;
  virtual int QuesData(int vertex) = 0;
  virtual int RetTup(int vertex) = 0;
  virtual int RetTin(int vertex) = 0;
  virtual void PushRes(pair<int, int> res_p) = 0;
  virtual vector<pair<int, int>> RetRes() = 0;
};

class HolVisitor : public Visitor {
private:
  vector<int> dist;
  vector<int> perent;
  vector<int> tin;
  vector<int> tup;
  vector<int> data;
  map<pair<int, int>, int> edges;
  vector<pair<int, int>> result;
public:
  HolVisitor(int quantity_ver);
  void Pvisit(int vertex, int to) override;
  void Dvisit(int dist_on_vertex, int to) override;
  int Retperent(int vertex) override;
  int Retdist(int vertex) override;
  void UseVertex(int vertex) override;
  void SetTup(int vertex, int timer) override;
  void SetTin(int vertex, int timer) override;
  int QuesData(int vertex) override;
  int RetTup(int vertex) override;
  int RetTin(int vertex) override;
  void PushRes(pair<int, int> res_p) override;
  vector<pair<int, int>> RetRes();
};

vector<pair<int, int>> HolVisitor::RetRes() {
  return result;
}

void HolVisitor::PushRes(pair<int, int> res_p) {
  result.emplace_back(res_p);
}

int HolVisitor::QuesData(int vertex) {
  return data[vertex];
}

int HolVisitor::RetTup(int vertex) {
  return tup[vertex];
}

int HolVisitor::RetTin(int vertex) {
  return tin[vertex];
}

void HolVisitor::Dvisit(int dist_on_vertex, int to) { dist[to] = dist_on_vertex; }

int HolVisitor::Retdist(int vertex) { return dist[vertex]; }

int HolVisitor::Retperent(int vertex) { return perent[vertex]; }

void HolVisitor::UseVertex(int vertex) {
  data[vertex] = 1;
}

HolVisitor::HolVisitor(int quantity_ver) {
  perent.resize(quantity_ver + 1, -1);
  dist.resize(quantity_ver + 1, -1);
  data.resize(quantity_ver);
  tin.resize(quantity_ver);
  tup.resize(quantity_ver);
}

void HolVisitor::SetTup(int vertex, int timer) {
  tup[vertex] = timer;
}

void HolVisitor::SetTin(int vertex, int timer) {
  tin[vertex] = timer;
}

void HolVisitor::Pvisit(int vertex, int to) { perent[to] = vertex; }

// я в визиторе все изменил, возвращать вектор не имеет смысла
void DFS(pair<int, int> ver_par, GraphOnVector<int, int, int>& graph, int& timer, int& count, Visitor* vis) {
  vis->UseVertex(ver_par.first);
  timer++;
  vis->SetTin(ver_par.first, timer);
  vis->SetTup(ver_par.first, timer);

  // этот злодей и тут есть(range-based for)
  for (auto ver_u : graph.RangeB(ver_par.first)) {
    if (ver_u == ver_par.second) {
      continue;
    }
    if (vis->QuesData(ver_u) == 1) {
      vis->SetTup(ver_par.first, min(vis->RetTup(ver_par.first), vis->RetTin(ver_u)));
    }
    else if (vis->QuesData(ver_u) == 0) {
      DFS(make_pair(ver_u, ver_par.first), graph, timer, count, vis);
      vis->SetTup(ver_par.first, min(vis->RetTup(ver_par.first), vis->RetTup(ver_u)));
      if (vis->RetTup(ver_u) > vis->RetTin(ver_par.first)) {
        int cnt = 0;
        for (auto ver_v : graph.RangeB(ver_par.first)) {
          if (ver_v == ver_u) {
            cnt++;
          }
        }

        if (cnt == 1 && ver_par.first != ver_u) {
          vis->PushRes(make_pair(ver_par.first, ver_u));
          count++;
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
  HolVisitor hv(num);
  vertex = &hv;
  int timer = 0;
  int count = 0;
  for (int i = 0; i < num; i++) {
    if (vertex->QuesData(i) == 0) {
      DFS(make_pair(i, -1), graph, timer, count, vertex);
    }
  }

  if (count == 0) {
    cout << count << '\n';
  }
  else {
    cout << count << '\n';
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
