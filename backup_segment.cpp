#include <iostream>
#include <algorithm>

using namespace std;

struct SegmentTreeNode {
	int sum;
	
	
	void assignLeaf(int value) {
		sum = value;
	}
	
	void merge(SegmentTreeNode& left, SegmentTreeNode& right) {
		sum = left.sum + right.sum;
	}
	
	int getValue() {
		return sum;
	}


};

template<class T, class V>
class SegmentTree {
	SegmentTreeNode* nodes;
	int N;
	
public:
	SegmentTree(T arr[], int N) {
		this->N = N;
		nodes = new SegmentTreeNode[getSegmentTreeSize(N)];
		buildTree(arr, 1, 0, N-1);
	}
	
	~SegmentTree() {
		delete[] nodes;
	}
	
	void printNode()
	{
		for (int i = 0; i < getSegmentTreeSize(N); ++i)
		{
			cout << nodes[i].getValue() << endl;
		}
	}
	

private:	
	void buildTree(T arr[], int stIndex, int lo, int hi) {
		if (lo == hi) {
			nodes[stIndex].assignLeaf(arr[lo]);
			return;
		}
		
		int left = 2 * stIndex, right = left + 1, mid = (lo + hi) / 2;
		buildTree(arr, left, lo, mid);
		buildTree(arr, right, mid + 1, hi);
		nodes[stIndex].merge(nodes[left], nodes[right]);
	}
	
	int getSegmentTreeSize(int N) {
		int size = 1;
		for (; size < N; size <<= 1);
		return size << 1;
	}
	
};

int main() {
	int N, i, A[50000], M, x, y;
	
	cout << "Enter N" << endl;
	cin >> N;
	for (i = 0; i < N; ++i)
		cin >> A[i];
	
	SegmentTree<int,int> st(A, N);
	cout << "Nodes" << endl;
	st.printNode();

	return 0;
}