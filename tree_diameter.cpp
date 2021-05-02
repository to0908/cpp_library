using Edge = array<int,2>;
// 直径上の点と直径の長さを返す
pair<vector<int>,int> Weighted_Tree_Diameter(const vector<vector<Edge>> &v){
    function<pair<int,int>(int,int)> dfs = [&](int p, int pre){
        pair<int,int> ret(0,p);
        for(auto i:v[p]){
            if(i[0] == pre)continue;
            pair<int,int> g = dfs(i[0],p);
            g.first += i[1];
            chmax(ret,g);
        }
        return ret;
    };
    int p = dfs(0,-1).second;
    auto [dist,q] = dfs(p,-1);
    function<vector<int>(int,int,int)> dia = [&](int p, int pre, int goal){
        vector<int> ret;
        for(auto i:v[p]){
            if(i[0] == pre)continue;
            vector<int> g = dia(i[0],p,goal);
            if(g.size()){
                swap(ret,g);
                ret.push_back(p);
                break;
            }
        }
        return ret;
    };
    return {dia(p,-1,q),dist};
}

// 直径上の点を返す
vector<int> Unweighted_Tree_Diameter(const vector<vector<int>> &v){
    function<pair<int,int>(int,int)> dfs = [&](int p, int pre){
        pair<int,int> ret(0,p);
        for(auto i:v[p]){
            if(i == pre)continue;
            pair<int,int> g = dfs(i,p);
            g.first++;
            chmax(ret,g);
        }
        return ret;
    };
    int p = dfs(0,-1).second;
    int q = dfs(p,-1).second;
    function<vector<int>(int,int,int)> dia = [&](int p, int pre, int goal){
        vector<int> ret;
        for(auto i:v[p]){
            if(i == pre)continue;
            vector<int> g = dia(i,p,goal);
            if(g.size()){
                swap(ret,g);
                ret.push_back(p);
                break;
            }
        }
        return ret;
    };
    return dia(p,-1,q);
}
