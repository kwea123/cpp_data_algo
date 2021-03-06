#include <iostream>
#include <time.h> //set time seed
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <map>
using namespace std;

void Knuth(int* a, int n){
	for(int i=1;i<n;i++){
		int j = rand()%(i+1); // j in 0..i
		int tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
	}
}

void insertionSort(int* a, int n) {
	for (int i=1; i<n; i++) {
		int v = a[i], j = i;
		for(;0<j && v<a[j-1];j--)
			a[j] = a[j-1];
		a[j] = v;
	}
}

void merge(int* a1, int* a2, int l, int m, int r){
	int i = l, j = m;
	for (int k = l; k < r; k++)
	if (i < m && (j == r || a1[i] <= a1[j]))
		a2[k] = a1[i++];
	else
		a2[k] = a1[j++];
}

void mergesortrec(int* a, int* tmp, int l, int r){
	if(l>=r-1)
		return;
	int m = l + (r-l)/2; //avoid r+l overflow
	mergesortrec(a, tmp, l, m);
	mergesortrec(a, tmp, m, r);
	for(int i=l;i<r;i++)
		tmp[i] = a[i];
	merge(tmp, a, l, m, r);
}

void mergeSort(int* a, int n){
	mergesortrec(a, new int[n], 0, n);
}

void split(list<int> l1, list<int>& l2, list<int>& l3){
	int i=0;
	while(!l1.empty()){
		if(i==0)
			l2.push_back(l1.front());
		else
			l3.push_back(l1.front());
		i = 1-i;
		l1.pop_front();
	}
}

list<int> merge(list<int> l1, list<int> l2){
	list<int> res;
	while(!l1.empty()&&!l2.empty()){
		int a1 = l1.front();
		int a2 = l2.front();
		if(a1<a2){
			l1.pop_front();
			res.push_back(a1);
		} else {
			l2.pop_front();
			res.push_back(a2);
		}
	}
	if(l1.empty()){
		for(int a2 : l2)
			res.push_back(a2);
	} else if(l2.empty()){
		for(int a1 : l1)
			res.push_back(a1);
	}
	return res;
}

list<int> mergeSort(list<int> l){
	if(l.size()==1)
		return l;
	list<int> l2, l3;
	split(l, l2, l3);
	l2 = mergeSort(l2);
	l3 = mergeSort(l3);
	return merge(l2, l3);
}

void swap(int* a, int i, int j){
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

int partition(int* a, int l, int r){
	int p = a[l], m = l;
	for (int i=l+1; i<r; i++)
		if(a[i]<p)
			swap(a, i, ++m);
	swap(a, l, m);
	return m;
}

void quickrec(int* a, int l, int r){
	if(l>=r-1)
		return;
	int m = partition(a, l, r);
	quickrec(a, l, m);
	quickrec(a, m+1, r);
}

void quickSort(int* a, int n){
	quickrec(a, 0, n);
}

void dutchFlag(int* a, int n){
	map<int, int> m;
	for(int i=0;i<n;i++)
		m[a[i]]++;
	int i = 0;
	for(auto it:m)
		for(int j=0;j<it.second;j++)
			a[i++] = it.first;
}

int main() {
	srand(time(NULL));

	/* KNUTH SHUFFLE */
//	int a[10] = {0,1,2,3,4,5,6,7,8,9};
//	Knuth(a, 10);
//	cout<<"Knuth shuffle!"<<endl;
//	for(int i=0;i<10;i++)
//		cout<<a[i]<<" ";
//	cout<<endl;

	/* INSERTION SORT */
//	insertionSort(a, 10);
//	cout<<"Insertion sort!"<<endl;
//	for(int i=0;i<10;i++)
//		cout<<a[i]<<" ";
//	cout<<endl;

	/* MERGE SORT */
//	cout<<"Merge sort!"<<endl;
//	mergeSort(a, 10);
//	for(int i=0;i<10;i++)
//		cout<<a[i]<<" ";
//	cout<<endl;

	/* MERGE SORT LIST */
//	list<int> l;
//	l.push_back(5);
//	l.push_back(1);
//	l.push_back(6);
//	l.push_back(10);
//	l.push_back(5);
//	l.push_back(4);
//	l.push_back(2);
//
//	l = mergeSort(l);
//
//	for(int i:l)
//		cout<<i<<" ";
//	cout<<endl;

	/* QUICK SORT */
//	cout<<"Quick sort!"<<endl;
//	quickSort(a, 10);
//	for(int i=0;i<10;i++)
//		cout<<a[i]<<" ";
//	cout<<endl;

//	sort(a, a+10);
//	for(int i=0;i<10;i++)
//		cout<<a[i]<<" ";
//	cout<<endl;

	/* DUTCH FLAG */
	int a[10] = {0,1,0,1,0,2,2,1,2,2};
	dutchFlag(a, 10);
	for(int i=0;i<10;i++)
		cout<<a[i]<<" ";
	cout<<endl;

	return 0;

}
