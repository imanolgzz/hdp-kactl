/**
 * Author: Sebascert
 * Date: Unknown
 * License: CC0
 * Source: Sebascert
 * Description: Pending
 * Time: Pending
 * Status: Tested
 */
#pragma once

// General E*V^2
// UnitNetwork/Matching E*sqrt(V)
// flow(u,v) = g[v][u].cap (idx)
struct Dinic {
	using ft = lli;
	struct edge {
		int to, rev, idx;
		ft cap;
	};
	int n;
	const ft INF;
	vector<vector<edge>> g;
	vector<int> dist, work;
	Dinic(int n) : n(n), INF(numeric_limits<ft>::max()), g(n), dist(n), work(n) {}
	void add(int u, int v, ft cap, int idx = -1) {
		g[u].pb({v, (int)sz(g[v]), -1, cap});
		g[v].pb({u, (int)sz(g[u]) - 1, idx, 0});
	}
	bool bfs(int s, int t) {
		fill(all(dist), -1);
		queue<int> q;
		dist[s] = 0;
		q.push(s);
		while(!q.empty() && dist[t] == -1) {
			int p = q.front();
			q.pop();
			for(auto&& e: g[p]) {
				if(e.cap > 0 && dist[e.to] == -1) {
					dist[e.to] = dist[p] + 1;
					q.push(e.to);
				}
			}
		}
		return dist[t] != -1;
	}
	ft dfs(int s, int t, ft flow) {
		if(s == t) return flow;
		for(int& i = work[s]; i < sz(g[s]); i++) {
			edge& e = g[s][i];
			if(e.cap > 0 && dist[s] < dist[e.to]) {
				ft d = dfs(e.to, t, min(flow, e.cap));
				if(d > 0) {
					e.cap -= d;
					g[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}
	ft flow(int s, int t) {
		if(s == t) return 0;
		ft flow = 0;
		while(bfs(s, t)) {
			fill(all(work), 0);
			ft f = 0;
			while((f = dfs(s, t, INF)) > 0) flow += f;
		}
		return flow;
	}
	vector<bool> mc;
	void mc_dfs(int u) {
		if(mc[u]) return;
		mc[u] = 1;
		for(auto& e: g[u])
			if(e.cap) mc_dfs(e.to);
	}
	lli mincut(int s, int t) {
		ft x = flow(s, t);
		mc.assign(n, 0);
		mc_dfs(s);
		return x;
	}
};