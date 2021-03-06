#include <iostream>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

struct AdjMatrix{
	int n;
	bool** M;

	AdjMatrix(int n, bool** M){
		this->n = n;
		this->M = M;
	}

	bool hasEdge(int i, int j){
		return M[i][j];
	}

	void addEdge(int i, int j){
		M[i][j] = 1;
	}

	void removeEdge(int i, int j){
		M[i][j] = 0;
	}

	list<int> neighbors(int i){
		list<int> l;
		for(int j=0;j<n;j++)
			if(M[i][j])
				l.push_back(j);
		return l;
	}

};

struct AdjList{
	map<int, list<int> > adj;

	void addEdge(int i, int j){
		adj[i].push_back(j);
	}

	bool hasEdge(int i, int j){
		return find(adj[i].begin(), adj[i].end(), j) != adj[i].end();
	}

	void removeEdge(int i, int j){
		adj[i].remove(j);
	}

	int nVertices(){
		return adj.size();
	}

	int nEdges(int i){
		return adj[i].size();
	}

};

struct AdjSet{

	map<int, set<int> > adj;

	void addEdge(int i, int j){
		adj[i].insert(j);
	}

	bool hasEdge(int i, int j){
		return find(adj[i].begin(), adj[i].end(), j) != adj[i].end();
	}

	void removeEdge(int i, int j){
		adj[i].erase(j);
	}

	set<int> vertices(){
		set<int> s;
		for(auto it : adj)
			s.insert(it.first);
		return s;
	}

	set<int> neighbors(int i){
		return adj[i];
	}

	void dfs(int i, set<int>& visited, int count, map<int, int>& result){ //result stores the depth of discovery
		if(visited.count(i))
			return;
		visited.insert(i);
		result[i] = count++;
		for(int j : neighbors(i))
			dfs(j, visited, count, result);
	}

	void dfs(int i, set<int>& visited){ //stack
		stack<int> st;
		st.push(i);
		while(!st.empty()){
			int j = st.top();
			st.pop();
			if(visited.count(j))
				continue;
			visited.insert(j);
			for(int k : neighbors(j))
				st.push(k);
		}
	}

	bool existPath(int i, int j){
		set<int> visited;
		map<int, int> result;
		dfs(i, visited, 0, result);
		return visited.count(j)>0;
	}

	void dfs(int i, int j, map<int, int>& visited){ //dfs from vertex j, coming from vertex i
		if(visited.count(j))
			return;
		visited[j] = i;
		for(int k : neighbors(j))
			dfs(j, k, visited);
	}

	void bfs(int i, queue<int>& q, set<int>& visited){
		q.push(i);
		visited.insert(i);
		while(!q.empty()){
			int j = q.front();
			q.pop();
			for(int k : neighbors(j))
				if(!visited.count(k)){
					q.push(k);
					visited.insert(k);
				}
		}
	}

	void bfs(int i, queue<int>& q, map<int, int>& distances){
		q.push(i);
		distances[i] = 0;
		while(!q.empty()){
			int j = q.front();
			int d = distances[j];
			q.pop();
			for(int k : neighbors(j))
				if(!distances.count(k)){
					q.push(k);
					distances[k] = d+1;
				}
		}
	}
};



int main() {

//	AdjList g;
//	g.addEdge(0, 3);
//	g.addEdge(1, 0);
//	g.addEdge(1, 4);
//	g.addEdge(2, 4);
//	g.addEdge(2, 5);
//	g.addEdge(3, 1);
//	g.addEdge(4, 3);
//
//	cout<<g.hasEdge(0,3)<<endl;


	AdjSet g;
	g.addEdge(0, 3);
	g.addEdge(1, 0);
	g.addEdge(1, 4);
	g.addEdge(2, 4);
	g.addEdge(2, 5);
	g.addEdge(3, 1);
	g.addEdge(4, 3);

	/* DFS */
//	set<int> visited;
//	map<int, int> result;
//	g.dfs(2, visited, 0, result);
//	for(auto it:result)
//		cout<<it.first<<" "<<it.second<<endl;

//	cout<<g.existPath(2, 1)<<endl;
//	cout<<g.existPath(1, 2)<<endl;

	/* PATH EXTRACTION */
//	map<int, int> visited;
//	g.dfs(-1, 2, visited);
//	for(auto it:visited)
//		cout<<it.first<<" "<<it.second<<endl;

	/* STACK CALL */
//	set<int> visited;
//	g.dfs(1, visited);
//	for(auto it:visited)
//		cout<<it<<endl;

	/* BFS DISTANCE*/
	queue<int> q;
	map<int, int> distances;
	g.bfs(2, q, distances);
	for(auto it:distances)
		cout<<it.first<<" "<<it.second<<endl;

	return 0;
}
