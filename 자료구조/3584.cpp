#include <iostream>
#include <vector>
#include <cstring>
#define MAX 10000
using namespace std;

vector<int> graph[MAX + 1];
bool chk[MAX + 1];
int depth[MAX + 1];
int parent[MAX + 1];
int N, s, e, root;

void dfs(int v, int d) {
	depth[v] = d;

	for (int i = 0; i < graph[v].size(); i++) {
		int next = graph[v][i];
		
		if (depth[next]) continue;
		parent[next] = v;
		dfs(next, d + 1);
	}
}

int func(int u, int v) {
	if (depth[u] > depth[v]) swap(u, v);

	while (depth[u] != depth[v]) {
		v = parent[v];
	}

	if (u == v) return u;

	while (parent[u] != parent[v]) {
		u = parent[u];
		v = parent[v];
	}

	return parent[u];
}

void input() {
	int u, v;
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> u >> v;
		graph[u].push_back(v);
		chk[v] = true;
	}

	for (int i = 1; i <= N; i++) {
		if (!chk[i]) {
			root = i;
			break;
		}
	}

	cin >> s >> e;
}

void init() {
	memset(depth, 0, sizeof(depth));
	memset(parent, 0, sizeof(parent));
	memset(chk, false, sizeof(chk));
	for (int i = 1; i <= N; i++) graph[i].clear();
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		input();
		dfs(root, 1);
		cout << func(s, e) << '\n';
		init();
	}

	return 0;
}