#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  edges root;
  t.push_back(root);
  int nodeNum = 0;
  for(int i = 0; i < patterns.size(); i++) {
	  string s = patterns[i];
	  int currNode = 0;
	  for(int j = 0; j < s.size(); j++) {
		  char currentSymbol = s[j];
		  edges::iterator edgeIt = t[currNode].find(currentSymbol);
		  if(edgeIt != t[currNode].end()){
			  currNode = edgeIt->second;
		  }else {
			  t[currNode][currentSymbol] = ++nodeNum;
			  edges temp;
			  t.push_back(temp);
			  currNode = nodeNum;
		  }
	  }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
