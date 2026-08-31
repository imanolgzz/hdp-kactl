/**
 * Author: Gusfield
 * Date: Unknown
 * License: CC0
 * Source: Cookie Clickers ICPC Notebook
 * Description: Computes the Z-function where $Z[i]$ is the length of the longest common prefix between $s$ and $s[i \dots n-1]$.
 * Usage:
 *  vector<int> z = z_function(s);
 * Time: $O(N)$
 * Status: Tested
 */
#pragma once

vector<int> z_function(string& s){
	int l=0,r=0,n=s.size();
	vector<int> z(s.size(),0); // z[i] = max k: s[0,k) == s[i,i+k)
	for(int i = 1; i < n; ++i){
		if(i<=r)z[i]=min(r-i+1,z[i-l]);
		while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
		if(i+z[i]-1>r)l=i,r=i+z[i]-1;
	}
	return z;
}