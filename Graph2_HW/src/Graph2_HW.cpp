#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <string>
using namespace std;

template <typename V>
struct Node{

	V node;
	int dist;

	Node(V node, int dist){
		this->node = node;
		this->dist = dist;
	}

	bool operator<(const Node& b) const{
		return dist > b.dist; //we want smaller values in front
	}
};

template <typename V>
struct Graph{

	map<V, set<V> > adj;
	map<pair<V, V>, int> edgeWeights;

	void addVertex(V v){
		set<V> s;
		adj[v] = s;
	}

	void addEdge(V i, V j, int d){
		adj[i].insert(j);
		pair<V, V> p(i,j);
		edgeWeights[p] = d;
	}

	bool hasEdge(V i, V j){
		return edgeWeight(i, j)>0;
	}

	void removeEdge(V i, V j){
		adj[i].erase(j);
	}

	int edgeWeight(V i, V j){
		pair<V, V> p(i,j);
		return edgeWeights[p];
	}

	set<V> vertices(){
		set<V> s;
		for(auto it : adj)
			s.insert(it.first);
		return s;
	}

	set<V> neighbors(V i){
		return adj[i];
	}

	int shortestPath(V source, V destination, map<V, int>& distances){
		set<V> visited;
		priority_queue<Node<V>> q;
		distances[source] = 0;
		q.push(Node<V>(source, 0));
		int i=0;
		while(!q.empty()){
			Node<V> n = q.top();
			q.pop();
			if(n.node==destination)
				break;
			if(visited.count(n.node))
				continue;
			visited.insert(n.node);
			for(V w : neighbors(n.node)){
				int d = n.dist + edgeWeight(n.node, w);
				// is it better then distances[w]?
				if(!distances.count(w)||d<distances[w]){ //yes, it's shorter
					distances[w] = d;
					q.push(Node<V>(w, d));
				}
			}
			i++;
		}
		return i;
	}

	void shortestPath(V source, V destination){
		map<V, int> distances;
		int i = shortestPath(source, destination, distances);
		cout<<"Distance : "<<distances[destination]<<" in "<<i<<" steps."<<endl;
	}

	/* HOMEWORK TO BE COMPLETED LATER... */
	void shortestPath_bi(V, V);
	void shortestPath_bi_correct(V, V);

};

/* HOMEWORK */
template <typename V>
void Graph<V>::shortestPath_bi(V source, V destination){
	int d=0;
	int i=0;
	cout<<"Distance : "<<d<<" in "<<i<<" steps."<<endl;
}

template <typename V>
void Graph<V>::shortestPath_bi_correct(V source, V destination){
	int i=0;
	int d=0;
	cout<<"Distance : "<<d<<" in "<<i<<" steps."<<endl;
}

void readGraph(string fileName, Graph<int>& g){

	/* DO NOT MODIFY THIS */

	ifstream fin(fileName);
	string s;
	int i, j, k;
	cout<<"reading graph...    "<<endl;
	while(fin>>s){
		if(s=="p"){
			fin>>s>>i>>j;
			for(int a=1;a<=i;a++)
				g.addVertex(a);
		}
		else{
			fin>>i>>j>>k;
			g.addEdge(i, j, k);
		}
	}
	cout<<"done."<<endl<<endl;
	fin.close();
}

int main() {
	Graph<int> g;
	readGraph("data/USA-road-d-NY.gr", g);

	int source = 190635, destination = 187333;
//	int source = 190637, destination = 187334;

	g.shortestPath(source, destination); //forward search
	g.shortestPath(destination, source); //backward search
//	g.shortestPath_bi(source, destination); //bidirectional search
//	g.shortestPath_bi_correct(source, destination); //bidirectional search


	return 0;
}
