#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef G_H
#define G_H

class BinarySearchTree;

class Graph
{
	friend class BinarySearchTree;
	int V; // No. of vertices
	list<int> *adj; // Pointer to an array containing adjacency lists
	void DFSUtil(int v, bool visited[]); // A function used by DFS
	
	/* To maintain vertex list so that can be used for algorithm*/
	vector<int> vertexList;
	int vertexListCounter;

	/* Edge List needed so that we can traverse	*/
	vector< pair<int,int> > bidirectionalEdges;

public:
	Graph(int V); // Constructor
	void addEdge(int v, int w); // function to add an edge to graph
	void DFS(); // prints DFS traversal of the complete graph
	void vectorListPrint();	//to print whether vertex is properly stored in the list or not
	void edgeList();
	vector< pair<int,int> > searchEdge(int x, bool bidirection);	//Search all the edges 

};


Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];

	/* creating a new vector to store the list of vertex in DFS order	*/
	vertexListCounter = 0;	// this is to maintain the index of Vertex List Vector
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

void Graph::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and print it

	vertexList.push_back(v);
	visited[v] = true;

	cout << v << " ";

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
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

	// Call the recursive helper function to print DFS traversal
	// starting from all vertices one by one
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			DFSUtil(i, visited);
}

void Graph::vectorListPrint()
{
	for (std::vector<int>::iterator i = vertexList.begin(); i != vertexList.end(); ++i)
	{
		cout << *i << endl;
	}
}

void Graph::edgeList()
{
	for (vector< pair <int,int> >::iterator i = bidirectionalEdges.begin(); i != bidirectionalEdges.end(); ++i)
	{
		cout << i -> first << " " << i -> second << endl;
	}
}

std::vector< pair<int,int> > Graph::searchEdge(int x, bool flagBidirectionalEdges = true)
{
	std::vector< pair<int,int> > vEdgeList;
	//for (std::vector<int>::iterator it = x.begin(); it != x.end(); ++it)
	//{
	
		for (vector< pair <int,int> >::iterator i = bidirectionalEdges.begin(); i != bidirectionalEdges.end(); ++i)
		{
			if(i -> second == x)
			{
				cout << i -> first << " " << i -> second << endl;
				vEdgeList.push_back(make_pair(i->first,i->second));
			}
			/*else
			{
				if(flagBidirectionalEdges && i -> second == x)
				{
					cout << i -> first << " " << i -> second << endl;
					vEdgeList.push_back(make_pair(i->first,i->second));
				}
			} */

	//	}
	}

	return vEdgeList;
}

// int main()
// {
// 	// Create a graph given in the above diagram
// 	Graph g(4);
// 	g.addEdge('u', 'x');
// 	g.addEdge('u', 'y');
// 	g.addEdge('x', 'y');
// 	g.addEdge('y', 'u');
// 	g.addEdge('y', 'z');
// 	//g.addEdge(3, 3);

// 	cout << "Following is Depth First Traversal\n";
	
// 	g.DFS();

// 	cout << "List Printing in DFS order" << endl;
// 	g.vectorListPrint();

// 	cout << "Edge List Printing in DFS order" << endl;
// 	g.edgeList();

// 	cout << "Edge list with 1 as vertex input (Unidirectional)" << endl;
// 	int x = 'x';
// 	g.searchEdge(x, false);	//second argument false - because this is unidirectional

// 	cout << "Edge list with 1 as vertex input (bidirectional)" << endl;	
// 	std::vector< pair<int,int> > vList;
// 	vList = g.searchEdge(x);	// no argument - bidirectional

// 	return 0;
// }

class BinarySearchTree;

class BSTNode
{
	friend class BinarySearchTree;
	protected:
		pair<int,int> m_vertex;
		BSTNode *m_left, *m_right;

	public:
		//BSTNode() : m_vertex(""), m_left(NULL), m_right(NULL) { }
		BSTNode(pair<int,int> vertex) : m_vertex(vertex), m_left(NULL), m_right(NULL) { }
		//	BSTNode(pair<int,int> vertex, BSTNode *left = NULL, BSTNode *right = NULL) : m_vertex(vertex), m_left(left), m_right(right) { }
		~BSTNode();

		void setVertex(pair<int,int> vertex)
		{
			m_vertex = vertex;
		}

		pair<int,int> getVertex()
		{
			return make_pair(m_vertex.first,m_vertex.second);
		}

		void setLeftNode(BSTNode *left)
		{
			m_left = left;
		}

		BSTNode* getLeftNode()
		{
			return m_left;
		}

		void setRightNode(BSTNode *right)
		{
			m_right = right;
		}

		BSTNode* getRightNode()
		{
			return m_right;
		}
};	

class BinarySearchTree
{
	protected:
		BSTNode *root;

		//void clear(BSTNode *);
		void inorder(BSTNode *node);
		//string search(BSTNode *, const string&) const;
		virtual void visit(BSTNode *node)
		{
			cout << node->m_vertex.first << " " << node->m_vertex.second << endl;
		}

	public:
		BinarySearchTree() : root(NULL) { }
		~BinarySearchTree()
		{
			//clear();
		}

		/*void clear()
		{
			clear(root);
			root = NULL;
		}*/

		bool isEmpty() const
		{
			return root == NULL;
		}

		void inorder()
		{
			inorder(root);
		}

		// string search(const string& value) const
		// {
		// 	return search(root,value);
		// }

		void insert(BSTNode*,std::vector<int>&);
		void buildBST(Graph);
		//void balance(string*, int, int);

};

/*void BinarySearchTree::clear(BSTNode *node)
{
	node = NULL;
}*/

void BinarySearchTree::insert(BSTNode *node, std::vector<int>& vertexList) 
{
	BSTNode *p = root, *prev = NULL;
	size_t pos_node, pos_p;

	std::vector<int>::iterator iterator_node = find(vertexList.begin(), vertexList.end(), node->m_vertex.first);
	pos_node = distance(vertexList.begin(),iterator_node);
	cout << "pos_node" << pos_node << endl;

	std::vector<int>::iterator iterator_low, iterator_high;
	iterator_low = vertexList.begin();
	iterator_high = vertexList.end();

	while (p != NULL)
	{
		prev = p;
		std::vector<int>::iterator iterator_p = find(iterator_low, iterator_high, p->m_vertex.first);
		pos_p = distance(vertexList.begin(),iterator_p);
		cout<< "pos_p" << " " <<pos_p << endl;
		//if(node->m_vertex.second != p->m_vertex.second)
		//	p = p->m_right;
		//assuming any vertices share only one edges
		
		if (pos_node < pos_p)
		{
			p = p->m_left;
			iterator_high = iterator_p - 1;
		}
		else
		{
			p = p->m_right;
			iterator_low = iterator_p + 1;
		}
	}

	if(root == NULL)
		root = node;
	else if (pos_node < pos_p)
		prev->m_left = node;
	else
		prev->m_right = node;
}

void BinarySearchTree::buildBST(Graph g) //should take argument vertex v
{
	//std::vector< <pair<int,int> > vEList; //find order of vertices from L 
	
	cout<<"in buildBST" << endl;
	for (std::vector<int>::iterator it = g.vertexList.begin(); it != g.vertexList.end(); ++it)
	{
		cout << " buildBST" << *it << " " <<endl;
		std::vector< pair<int,int > > vel;
		vel = g.searchEdge(*it);

		for(std::vector< pair<int,int> >::iterator ite = vel.begin(); ite != vel.end(); ++ite)
		{
			//cout << "Before if and " << *it << " " << ite -> first << ite->second<< endl;
			//if(*it == ite->first)
			//{	
			//	cout << " creating node" << ite->first << " "<< ite->second << " " <<endl;
				BSTNode *node = new BSTNode(make_pair(ite->first,ite->second));
				cout << "Node" << " " << node->m_vertex.first << node->m_vertex.second <<endl;
				insert(node,g.vertexList);
			//}
		}

	}
	
}

void BinarySearchTree::inorder(BSTNode *node)
{
	if(node!=NULL)
	{
		inorder(node->m_left);
		cout << node->m_vertex.first << " " << node->m_vertex.second<< endl;
		inorder(node->m_right);

	}
}

int main()
{
	BinarySearchTree bst;
	Graph g(8);

	// g.addEdge(0, 1);
	// g.addEdge(0, 2);
	// g.addEdge(1, 2);
	// g.addEdge(2, 0);
	// g.addEdge(2, 3);
	//g.addEdge(3, 3);

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
	int x = 1;
	g.searchEdge(x, false);	//second argument false - because this is unidirectional

	cout << "Edge list with 1 as vertex input (bidirectional)" << endl;	
	/*std::vector< pair<int,int> > vList;
	vList = g.searchEdge(x);	// no argument - bidirectional*/

	//cout << "Before calling buildBST " << endl; 
	bst.buildBST(g);

	cout<<"Inorder traversal is:" <<endl;
	bst.inorder();

	return 0;
}


#endif