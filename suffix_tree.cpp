#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

#define pi pair<int,int>
#define f first
#define s second
#define mp make_pair

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.

struct Node {
	vector<Node*> nextNode;
	vector<pi> edges;
};

// return same charachter numbers 
int getCommanStringLength(const string& text, int stp1, int stp2, int stringLen) {
	
	int sameChar = 0;
	
	while(text[stp1+sameChar] == text[stp2+sameChar]) {
		sameChar++;
		if(sameChar == stringLen || stp1 + sameChar == text.size()) {
			break;
		}
	}
	return sameChar;
}

// please take care orders
void updateTree(Node* root, const string& text, int substringIdx) {
	if(substringIdx >= text.size()) return;
	
	for(int i = 0; i < root->nextNode.size(); i++) {
		int stp1 = root->edges[i].f;
		int commonstr = getCommanStringLength(text, stp1, substringIdx, root->edges[i].s);
		if(commonstr > 0 && commonstr < root->edges[i].s) {
			Node* oldNode = root->nextNode[i];
			Node* newNode = new Node;
			pi partOldEdge = mp(stp1 + commonstr, root->edges[i].s - commonstr);
			pi newEdge = mp(substringIdx + commonstr, text.size() - substringIdx - commonstr);
			Node *middle = new Node;
			middle->nextNode.push_back(oldNode);
			middle->nextNode.push_back(newNode);
			middle->edges.push_back(partOldEdge);
			middle->edges.push_back(newEdge);
			root->nextNode[i] = middle;
			root->edges[i].s = commonstr;
		}else if(commonstr == root->edges[i].s) {
			Node* nextNode = root->nextNode[i];
			updateTree(nextNode, text, substringIdx + commonstr);
			return;
		} else if(commonstr == 0 && i == root->nextNode.size() -1) {
			Node* newNode = new Node;
			pi newEdge = mp(substringIdx, text.size() - substringIdx);
			root->nextNode.push_back(newNode);
			root->edges.push_back(newEdge);
			return;
		}
	}
	Node* nextNode = new Node;
	root->nextNode.push_back(nextNode);
	pi edge = mp(substringIdx, text.size() - substringIdx);
	root->edges.push_back(edge);
	return;
}

void getSubtrings(Node* root, const string& text, vector<string>& result) {
	for(int i = 0; i < root->nextNode.size(); i++) {
		result.push_back(text.substr(root->edges[i].f, root->edges[i].s));
		Node* nextNode = root->nextNode[i];
		getSubtrings(nextNode, text, result);
	}
}
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself
  Node* root = new Node;
  for(int i = 0; i < text.size(); i++) {
		updateTree(root, text, i);
	}
	getSubtrings(root, text, result);
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
