//#include <iostream>
//#include <fstream>
//#include <map>
//#include <set>
//#include <queue>
//#include <vector>
//#include <string>
//using namespace std;
//
//template <typename V>
//struct Node{
//
//	V node;
//	int dist;
//
//	Node(V node, int dist){
//		this->node = node;
//		this->dist = dist;
//	}
//
//	bool operator<(const Node& b) const{
//		return dist > b.dist; //we want smaller values in front
//	}
//};
//
//template <typename V>
//struct Graph{
//
//	map<V, set<V> > adj;
//	map<pair<V, V>, int> edgeWeights;
//
//	void addVertex(V v){
//		set<V> s;
//		adj[v] = s;
//	}
//
//	void addEdge(V i, V j, int d){
//		adj[i].insert(j);
//		pair<V, V> p(i,j);
//		edgeWeights[p] = d;
//	}
//
//	bool hasEdge(V i, V j){
//		return edgeWeight(i, j)>0;
//	}
//
//	void removeEdge(V i, V j){
//		adj[i].erase(j);
//	}
//
//	int edgeWeight(V i, V j){
//		pair<V, V> p(i,j);
//		return edgeWeights[p];
//	}
//
//	set<V> vertices(){
//		set<V> s;
//		for(auto it : adj)
//			s.insert(it.first);
//		return s;
//	}
//
//	set<V> neighbors(V i){
//		return adj[i];
//	}
//
//	int shortestPath(V source, V destination, map<V, int>& distances){
//		set<V> visited;
//		priority_queue<Node<V>> q;
//		distances[source] = 0;
//		q.push(Node<V>(source, 0));
//		int i=0;
//		while(!q.empty()){
//			Node<V> n = q.top();
//			q.pop();
//			if(n.node==destination)
//				break;
//			if(visited.count(n.node))
//				continue;
//			visited.insert(n.node);
//			for(V w : neighbors(n.node)){
//				int d = n.dist + edgeWeight(n.node, w);
//				// is it better then distances[w]?
//				if(!distances.count(w)||d<distances[w]){ //yes, it's shorter
//					distances[w] = d;
//					q.push(Node<V>(w, d));
//				}
//			}
//			i++;
//		}
//		return i;
//	}
//
//	void shortestPath(V source, V destination){
//		map<V, int> distances;
//		int i = shortestPath(source, destination, distances);
//		cout<<"Distance : "<<distances[destination]<<" in "<<i<<" steps."<<endl;
//	}
//
//	void shortestPath_bi(V, V);
//	void shortestPath_bi_correct(V, V);
//
//};
//
//template <typename V>
//void Graph<V>::shortestPath_bi(V source, V destination){
//	set<V> visitedF, visitedB;
//	map<V, int> distancesF, distancesB;
//	priority_queue<Node<V> > qF, qB;
//	distancesF[source] = 0;
//	distancesB[destination] = 0;
//	Node<V> last(source, 0);
//	qF.push(last);
//	qB.push(Node<V>(destination, 0));
//
//	int i=0;
//	while(!visitedF.count(last.node)||!visitedB.count(last.node)){
//		if(i%2==0&&!qF.empty()){
//			last = qF.top();
//			qF.pop();
//			if(visitedF.count(last.node))
//				continue;
//			visitedF.insert(last.node);
//			for(V w : neighbors(last.node)){
//				int d = last.dist + edgeWeight(last.node, w);
//				// is it better then distances[w]?
//				if(!distancesF.count(w)||d<distancesF[w]){ //yes, it's shorter
//					distancesF[w] = d;
//					qF.push(Node<V>(w, d));
//				}
//			}
//		} else if(i%2==1&&!qB.empty()){
//			last = qB.top();
//			qB.pop();
//			if(visitedB.count(last.node))
//				continue;
//			visitedB.insert(last.node);
//			for(V w : neighbors(last.node)){
//				int d = last.dist + edgeWeight(last.node, w);
//				// is it better then distances[w]?
//				if(!distancesB.count(w)||d<distancesB[w]){ //yes, it's shorter
//					distancesB[w] = d;
//					qB.push(Node<V>(w, d));
//				}
//			}
//		}
//		i++;
//	}
//	int d = distancesF[last.node]+distancesB[last.node];
//	cout<<"Distance : "<<d<<" in "<<i<<" steps."<<endl;
//}
//
//template <typename V>
//void Graph<V>::shortestPath_bi_correct(V source, V destination){
//	set<V> visitedF, visitedB;
//	map<V, int> distancesF, distancesB;
//	priority_queue<Node<V> > qF, qB;
//	distancesF[source] = 0;
//	distancesB[destination] = 0;
//	Node<V> last(source, 0);
//	qF.push(last);
//	qB.push(Node<V>(destination, 0));
//
//	int i=0;
//	while(!visitedF.count(last.node)||!visitedB.count(last.node)){
//		if(i%2==0&&!qF.empty()){
//			last = qF.top();
//			qF.pop();
//			if(visitedF.count(last.node))
//				continue;
//			visitedF.insert(last.node);
//			for(V w : neighbors(last.node)){
//				int d = last.dist + edgeWeight(last.node, w);
//				// is it better then distances[w]?
//				if(!distancesF.count(w)||d<distancesF[w]){ //yes, it's shorter
//					distancesF[w] = d;
//					qF.push(Node<V>(w, d));
//				}
//			}
//		} else if(i%2==1&&!qB.empty()){
//			last = qB.top();
//			qB.pop();
//			if(visitedB.count(last.node))
//				continue;
//			visitedB.insert(last.node);
//			for(V w : neighbors(last.node)){
//				int d = last.dist + edgeWeight(last.node, w);
//				// is it better then distances[w]?
//				if(!distancesB.count(w)||d<distancesB[w]){ //yes, it's shorter
//					distancesB[w] = d;
//					qB.push(Node<V>(w, d));
//				}
//			}
//		}
//		i++;
//	}
//	int d = distancesF[last.node]+distancesB[last.node];
//	// pq to vector
//	vector<V> qBv, qFv;
//	while(!qF.empty()){
//		Node<V> n = qF.top();
//		qF.pop();
//		if(visitedB.count(n.node))
//			qFv.push_back(n.node);
//	}
//	while(!qB.empty()){
//		Node<V> n = qB.top();
//		qB.pop();
//		if(visitedF.count(n.node))
//			qBv.push_back(n.node);
//	}
//
//	for(V i : qBv)
//		for(V j : qFv)
//			if(hasEdge(i,j))
//				d = min(d, distancesF[i]+edgeWeight(i,j)+distancesB[j]);
//
//	cout<<"Distance : "<<d<<" in "<<i<<" steps."<<endl;
//}
//
//void readGraph(string fileName, Graph<int>& g){
//	ifstream fin(fileName);
//	string s;
//	int i, j, k;
//	cout<<"reading graph...    "<<endl;
//	while(fin>>s){
//		if(s=="p"){
//			fin>>s>>i>>j;
//			for(int a=1;a<=i;a++)
//				g.addVertex(a);
//		}
//		else{
//			fin>>i>>j>>k;
//			g.addEdge(i, j, k);
//		}
//	}
//	cout<<"done."<<endl<<endl;
//	fin.close();
//}
//
//int main() {
//	Graph<int> g;
//
//	readGraph("data/USA-road-d-NY.gr", g);
//
//	int source = 190635, destination = 187333;
////	int source = 190637, destination = 187334;
//
//	g.shortestPath(source, destination); //forward search
//	g.shortestPath(destination, source); //backward search
//	g.shortestPath_bi(source, destination); //bidirectional search
//	g.shortestPath_bi_correct(source, destination); //bidirectional search
//
//
//	return 0;
//}
