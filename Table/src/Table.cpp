#include <iostream>
#include <stdlib.h> //rand, srand
#include <stdio.h>
#include <string.h>
#include <time.h> //set time seed
#include <ctime> // compute elapsed time
#include <stdexcept>
#include <stack>
#include <vector>
#include <list>

using namespace std;

int sum(int a[], int length) {
	int s = 0;
	for (int i = 0; i < length; i++)
		s += a[i];
	return s;
}

double evalPoly(double a[], int d, double x){ // a of size d+1
	double r = 0.0;
	for(int i=d;i>=0;i--)
		r = a[i]*x + r;
	return r;
}

void shuffle(int a[], int length){
	for(int i=1;i<length;i++){
		int j = rand()%(i+1);
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}

void print_array(int a[], int length){
	for (int i=0; i<length; i++)
		cout<<a[i]<<" ";
}

bool binary_search(int a[], int length, int v){
	int lo = a[0];
	int hi = a[length-1];
	while(lo < hi){
		int mi = lo + (hi-lo)/2; // why do we compute in this way?
		if(v==a[mi])
			return true;
		if(v<a[mi])
			hi = mi-1;
		else
			lo = mi+1;
	}
	return false;
}

int* resizable_array(int total){ // total=the total number of elements we want to add
	int* v = new int[10]; //initialize with size=10
	int length = 10;
	for(int i=0; i<total;i++){
		if(i==length){
			int* oldv = v;
			v = new int[length+1];
			memcpy (v, oldv, length * sizeof(int));
			delete[] oldv; //important!
			length++;
		}
		v[i] = 1;
	}
	return v;
}

int* resizable_array_improved(int total){ // total=the total number of elements we want to add
	int* v = new int[10]; //initialize with size=10
	int length = 10;
	for(int i=0; i<total;i++){
		if(i==length){
			int* oldv = v;
			v = new int[length*2];
			memcpy (v, oldv, length * sizeof(int));
			delete[] oldv; //important!
			length*=2;
		}
		v[i] = 1;
	}
	return v;
}

void stack_example(){
	stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	while(!s.empty()){
		cout<<s.top()<<endl;
		s.pop();
	}

}

void swap_stack(stack<int>& s1, stack<int>& s2){ //remember to pass by ref
	int e1 = s1.top();
	s1.pop();
	int e2 = s2.top();
	s2.pop();
	s1.push(e2);
	s2.push(e1);
}

struct Singly{
	int x;
	Singly* next;
	Singly(int x, Singly* next){
		this->x = x;
		this->next = next;
	}

	int size(){
		int s=1;
		Singly* ptr = this;
		while(ptr->next != NULL){
			ptr = ptr->next;
			s++;
		}
		return s;
	}

	bool contains(int v){
		if(this==NULL)
			return false;
		if(this->x == v)
			return true;
		return this->next->contains(v);
	}

	int get(int i){
		int ii = 0;
		Singly* ptr = this;
		while(ii<i){
			ptr = ptr->next;
			ii++;
			if(ptr==NULL)
				throw invalid_argument("index larger than the length");
		}
		return ptr->x;
	}

	void insert(Singly* s, int i){
		//homework
	}

	void remove(int i){
		//homework
	}
};

bool hasCycle(Singly* s){
	if(s==NULL)
		return false;
	Singly* tortoise = s;
	Singly* hare = s->next;
	while(tortoise != hare){
		if(hare==NULL)
			return false;
		hare = hare->next;
		if(hare==NULL)
			return false;
		hare = hare->next;
		tortoise = tortoise->next;
	}
	return true;
}

int josephus(int n, int m){
	//homework
}

int main() {
	/* ARRAY */
//	srand(time(NULL));
//	int a[] = {1,2,4,5,6,7,10};
//	int length = sizeof(a)/sizeof(*a);
//	shuffle(a, length);
//	print_array(a, length);

//	clock_t begin = clock();
//	resizable_array(100000);
//	clock_t end = clock();
//	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//	cout<<elapsed_secs<<endl;
//
//	begin = clock();
//	resizable_array_improved(100000);
//	end = clock();
//	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//	cout<<elapsed_secs<<endl;

	/* STACK */
//	stack_example();

//	stack<int> s1;
//	stack<int> s2;
//	s1.push(1);
//	s1.push(2);
//	s2.push(3);
//	s2.push(4);
//	cout<<s1.top()<<" "<<s2.top()<<endl;
//	swap_stack(s1, s2);
//	cout<<s1.top()<<" "<<s2.top()<<endl;

	/* LINKED LIST */
//	Singly* s = new Singly(0, NULL);
//	s = new Singly(1, s);
//	s = new Singly(5, s);
//	s = new Singly(3, s);
//	s = new Singly(4, s);
//	cout<<s->size()<<endl;
//	cout<<s->contains(2)<<endl;
//	cout<<s->get(2)<<endl;
////	cout<<s->get(6)<<endl; //exception here

	/* CYCLIC LIST */
	Singly* s4 = new Singly(4, NULL);
	Singly* s2 = new Singly(2, new Singly(3, s4));
	Singly* s0 = new Singly(0, new Singly(1, s2));

	s4->next = s2;

//	cout<<hasCycle(s0)<<endl; //floyd's cycle detection

	return 0;
}
