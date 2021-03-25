const ll mul[] = {1007,1009,1013,1001};
const ll mod[] = {1000000007,1000000023,1000000087,1000000093};
const int MAX = 1100005, hash_size = 4;
ll beki[hash_size][MAX+1];
bool inited = false;

void Hash_init() {
	inited = true;
	for(int i=0;i<hash_size;i++){
		beki[i][0] = 1;
		for(int j=0;j<MAX;j++){
			beki[i][j+1] = (beki[i][j]*mul[i])%mod[i];
		}
	}
}

struct Roling_Hash{
	vector<vector<ll>> hash;
	int n;
	Roling_Hash(string s){
		hash.resize(hash_size);
		int n = s.size();
		for(int i=0;i<hash_size;i++){
			hash[i].resize(n+1);
			for(int j=0;j<n;j++){
				hash[i][j+1] = (hash[i][j] * mul[i] % mod[i] + s[j]);
				if(hash[i][j+1] >= mod[i])hash[i][j+1] -= mod[i];
			}
		}
	}
	Roling_Hash(vector<ll> s){
		n = s.size();
		for(int i=0;i<hash_size;i++){
			hash[i].resize(n+1);
			for(int j=0;j<n;j++){
				hash[i][j+1] = (hash[i][j] * mul[i] % mod[i] + s[j]);
				if(hash[i][j+1] >= mod[i])hash[i][j+1] -= mod[i];
			}
		}
	}

	// hash of S[l,r)
	vector<ll> get(int l, int r){
		// assert(inited);
		vector<ll> ret(hash_size);
		int x = r - l;
		for(int i=0;i<hash_size;i++){
			ret[i] = (hash[i][r] - (hash[i][l]*beki[i][x])%mod[i] + mod[i])%mod[i];
		}
		return ret;
	}

	// S[l1:r1] == T[l2:r2]かどうか.
	bool same(Roling_Hash &T, int l1, int r1, int l2=-1, int r2=-1){
		if(l2==-1 && r2==-1)l2=l1, r2=r1;
		assert(l2!=-1 && r2!=-1);
		bool same = true;
		vector<ll> v = this->get(l1,r1);
		vector<ll> u = T.get(l2,r2);
		for(int i=0;i<hash_size;i++){
			if(v[i]!=u[i])same=false;
		}
		return same;
	}
};
