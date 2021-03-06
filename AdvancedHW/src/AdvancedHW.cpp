#include <stdlib.h>
#include <iostream>
using namespace std;

int N = 8;

bool check(int* col, int r){
	for(int q=0;q<r;q++)
		if(col[q]==col[r]||abs(col[q]-col[r])==r-q)
			return false;
	return true;
}

int countSolutions1(int* col, int r){
	if(r==N)
		return 1;
	int res = 0;
	for(int c=0;c<N;c++) {
		col[r] = c;
		if (check(col, r))
			res += countSolutions1(col, r + 1);
	}
	return res;
}

int countSolutionsRec(int a, int b, int c) {
	if (a == 0) return 1;
	int f = 0;
	int e; //fill in here
	while (e != 0) {
		int d; //fill in here
		f += countSolutionsRec(??,??,??); //fill in a, b, c here
		e -= d;
	}
	return f;
}

int countSolutions2(int n) {
	return countSolutionsRec(??, 0, 0); //fill in a here
}

int main() {
//	int* col = new int[N]();
//	cout<<"Number of solutions for "<<N<<" queens : "<<countSolutions1(col, 0)<<endl;

	cout<<"Number of solutions for "<<N<<" queens : "<<countSolutions2(N)<<endl;

	return 0;
}
