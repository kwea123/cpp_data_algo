#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct Pair{
	string first, second;
	Pair(string first, string second){
		this->first = first;
		this->second = second;
	}

	int hashString(string s){
		int h = 0;
		for (size_t i = 0; i < s.length(); i++)
			h = 31 * h + s[i];
		return h;
	}

	int hash() {
		return hashString(this->first) + hashString(this->second);
	}

	bool operator==(const Pair& b) const{
		return first==b.first && second==b.second;
	}

};



struct Bucket{
	Pair* key;
	vector<string>* value;
	Bucket* next;

	Bucket(Pair* key, vector<string>* value, Bucket* next){
		this->key = key;
		this->value = value;
		this->next = next;
	}

	static vector<string>* get(Bucket* b, Pair* k){
		for(;b!=NULL;b=b->next)
			if(*(b->key)==*k)
				return b->value;
		return NULL;
	}

};


struct HashTable{
	static const int M = 5003;
	Bucket** buckets;
	HashTable(){
		buckets = new Bucket*[M];
		for(int i=0;i<M;i++) //remember to set to null
			buckets[i]=NULL;
	}

	void add(Pair* key, vector<string>* values){
		int i = (key->hash() & 0x7fffffff) % M; //mask the sign bit to avoid negative
		buckets[i] = new Bucket(key, values, buckets[i]);
	}

	vector<string>* get(Pair* key) {
		int i = (key->hash() & 0x7fffffff) % M;
		return Bucket::get(buckets[i], key);
	}


};

string randomElement(vector<string>* v) {
	int i = rand() % v->size();
	return v->at(i);
}

/* HOMEWORK */

struct IC{
	int i;
	set<int> c;
	IC(int i, set<int> c){
		this->i = i;
		this->c = c;
	}

	bool operator==(const IC& b) const{
		return i==b.i && c==b.c;
	}

	bool operator<(const IC& b) const{
		return i<b.i && c<b.c;
	}
};

int N = 15;
int matrix[15][15];
map<set<int>, int> m;

int main() {

	/* GENERATE TEXT */
//	srand(time(NULL));
//
//	HashTable* ht = new HashTable();
//
//	ifstream fin("text.txt");
//	string s, first, second;
//	int total = 0;
//	while( fin >> s ){
//		if(total==0)
//			first = s;
//		else if(total==1)
//			second = s;
//		else{
//			Pair* p = new Pair(first, second);
//			vector<string>* l = ht->get(p);
//			if(l==NULL){
//				l = new vector<string>();
//				ht->add(p, l);
//			}
//			l->push_back(s);
//			// update first and second
//			first = second;
//			second = s;
//		}
//		total++;
//	}

	// count occurrence
//	Pair* p = new Pair("it", "was");
//	vector<string>* l = ht->get(p);
//	for(auto x : *l){
//		cout<<x<<endl;
//	}
//	cout<<l->size();

	// sample a sentence
//	int len = 20;
//	first = "he";
//	second = "was";
//	cout<<first<<" "<<second;
//	for(int i=0;i<len-2;i++){
//		Pair* p = new Pair(first, second);
//		vector<string>* l = ht->get(p);
//		string next = randomElement(l);
//		first = second;
//		second = next;
//		cout<<" "<<next;
//	}

	/* FIBO */
//	unordered_map<int, long long> m;
//	m[0] = 0;
//	m[1] = 1;
//	for(int i=2;i<=100;i++){
//		m[i] = m[i-2] + m[i-1];
//	}
//	cout<<m[80];


	/* HOMEWORK */
//	ifstream fin("matrix.txt");
//	for(int i=0;i<N;i++)
//		for(int j=0;j<N;j++)
//			fin>>matrix[i][j];
//
//	set<int> s;
//	map<set<int>, int> newM;
//	m[s] = 0;
//	int t = 0;
//	for(int k=0;k<N;k++){
//		newM.clear();
//		for(auto it : m){
//			for(int i=0;i<N;i++){
//				set<int> scopy = it.first;
//				if(!scopy.count(i)){
//					scopy.insert(i);
//					newM[scopy] = max(newM[scopy], matrix[N-k-1][i] + it.second);
//				}
//			}
//		}
//		m = newM;
//	}
//	for(auto it : m)
//		cout<<it.second<<endl;
//	cout<<"number of ops : "<<t<<endl;

	return 0;

}
