const int MAX = 3000010;
vector<int> prime;
bool not_prime[MAX];
void era(){
	not_prime[0]=not_prime[1]=1;
	for(int i=2;i*i<MAX;i++){
		if(not_prime[i])continue;
		for(int j=i+i;j<MAX;j+=i){
			not_prime[j]=1;
		}
	}
	for(int i=2;i<MAX;i++)if(not_prime[i] == false)prime.push_back(i);
}
