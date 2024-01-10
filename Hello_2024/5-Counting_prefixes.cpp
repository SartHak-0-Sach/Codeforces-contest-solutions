#include <iostream>
#include <vector>
using namespace std;

template <typename T> T mod_inv_in_range(T a, T m) {
	// assert(0 <= a && a < m);
	T x = a, y = m;
	// coeff of a in x and y
	T vx = 1, vy = 0;
	while (x) {
		T k = y / x;
		y %= x;
		vy -= k * vx;
		std::swap(x, y);
		std::swap(vx, vy);
	}
	assert(y == 1);
	return vy < 0 ? m + vy : vy;
}

template <typename T> struct extended_gcd_result {
	T gcd;
	T coeff_a, coeff_b;
};
template <typename T> extended_gcd_result<T> extended_gcd(T a, T b) {
	T x = a, y = b;
	// coeff of a and b in x and y
	T ax = 1, ay = 0;
	T bx = 0, by = 1;
	while (x) {
		T k = y / x;
		y %= x;
		ay -= k * ax;
		by -= k * bx;
		std::swap(x, y);
		std::swap(ax, ay);
		std::swap(bx, by);
	}
	return {y, ay, by};
}

template <typename T> T mod_inv(T a, T m) {
	a %= m;
	a = a < 0 ? a + m : a;
	return mod_inv_in_range(a, m);
}

template <int MOD_> struct modnum {
	static constexpr int MOD = MOD_;
	static_assert(MOD_ > 0, "MOD must be positive");

private:
	int v;

public:

	modnum() : v(0) {}
	modnum(int64_t v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << int(n); }
	friend std::istream& operator >> (std::istream& in, modnum& n) { int64_t v_; in >> v_; n = modnum(v_); return in; }

	friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
	friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }

	modnum inv() const {
		modnum res;
		res.v = mod_inv_in_range(v, MOD);
		return res;
	}
	friend modnum inv(const modnum& m) { return m.inv(); }
	modnum neg() const {
		modnum res;
		res.v = v ? MOD-v : 0;
		return res;
	}
	friend modnum neg(const modnum& m) { return m.neg(); }

	modnum operator- () const {
		return neg();
	}
	modnum operator+ () const {
		return modnum(*this);
	}

	modnum& operator ++ () {
		v ++;
		if (v == MOD) v = 0;
		return *this;
	}
	modnum& operator -- () {
		if (v == 0) v = MOD;
		v --;
		return *this;
	}
	modnum& operator += (const modnum& o) {
		v -= MOD-o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}
	modnum& operator -= (const modnum& o) {
		v -= o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}
	modnum& operator *= (const modnum& o) {
		v = int(int64_t(v) * int64_t(o.v) % MOD);
		return *this;
	}
	modnum& operator /= (const modnum& o) {
		return *this *= o.inv();
	}

	friend modnum operator ++ (modnum& a, int) { modnum r = a; ++a; return r; }
	friend modnum operator -- (modnum& a, int) { modnum r = a; --a; return r; }
	friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
	friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
	friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
	friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};

template <typename T> T pow(T a, long long b) {
	assert(b >= 0);
	T r = 1; while (b) { if (b & 1) r *= a; b >>= 1; a *= a; } return r;
}

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

	int T; cin >> T;
	while (T--) {
		int N; cin >> N;
		std::vector<int> P_sorted(N);
		for (auto& p : P_sorted) cin >> p;
		std::vector<int> freq(2*N+1);
		freq[0+N]++;
		for (int p : P_sorted) {
			freq[p+N]++;
		}
		int LO = std::min(0, P_sorted[0]);
		int HI = std::max(0, P_sorted[N-1]);
		//cerr << "Case " << "N = " << N << ' ' << LO << ' ' << HI << '\n';
		{
			bool good = true;
			for (int i = LO; i <= HI; i++) {
				if (freq[i+N] == 0) {
					good = false;
				}
			}
			if (!good) {
				cout << 0 << '\n';
				continue;
			}
		}

		using num = modnum<998244353>;

		const int V = N+1;
		std::vector<num> fact(V+1);
		fact[0] = 1;
		for (int i = 1; i <= V; i++) fact[i] = fact[i-1] * num(i);
		std::vector<num> ifact(V+1);
		ifact[V] = inv(fact[V]);
		for (int i = V; i >= 1; i--) ifact[i-1] = ifact[i] * num(i);

		// We'll just solve it separately for each endpoint
		std::vector<int> r_edges(2*N+1);
		std::vector<int> l_edges(2*N+1);
		num ans = 0;
		for (int en = LO; en <= HI; en++) {
			//cerr << "trying " << en << '\n';
			int st = 0;
			bool good = true;
			for (int i = LO; i <= HI; i++) {
				int cur_in_deg = ((i == LO) ? 0 : r_edges[i-1+N]) + (i == st);
				int cur_out_deg = ((i == LO) ? 0 : l_edges[i-1+N]) + (i == en);

				int nxt_out_edges = freq[i+N] - cur_out_deg;
				int nxt_in_edges = freq[i+N] - cur_in_deg;
				if (i == HI) {
					if (nxt_out_edges != 0 || nxt_in_edges != 0) {
						good = false;
					}
					break;
				}
				if (nxt_out_edges < 0 || nxt_in_edges < 0 || nxt_out_edges + nxt_in_edges == 0) {
					good = false;
					break;
				}
				r_edges[i+N] = nxt_out_edges;
				l_edges[i+N] = nxt_in_edges;
			}
			if (!good) continue;
			num r = 1;
			num num_trees = 1;
			for (int i = LO; i < 0; i++) {
				num_trees *= num(l_edges[i+N]);
			}
			for (int i = 0; i < HI; i++) {
				num_trees *= num(r_edges[i+N]);
			}
			r *= num_trees;
			for (int i = LO; i < HI; i++) {
				r *= ifact[l_edges[i+N]];
				r *= ifact[r_edges[i+N]];
			}
			for (int i = LO; i <= HI; i++) {
				r *= fact[freq[i+N]-1];
			}
			//cerr << "en " << en << ' ' << r << '\n';
			ans += r;
		}
		cout << ans << '\n';
	}

	return 0;
}