#include <cstdio>
#include <iostream>
#include <queue>
#include <limits>
#include <vector>
#include <utility>

using std::pair;
using std::cin;
using std::cout;
using std::vector;
using std::priority_queue;
using std::greater;
using std::make_pair;

// Матрица почти не поменялась, только вес с 1 на weight и немного итератор 
template <typename T1, typename T2, typename K> class Graph {
public:
  virtual int RetQuantive() = 0;
  virtual vector<pair<T1, T2>> RetAdjacent(T1 ver) = 0;
  virtual void SetV() = 0;
  virtual void SetWay(int start) = 0;
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
  void SetWay(T1 start);
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
      point -= 1;
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
    if (*point >= 1 and i > 0) {
      break;
    }
    else {
      point += 1;
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
    int weight;
    cin >> t_from >> t_to >> weight;
    graph_[t_from][t_to] = weight;
    graph_[t_to][t_from] = weight;
  }
  for (int i = 0; i <= quantity_ver; ++i) {
    graph_[i].push_back(-1);
  }
}

template <typename T1, typename T2, typename K>
void GraphOnMatrix<T1, T2, K>::SetWay(T1 start) {
  this->start = start;
}

template <typename T1, typename T2, typename K>
GraphOnMatrix<T1, T2, K>::GraphOnMatrix(int ver, int edg) {
  quantity_ver = ver;
  edge = edg;
}

template <typename T1, typename T2, typename K>
int GraphOnMatrix<T1, T2, K>::RetQuantive() {
  return quantity_ver;
}

//Тут более значительные изменения, итератор теперь это пара, немного поменяны методы
template <typename T1, typename T2, typename K>
class GraphOnVector : public Graph<T1, T2, K> {
public:
  GraphOnVector(int edg, int ver);
  int RetQuantive();
  vector<pair<T1, T2>> RetAdjacent(T1 ver);
  void SetV();
  void SetWay(int start);
  int Start() { return start; }
  int Fin() { return finish; }
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
  int quantity_ver = 0;
  int edge = 0;
  T1 start = 0;
  T2 finish = 0;
  int t_from = 0;
  int t_to = 0;
  vector<T1> dist;
  vector<T1> parent;
  vector<vector<pair<int, int>>> graph_;
};

template <typename T1, typename T2, typename K>
typename GraphOnVector<T1, T2, K>::OnIter::Iterator GraphOnVector<T1, T2, K>::OnIter::begin() {
  Iterator temp(fir_point);
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
  if (*point != make_pair(-1, -1)) {
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
vector<pair<T1, T2>> GraphOnVector<T1, T2, K>::RetAdjacent(T1 ver) {
  return graph_[ver];
}

template <typename T1, typename T2, typename K>
void GraphOnVector<T1, T2, K>::SetV() {
  graph_.resize(quantity_ver);
  for (int j = 0; j < edge; j++) {
    int weight;
    cin >> t_from >> t_to >> weight;
    graph_[t_from].emplace_back(t_to, weight);
    graph_[t_to].emplace_back(t_from, weight);
  }
  for (int i = 0; i < static_cast<int>(graph_.size()); ++i) {
    graph_[i].emplace_back(-1, -1);
  }
}

template <typename T1, typename T2, typename K>
void GraphOnVector<T1, T2, K>::SetWay(int start) {
  this->start = start;
}

template <typename T1, typename T2, typename K>
GraphOnVector<T1, T2, K>::GraphOnVector(int edg, int ver) {
  quantity_ver = ver;
  edge = edg;
}

template <typename T1, typename T2, typename K>
int GraphOnVector<T1, T2, K>::RetQuantive() {
  return quantity_ver;
}

// Добавлен метод RetAllDist
class Visitor {
public:
  virtual void Pvisit(const int& vertex, const int& to) = 0;
  virtual void Dvisit(const int& dist_on_vertex, const int& to) = 0;
  virtual const int& Retperent(const int& vertex) = 0;
  virtual const int& Retdist(const int& vertex) = 0;
  virtual vector<int> RetAllDist() = 0;
  virtual const int& RetKinf() = 0;
};

class SpecificVisitor : public Visitor {
public:
  SpecificVisitor(const int& quantity_ver);
  void Pvisit(const int& vertex, const int& to) override;
  void Dvisit(const int& dist_on_vertex, const int& to) override;
  const int& Retperent(const int& vertex) override;
  const int& Retdist(const int& vertex) override;
  vector<int> RetAllDist() override;
  const int& RetKinf() override;
private:
  vector<int> dist;
  vector<int> perent;
  const int kInf = std::numeric_limits<int>::max();
};

const int& SpecificVisitor::RetKinf() { return kInf; }

void SpecificVisitor::Dvisit(const int& dist_on_vertex, const int& to) { dist[to] = dist_on_vertex; }

const int& SpecificVisitor::Retdist(const int& vertex) { return dist[vertex]; }

const int& SpecificVisitor::Retperent(const int& vertex) { return perent[vertex]; }

SpecificVisitor::SpecificVisitor(const int& quantity_ver) {
  perent = vector<int>(quantity_ver, kInf);
  dist = vector<int>(quantity_ver, kInf);
}

void SpecificVisitor::Pvisit(const int& vertex, const int& to) { perent[to] = vertex; }

vector<int> SpecificVisitor::RetAllDist() {
  return dist;
}

//=========================

// Тут использован и Визитор и range-based for, выводов тут нет, возвращает визитор, можно вернуть и вектор, это обрабытывается в мейне
Visitor* Dijkstra(Visitor* vis, GraphOnVector<int, int, pair<int, int>>& temp_iter) {
  int num = static_cast<int>(temp_iter.RetQuantive());
  vis->Dvisit(0, temp_iter.Start());
  priority_queue<pair<int, int>, vector<pair<int, int>>,
    greater<pair<int, int>>>
    pq;
  pq.push(make_pair(0, temp_iter.Start()));
  while (!pq.empty()) {
    int ver_u = pq.top().second;
    int dist_t = pq.top().first;
    pq.pop();
    if (dist_t > vis->Retdist(ver_u)) {
      continue;
    }
    for (auto&& edge : temp_iter.RangeB(ver_u)) {
      if (edge.first == -1 and edge.second == -1) {
        continue;
      }
      int ver_v = edge.first;
      int weight = edge.second;
      if (vis->Retdist(ver_u) + weight < vis->Retdist(ver_v)) {
        vis->Dvisit(vis->Retdist(ver_u) + weight, ver_v);
        pq.push(make_pair(vis->Retdist(ver_v), ver_v));
      }
    }
  }
  return vis;
}

int main() {
  int bloks;
  int start;
  cin >> bloks;
  for (int i = 0; i < bloks; i++) {
    int num_rooms;
    int num_transitions;
    cin >> num_rooms >> num_transitions;
    GraphOnVector<int, int, pair<int, int>> gr(num_transitions, num_rooms);
    gr.SetV();
    cin >> start;
    gr.SetWay(start);
    Visitor* vertex;
    SpecificVisitor hv(num_rooms);
    vertex = &hv;
    vertex = Dijkstra(vertex, gr);
    for (auto distance : vertex->RetAllDist()) {
      if (distance == hv.RetKinf()) {
        cout << "2009000999 ";
      }
      else {
        cout << distance << " ";
      }
    }
    cout << '\n';
  }
  return 0;
}
/*
2
5 7
1 2 5
1 3 2
2 3 4
2 4 3
3 4 6
0 3 20
0 4 10
1
5 7
1 2 5
1 3 2
2 3 4
2 4 3
3 4 6
0 3 20
0 4 10
1

*/
