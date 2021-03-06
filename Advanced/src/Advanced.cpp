#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
using namespace std;

struct BIT{
	int N;
	int* tree;

	BIT(int N){
		this->N = N;
		this->tree = new int[N+1]();
	}

	void add(int idx, int val){ //adds val to a[idx]
	    while (idx <= N){
	        tree[idx] += val;
	        idx += (idx & -idx);
	    }
	}

	int cumulativeSum(int idx){ //returns a[1]+...+a[idx]
		int sum = 0;
		while (idx > 0){
			sum += tree[idx];
			idx -= (idx & -idx);
		}
		return sum;
	}

	int rangeSum(int l, int r){ //returns a[l]+...+a[r]
		if(l>r)
			return cumulativeSum(l) - cumulativeSum(r-1);
		return cumulativeSum(r) - cumulativeSum(l-1);
	}

	int get(int idx){ //get a[idx]
		int sum = tree[idx];
		if (idx > 0){
		    int z = idx - (idx & -idx);
		    idx--;
		    while (idx != z){
		        sum -= tree[idx];
		        idx -= (idx & -idx);
		    }
		}
		return sum;
	}

};

struct BIT_RMQ{
	int N, n; //N=tree size, n=array size
	int* tree;
	int* a;

	void constructRec(int* a, int l, int r, int idx){ //construct tree recursively for a[l..r]
		if(l==r){ //if there's only one element
			tree[idx] = l;
			return;
		}

		int m = l + (r-l)/2;
		constructRec(a, l, m, 2*idx);
		constructRec(a, m+1, r, 2*idx+1);
		if(a[tree[2*idx]]<=a[tree[2*idx+1]])
			tree[idx] = tree[2*idx];
		else
			tree[idx] = tree[2*idx+1];
	}

	BIT_RMQ(int n, int* a){ //construct BIT for an array of size n (copy), for RMQ

		this->a = new int[n];
		for(int i=0;i<n;i++)
			this->a[i] = a[i];
		this->n = n;

		int h = (int)(ceil(log2(n))); //height of segment tree
		this->N = 2*(int)pow(2, h) - 1; //maximum size of segment tree
		this->tree = new int[this->N+1]();
		for(int i=0;i<=this->N;i++) //initialise everything to -1
			this->tree[i] = -1;

		constructRec(a, 0, n-1, 1); //construct tree from idx = 1 (root)
	}

	int RMQRec(int tl, int tr, int ql, int qr, int idx){ //return min index of a[ql..qr] from tree[tl..tr], idx=index of current node
		if(ql<=tl&&qr>=tr) //if the tree segment is included in the query segment
			return tree[idx];
		if(qr<tl||ql>tr) //if the query segment is outside the tree segment
			return -1;
		int m = tl + (tr-tl)/2;
		int i1 = RMQRec(tl, m, ql, qr, 2*idx);
		int i2 = RMQRec(m+1, tr, ql, qr, 2*idx+1);
		if(i1==-1)
			return i2;
		if(i2==-1)
			return i1;
		if(a[i1]<=a[i2])
			return i1;
		return i2;
	}

	int RMQ(int ql, int qr){ //return min index for a[ql..qr]
		if(ql>qr)
			return RMQRec(0, n-1, qr, ql, 1);
		return RMQRec(0, n-1, ql, qr, 1);
	}

	/* EXERCISE */
	void updateRange(int l, int r, int i, int idx){
		if(l==r) //if l==r (==i), nothing to do
			return;
		if(i<l||i>r) //i not in range, nothing to modify
			return;
		int m = l + (r-l)/2;
		updateRange(l, m, i, 2*idx);
		updateRange(m+1, r, i, 2*idx+1);
		if(a[tree[2*idx]]<=a[tree[2*idx+1]])
			tree[idx] = tree[2*idx];
		else
			tree[idx] = tree[2*idx+1];
	}

	void update(int i, int newVal){ //assign a[i] = newVal, update the tree
		a[i] = newVal;
		updateRange(0, n-1, i, 1);
	}
};

struct Tree{
	int value;
	vector<Tree*> children;

	Tree(int value){
		this->value = value;
	}

	void addChild(Tree* child){
		children.push_back(child);
	}

};

vector<int> eulerTour(Tree* t){
	vector<int> v;
	v.push_back(t->value);
	if(t->children.size()==0) //if no children
		return v;
	for(Tree* child : t->children){
		vector<int> vc = eulerTour(child);
		v.insert(v.end(), vc.begin(), vc.end());
		v.push_back(t->value);
	}
	return v;
}

vector<int> levelTour(Tree* t, int l){
	vector<int> v;
	v.push_back(l);
	if(t->children.size()==0) //if no children
		return v;
	for(Tree* child : t->children){
		vector<int> vc = levelTour(child, l+1);
		v.insert(v.end(), vc.begin(), vc.end());
		v.push_back(l);
	}
	return v;
}

vector<int> occurrence(vector<int> eulerTour, int n){ //n=number of nodes
	vector<int> v(n+1);
	int pos=1;
	for(int x:eulerTour)
		v[x] = v[x]?min(v[x], pos++):(pos++);
	return v;
}

int LCA(vector<int> L, vector<int> E, vector<int> H, int t1, int t2){
	int* La = &L[0];
	int N = (int)L.size();
	BIT_RMQ bit_rmq = BIT_RMQ(N, La);
	return E[bit_rmq.RMQ(H[t1], H[t2])];
}


int main() {

	/* BIT */
//	int N = 50000;
//	BIT bit = BIT(N);
//
//	clock_t t1 = clock();
//
//	for(int i=1;i<=N;i++)
//		bit.add(i, i);
//	for(int i=1;i<N;i++)
//		bit.cumulativeSum(i);
//
//	clock_t t2 = clock();
//	cout<<"BIT takes : "<<t2 - t1<<" clock cycles."<<endl;
//
//	int* a = new int[N+1]();
//	int sum = 0;
//	for(int i=1;i<=N;i++)
//		a[i] = i;
//	for(int i=1;i<N;i++){
//		sum = 0;
//		for(int j=1;j<=i;j++)
//			sum += a[j];
//	}
//
//	cout<<"Array takes : "<<clock() - t2<<" clock cycles."<<endl;

	/* RMQ */
//	int a[10] = {2, 4, 3, 1, 6, 7, 8, 9, 1, 7};
//	BIT_RMQ bit_rmq = BIT_RMQ(10, a);
//	cout<<bit_rmq.RMQ(2, 7)<<endl;
//	cout<<bit_rmq.RMQ(5, 9)<<endl;
//	bit_rmq.update(8, 10);
//	cout<<bit_rmq.RMQ(5, 9)<<endl;

	/* LCA */
	int N = 13;
	Tree** tree = new Tree*[N+1];
	for(int i=1;i<=N;i++)
		tree[i] = new Tree(i);
	tree[10]->addChild(tree[12]);
	tree[10]->addChild(tree[13]);
	tree[7]->addChild(tree[10]);
	tree[7]->addChild(tree[11]);
	tree[6]->addChild(tree[8]);
	tree[6]->addChild(tree[9]);
	tree[3]->addChild(tree[5]);
	tree[3]->addChild(tree[6]);
	tree[3]->addChild(tree[7]);
	tree[1]->addChild(tree[2]);
	tree[1]->addChild(tree[3]);
	tree[1]->addChild(tree[4]);

	vector<int> L = levelTour(tree[1], 0);
	vector<int> E = eulerTour(tree[1]);
	vector<int> H = occurrence(E, N);

	int t1 = 9, t2 = 12;

	cout<<"The LCA of "<<t1<<" and "<<t2<<" is "<<LCA(L, E, H, t1, t2)<<endl;

	return 0;
}
