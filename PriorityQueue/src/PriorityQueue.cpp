#include <iostream>
#include <fstream>
#include <queue>
#include <functional>
#include <stdexcept>
#include <unordered_set>
#include <set>
#include <map>
using namespace std;

struct PriorityQueue{
	int* elements;
	int size;

	PriorityQueue(int capacity){
		elements = new int[capacity];
		size = 0;
	}

	bool isEmpty(){
		return size == 0;
	}

	int getMin(){
		if(isEmpty())
			throw exception();
		return elements[0];
	}

	void moveUp(int x, int i) { //add x to the position i and move it up
		while (i > 0) {
			int parent_i = (i - 1) / 2;
			int y = elements[parent_i];
			if (y <= x)
				break;
			elements[i] = y; //insert y to this place
			i = parent_i; //and move the node up, keep comparing
		}
		elements[i] = x;
	}

	void add(int x) {
		moveUp(x, size++);
	}

	void moveDown(int x, int i) { //add x to the position i and move it down
		int n = size;             //remember, we move the bottom right element to i=0
		while (true) {
			int j = 2 * i + 1;
			if (j >= n) //if no left child, no right child either
				break;
			if (j + 1 < n && elements[j] > elements[j + 1]) //if left child > right child, j++, compare the below code
				j++;
			if (x <= elements[j]) //if x is smaller than the bigger of its children, no need to move down anymore
				break;
			elements[i] = elements[j]; //otherwise we need to move down further
			i = j;
		}
		elements[i] = x;
	}

	int removeMin() {
		if (isEmpty())
			throw exception();
		int n = --size;
		int r = elements[0];
		if (n > 0)
			moveDown(elements[n], 0);
		return r;
	}


};

struct cmp
{
    bool operator()(string a, string b)
    {
    	if(a.length()==b.length())
    		return a > b; //alphabetical if same length
        return a.length() > b.length();
    }
};

struct HuffmanTree{

	int freq;
	char c;
	HuffmanTree *left, *right;

	HuffmanTree(char c, int freq){ //leaf
		this->c = c;
		this->freq = freq;
		this->left = NULL;
		this->right = NULL;
	}

	HuffmanTree(HuffmanTree *left, HuffmanTree *right){ //internal node
		this->c = '\0';
		this->left = left;
		this->right = right;
		this->freq = left->freq + right->freq;
	}

	/* HOMEWORK */
	void traverse(string prefix, map<char, string>& m){
		if(left==NULL){ //if leaf
			m[c] = prefix;
			return;
		}
		left->traverse(prefix+"0", m);
		right->traverse(prefix+"1", m);
	}

	char find(string prefix, int i){
		if(left==NULL) //if leaf
			return c;
		if(i==(int)prefix.length())
			throw exception(); //corrupted code
		if(prefix[i]=='0')
			return left->find(prefix, i+1);
		else
			return right->find(prefix, i+1);
	}

	bool operator<(const HuffmanTree& b) const{
		return freq > b.freq; //we want smaller values in front
	}
};

struct comparator
{
  bool operator()(const HuffmanTree* lhs, const HuffmanTree* rhs) const
  {
    return lhs->freq > rhs->freq; //we want smaller values in front
  }
};

int main() {

	/* WIKI TITLE */
//	priority_queue<string, vector<string>, cmp> q; //increasing order
//
//	ifstream fin("enwiki-latest-all-titles");
//	string s;
//	int i = 0;
//	int M = 10;
////	int limit = 1000000; //total = 13644994 titles
//	while( fin >> s ){
//		i++;
//		q.push(s);
//		if(i>M) //remove the first element when size>100
//			q.pop();
////		if(i>=limit)
////			break;
//	}
//
//	cout<<"There are "<<i<<" titles"<<endl;
//
//	while(!q.empty()){
//		cout<<q.top()<<endl;
//		q.pop();
//	}

	/* HUFFMAN TREE */
	string word = "mississippi";

	priority_queue<HuffmanTree*, vector<HuffmanTree*>, comparator> q;
	q.push(new HuffmanTree('i',4));
	q.push(new HuffmanTree('s',4));
	q.push(new HuffmanTree('m',1));
	q.push(new HuffmanTree('p',2));
	while(q.size()>1){
		HuffmanTree* left = q.top();
		q.pop();
		HuffmanTree* right = q.top();
		q.pop();
		q.push(new HuffmanTree(left, right));
	}

	/* HOMEWORK */
	// traverse
	map<char, string> m;
	HuffmanTree* t = q.top();
	t->traverse("", m);
	cout<<"original word : "<<word<<endl;
	for(auto it:m)
		cout<<it.first<<" "<<it.second<<endl;

	// encode
	string encode = "";
	for(char c : word)
		encode+=m[c];
	cout<<"encode : "<<encode<<endl;

	// decode
	int i=0;
	string decode = "";
	while(i<(int)encode.length()){
		char c = t->find(encode, i);
		decode += c;
		i += m[c].length();
	}
	cout<<"decode : "<<decode<<endl;

	return 0;
}
