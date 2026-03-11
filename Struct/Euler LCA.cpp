struct EulerTourLCA {
    vector<int> first_visit;
    vector<int> tour;
    vector<int> depths;
    vector<int> node_depth;
    vector<vector<int>> st;
    vector<int> log_table;
	  vector<int> in_time;
    vector<int> sub_size;
    int pre_timer;

    EulerTourLCA(const vector<vector<int>>& G, int n, int root = 0) {
        first_visit.resize(n);
        node_depth.resize(n);
        tour.reserve(2 * n);
        depths.reserve(2 * n);
        in_time.resize(n);
        sub_size.resize(n);
		    pre_timer = 0;
        dfs(G, root, -1, 0);

        int m = depths.size();
        int max_log = 31 - __builtin_clz(m) + 1;
        st.assign(max_log, std::vector<int>(m));
        log_table.assign(m + 1, 0);
        for (int i = 2; i <= m; i++) log_table[i] = log_table[i / 2] + 1;

        for (int i = 0; i < m; i++) st[0][i] = i;
        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= m; i++) {
                int left = st[j - 1][i];
                int right = st[j - 1][i + (1 << (j - 1))];
                st[j][i] = (depths[left] < depths[right]) ? left : right;
            }
        }
    }

    void dfs(const vector<vector<int>>& G, int u, int p, int d) {
        first_visit[u] = tour.size();
		    in_time[u] = pre_timer++;
        sub_size[u] = 1;
        node_depth[u] = d;
        tour.push_back(u);
        depths.push_back(d);
        for (int v : G[u]) {
            if (v == p) continue;
            dfs(G, v, u, d + 1);
            tour.push_back(u);
            depths.push_back(d);
        }
    }

    int lca(int u, int v) const {
        int l = first_visit[u];
        int r = first_visit[v];
        if (l > r) swap(l, r);
        int j = log_table[r - l + 1];
        int left = st[j][l];
        int right = st[j][r - (1 << j) + 1];
        return tour[depths[left] < depths[right] ? left : right];
    }

    int dist(int u, int v) const {
        return node_depth[u] + node_depth[v] - 2 * node_depth[lca(u, v)];
    }
	int get_id(int u) const { return in_time[u]; }
	int get_subtree_size(int u) const { return sub_size[u]; }
};
