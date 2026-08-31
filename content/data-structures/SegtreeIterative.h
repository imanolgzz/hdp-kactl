/**
 * Author: Sebascert 
 * Date: unknown
 * License: CC0
 * Source: me
 * Description: Iterative implementation of segment tree, faster but not easy to modify.
 * Answers Queries [L,R]
 * Time: O(\log N).
 * Status: stress-tested a bit
 */
#pragma once

struct Segtree {
	struct Node {
		lli x;
		Node(lli x = 0) : x(x) {}
		Node operator+(const Node& n) { return Node(x + n.x); }
	};
	int n;
	vector<Node> st;
	Segtree(int n) : n(n), st(2 * n) {}
	void update(int i, lli x) {
		i += n;
		st[i] = Node(x); // update
		for(; i; i /= 2) st[i / 2] = st[i] + st[i ^ 1];
	}
	lli query(int l, int r) { // [l,r]
		Node ll, rr;
		for(l += n, r += n + 1; l < r; l /= 2, r /= 2) {
			if(l & 1) ll = ll + st[l++];
			if(r & 1) rr = st[--r] + rr;
		}
		return (ll + rr).x;
	}
};