struct Sieve {
	int n;
 	vector<int> f, primes;
  	Sieve(int n=1) : n(n), f(n+1) {
    	f[0] = f[1] = -1;
    	for (ll i = 2; i <= n; ++i) {
      		if (f[i]) continue;
     		primes.push_back(i);
      		f[i] = i;
      		for (ll j = i*i; j <= n; j += i) {
        		if (!f[j]) f[j] = i;
      		}
    	}
 	}

  	bool isPr(int x) { return f[x] == x;}

  	vector<int> factorList(int x) {
    	vector<int> res;
    	while (x != 1) {
      		res.push_back(f[x]);
      		x /= f[x];
    	}
    	return res;
  	}
  	vector<pair<int,int>> factor(int x) {
    	vector<int> fl = factorList(x);
    	if (fl.size() == 0) return {};
    	vector<pair<int,int>> res(1, mkp(fl[0], 0));
    	for (int p : fl) {
      		if (res.back().first == p) {
        		res.back().second++;
      		}
			else {
        		res.emplace_back(p, 1);
      		}
    	}
   	 	return res;
  	}

	
  	vector<pair<ll,int>> factor(ll x) {
    	vector<pair<ll,int>> res;
    	for (int p : primes) {
      		int y = 0;
      		while (x%p == 0) x /= p, ++y;
      		if (y != 0) res.emplace_back(p,y);
    	}
    	if (x != 1) res.emplace_back(x,1);
    	return res;
  	}

	mint lcm_mint (vi a){
		mint base = 1;
		map<int,vector<int>> mp;
		for(int k : a){
			for(auto [fa,num] : factor(k)){
				mp[fa].pb(num);
			}
		}
		for(auto& [k,lis] : mp){
			sort(lis.rbegin(),lis.rend());
			base *= mint(k).pow(lis[0]);
		}
		return base;
	}
};//sieve(1e7);
