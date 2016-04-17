#include <iostream>
#include <list>
#include <vector>
#include <algorithm>


using namespace std;

class BinarySearchTree;

template <class T>
class Graph
{
	friend class BinarySearchTree;
	int V; // No. of vertices
	list<T> *adj; // Pointer to an array containing adjacency lists
	//void DFSUtil(T v, bool visited[]); // A function used by DFS
	
	/* To maintain vertex list so that can be used for algorithm*/
	vector<T> vertexList;
	T vertexListCounter;

	/* Edge List needed so that we can traverse	*/
	vector<pair<T,T> > bidirectionalEdges;

public:
	Graph(int V); // Constructor
	//void addEdge(T v, T w); // function to add an edge to graph
	//void DFS(); // prints DFS traversal of the complete graph
	//void vectorListPrint();	//to print whether vertex is properly stored in the list or not
	//void edgeList();
	vector<list < pair<T,T> > > searchEdge(T x, bool bidirection);	//Search all the edges 

};

template <typename T>
Graph<T>::Graph(int V)
{
	this->V = V;
	adj = new list<T>[V];

	/* creating a new vector to store the list of vertex in DFS order	*/
	vertexListCounter = 0;	// this is to maintain the index of Vertex List Vector
}

// template <typename T>
// void Graph<T>::addEdge(T v, T w)
// {
// 	adj[v].push_back(w); // Add w to v’s list.
// }

// template <typename T>
// void Graph<T>::DFSUtil(T v, bool visited[])
// {
// 	// Mark the current node as visited and print it

// 	vertexList.push_back(v);
// 	visited[v] = true;

// 	cout << v << " ";

// 	// Recur for all the vertices adjacent to this vertex
// 	list<T>::iterator i;
// 	for(i = adj[v].begin(); i != adj[v].end(); ++i)
// 		if(!visited[*i])
// 		{
// 			bidirectionalEdges.push_back(make_pair(v,*i));
// 			bidirectionalEdges.push_back(make_pair(*i,v));
// 			DFSUtil(*i, visited);
// 		}
// }

// // The function to do DFS traversal. It uses recursive DFSUtil()
// template <typename T>
// void Graph<T>::DFS()
// {
// 	// Mark all the vertices as not visited
// 	bool *visited = new bool[V];
// 	for (int i = 0; i < V; i++)
// 		visited[i] = false;

// 	// Call the recursive helper function to print DFS traversal
// 	// starting from all vertices one by one
// 	for (int i = 0; i < V; i++)
// 		if (visited[i] == false)
// 			DFSUtil(i, visited);
// }

// template <typename T>
// void Graph<T>::vectorListPrint()
// {
// 	for (std::vector<typename T>::iterator i = vertexList.begin(); i != vertexList.end(); ++i)
// 	{
// 		cout << *i << endl;
// 	}
// }

// template <typename T>
// void Graph<T>::edgeList()
// {
// 	for (vector< pair <typename T,typename T> >::iterator i = bidirectionalEdges.begin(); i != bidirectionalEdges.end(); ++i)
// 	{
// 		cout << i -> first << " " << i -> second << endl;
// 	}
// }

template <typename T1,T2>
std::vector<list < pair<T1,T2> > > Graph<T>::searchEdge(T x, bool flagBidirectionalEdges = true)
{
	std::vector<list<pair<typename T,typename T>>> vEdgeList;
	for (vector< pair <typename T,typename T> >::iterator i = bidirectionalEdges.begin(); i != bidirectionalEdges.end(); ++i)
	{
		if(i -> first == x)
		{
			cout << i -> first << " " << i -> second << endl;
			vEdgeList.push_back(make_pair(i->first,i->second));
		}
		else
		{
			if(flagBidirectionalEdges && i -> second == x)
			{
				cout << i -> first << " " << i -> second << endl;
				vEdgeList.push_back(make_pair(i->first,i->second));
			}
		}

	}

	return vEdgeList;
}

int main()
{
	// Create a graph given in the above diagram
	Graph<char> g(4);
	g.addEdge('u', 'x');
	g.addEdge('u', 'y');
	g.addEdge('x', 'y');
	g.addEdge('y', 'u');
	g.addEdge('y', 'z');
	//g.addEdge(3, 3);

	cout << "Following is Depth First Traversal\n";
	
	g.DFS();

	cout << "List Printing in DFS order" << endl;
	g.vectorListPrint();

	cout << "Edge List Printing in DFS order" << endl;
	g.edgeList();

	cout << "Edge list with 1 as vertex input (Unidirectional)" << endl;
	char x = 'x';
	g.searchEdge(x, false);	//second argument false - because this is unidirectional

	cout << "Edge list with 1 as vertex input (bidirectional)" << endl;	
	std::vector<list < pair<char,char> > > vList;
	vList = g.searchEdge(x);	// no argument - bidirectional

	return 0;
}