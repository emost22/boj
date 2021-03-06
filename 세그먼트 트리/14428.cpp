#include <iostream>
#define INF 2147483647
using namespace std;

pair<int, int> tree[400001];
int N, M;

pair<int, int> cmp(pair<int, int> a, pair<int, int> b) {
	if (a.first < b.first) return a;
	else if (a.first > b.first) return b;
	else {
		if (a.second < b.second) return a;
		else return b;
	}
}

pair<int, int> update(int node, int s, int e, int idx, int diff) {
	if (idx < s || idx > e) return { INF,-1 };
	if (s == e) {
		tree[node] = { diff, idx };
		return tree[node];
	}

	int m = (s + e) / 2;
	update(node * 2, s, m, idx, diff);
	update(node * 2 + 1, m + 1, e, idx, diff);

	tree[node] = cmp(tree[node * 2], tree[node * 2 + 1]);

	return tree[node];
}

pair<int, int> query(int node, int s, int e, int l, int r) {
	if (s > r || l > e) return { INF, -1 };
	if (l <= s && e <= r) return tree[node];

	int m = (s + e) / 2;
	return cmp(query(node * 2, s, m, l, r), query(node * 2 + 1, m + 1, e, l, r));
}

void func() {
	int type, x, y;
	cin >> M;
	while (M--) {
		cin >> type >> x >> y;
		if (type == 1) {
			update(1, 1, N, x, y);
		}
		else {
			pair<int, int> ans = query(1, 1, N, x, y);
			cout << ans.second << '\n';
		}
	}
}

void input() {
	int x;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> x;
		update(1, 1, N, i, x);
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios::sync_with_stdio(false);

	input();
	func();

	return 0;
}