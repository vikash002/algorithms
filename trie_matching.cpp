#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

typedef vector<Node> trie;

trie build_trie(vector<string>& p) {
	trie t;
	Node root;
	t.push_back(root);
	int nodeNum = 0;
	for(int i = 0; i < p.size(); i++) {
		string s = p[i];
		int currNode = 0;
		for(int j = 0; j < s.length(); j++) {
			int  chIndex = letterToIndex(s[j]);
			int nextNode = t[currNode].next[chIndex];
			if(nextNode != NA) {
				currNode = nextNode;
			}else {
				t[currNode].next[chIndex] = ++nodeNum;
				Node temp;
				t.push_back(temp);
				currNode = nodeNum;
			}
		}
	}
	return t;
}

int prefixMatching(string text, trie &t) {
	char currSymbol = text[0];
	Node currNode = t[0];
	unsigned int letterInt = 0;
	int currSymbolId = letterToIndex(currSymbol);
	while(true) {
		if(currNode.isLeaf()) return 1;
		else if(currNode.next[currSymbolId] != NA) {
			currNode = t[currNode.next[currSymbolId]];
			if(letterInt < text.size() - 1) {
				currSymbol = text[++letterInt];
				currSymbolId = letterToIndex(currSymbol);
			} else {
				if(currNode.isLeaf()) {
					return 1;
				} else {
					return 0;
				}
			}
		}else {
			return 0;
		}
	}
}

vector <int> solve (const string& text, int n, vector <string> patterns)
{
	vector <int> result;
	trie t = build_trie(patterns);
	for(int i = 0; i < text.size(); i++) {
		string newText = text.substr(i, text.length() -1);
		int cp = prefixMatching(newText, t);
		if(cp) {
			result.push_back(i);
		}
	}
	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
