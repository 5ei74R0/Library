#include <bits/stdc++.h>
using namespace std;

/*GRAPH_TEMPLATE=============================================*/
template<typename T>
class Edge {
public:
    int srch; //searched?探索状態記録「null = -1」
    int to; //辺の行き先
    T cost; //辺の重み
    Edge(int t, T w) : srch(-1), to(t), cost(w) {}
    Edge(int t, T w, int src) : srch(src), to(t), cost(w) {}
};
template<typename T>
using W_Graph = std::vector<std::vector<Edge<T>>>;   //重み付きグラフ
using Graph = std::vector<std::vector<int>>;         //通常グラフ
template<typename T>
using Matrix = std::vector<std::vector<T>>;          //隣接行列(使わなさそう...)

/*===========================================================*/
//  入力受け取り例
int main(){
    int n, m; cin >> n >> m;
    W_Graph<double> W_G(n); //doubleの重みをもった重み付きグラフ
    Graph G(m);  //普通のグラフ

    for(int i = 0; i < n; i++) { // W_Gに入力
        int from, to;
        double cost;
        cin >> from >> to >> cost;
        W_G[from].push_back(Edge<double>(to, cost));
    }


    for(int i = 0; i < m; i++) { // Gに入力
        int from, to;
        cin >> from >> to;
        G[from].push_back(to);
    }
}