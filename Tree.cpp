struct TreeNode
{
	struct TreeNode *left, *right;
	char c;
};

typedef struct TreeNode TreeNode;



/*
LCA of two nodes in TreeNode
*/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    return !left ? right : !right ? left : root;
}

/* Driver code: Main Program */



/*
Path

class Solution { 
public:
    int maxPathSum(TreeNode* root) {
        sum = INT_MIN;
        pathSum(root);
        return sum;
    }
private:
    int sum;
    int pathSum(TreeNode* node) {
        if (!node) return 0;
        int left = max(0, pathSum(node -> left));
        int right = max(0, pathSum(node -> right));
        sum = max(sum, left + right + 1);
        return max(left, right) + 1;
    }
};*/