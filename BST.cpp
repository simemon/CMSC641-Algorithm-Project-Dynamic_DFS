#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "Static_DFS.cpp"
using namespace std;

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
		virtual ~BSTNode();

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
		virtual ~BinarySearchTree()
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

		void insert(BSTNode*);
		void buildBST(Graph);
		//void balance(string*, int, int);

};

/*void BinarySearchTree::clear(BSTNode *node)
{
	node = NULL;
}*/

void BinarySearchTree::insert(BSTNode *node) //
{
	BSTNode *p = root, *prev = NULL;

	while (p != NULL)
	{
		prev = p;
		//if(node->m_vertex.second != p->m_vertex.second)
		//	p = p->m_right;
		//assuming any vertices share only one edges
		if (node->m_vertex.first < p->m_vertex.first)
			p = p->m_left;
		else if (node->m_vertex.first > p->m_vertex.first)
			p = p->m_right;
	}

	if(root == NULL)
		root = node;

	else if (node->m_vertex.first < p->m_vertex.first)
		prev->m_left = node;
	else if (node->m_vertex.first > p->m_vertex.first)
		prev->m_right = node;
}

void BinarySearchTree::buildBST(Graph g) //should take argument vertex v
{
	//std::vector< <pair<int,int> > vEList; //find order of vertices from L 
	
	for (std::vector<int>::iterator it = g.vertexList.begin(); it != g.vertexList.end(); ++it)
	{
		std::vector< <pair<int,int>> > vel;
		vel = g.searchEdge(*it);
		for(std::vector< <pair<int,int> >::iterator ite = vel.begin(); ite != vel.end(); ++ite)
		{
			if(*it == *ite->first)
			{
				BSTNode *node = new BSTNode(make_pair(*ite->first,*ite->second));
				insert(node);
			}
		}

	}
	
}

void BinarySearchTree::inorder(BSTNode *node)
{
	if(node!=NULL)
	{
		inorder(node->m_left);
		cout << node->m_vertex.first << " " << node->m_vertex.second;
		inorder(node->m_right);

	}
}
