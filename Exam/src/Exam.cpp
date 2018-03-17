#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

vector<string> kdistinct(int k, string s){
	// this function takes an integer k and a string s (lowercase English letters only)
	// the return is a vector containing ALL substrings of s
	// of length k, and whose letters are all distinct.

	// E.g. k = 3, s = "adabrb"
	// the return is ["dab", "abr"] (as a vector)

	// Explanation :
	// the first substring of s (of length k=3) is "ada",
	// but its letters are not all distinct (there are 2 a's)
	// so it's not contained in the returned vector
	// the second substring is "dab", OK
	// the third substring is "abr", OK
	// the last substring is "brb", not all letters are distinct.

	// Requirements :
	// Your program must run in O(n) (n is the length of s)
	// A naive solution runs in O(nk)...

	vector<string> v;
	return v;
}


struct Tree{
	int value;
	Tree* left;
	Tree* right;
	Tree(Tree* left, int value, Tree* right){
		this->value = value;
		this->left = left;
		this->right = right;
	}
};

void inorderTraversal(Tree* t){
	if(t==NULL)
		return;
	inorderTraversal(t->left);
	cout<<t->value;
	inorderTraversal(t->right);
}

void preorderTraversal(Tree* t){
	if(t==NULL)
		return;
	cout<<t->value;
	preorderTraversal(t->left);
	preorderTraversal(t->right);
}

Tree* tree_from_preorder_and_inorder(string preorder, string inorder){
	// this function takes the preorder and inorder traversals of a binary tree
	// assuming that the value of each node is a distinct integer in 0~9
	// (such that each node occupies exactly 1 character for the sake of disambiguation)
	// the return is the (only) tree having the according traversals

	// E.g. preorder = "0136742589", inorder = "6371402859"
	// the return is
	//               0
	//              / \
	//             1   2
	//            / \   \
	//           3   4   5
	//          / \     / \
	//         6   7   8   9

	// Requirements : What's your program's complexity?
	// Hint : To contruct a tree, which method do we often use?

	return NULL;
}

int* dutch_nation_flag_problem_k(int k, int* a, int n){
	// this function takes an integer k and an array a of length n
	// the elements of a are in range 0~(k-1)
	// the return is the sorted array of a

	// E.g. k = 3, a = [0, 2, 1, 1, 2, 0]
	// the return is [0, 0, 1, 1, 2, 2] (as an array)

	// Requirements :
	// Your program must run in O(max(n,k))
	// You MUST NOT use sort() function in STL (which runs slower in this problem : O(nlogn))

	return new int[n];
}

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

	void traverse(string prefix, map<char, string>& m){
		// for q4, fill in here
	}

};

struct comparator
{
  bool operator()(const HuffmanTree* lhs, const HuffmanTree* rhs) const
  {
    return lhs->freq > rhs->freq; //we want smaller values in front
  }
};

string huffman_encode(string text){
	// this function takes a string text, construct the Huffman tree of text, and encode it.
	// the return is the encoded string (of 0's and 1's)

	string encode = "";
	return encode;
}

int main() {

	srand(time(NULL)); // set random seed // irrelevant to the problems

	// question 1.
	cout<<"Q1 : "<<endl;
	vector<string> q1 = kdistinct(4, "cdawgdgsvsbrfsdaaa");
	for(string s:q1)
		cout<<s<<" "; //the answer is ["cdaw", "dawg", "awgd", "dgsv", "vsbr", "sbrf", "brfs", "rfsd", "fsda"]
	cout<<endl;

	// question 2.
	cout<<"Q2 : "<<endl;
	string preorder = "0136742589";
	string inorder = "6371402859";
	Tree* q2 = tree_from_preorder_and_inorder(preorder, inorder);
	preorderTraversal(q2);
	cout<<endl;
	inorderTraversal(q2);
	cout<<endl; // are they equal to the inputs?

	// question 3.
	cout<<"Q3 : "<<endl;
	int n = 1000000, k = 20;
	int* a = new int[n];
	for(int i=0;i<n;i++)
		a[i] = rand()%k;
	int* q3 = dutch_nation_flag_problem_k(k, a, n);
	bool b = true;
	sort(a, a+n); // sort using STL
	for(int i=0;i<n;i++)
		b = b&(a[i]==q3[i]);
	cout<<(b?"correct!":"wrong!")<<endl;

	// question 4.
	cout<<"Q4 : "<<endl;
	ifstream fin("alice.txt");
	string text, s;
	while(fin>>s)
		text += s+' ';

	string q4 = huffman_encode(text);
	cout<<"original size : "<<text.length()<<" bytes"<<endl;
	cout<<"compressed size : "<<q4.length()/8<<" bytes"<<endl;

	return 0;
}
