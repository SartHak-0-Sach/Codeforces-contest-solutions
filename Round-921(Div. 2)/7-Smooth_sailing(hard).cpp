#include <stdio.h>
#include <string.h>

#define NM	300000
#define INF	0x3f3f3f3f

int min(int a, int b) { return a < b ? a : b; }

int di[] = { -1, 1, 0, 0 };
int dj[] = { 0, 0, -1, 1 };

int ds[NM * 2], ww[NM * 2];

int find(int i) {
	return ds[i] < 0 ? i : find(ds[i]);
}

void join(int i, int j, int w) {
	i = find(i);
	j = find(j);
	if (i == j)
		return;
	if (ds[i] > ds[j])
		ds[i] = j, ww[i] = w;
	else {
		if (ds[i] == ds[j])
			ds[i]--;
		ds[j] = i, ww[j] = w;
	}
}

int query(int i, int j) {
	int w = INF;

	while (i != j)
		if (ww[i] > ww[j])
			w = ww[i], i = ds[i];
		else
			w = ww[j], j = ds[j];
	return w;
}

int main() {
	static char cc[NM + 1], active[NM];
	static int dd[NM], qu[NM], ans[NM];
	int n, m, q, cnt, g, h, i, i_, i1, j, j_, j1, ij, ij_, d;

	scanf("%d%d%d", &n, &m, &q);
	for (i = 0; i < n; i++)
		scanf("%s", cc + i * m);
	i1 = -1, j1 = -1;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			ij = i * m + j;
			if (cc[ij] == '#') {
				i1 = i, j1 = j;
				goto out;
			}
		}
out:
	for (ij = 0; ij < n * m; ij++)
		dd[ij] = n * m + 1;
	cnt = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			ij = i * m + j;
			if (cc[ij] == 'v')
				dd[ij] = 0, qu[cnt++] = ij;
		}
	for (h = 0; h < cnt; h++) {
		ij = qu[h], i = ij / m, j = ij % m, d = dd[ij] + 1;
		for (g = 0; g < 4; g++) {
			i_ = i + di[g], j_ = j + dj[g], ij_ = i_ * m + j_;
			if (i_ >= 0 && i_ < n && j_ >= 0 && j_ < m && dd[ij_] > d)
				dd[ij_] = d, qu[cnt++] = ij_;
		}
	}
	memset(ds, -1, n * m * 2 * sizeof *ds), memset(ww, -1, n * m * 2 * sizeof *ww);
	for (h = cnt - 1; h >= 0; h--) {
		ij = qu[h], i = ij / m, j = ij % m, d = dd[ij];
		if (cc[ij] != '#') {
			active[ij] = 1;
			for (g = 0; g < 4; g++) {
				i_ = i + di[g], j_ = j + dj[g], ij_ = i_ * m + j_;
				if (i_ >= 0 && i_ < n && j_ >= 0 && j_ < m && cc[ij_] != '#' && active[ij_]) {
					if ((i < i1) != (i_ < i1) && j < j1)
						join(ij << 1 | 0, ij_ << 1 | 1, d), join(ij << 1 | 1, ij_ << 1 | 0, d);
					else
						join(ij << 1 | 0, ij_ << 1 | 0, d), join(ij << 1 | 1, ij_ << 1 | 1, d);
				}
			}
		}
	}
	for (ij = 0; ij < n * m; ij++)
		if (cc[ij] != '#')
			ans[ij] = min(query(ij << 1 | 0, ij << 1 | 1), dd[ij]);
	while (q--) {
		scanf("%d%d", &i, &j), i--, j--, ij = i * m + j;
		printf("%d\n", ans[ij]);
	}
	return 0;
}
