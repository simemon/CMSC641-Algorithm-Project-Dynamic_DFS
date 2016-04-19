#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;

#ifndef G_H
#define G_H

class SegmentTree;
class BinarySearchTree;
class Graph
{
	friend class SegmentTree;
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
	Graph() { }
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
	cout<<"In search edge: "<< x << endl;
	std::vector< pair<int,int> > vEdgeList;

	for (vector< pair <int,int> >::iterator i = bidirectionalEdges.begin(); i != bidirectionalEdges.end(); ++i)
	{
		if(i->second == x)
		{

			vEdgeList.push_back(make_pair(i->first,i->second));
		}
		else
		{
			if(flagBidirectionalEdges && i->second == x)
			{
				cout << i->first << " " << i->second << endl;
				vEdgeList.push_back(make_pair(i->first,i->second));
			}
		}

	//	}
	}

	return vEdgeList;
}

Graph g(8);


class BinarySearchTree;
class BSTNode
{
	friend class BinarySearchTree;
 	protected:
		
		BSTNode *m_left, *m_right;

	public:
		pair<int,int> m_vertex;
		BSTNode()
		{

		}
		BSTNode(pair<int,int> vertex) : m_vertex(vertex), m_left(NULL), m_right(NULL) { }
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

		BSTNode* copy()
		{
			return copy(this);
		}

		BSTNode* copy(BSTNode* root) 
		{
     
			BSTNode *new_root;
			 
			 if(root != NULL)
			 {
			     new_root = new BSTNode;
			     new_root -> m_vertex = root -> m_vertex;
			     new_root -> m_left = copy(root -> m_left);
			     new_root -> m_right = copy(root -> m_right);
			 } 
			 else 
			 	return NULL;
			 return new_root;
		}
};	

class BinarySearchTree
{
	protected:

		BSTNode *root;
		void inorder(BSTNode*);
		
		virtual void visit(BSTNode *node)
		{
			cout << node->m_vertex.first << " " << node->m_vertex.second << endl;
		}

	public:
		BinarySearchTree* copyTree();
		BinarySearchTree(BSTNode* r = NULL) : root(r) { }
		
		~BinarySearchTree()
		{
			//clear();
		}

		bool isEmpty() const
		{
			return root == NULL;
		}

		void inorder()
		{
			inorder(root);
		}

		void insert(BSTNode*);
		void buildBST(int);
		
		void inorderWithVector(BSTNode*, vector<BSTNode*>&);
		vector<BSTNode*> inorderforList()
		{
			vector<BSTNode*> v;
			cout << "Going inside inorderWithVector" << endl;
			inorderWithVector(root, v);
			return v;
		}
};

BinarySearchTree*  BinarySearchTree::copyTree()
{
	BSTNode* new_root = root -> copy();	
	BinarySearchTree* new_tree = new BinarySearchTree(new_root);
	return new_tree;
}


void BinarySearchTree::insert(BSTNode *node) 
{

	node -> m_left = node -> m_right = NULL;

	if(root == NULL)
	{
		root = node;
		cout << "Assigned to root: " << node->m_vertex.first << "-" << node->m_vertex.second << endl;
		return;
	}
	
	cout << "Node : " << node->m_vertex.first << "-" << node->m_vertex.second << endl;
	
	BSTNode *p = root, *prev = NULL;

	size_t pos_node, pos_p;
	std::vector<int>::iterator iterator_node = find(g.vertexList.begin(), g.vertexList.end(), node->m_vertex.first);
	pos_node = distance(g.vertexList.begin(),iterator_node);

	std::vector<int>::iterator iterator_low, iterator_high;
	iterator_low = g.vertexList.begin();
	iterator_high = g.vertexList.end();

	while (p != NULL)
	{
		prev = p;
		vector<int>::iterator iterator_p = find(iterator_low, iterator_high, p->m_vertex.first);
		pos_p = distance(g.vertexList.begin(),iterator_p);
		
		if (pos_node < pos_p)
		{
			p = p -> m_left;
			iterator_high = iterator_p - 1;
		}
		else
		{
			p = p -> m_right;
			iterator_low = iterator_p + 1;
		}
	}

	if (pos_node < pos_p)
		prev -> m_left = node;
	else
		prev -> m_right = node;
}

void BinarySearchTree::buildBST(int x) //should take argument vertex v
{ 
	cout << "In build BST for leaf node through assignLeaf" << endl;
	std::vector< pair<int,int> > vel;
	vel = g.searchEdge(x);
	for(std::vector< pair<int,int> >::iterator ite = vel.begin(); ite != vel.end(); ++ite)
	{
		BSTNode *node = new BSTNode(make_pair(ite->first,ite->second));
		insert(node);
	}
}

void BinarySearchTree::inorder(BSTNode *node)
{
	if(node!=NULL)
	{
		inorder(node->m_left);
		sleep(1);
		cout << node->m_vertex.first << " " << node->m_vertex.second<< endl;
		inorder(node->m_right);
	}
}

void BinarySearchTree::inorderWithVector(BSTNode* node, vector<BSTNode*> &v)
{
	if(node!=NULL)
	{
		inorderWithVector(node->m_left, v);
		v.push_back(node);
		inorderWithVector(node->m_right, v);
	}
}

class BinarySearchTree;

struct SegmentTreeNode 
{

	std::vector<int> segVertex;
	std::vector<pair<int,int> > eList;

	BinarySearchTree *ptrBST;
  
  void assignLeaf(int value) 
  {
  	
  	ptrBST = new BinarySearchTree();
  	ptrBST -> buildBST(value);

  	cout<<"Inorder of BST at " << value << endl; 
  	
  	ptrBST->inorder();
    segVertex.push_back(value);
  }
  
  void merge(SegmentTreeNode& left, SegmentTreeNode& right) {

  	cout << "In Merge Function: " << endl;

  	segVertex.reserve( left.segVertex.size() + right.segVertex.size() );
  	segVertex.insert(segVertex.end(), left.segVertex.begin(), left.segVertex.end());
  	segVertex.insert(segVertex.end(), right.segVertex.begin(), right.segVertex.end());
  	
	BinarySearchTree *leftBST = left.ptrBST, *rightBST = right.ptrBST;

  	if(leftBST != NULL && rightBST != NULL)
  	{

  		ptrBST = leftBST -> copyTree();
  		vector<BSTNode*> v = rightBST -> inorderforList();

  		for (vector<BSTNode*>::iterator i = v.begin(); i != v.end(); ++i)
  		{
  			ptrBST -> insert(*i);
  		}

  		cout << "Before ptrBST -> inorder()" << endl; 
  		ptrBST -> inorder();
  		cout << "After ptrBST -> inorder()" << endl; 
  	}


  }

};

class SegmentTree 
{
  SegmentTreeNode* nodes;
  int N;

public:
  SegmentTree() 	//N should be the vertex count
  { 
    N = g.vertexList.size();
    nodes = new SegmentTreeNode[getSegmentTreeSize(N)];
    buildTree(1, 0, N-1);
    
  }
  
  ~SegmentTree() {
    delete[] nodes;
  }
  
  private:	
  void buildTree(int stIndex, int lo, int hi) 
  {

  	if (lo == hi) 
  	{
  	  nodes[stIndex].assignLeaf(g.vertexList[lo]);
      return;
    }
    
    int left = 2 * stIndex;
    int right = left + 1;
    int mid = (lo + hi) / 2;

    buildTree(left, lo, mid);
    buildTree(right, mid + 1, hi);
    nodes[stIndex].merge(nodes[left], nodes[right]);
  }
  
  int getSegmentTreeSize(int N) 
  {
    int size = 1;
    for (; size < N; size <<= 1);
    return size << 1;
  }
   
};


int main()
{

	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	
	cout << "Following is Depth First Traversal" <<endl;
	
	g.DFS();

	cout << "List Printing in DFS order" << endl;
	g.vectorListPrint();

	cout << "Edge List Printing in DFS order" << endl;
	g.edgeList();

	SegmentTree segTree;

	return 0;
}

#endif