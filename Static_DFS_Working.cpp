#include <ctime>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <set>
#include <climits>


#define EDGES 700
#define VERTEX 500

#define DEBUG false


/*#define VERTEX 11
#define EDGES 16
*/

/*#define VERTEX 8
#define EDGES 9
*/

/*int VERTEX;
int EDGES;*/

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

	vector<int> vertexList;
	int vertexListCounter;

	/* Edge List needed so that we can traverse	*/
	vector< pair<int,int> > bidirectionalEdges;


public:
	vector< pair<int,int> > DFSEdges;
	Graph() { }
	Graph(int V); // Constructor
	void addEdge(int v, int w); // function to add an edge to graph
	void DFS(); // prints DFS traversal of the complete graph
	void vectorListPrint();	//to print whether vertex is properly stored in the list or not
	void edgeList();
	vector< pair<int,int> > searchEdge(int x, bool bidirection);	//Search all the edges 
	void DFSEdgeList();
	void PathUtil(int a, int b, vector<int> &v);
	vector<int> findChildren(int w);
	vector<int> Path(int a, int b)
	{
		vector<int> pathvector;
		PathUtil(a,b,pathvector);
		pathvector.push_back(a);
		reverse(pathvector.begin(), pathvector.end());
		return pathvector;
	}
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
	bidirectionalEdges.push_back(make_pair(v, w));
	bidirectionalEdges.push_back(make_pair(w, v));
}

void Graph::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and print it
	vertexList.push_back(v);
	visited[v] = true;

	if(DEBUG)
		cout << v << " ";
	// Recur for all the vertices adjacent to this vertex

	list<int>::iterator i;
	for(i = adj[v].begin(); i != adj[v].end(); ++i)
		if(!visited[*i])
		{
			/*bidirectionalEdges.push_back(make_pair(v,*i));
			bidirectionalEdges.push_back(make_pair(*i,v));*/
			
			DFSEdges.push_back(make_pair(v,*i));

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

void Graph::DFSEdgeList()
{
	for (vector< pair <int,int> >::iterator i = DFSEdges.begin(); i != DFSEdges.end(); ++i)
	{
		cout << i -> first << " " << i -> second << endl;
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
	/*cout<<"In search edge: "<< x << endl;*/
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
				if(DEBUG)
					cout << i->first << " " << i->second << endl;
				vEdgeList.push_back(make_pair(i->first,i->second));
			}
		}

	//	}
	}

	return vEdgeList;
}

void Graph::PathUtil(int a, int b, vector<int> &pathvector)
{
	if(a == b)
		return;
	for (vector<pair <int, int> >::reverse_iterator i = DFSEdges.rbegin(); i != DFSEdges.rend(); ++i)
	{
		if(i -> first == a  && i -> second <= b)	
		{
			PathUtil(i -> second, b, pathvector);
			pathvector.push_back(i -> second);
			break;
		}
	}
}

vector<int> Graph::findChildren(int w)
{
	std::vector<int> childVector;
	childVector.push_back(w);
	for (vector<pair <int,int> >::iterator i = DFSEdges.begin(); i != DFSEdges.end(); ++i)
	{
		if(i -> first == w && i -> second > w)
		{
			childVector.push_back(i -> second);
		}
	}	
	return childVector;
}


Graph g(VERTEX);

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
		
		void inorder(BSTNode*);
		
		virtual void visit(BSTNode *node)
		{
			cout << node->m_vertex.first << " " << node->m_vertex.second << endl;
		}
	public:
		BSTNode *root;
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
		/*cout << "Assigned to root: " << node->m_vertex.first << "-" << node->m_vertex.second << endl;*/
		return;
	}
	
	/*cout << "Node : " << node->m_vertex.first << "-" << node->m_vertex.second << endl;*/
	
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
	/*cout << "In build BST for leaf node through assignLeaf" << endl;*/
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
	if(node != NULL)
	{
		inorder(node->m_left);
		cout << node->m_vertex.first << " " << node->m_vertex.second<< endl;
		inorder(node->m_right);
	}
}

void BinarySearchTree::inorderWithVector(BSTNode* node, vector<BSTNode*> &v)
{
	if(node != NULL)
	{
		inorderWithVector(node->m_left, v);
		v.push_back(node);
		inorderWithVector(node->m_right, v);
	}
}

class BinarySearchTree;

struct SegmentTreeNode 
{
  vector<int> segVertex;
  vector<pair<int,int> > eList;
  BinarySearchTree *ptrBST;
 
  BinarySearchTree* getBinarySearchTree()
  {
  	return ptrBST;
  }

  void assignLeaf(int value) 
  {
  	
  	ptrBST = new BinarySearchTree();
  	ptrBST -> buildBST(value);

  	if(DEBUG)
  		cout<<"Inorder of BST at " << value << endl; 
  	
  	if(DEBUG)
  		ptrBST->inorder();
    segVertex.push_back(value);
  }

  void merge(SegmentTreeNode& left, SegmentTreeNode& right) 
  {

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
  
  SegmentTreeNode* getNodes()
  {
  	return nodes;
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

pair <int, int> Query(vector<BSTNode*> &BSTNodeVector, int w, int x, int y)
{
	clock_t begin = clock();
	
	vector<int> pathList = g.Path(x,y);	
	std::vector<int> childVector = g.findChildren(w);	//w
  	int a = INT_MAX, b = INT_MAX;
	pair<int, int > final_edge = make_pair(INT_MAX,INT_MAX);
	for (std::vector<BSTNode*>::iterator i = BSTNodeVector.begin(); i != BSTNodeVector.end(); ++i)
	{
		if(find(pathList.begin(),pathList.end(), (*i)-> m_vertex.first) != pathList.end() && find(childVector.begin(),childVector.end(), (*i) -> m_vertex.second) != childVector.end())
		{
			/*cout << (*i) -> m_vertex.first << " " << (*i) -> m_vertex.second << endl;*/
			if(final_edge.first > (*i) -> m_vertex.first)
			{
				final_edge.first = (*i) -> m_vertex.first;
				final_edge.second = (*i) -> m_vertex.second;		
			}
		}
	}

	clock_t end = clock();
  	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  	cout << "elapsed_secs: " << elapsed_secs << endl;

	return final_edge;
}


int main(int argc, char* argv[])
{

	/*VERTEX = atoi(argv[1]);
	EDGES = atoi(argv[2]);

	cout << VERTEX << endl;
	cout << EDGES << endl;*/


	srand (time(NULL));
	set < pair<int,int> > s;
	int v1, v2;

	while(s.size() != EDGES)
	{
		v1 = rand() % VERTEX;
		v2 = rand() % VERTEX;
		if(v1 == v2)
			continue;
		pair<int, int> p1(v1, v2);
		pair<int, int> p2(v2, v1);

		if(s.find(p2) != s.end())
			continue;
		s.insert(p1);
	}

	for (set< pair<int,int> >::iterator i = s.begin(); i != s.end(); ++i)
	{
		pair<int,int> p1 = *i;
		cout << p1.first << " " << p1.second << endl;		
	}

	for (set< pair<int,int> >::iterator i = s.begin(); i != s.end(); ++i)
	{
		pair<int,int> p1 = *i;
		g.addEdge(p1.first, p1.second);
	}	

	// These are 16 edges and 11 vertices
	// g.addEdge(0, 3);
	// g.addEdge(0, 6);
	// g.addEdge(5, 10);
	// g.addEdge(6, 7);
	// g.addEdge(7, 8);
	// g.addEdge(7, 9);
	// g.addEdge(8, 10);
	// g.addEdge(10, 9);
	// g.addEdge(1, 2);
	// g.addEdge(1, 9);
	// g.addEdge(2, 3);
	// g.addEdge(2, 9);
	// g.addEdge(3, 4);
	// g.addEdge(4, 5);
	// g.addEdge(4, 8);
	// g.addEdge(5, 6);


	// These are 9 edges and 8 vertices

	// Mapping:
	// x = 0
	// z = 1
	// u = 2
	// w = 3
	// y = 4
	// v = 5
	// s = 6
	// t = 7	

	/*g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(2, 4);
	g.addEdge(1, 5);
	g.addEdge(0, 6);
	g.addEdge(6, 7);

	g.addEdge(0, 3);
	g.addEdge(1, 4);*/
	
	
	g.DFS();
	cout << "List Printing in DFS order" << endl;
	g.vectorListPrint();
	cout << "Edge List Printing in DFS order" << endl;
	g.edgeList();
	
	cout << "elapsed_secs starts for SegmentTree" << endl;
	clock_t begin = clock();
	SegmentTree segTree;
	clock_t end = clock();
  	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  	cout << "elapsed_secs: " << elapsed_secs << endl;


  	SegmentTreeNode *nodes = segTree.getNodes();
  	BinarySearchTree *ptrBST =  nodes[1].getBinarySearchTree();
  	BSTNode* rootNode = ptrBST -> root;
  	vector<BSTNode*> BSTNodeVector = ptrBST -> inorderforList();

  	/*cout << "Printing Vector of root SegmentTree" << endl;
  	for (std::vector<BSTNode*>::iterator i = BSTNodeVector.begin(); i != BSTNodeVector.end(); ++i)
  	{
		cout << (*i) -> m_vertex.first << " " << (*i) -> m_vertex.second << endl;  		
  	}

  	cout << "DFS Edge List" << endl;
 	g.DFSEdgeList();
 	cout << "Path List" << endl;
 	vector<int> pathList = g.Path(0,5);
  	for (vector<int>::iterator i = pathList.begin(); i != pathList.end(); ++i)
  	{
  		cout << *i << endl;
  	}
  	cout << "Children List" << endl;
  	std::vector<int> childVector = g.findChildren(2);	//w
  	for (vector<int>::iterator i = childVector.begin(); i != childVector.end(); ++i)
  	{
  		cout << *i << endl;
  	}*/
  	
  	int w = rand() % VERTEX;
  	int y;
  	while(1)
  	{
  		y = rand() % VERTEX;
  		if(y != w)
  			break;
  	}
  	cout << "W: " << w << endl;
  	cout << "Y: " << y << endl;



 	pair<int,int> final_edge = Query(BSTNodeVector,w,0,y);
  	cout << "Edge: " << final_edge.first  << " " << final_edge.second << endl;
  	cout << "Total edges: " << EDGES << " and Total vertices: " << VERTEX << endl;

	return 0;
}

#endif