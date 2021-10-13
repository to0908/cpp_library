template<typename T, typename Vertex>
struct ReRooting{

    vector<vector<array<ll,2>>> v;
    vector<vector<T>> dp;
    vector<T> ans;
    vector<Vertex> d;
    bool vertex_info = false;

    ReRooting(int n) : v(n), dp(n), ans(n) {};

    void add_edge(int &a, int &b, ll &c){
        v[a].push_back({b,c});
        v[b].push_back({a,c});
    }
    void set_vertex(vector<Vertex> &x){
        vertex_info = true;
        d = x;
    }

    T dfs(int p=0, int pre=-1){
        T ret = ident;
        if(vertex_info){
            ret = d[p];
        }
        for(auto [i,c] : v[p]){
            if(i != pre){
                T t = f(dfs(i,p), c);
                ret = g(ret, t);
                dp[p].push_back(t);
            }
        }
        return ret;
    }

    void solve(int p, int pre, T par){
        T npar = par;
        if(pre != -1){
            npar = g(npar, ident);
        }

        int n = dp[p].size();
        vector<T> ldp(n+1), rdp(n+1);
        for(int i=0;i<n;i++){
            ldp[i+1] = g(ldp[i+1], dp[p][i]);
            ldp[i+1] = g(ldp[i+1], ldp[i]);
            rdp[n-i-1] = g(rdp[n-i-1], dp[p][n-1-i]);
            rdp[n-i-1] = g(rdp[n-i-1], rdp[n-i]);
        }
        int cnt = 0;
        for(auto [i, c] : v[p]){
            if(i != pre){
                T nx = npar;
                if(vertex_info){
                    nx = g(npar, d[p]);
                }
                solve(i, p, f(g(nx, g(ldp[cnt], rdp[cnt+1])), c));
                cnt++;
            }
        }
        ans[p] = g(npar, ldp[n]);
    }

    void solve(){
        solve(0, -1, ident);
    }

private:
    // ここは問題固有
    
    T ident = 0;

    // 辺情報の処理
    T f(T a, ll c){
        return a + c;
    }

    // 答えのマージ
    T g(T a, T b){
        return max(a,b);
    }
};
