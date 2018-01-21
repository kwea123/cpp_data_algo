#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

struct Tree{
	string value;
	Tree* left;
	Tree* right;
	Tree(Tree* left, string value, Tree* right){
		this->value = value;
		this->left = left;
		this->right = right;
	}
};

void inorderTraversal(Tree* t){
	if(t==NULL)
		return;
	inorderTraversal(t->left);
	cout<<t->value<<" ";
	inorderTraversal(t->right);
}

list<string> inorder(Tree* t){
	list<string> res;
	if(t==NULL)
		return res;
	res = inorder(t->left);
	res.push_back(t->value);
	list<string> r = inorder(t->right);
	res.splice(res.end(), r);
	return res;
}

void inorder(Tree* t, list<string>& res){
	if(t==NULL)
		return;
	inorder(t->left, res);
	res.push_back(t->value);
	inorder(t->right, res);
}

void BFS(Tree* t, list<string>& res){
	queue<Tree*> q;
	q.push(t);
	while (!q.empty())
	{
		Tree* p = q.front(); q.pop();
		res.push_back(p->value);
		if (p->left)  q.push(p->left);
		if (p->right) q.push(p->right);
	}
}

struct BST{
	string value;
	BST* left;
	BST* right;
	BST(BST* left, string value, BST* right){
		this->value = value;
		this->left = left;
		this->right = right;
	}
};

string getMin(BST* b){
	while(b->left!=NULL){
		b = b->left;
	}
	return b->value;
}

bool contains(BST* b, string v){
	while(b != NULL){
		int c = v.compare(b->value);
		if(c==0)
			return true;
		if(c<0){
			b = b->left;
		} else {
			b = b->right;
		}
		//b = c<0?b->left:b->right; //the above if else is equivalent to this line
	}
	return false;
}

BST* add(BST* b, string x){
	if(b==NULL)
		return new BST(NULL, x, NULL);
	int c = x.compare(b->value);
	if(c<0){
		b->left = add(b->left, x);
	} else if(c>0){
		b->right = add(b->right, x);
	}
	//if c==0 nothing to do because we only keep one occurrence
	return b;
}


BST* removeMin(BST* b){
	if(b->left==NULL) //the min is the root
		return b->right;
	b->left = removeMin(b->left);
	return b;
}

BST* remove(BST* b, string x){
	if(b==NULL)
		return NULL;
	int c = x.compare(b->value);
	if(c<0){
		b->left = remove(b->left, x);
	} else if(c>0) {
		b->right = remove(b->right, x);
	} else { //if x==b->value, i.e. we want to remove the root
		if(b->right==NULL)
			return b->left;
		// do root = min(R) and removeMin
		b->value = getMin(b->right);
		b->right = removeMin(b->right);
	}
	return b;
}


struct AVL{
	string value;
	AVL *left, *right;
	int height;
	AVL(AVL* left, string value, AVL* right){
		this->left = left;
		this->value = value;
		this->right = right;
		this->height = 1+max(left->height, right->height);
	}
};

bool contains(AVL* b, string v){
	while(b != NULL){
		int c = v.compare(b->value);
		if(c==0)
			return true;
		if(c<0){
			b = b->left;
		} else {
			b = b->right;
		}
		//b = c<0?b->left:b->right; //the above if else is equivalent to this line
	}
	return false;
}

string getMin(AVL* b){
	while(b->left!=NULL){
		b = b->left;
	}
	return b->value;
}

AVL* rotateLeft(AVL* b){
	AVL* r = b->right;
	b->right = r->left;
	r->left = b;
	b->height = 1 + max(b->left->height, b->right->height);
	r->height = 1 + max(r->left->height, r->right->height);
	return r;
}

AVL* rotateRight(AVL* b){
	AVL* l = b->left;
	b->left = l->right;
	l->right = b;
	b->height = 1 + max(b->left->height, b->right->height);
	l->height = 1 + max(l->left->height, l->right->height);
	return l;
}

AVL* balance(AVL* b){
	AVL *l = b->left, *r = b->right;
	int hl = l->height, hr = r->height;
	if(hl>hr+1){ //imbalance from the left child
		AVL *ll = l->left, *lr = l->right;
		if (ll->height >= lr->height) //imbalance from the left child of the left child
			return rotateRight(b);
		else { //imbalance from the right child of the left child
			b->left = rotateLeft(b->left);
			return rotateRight(b);
		}
	} else if (hr>hl+1){ //imbalance from the right child, symmetric
		AVL *rl = r->left, *rr = r->right;
		if (rr->height >= rl->height)
			return rotateLeft(b);
		else {
			b->right = rotateRight(b->right);
			return rotateLeft(b);
		}
	} else { // no imbalance
		b->height = 1 + max(hl, hr);
		return b;
	}
}

int main() {
	Tree* t = new Tree(new Tree(NULL, "B", NULL), "A", new Tree (new Tree(NULL, "D", NULL), "C", NULL));

	/* NAIVE INORDER */
//	inorderTraversal(t);
//
//	list<string> l = inorder(t);
//	while(!l.empty()){
//		cout<<l.front()<<" ";
//		l.pop_front();
//	}

	/* LINEAR INORDER */
//	list<string> l;
//	inorder(t, l);
//	while(!l.empty()){
//		cout<<l.front()<<" ";
//		l.pop_front();
//	}

	/* BFS */
//	list<string> l;
//	BFS(t, l);
//	while(!l.empty()){
//		cout<<l.front()<<" ";
//		l.pop_front();
//	}

	/* BST */


	return 0;
}
