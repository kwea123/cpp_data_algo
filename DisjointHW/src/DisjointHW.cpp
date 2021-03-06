#include <iostream>
#include <vector>
#include <set>
#include <time.h> //set time seed
#include <stdlib.h>
using namespace std;

struct Cell{
	int x, y, rank;
	Cell* root;

	Cell(int x, int y){
		this->x = x;
		this->y = y;
		this->rank = 0;
		this->root = this;
	}

};

Cell* find(Cell* x){
	if(x->root!=x){ //path compression
		Cell* root = find(x->root);
		x->root = root;
		return root;
	}
	return x;
}

void uni(Cell* x, Cell* y){
	Cell* xRoot = find(x);
	Cell* yRoot = find(y);

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

int N = 5;
vector<vector<Cell*> > cells(N, vector<Cell*>(N));
vector<pair<Cell*, Cell*> > pairs;
set<pair<pair<int, int>,pair<int, int> > > noWall;

void init(){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			cells[i][j] = new Cell(i, j);
}

void printLabyrinth(){

	/* DO NOT MODIFY THIS */

	for(int i=0;i<2*N+1;i++){
		for(int j=0;j<2*N+1;j++){
			if(i==0||j==0||i==2*N||j==2*N){ //bounding walls
				if(i==1&&j==0)
					cout<<'S';
				else if(i==2*N-1&&j==2*N)
					cout<<'E';
				else
					cout<<'#';
			} else if(i%2==0&&j%2==0){ //inner nodes
				cout<<'#';
			} else if(j%2==0){ //walls left/right
				int x = (i-1)/2;
				int y = j/2;
				pair<int, int> l(x, y-1), r(x, y);
				pair<pair<int, int>, pair<int, int> > pp(l,r);
				cout<<(noWall.count(pp)?' ':'#');
			} else if(i%2==0){ //wals up/down
				int x = i/2;
				int y = (j-1)/2;
				pair<int, int> u(x-1, y), d(x, y);
				pair<pair<int, int>, pair<int, int> > pp(u,d);
				cout<<(noWall.count(pp)?' ':'#');
			} else{
				cout<<' ';
			}
		}
		cout<<endl;
	}
}

/* HOMEWORK FILL IN THESE THREE METHODS */

void Knuth(){

}

void constructPairs(){

}

void constructNoWalls(){

}

int main() {
	srand(time(NULL));

	init();

	constructPairs();
	Knuth();
	constructNoWalls();

	printLabyrinth();

//	cout<<noWall.size()<<endl;

	return 0;
}
