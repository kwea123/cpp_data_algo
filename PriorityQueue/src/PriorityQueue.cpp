#include <iostream>
#include <fstream>
#include <queue>
#include <functional>
#include <stdexcept>
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


int main() {

	priority_queue<string, vector<string>, cmp> q; //increasing order

	ifstream fin("enwiki-latest-all-titles-in-ns0");
	string s;
	int i = 0;
	int M = 10;
	int limit = 1000000; //total = 13644994 titles
	while( fin >> s ){
		i++;
		q.push(s);
		if(i>M) //remove the first element when size>100
			q.pop();
//		if(i>=limit)
//			break;
	}

	cout<<"There are "<<i<<" titles"<<endl;

	while(!q.empty()){
		cout<<q.top()<<endl;
		q.pop();
	}

	return 0;
}
