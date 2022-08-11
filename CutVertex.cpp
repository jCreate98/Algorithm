#include <iostream>

using namespace std;

int edges[1000][1000]; // edges[from][to] = 1 tree / = 2 parent / = 3 back
int nodes[1000];
int pre[1000];
int L[1000];
int nnodes;
int nedges;
int to, from;
int pr = 1;
int root;

void dfs(int index, int p) {
	nodes[index] = 1;
	pre[index] = pr; 
	pr++;
	for (int i = 1; i <= nnodes; i++) {
		if (i == p) 
		{
			edges[index][p] = 2;
		}
		else if (edges[index][i] == 1 && nodes[i] != 1)
		{
			dfs(i, index);
		}
		else if (edges[index][i] == 1 && nodes[i] == 1)
		{
			edges[index][i] = 3;
			edges[i][index] = 0;
		}
	}
}

void find_CV(int index) {
	int low = pre[index];

	for (int j = 1; j <= nnodes; j++) {
		if ((edges[index][j] == 1) && (edges[j][index] == 2))
		{
			L[j] = 10000;
			find_CV(j);
			low = min(low, L[j]);
		}
		else if ((edges[index][j] == 3) && (edges[j][index] == 0)) 
		{
			low = min(low, pre[j]);
		}
	}
	L[index] = low;
}

int is_CV(int index) {
	if (index == root) {
		int child = 0;
		for (int i = 1; i <= nnodes; i++) {
			if (edges[index][i] == 1) {
				child++;
				if (child > 1)
					return 1;
			}
		}
		return 0;
	}

	for (int i = 1; i <= nnodes; i++) {
		if (edges[index][i] == 1) {
			if (L[i] >= pre[index])
				return 1;
		}
	}
	return 0;
}

int main(void) {
	cout << "The number of Nodes = ";
	cin >> nnodes;
	cout << "The number of Edges = ";
	cin >> nedges;
	cout << "Edges (node1 node2) = ";
	for (int i = 0; i < nedges; i++) {
		cin >> to;
		cin >> from;
		edges[to][from] = 1;
		edges[from][to] = 1;
	}
	root = 1;
	dfs(root, 0);
	find_CV(root);

	for (int i = 1; i < nnodes; i++) {
		if (is_CV(i)) {
			cout << i << "th node is  CutVertex" << endl;
		}
	}
	return 0;
}