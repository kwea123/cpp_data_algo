#include <iostream>
using namespace std;

string s1 = "afgerbc";
string s2 = "rdgnrqyc";
int n1 = s1.length();
int n2 = s2.length();
int length[10][10];
void LCS(){
	for(int i=0;i<=n1;i++)
		length[i][0] = 0;
	for(int j=0;j<=n2;j++)
		length[0][j] = 0;
	for(int i=1;i<=n1;i++)
		for(int j=1;j<=n2;j++){
			if(s1[i-1]==s2[j-1])
				length[i][j] = 1+length[i-1][j-1];
			else
				length[i][j] = max(length[i-1][j], length[i][j-1]);
		}
}

int prev[10][10];

void LCS2(){
	for(int i=0;i<=n1;i++)
		length[i][0] = 0;
	for(int j=0;j<=n2;j++)
		length[0][j] = 0;
	for(int i=1;i<=n1;i++)
		for(int j=1;j<=n2;j++){
			if(s1[i-1]==s2[j-1]){
				length[i][j] = 1+length[i-1][j-1];
				prev[i][j] = 0; //upper left
			}
			else if(length[i-1][j]<length[i][j-1]){
				length[i][j] = length[i][j-1];
				prev[i][j] = 1; //left
			}
			else{
				length[i][j] = length[i-1][j];
				prev[i][j] = 2; //up
			}
		}
}

string print_LCS(int i, int j){
	if(i==0||j==0) return "";
	if(prev[i][j]==0)
		return print_LCS(i-1, j-1) + s1[i-1]; //or s2[j-1]
	else if(prev[i][j]==1)
		return print_LCS(i, j-1);
	else
		return print_LCS(i-1, j);
}

int W = 15; //capacity of the knapsack
int N = 5; //number of objects
int weights[5] = {12, 2, 1, 1, 4};
int vs[5] = {4, 2, 2, 1, 10};
int ks[10][20];

void KS(){
	for(int w=0;w<=W;w++)
		ks[0][w] = 0;
	for(int i=0;i<N;i++)
		ks[i][0] = 0;
	for(int i=1;i<=N;i++)
		for(int w=0;w<=W;w++){
			if(w>weights[i-1]) //if we can put the ith object
				ks[i][w] = max(vs[i-1] + ks[i-1][w-weights[i-1]], ks[i-1][w]); //put it or not
			else
				ks[i][w] = ks[i-1][w];
		}
}

void print_KS(){ //print content
	int w = ks[N][W]; //final weight
	for(int i=N-1;i>=0;i--)
		if(w>=weights[i]&&ks[i+1][w]==vs[i]+ks[i][w-weights[i]]){
			cout<<i<<endl;
			w-=weights[i];
		}
}

int main() {
	/* LCS */
//	LCS();
//	LCS2();
//	cout<<length[n1][n2]<<endl;
//	cout<<print_LCS(n1, n2);

	/* KNAPSACK */
	KS();
	cout<<ks[N][W]<<endl;
	print_KS();

	return 0;
}
