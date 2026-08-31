/**
 * Author: Leones000
 * Date: unknown
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals.
 * Answers Queries [L,R]
 * Time: O(\log N).
 * Status: stress-tested a bit
 */
#pragma once

struct LazySegtree{
	#define mid (l + r) / 2
	#define left(u) (u + 1)
	#define right(u) (u + ((mid - l + 1) << 1))
	struct Node{
		lli s, lazy;
		Node(lli s = 0, lli lazy = 0) : s(s), lazy(lazy) {}
		Node operator + (const Node &n){
			return Node(s + n.s);
		} 
	};
	vector<Node> st;
	int N;	
	LazySegtree(int n) : st(2 * n), N(n) {}
	void push(int u, int l, int r){
		if(st[u].lazy){
			if(l < r){
				st[left(u)].lazy += st[u].lazy;
				st[right(u)].lazy += st[u].lazy;
			}
			st[u].s += st[u].lazy * (r - l + 1);
			st[u].lazy = 0;
		}
	}

	void update(int u, int l, int r, int ll, int rr, lli val){
		push(u,l,r);
		if(l > r or r < ll or l > rr) return;
		if(ll <= l and r <= rr){
			st[u].lazy += val;
			push(u,l,r);
			return;
		}
		update(left(u), l, mid, ll, rr, val);
		update(right(u), mid + 1, r, ll, rr, val);
		st[u] = st[left(u)] + st[right(u)];
	}
	Node query(int u, int l, int r, int ll, int rr){
		push(u,l,r);
		if(l > r or r < ll or l > rr) return Node();
		if(ll <= l and r <= rr) return st[u];
		return query(left(u), l, mid, ll, rr) + query(right(u), mid + 1, r, ll, rr);
	}

	void update(int ll, int rr, lli val){
					update(0,0,N-1,ll,rr,val);
	}

	Node query(int ll, int rr){
					return query(0,0,N-1,ll,rr);
	}
};
