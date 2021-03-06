#include <iostream>
#include <map>
#include <set>
#include <queue>
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

	Graph(){
		;
	}

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
		return find(adj[i].begin(), adj[i].end(), j) != adj[i].end();
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

	void shortestPath(V source, map<V, int>& distances){
		set<V> visited;
		priority_queue<Node<V>> q;
		distances[source] = 0;
		q.push(Node<V>(source, 0));
		while(!q.empty()){
			Node<V> n = q.top();
			q.pop();
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
		}
	}

	void shortestPath(V source, map<V, V>& antecedents, map<V, int>& distances){
		set<V> visited;
		priority_queue<Node<V>> q;
		distances[source] = 0;
		q.push(Node<V>(source, 0));
		antecedents[source] = source;
		while(!q.empty()){
			Node<V> n = q.top();
			q.pop();
			if(visited.count(n.node))
				continue;
			visited.insert(n.node);
			for(V w : neighbors(n.node)){
				int d = n.dist + edgeWeight(n.node, w);
				// is it better then distances[w]?
				if(!distances.count(w)||d<distances[w]){ //yes, it's shorter
					distances[w] = d;
					q.push(Node<V>(w, d));
					antecedents[w] = n.node;
				}
			}
		}
	}

};

template <typename V>
void backTrack(V destination, V source, map<V, V> antecedents){
	while(destination!=source){
		cout<<destination;
		destination = antecedents[destination];
	}
//	V v = destination;
//	cout<<v;
//	while(v!=source){
//		V ante = antecedents[v];
//		cout<<"<-"<<ante;
//		v = ante;
//	}
}

int main() {
	Graph<int> g;
	for(int i=0;i<5;i++)
		g.addVertex(i);
	g.addEdge(0, 3, 1);
	g.addEdge(1, 0, 2);
	g.addEdge(1, 4, 1);
	g.addEdge(2, 1, 4);
	g.addEdge(2, 4, 1);
	g.addEdge(2, 5, 3);
	g.addEdge(0, 3, 1);
	g.addEdge(3, 1, 1);
	g.addEdge(4, 3, 1);
	g.addEdge(4, 5, 1);

	/* DIJKSTRA */
//	map<int, int> distances;
//	g.shortestPath(2, distances);
//
//	for(auto it:distances)
//		cout<<it.first<<" "<<it.second<<endl;

	/* PATH EXTRACTION */
	map<int, int> distances;
	map<int, int> antecedents;
	g.shortestPath(2, antecedents, distances);
	// shortest path to 0 from 2:
	backTrack(0, 2, antecedents);


	return 0;
}
