#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int N = 41;
int pathColor = 8;
int deadEndColor = 9;

struct Cell{

	/* DO NOT MODIFY THIS */

	int x, y;

	Cell(int x, int y){
		this->x = x;
		this->y = y;
	}

	bool operator==(const Cell& b) const{
		return x==b.x && y==b.y;
	}

};

struct Ocean{

	/* DO NOT MODIFY THIS */

	Cell *nemo, *marlin;
	vector<vector<Cell*> > cells;
	vector<string> matrix;
	int** mark; //of size [N][N]

	Ocean(vector<vector<Cell*> > cells, vector<string> matrix){
		this->cells = cells;
		this->matrix = matrix;
		mark = new int*[N];
		for(int i=0;i<N;i++){
			mark[i] = new int[N];
			for(int j=0;j<N;j++){
				mark[i][j] = -1;
				if(matrix[i][j]=='N')
					nemo = cells[i][j];
				if(matrix[i][j]=='M')
					marlin = cells[i][j];
			}
		}
	}

	Cell* west(Cell* c){
		return cells[c->x][c->y-1];
	}

	Cell* south(Cell* c){
		return cells[c->x+1][c->y];
	}

	Cell* east(Cell* c){
		return cells[c->x][c->y+1];
	}

	Cell* north(Cell* c){
		return cells[c->x-1][c->y];
	}

	vector<Cell*> neighbors(Cell* c){ // in order WSEN
		vector<Cell*> v;
		if(c->y>0)
			v.push_back(west(c));
		if(c->x<N-1)
			v.push_back(south(c));
		if(c->y<N-1)
			v.push_back(east(c));
		if(c->x>0)
			v.push_back(north(c));
		return v;
	}

	bool isWall(Cell* c){
		return matrix[c->x][c->y] == '#';
	}

	bool isNemo(Cell* c){
		return *c==*nemo;
	}

	bool isMarlin(Cell* c){
		return *c==*marlin;
	}

	bool isShark(Cell* c){
		return matrix[c->x][c->y] == 'S';
	}

	void setMark(Cell* c){
		mark[c->x][c->y] = 0;
	}

	void setMark(Cell* c, int v){
		mark[c->x][c->y] = v;
	}

	void unMark(Cell* c){
		mark[c->x][c->y] = -1;
	}

	int getMark(Cell* c){
		return mark[c->x][c->y];
	}

	bool isMarked(Cell* c){
		return mark[c->x][c->y] >= 0;
	}

	void printMarked(){ //print out the paths in the ocean
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(matrix[i][j]=='#'||matrix[i][j]=='N'||matrix[i][j]=='M'||matrix[i][j]=='S')
					cout<<matrix[i][j];
				else if(mark[i][j]==pathColor)
					cout<<'.';
				else if(mark[i][j]>0)
					cout<<'X';
				else
					cout<<' ';
			}
			cout<<endl;
		}
	}

	/* DEFINES THE METHODS TO BE COMPLETED LATER */
	bool dfsFrom(Cell*); //return true if there is a path from c to nemo
	void dfs(); //performs a dfs search
	void bfs(); //performs a bfs search
	void bfsWithDistance(); //bfs with distance
	void bfsWithShortestPath(); //bfs that also marks (one of) the shortest path
	void backTrack(); //auxiliary method for bfsWithShortestPath()
	void avoidSharks(); //bfs that encounters the least number of sharks

};

Ocean readFile(string fileName){

	/* DO NOT MODIFY THIS */

	vector<vector<Cell*> > cells(N, vector<Cell*>(N));
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			cells[i][j] = new Cell(i, j);

	string s;
	vector<string> matrix;
	ifstream fin(fileName); //41*41
	while(getline(fin,s))
		matrix.push_back(s);
	fin.close();

	Ocean* o = new Ocean(cells, matrix);
	return *o;
}

ostream& operator<<(ostream &strm, const Cell &c) { //Cell tostring
	return strm<<"("<<c.x<<" "<<c.y<<")";
}

ostream& operator<<(ostream &strm, const Ocean &o) { //Ocean tostring
	for(string x : o.matrix)
		strm<<x<<endl;
	return strm;
}

/* METHODS TO BE COMPLETED */

bool Ocean::dfsFrom(Cell* c){
	return false;
}

void Ocean::dfs(){

}

void Ocean::bfs(){

}

void Ocean::bfsWithDistance(){

}

const int WEST = 1, SOUTH = 2, EAST = 3, NORTH = 4;

void Ocean::backTrack(){

}

void Ocean::bfsWithShortestPath(){

}

void Ocean::avoidSharks(){

}


int main() {

	Ocean o = readFile("o1.txt");
//	Ocean o = readFile("o2.txt"); //o2 and o3 are for the second part
//	Ocean o = readFile("o3.txt");

	/* TEST THIS LINE TO SEE THE OCEAN */
	cout<<o<<endl;

	/* HOMEWORK TO BE COMPLETED */

	/* FIRST PART */
	/* DFS */
//	o.dfs();
//	o.printMarked();

	/* BFS */
//	o.bfs();
//	o.printMarked();

	/* BFS WITH DISTANCE */
//	o.bfsWithDistance();
//	cout<<"Distance to Nemo : "<<o.getMark(o.nemo)<<endl; //true = 104

	/* BFS WITH SHORTEST PATH */
//	o.bfsWithShortestPath();
//	o.printMarked();

	/* SECOND PART */
//	o.avoidSharks();
//	o.printMarked();


	return 0;
}
