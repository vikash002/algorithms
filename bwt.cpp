#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string BWT(const string& text) {
  string result = "";
  vector<string> cyclicText;
  // write your code here
  for(int i = 0; i < text.length(); i++) {
	  string temp = text.substr(i) + text.substr(0, i);
	  cyclicText.push_back(temp);
  }
  sort(cyclicText.begin(), cyclicText.end());
  for(int i = 0; i < cyclicText.size(); i++) {
	  result += cyclicText[i][cyclicText[i].length() -1];
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
