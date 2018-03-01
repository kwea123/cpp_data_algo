#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

struct Node{
	int rank;
	Node* root;

	Node(){
		this->root = this;
		this->rank = 0;
	}

};

Node* find(Node* x){
	if(x->root!=x){ //path compression
		Node* root = find(x->root);
		x->root = root;
		return root;
	}
	return x;
}

void uni(Node* x, Node* y){
	Node* xRoot = find(x);
	Node* yRoot = find(y);

	if(xRoot==yRoot)
		return;

	if(xRoot->rank < yRoot->rank)
		xRoot->root = yRoot;
	else if(xRoot->rank > yRoot->rank)
		yRoot->root = xRoot;
	else{
		yRoot->root = xRoot;
		xRoot->rank++;
	}
}

set<Node*> classes(set<Node*> s){
	set<Node*> res;
	for(Node* n : s)
		if(!res.count(n->root))
			res.insert(n->root);
	return res;
}

int nClasses(set<Node*> s){
	return classes(s).size();
}

/*---Stone------*/
struct Stone{
	int x,y,rank,liberty,color;
	Stone* root;

	Stone(int x, int y, int color){
		this->x = x;
		this->y = y;
		this->rank = 0;
		this->liberty = 4;
		this->color = color;
		this->root = this;
	}

};

Stone* find(Stone* x){
	if(x->root!=x){ //path compression
		Stone* root = find(x->root);
		x->root = root;
		return root;
	}
	return x;
}

Stone* uni(Stone* x, Stone* y){ //returns the pointer to be delete from representatives
	Stone* xRoot = find(x);
	Stone* yRoot = find(y);

	if(xRoot==yRoot)
		return NULL;

	if(xRoot->rank < yRoot->rank){
		xRoot->root = yRoot;
		return xRoot;
	} else if(xRoot->rank > yRoot->rank){
		yRoot->root = xRoot;
		return yRoot;
	} else{
		yRoot->root = xRoot;
		xRoot->rank++;
		return yRoot;
	}
}

struct Board{
	const static int N = 19;
	Stone* stones[N][N];
	set<Stone*> groups;

	Board(){
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				stones[i][j] = new Stone(i, j, -1); //color = -1 nothing
	}

	vector<Stone*> neighbors(Stone* s){
		vector<Stone*> v;
		if(s->x>0)
			v.push_back(stones[s->x-1][s->y]);
		if(s->y>0)
			v.push_back(stones[s->x][s->y-1]);
		if(s->x<N-1)
			v.push_back(stones[s->x+1][s->y]);
		if(s->y<N-1)
			v.push_back(stones[s->x][s->y+1]);
		return v;
	}

	void putStone(int x, int y, int color){ //color = 0 black 1 white
		Stone* s = stones[x][y];
		s->color = color;
		bool containsNeighbor = false;
		for(Stone* n : neighbors(s))
			if(n->color==s->color){
				Stone* toDelete = uni(n, s);
				groups.erase(toDelete);
				containsNeighbor = true;
			}
		if(!containsNeighbor)
			groups.insert(s);
	}

	int numGroups(int color){
		int n = 0;
		for(Stone* rep : groups)
			if(rep->color==color)
				n++;
		return n;
	}

	void drawBoard(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(stones[i][j]->color==0)
					cout<<"x";
				else if(stones[i][j]->color==1)
					cout<<"o";
				else
					cout<<"+";
			}
			cout<<endl;
		}
	}
};

const int V = 7, E = 11;
struct Edge{
	int a, b, w;
	Edge(int a, int b, int w){
		this->a = a;
		this->b = b;
		this->w = w;
	}
};
bool operator<(Edge e1, Edge e2) {return e1.w < e2.w;}

int p[V];
void initV() {for (int i=0; i<V; i++) p[i] = i;}
int find(int x) {return x == p[x] ? x : (p[x] = find(p[x]));}
void uni(int x, int y) {p[find(x)] = find(y);}

int main() {
//	Node* x1 = new Node();
//	Node* x2 = new Node();
//	Node* x3 = new Node();
//	set<Node*> s;
//	s.insert(x1);
//	s.insert(x2);
//	s.insert(x3);
//	uni(x1,x2);
//	uni(x1,x3);
//	cout<<nClasses(s);

	/* BOARD */
//	int B=0, W=1;
//	Board board = Board();
//
//	board.putStone(1, 0, B);
//	board.putStone(1, 1, B);
//	board.putStone(2, 1, B);
//	board.putStone(3, 1, B);
//	board.putStone(3, 0, B);
//	board.putStone(4, 0, B);
//	board.putStone(1, 4, B);
//	board.putStone(2, 5, B);
//	board.putStone(3, 4, B);
//	board.putStone(3, 6, B);
//	board.putStone(5, 1, B);
//	board.putStone(5, 2, B);
//	board.putStone(5, 3, B);
//	board.putStone(5, 5, B);
//	board.putStone(7, 3, B);
//	board.putStone(8, 3, B);
//	board.putStone(9, 1, B);
//	board.putStone(9, 3, B);
//
//	board.putStone(0, 1, W);
//	board.putStone(0, 2, W);
//	board.putStone(1, 2, W);
//	board.putStone(2, 2, W);
//	board.putStone(2, 3, W);
//	board.putStone(3, 2, W);
//	board.putStone(4, 1, W);
//	board.putStone(4, 2, W);
//	board.putStone(5, 0, W);
//	board.putStone(6, 0, W);
//	board.putStone(7, 1, W);
//
//	board.drawBoard();
//	cout<<"black groups : "<<board.numGroups(B)<<endl;
//	cout<<"white groups : "<<board.numGroups(W)<<endl;

	initV();
	vector<Edge> e;
	e.push_back(Edge(0,1,5));
	e.push_back(Edge(0,5,3));
	e.push_back(Edge(1,2,10));
	e.push_back(Edge(1,4,1));
	e.push_back(Edge(1,6,4));
	e.push_back(Edge(2,3,5));
	e.push_back(Edge(2,6,8));
	e.push_back(Edge(3,4,7));
	e.push_back(Edge(3,6,9));
	e.push_back(Edge(4,5,6));
	e.push_back(Edge(4,6,2));

	sort(e.begin(), e.end()); //sort the edges

	int i, j, totalW=0;
	for (i=0, j=0; i<V-1 && j<E; i++){ //i=V, j=E
		while (find(e[j].a) == find(e[j].b)) //if it forms a cycle (in the same spanning tree)
			j++; //next edge

		uni(e[j].a, e[j].b);

		cout<<e[j].a<<" "<<e[j].b<<endl; //output the edge
		totalW += e[j].w;

		j++; //next edge
	}
	cout<<"Minimum weight : "<<totalW<<endl;

	return 0;
}
