#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
void solve(){
	int N;
	cin >> N;
	vector<ll> A(N);
	for(ll& x : A) cin >> x;
	ll sum = 0;
	vector<int> freq(2);
	for(int i = 0; i < N; i++){
		sum += (A[i] / 2) * 2;
		freq[A[i] % 2]++;
		int v = (freq[1] + 1) / 3;
		ll ans = sum + v * 2;
		if(i == 0 && freq[1]) ans++;
		cout << (ans) << " \n"[i+1 == N];
	}
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--) solve();
}