#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

typedef int graphtype;
using namespace std;

class Graph
{
	int V; 				  // No. of vertices
	list<graphtype> *adj; // Pointer to an array containing adjacency lists
	void DFSUtil(graphtype v, bool visited[]); // A function used by DFS
	
	/* To maintain vertex list so that can be used for algorithm*/
	vector<graphtype> vertexList;
	int vertexListCounter;

	/* Edge List needed so that we can traverse	*/
	vector<pair<graphtype,graphtype> > bidirectionalEdges;


public:
	Graph(int V); // Constructor
	void addEdge(graphtype v, graphtype w); // function to add an edge to graph
	void DFS(); // prints DFS traversal of the complete graph
	void vectorListPrint();	//to print whether vertex is properly stored in the list or not
	void edgeList();
	void searchEdge(graphtype x, bool bidirection);	//Search all the edges 
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<graphtype>[V];

	/* creating a new vector to store the list of vertex in DFS order	*/
	vertexListCounter = 0;	// this is to maintain the index of Vertex List Vector
}

void Graph::addEdge(graphtype v, graphtype w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

void Graph::DFSUtil(graphtype v, bool visited[])
{
	// Mark the current node as visited and print it

	vertexList.push_back(v);
	visited[v] = true;

	cout << v << " ";

	// Recur for all the vertices adjacent to this vertex
	list<graphtype>::iterator i;
	for(i = adj[v].begin(); i != adj[v].end(); ++i)
		if(!visited[*i])
		{
			bidirectionalEdges.push_back(make_pair(v,*i));
			bidirectionalEdges.push_back(make_pair(*i,v));
			DFSUtil(*i, visited);
		}
}

// The function to do DFS traversal. It uses recursive DFSUtil()
void Graph::DFS()
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	cout << "Before calling DFSUtil" << endl;
	// Call the recursive helper function to print DFS traversal
	// starting from all vertices one by one
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			DFSUtil(i, visited);
}

void Graph::vectorListPrint()
{
	for (std::vector<graphtype>::iterator i = vertexList.begin(); i != vertexList.end(); ++i)
	{
		cout << *i << endl;
	}
}

void Graph::edgeList()
{
	for (vector< pair <graphtype,graphtype> >::iterator i = bidirectionalEdges.begin(); i != bidirectionalEdges.end(); ++i)
	{
		cout << i -> first << " " << i -> second << endl;
	}
}

void Graph::searchEdge(graphtype x, bool flagBidirectionalEdges = true)
{
	for (vector< pair <graphtype,graphtype> >::iterator i = bidirectionalEdges.begin(); i != bidirectionalEdges.end(); ++i)
	{
		if(i -> first == x)
		{
			cout << i -> first << " " << i -> second << endl;
		}
		else
		{
			if(flagBidirectionalEdges && i -> second == x)
			{
				cout << i -> first << " " << i -> second << endl;
			}
		}

	}
}

int main()
{
	// Create a graph given in the above diagram
	Graph g(8);
	
	/*
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	*/

	/*
	g.addEdge('x', 'z');
	g.addEdge('x', 'u');
	g.addEdge('z', 'y');
	g.addEdge('z', 'w');
	g.addEdge('u', 'v');
	g.addEdge('w', 's');
	g.addEdge('w', 't');
	*/

	/*
	x = 0
	z = 1
	u = 2
	w = 3
	y = 4
	v = 5
	s = 6
	t = 7
	*/
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(2, 5);
	g.addEdge(3, 6);
	g.addEdge(3, 7);

	g.addEdge(0,6);
	g.addEdge(1,7);


	cout << "Following is Depth First Traversal\n";
	g.DFS();

	cout << "List Printing in DFS order" << endl;
	g.vectorListPrint();

	cout << "Edge List Printing in DFS order" << endl;
	g.edgeList();

	cout << "Edge list with 1 as vertex input (Unidirectional)" << endl;
	graphtype x = 0;
	g.searchEdge(x, false);	//second argument false - because this is unidirectional

	cout << "Edge list with 1 as vertex input (bidirectional)" << endl;	
	g.searchEdge(x);	// no argument - bidirectional

	return 0;
}