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

long long** combi(int N){
	long long** dp;
	dp = new long long*[N+1];
	for(int i=0;i<=N;i++)
		dp[i] = new long long[N+1]();
	dp[1][0] = dp[1][1] = 1;
	for(int i=2;i<=N;i++)
		for(int j=0;j<=i;j++)
			dp[i][j] = (j>0?dp[i-1][j-1]:0) + dp[i-1][j];
	return dp;
}

long long choose(long long n, long long k){
	if(k==0)
		return 1;
	return (n * choose(n - 1, k - 1)) / k;
}

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

map<int, int> m;
int f(int i, int c) {
	if (i == N) return 0;
	if (m.count(c)) return m[c];
	int s = 0;
	for (int j = 0; j < N ; j++){
		int cj = 1<<j;
		if (c&cj)
			s = max(s, matrix[i][j] + f(i + 1, c&~cj));
	}
	m[c] = s;
	return s;
}

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
//	fin.close();

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

//	long long **dp = combi(50);
//	cout<<dp[50][25]<<endl;
//
//	cout<<choose(50, 25)<<endl;

	ifstream fin("matrix.txt");
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			fin>>matrix[i][j];
	cout<<f(0, ~(~0 << N));

	return 0;

}
