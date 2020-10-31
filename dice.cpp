#include<bits/stdc++.h> 
using namespace std;
typedef long long ll;
#define endl '\n'
#define all(x) (x).begin(),(x).end()
template<typename T1,typename T2> bool chmin(T1 &a,T2 back){if(a<=back)return 0; a=back; return 1;}
template<typename T1,typename T2> bool chmax(T1 &a,T2 back){if(a>=back)return 0; a=back; return 1;}
int dx[4]={0,1,0,-1}, dy[4]={1,0,-1,0};


template<typename T>
struct dice{
    T top,bottom,lef,ri,front,back;
    dice(vector<T> v){
        assert(v.size() == 6);
        top = v[0];
        front = v[1];
        ri = v[2];
        lef = v[3];
        back = v[4];
        bottom = v[5];
    }
    // (a,b,c,d) -> (b,c,d,a)
    void rotation(T &a,T &b,T &c,T &d){
        swap(a,b); swap(b,c); swap(c,d);
    }
    void turn_right(){
        rotation(top,lef,bottom,ri);
    }
    void turn_left(){
        rotation(top,ri,bottom,lef);
    }
    void turn_front(){
        rotation(top,back,bottom,front);
    }
    void turn_back(){
        rotation(top,front,bottom,back);
    }

    // 向きと目が全て同じかどうか
    bool operator==(const dice& d) const{
        if(d.back != back)return false;
        if(d.front != front)return false;
        if(d.bottom != bottom)return false;
        if(d.top != top)return false;
        if(d.lef != lef)return false;
        if(d.ri != ri)return false;
        return true;
    }

    // 回転も考慮して同型判定
    bool same(dice d){
        for(int i=0;i<2;i++){
            for(int j=0;j<4;j++){
                this->turn_front();
                for(int k=0;k<4;k++){
                    this->turn_left();
                    if(d == *this)return true;
                }
            }
            this->turn_left();
            this->turn_left();
        }
        return false;
    }
};



signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(20);

    int n;
    cin>>n;
    vector<dice<int>> d;
    for(int i=0;i<n;i++){
        vector<int> v(6);
        for(int j=0;j<6;j++)cin>>v[j];
        d.push_back(dice<int>(v));
    }
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
        if(d[i].same(d[j])){
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
}
