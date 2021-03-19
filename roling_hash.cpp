const vector<ll> mul = {1007,1009,1013,1001};
const vector<ll> mod = {1000000007,1000000023,1000000087,1000000093};
vector<vector<ll>> roling_hash(string s,int sz = 4){
	int n = s.size();
	vector<vector<ll>> hash(sz,vector<ll>(n+1));
	assert((int)mul.size() >= sz);
	for(int i=0;i<n;i++){
		for(int j=0;j<sz;j++){
			hash[j][i+1] = (hash[j][i] * mul[j] % mod[j] + s[i]);
			if(hash[j][i+1] >= mod[j])hash[j][i+1] -= mod[j];
		}
	}
	return hash;
}
