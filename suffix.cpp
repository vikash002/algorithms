#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

int main() {
	string s;
	vector<string> vv;
	map<string, int> m;
	cin >> s;
	for(int i = 0; i < s.length(); i++) {
		m[s.substr(i, s.length() -1)] = i;
		vv.push_back(s.substr(i, s.length() -1));
	}
	sort(vv.begin(), vv.end());
	for(int i = 0; i < vv.size(); i++) {
		cout << m[vv[i]] << endl;
	}
	return 0;
}
