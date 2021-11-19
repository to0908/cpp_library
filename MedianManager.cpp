template< typename T >
struct MedianManager {
    T median;
    int n;
    multiset<T> r;
    multiset<T, greater<T>> l;

    MedianManager(){
        median = 0;
        n = 0;
    }

    T get(){
        // 偶数の時は小さい方を返す
        return median;
    }

    T rsize(){ return r.size(); }
    T lsize() { return l.size(); }

    T insert(T x){
        n++;
        if(n == 1) {
            median = x;
            return median;
        }
        if(median < x) {
            r.insert(x);
            if(n % 2) {
                l.insert(median);
                rpop();
            }
        }
        else{
            l.insert(x);
            if(n % 2 == 0) {
                r.insert(median);
                lpop();
            }
        }
        return median;
    }

    T erase(T x){
        assert(n > 0);
        n--;
        if(n == 0) {
            median = 0;
            return 0;
        }
        if(x == median) {
            if(n % 2) {
                rpop();
            }
            else {
                lpop();
            }
        }
        else if(x < median) {
            auto itr = l.find(x);
            assert(itr != l.end());
            l.erase(itr);
            if(n % 2) {
                l.insert(median);
                rpop();
            }
        }
        else if(x > median) {
            auto itr = r.find(x);
            assert(itr != r.end());
            r.erase(itr);
            if(n % 2 == 0) {
                r.insert(median);
                lpop();
            }
        }
        return median;
    }

private:
    void rpop() {
        median = *r.begin();
        r.erase(r.begin());
    }
    void lpop() {
        median = *l.begin();
        l.erase(l.begin());
    }
};
