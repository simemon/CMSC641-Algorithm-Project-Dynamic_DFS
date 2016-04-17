#include <iostream>
#nclude "BST.cpp"
using namespace std;

int main()
{
	BinarySearchTree bst;
	Graph g;

	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	//g.addEdge(3, 3);

	cout << "Following is Depth First Traversal\n";
	
	g.DFS();

	cout << "List Printing in DFS order" << endl;
	g.vectorListPrint();

	cout << "Edge List Printing in DFS order" << endl;
	g.edgeList();

	cout << "Edge list with 1 as vertex input (Unidirectional)" << endl;
	int x = 1;
	g.searchEdge(x, false);	//second argument false - because this is unidirectional

	cout << "Edge list with 1 as vertex input (bidirectional)" << endl;	
	std::vector< pair<int,int> > vList;
	vList = g.searchEdge(x);	// no argument - bidirectional

	bst.buildTree();

	bst.inorder();

	return 0;
}