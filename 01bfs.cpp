struct bfs01 {
    struct state {
        int v, cost;
    };

    const int INF = 1e9+9;
    int N;
    vector< vector<array<int,2>> > E;

    bfs01(int n): N(n), E(n) {}

    //有効グラフの時はこっち。u→vに距離xで結ぶ
    void add_directed_edge(int u, int v, int x) {
        E[u].push_back({v,x});
    }

    //無向グラフの時はこっち。uとvを双方向に距離xで結ぶ
    void add_undirected_edge(int u, int v, int x) {
        E[u].push_back({v,x});
        E[v].push_back({u,x});
    }

    //Sを始点として、他の頂点への最短経路を探す
    vector<int> shortest_path(int S) {
        vector<int> dp(E.size(), INF);
        deque<state> q;
        q.push_back((state) { S, 0 });
        while(!q.empty()) {
            int v = q.front().v, cost = q.front().cost;
            q.pop_front();
            if(dp[v] < cost) continue;
            dp[v] = cost;
            for(auto e:E[v]) {
                auto [nv, x] = e;
                int ncost = cost + x;
                if(dp[nv] > ncost){
                    dp[nv] = ncost;
                    if(x) q.push_back((state) { nv, ncost });
                    else q.push_front((state) {nv, ncost});
                }
            }
        }
        return dp;
    }
};
