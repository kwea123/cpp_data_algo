#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <math.h>
using namespace std;

template <typename V>
struct FlowGraph{

	V s, t;
	map<V, set<V> > adj;
	map<pair<V, V>, int> edgeWeights;

	void addVertex(V v){
		set<V> s;
		adj[v] = s;
	}

	void addEdge(V i, V j, int d){
		if(d==0&&adj[i].count(j))
			adj[i].erase(j);
		else
			adj[i].insert(j);
		pair<V, V> p(i,j);
		edgeWeights[p] = d;
	}

	int edgeWeight(V i, V j){
		pair<V, V> p(i,j);
		return edgeWeights[p];
	}

	set<V> neighbors(V i){
		return adj[i];
	}

	bool bfs(queue<V>& q, map<V, V>& visited){
		q.push(s);
		visited[s] = s;
		while(!q.empty()){
			V j = q.front();
			if(j==t)
				return true;
			q.pop();
			for(V k : neighbors(j))
				if(!visited.count(k)){
					q.push(k);
					visited[k] = j;
				}
		}
		return false;
	}

	int maxflow(){
		int flow = 0;
		while(1){
			queue<V> q;
			map<V, V> visited;
			if(!bfs(q, visited)) // if we cannot go from s to t in the residual graph
				break;
			V parent = t;
			int bottleneck = 1e8; // a large value
			while(parent!=s){
				bottleneck = min(bottleneck, edgeWeight(visited[parent], parent));
				parent = visited[parent];
			}
			flow += bottleneck;
			parent = t;
			while(parent!=s){
				addEdge(visited[parent], parent, edgeWeight(visited[parent], parent)-bottleneck);
				addEdge(parent, visited[parent], edgeWeight(parent, visited[parent])+bottleneck);
				parent = visited[parent];
			}
		}
		return flow;
	}

};

int main() {
	FlowGraph<int> g;
	for(int i=0;i<8;i++)
		g.addVertex(i);
	g.s = 0;
	g.t = 7;
	g.addEdge(0, 1, 10);
	g.addEdge(0, 2, 5);
	g.addEdge(0, 3, 15);
	g.addEdge(1, 2, 4);
	g.addEdge(1, 4, 9);
	g.addEdge(1, 5, 15);
	g.addEdge(2, 3, 4);
	g.addEdge(2, 5, 8);
	g.addEdge(3, 6, 16);
	g.addEdge(4, 5, 15);
	g.addEdge(4, 7, 10);
	g.addEdge(5, 6, 15);
	g.addEdge(5, 7, 10);
	g.addEdge(6, 2, 6);
	g.addEdge(6, 7, 10);

	cout<<g.maxflow();

	return 0;
}
