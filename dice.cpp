// verify
// https://onlinejudge.u-aizu.ac.jp/solutions/problem/3206/review/4965625/totori0908/C++17
template<typename T>
struct Dice{
	T top,bottom,lef,ri,front,back;
	T base = -1;
	Dice(vector<T> v){
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
		// 回転の時にごちゃごちゃやるなら定数倍かかるけど3回反対方向に回転するほうが楽という主張
		// turn_right(); turn_right(); turn_right();
		rotation(top,ri,bottom,lef);
	}
	void turn_back(){
		rotation(top,front,bottom,back);
	}
	void turn_front(){
		// turn_back(); turn_back(); turn_back();
		rotation(top,back,bottom,front);
	}

	// 向きと目が全て同じかどうか
	bool operator==(const Dice& d) const{
		if(d.back != back)return false;
		if(d.front != front)return false;
		if(d.bottom != bottom)return false;
		if(d.top != top)return false;
		if(d.lef != lef)return false;
		if(d.ri != ri)return false;
		return true;
	}

	// 回転も考慮して同型判定
	bool same(Dice d){
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

	// 全ての向きを考慮して、最大何個一致しているか
	int count_same(Dice d){
		int ret = 0;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				this->turn_front();
				for(int k=0;k<4;k++){
					int cnt = 6;
					this->turn_left();
					if (d.back != this->back)cnt--;
					if(d.front != this->front)cnt--;
					if(d.bottom != this->bottom)cnt--;
					if(d.top != this->top)cnt--;
					if(d.lef != this->lef)cnt--;
					if(d.ri != this->ri)cnt--;
					chmax(ret,cnt);
				}
			}
			this->turn_left();
		}
		return ret;
	}

	// debug
	void print(){
		cerr << "bottom: " << bottom << endl;
		cerr << "front: " << front << endl;
		cerr << "top: " << top << endl;
		cerr << "back: " << back << endl;
		cerr << "left: " << lef << endl;
		cerr << "right: " << ri << endl; 
	}
};
