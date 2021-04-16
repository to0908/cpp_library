template < typename Monoid >
struct Segtree{
	using FM = function < Monoid(Monoid, Monoid) >;
	using FA = function < void(Monoid&, Monoid) >;
	int N;
	vector<Monoid> dat;
	
	const FM fm;
	const FA fa;
	const Monoid M1;

	Segtree(int n,const FM fm, const FA fa, const Monoid &M1): fm(fm), fa(fa), M1(M1){
		N = 1;
		while(N < n) N *= 2;
		dat.assign(2*N,M1);
	}

	void set(int idx, const Monoid &x){
		dat[idx+N-1] = x;
	}

	void build(){
		for(int i=N-2; i>=0; i--){
			dat[i] = fm(dat[2*i+1], dat[2*i+2]);
		}
	}

	void update(int idx, const Monoid &x){
		idx += N-1;
		fa(dat[idx],x);
		while(idx > 0){
			idx = (idx-1)/2;
			dat[idx] = fm(dat[idx*2 + 1], dat[idx*2+2]);
		}
	}

	Monoid get(int a, int b, int k, int l, int r){
		if(r<=a || b<=l) return M1;
		if(a<=l && r<=b) return dat[k];
		else{
			Monoid vl = get(a,b,k*2+1,l,(l+r)/2);
			Monoid vr = get(a,b,k*2+2,(l+r)/2,r);
			return fm(vl,vr);
		}
	}
	Monoid get(int a,int b){ return get(a,b,0,0,N); }

	Monoid at(int k) {return dat[k+N-1];}

	void debug(){
		for(int i=N-1;i<dat.size();i++){
			cerr << dat[i] << ", ";
		}
		cerr << "\n";
	}
};

// Range Minimum Query
// auto fm = [](ll a,ll b){ return min(a,b); };
// auto fa = [](ll& a, ll b){ a=b; };
// Segtree<ll> seg(n, fm, fa, INF);

// Range Sum Query
// auto fm = [](ll a,ll b){ return a+b; };
// auto fa = [](ll& a, ll b){ a+=b; };
// Segtree<ll> seg(n, fm, fa, 0);

// Point Set Range Composite
// change f(x) = ax+b, query f(f(f(...)) % mod -> return {a,b}
// struct S{ ll a,b; };
// const ll mod = 998244353;
// auto fm = [](S a,S b){ return S{a.a*b.a%mod,(a.b*b.a+b.b)%mod}; };
// auto fa = [](S& a, S b){ a = b; };
// Segtree<S> seg(500050, fm, fa, S{1,0});
