#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;
#define psi pair<string,int>
#define f first
#define s second
#define mp make_pair
#define ffor(i,n) for(i = 0; i < n; i++)
#define rfor(i,n) for(i = n; i >= 0; i--)

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

bool comp(const psi& l, const psi& r) {
	return l.f < r.f;
}
vector<int> BuildSuffixArray(const string& text) {
  vector<int> result;
  // Implement this function yourself
  vector<psi> suffixes;
  for(int i = 0; i < text.size(); i++) {
		suffixes.push_back(mp(text.substr(i),i));
	}
	sort(suffixes.begin(), suffixes.end(), comp);
	for(psi tt : suffixes) {
		result.push_back(tt.s);
	}
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
