#ifndef AVL_H
#define AVL_H

#include <vector>
using std::vector;
using std::max;

template <class T>
class TreeNode {
public:
    T val;
    TreeNode *left;
    TreeNode *right;
    int height;

    TreeNode(): val(0), left(NULL), right(NULL), height(1) {}
    TreeNode(T n): val(n), left(NULL), right(NULL), height(1) {}
};

template <class T>
int height(TreeNode<T> *node) {
    if (node == NULL) return 0;
    return node->height;
}

template <class T>
int getBalanceFactor(TreeNode<T> *node) {
    if (node == NULL) return 0;
    return height(node->right) - height(node->left);
}

template <class T>
class AVL {
public:
    TreeNode<T> *root;
    AVL(): root(NULL) {}
    void insert(T);
    vector<T> preorder();
    vector<T> inorder();
    vector<T> posorder();

private:
    TreeNode<T>* rightRotation(TreeNode<T>*);
    TreeNode<T>* leftRotation(TreeNode<T>*);
    TreeNode<T>* internalInsert(TreeNode<T>*, T);
    void internalPreorder(TreeNode<T>*, vector<T>&);
    void internalInorder(TreeNode<T>*, vector<T>&);
    void internalPosorder(TreeNode<T>*, vector<T>&);
};

template <class T>
void AVL<T>::insert(T n) {
    root = internalInsert(root, n);
}

template <class T>
vector<T> AVL<T>::preorder() {
    vector<T> res;
    internalPreorder(root, res);
    return res;
}

template <class T>
vector<T> AVL<T>::inorder() {
    vector<T> res;
    internalInorder(root, res);
    return res;
}

template <class T>
vector<T> AVL<T>::posorder() {
    vector<T> res;
    internalPosorder(root, res);
    return res;
}

template <class T>
TreeNode<T>* AVL<T>::rightRotation(TreeNode<T>* a) {
/*
    a         b
   / \       / \
  b   pr    bl  a
 / \           / \
bl  br         br ar
*/
    TreeNode<T> *b = a->left;
    TreeNode<T> *br = b->right;

    a->left = br;
    b->right = a;

    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(b->left), height(b->right)) + 1;

    return b;
}

template <class T>
TreeNode<T>* AVL<T>::leftRotation(TreeNode<T>* a) {
/*
    a           b
   / \         / \
  al  b       a   br
     / \     / \
     bl br  al  bl
*/
    TreeNode<T> *b = a->right;
    TreeNode<T> *bl = b->left;

    a->right = bl;
    b->left = a;

    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(b->left), height(b->right)) + 1;

    return b;
}

template <class T>
TreeNode<T>* AVL<T>::internalInsert(TreeNode<T>* node, T n) {
    if (node == NULL) {
        return new TreeNode<T>(n);
    }

    if (n <= node->val) {
        node->left = internalInsert(node->left, n);
    }
    else if (n > node->val) {
        node->right = internalInsert(node->right, n);
    }

    // update the height of this node
    node->height = max(height(node->left), height(node->right)) + 1;

    // calculate the balance factor
    int balanceFactor = getBalanceFactor(node);

    // Right Right
    if (balanceFactor > 1 && n > node->right->val) {
        node = leftRotation(node);
    }
    // Left Left
    else if (balanceFactor < -1 && n <= node->left->val) {
        node = rightRotation(node);
    }
    // Right Left
    else if (balanceFactor > 1 && n <= node->right->val) {
        node->right = rightRotation(node->right);
        node = leftRotation(node);
    }
    // Left Right
    else if (balanceFactor < -1 && n > node->left->val) {
        node->left = leftRotation(node->left);
        node = rightRotation(node);
    }

    return node;
}

template <class T>
void AVL<T>::internalPreorder(TreeNode<T>* node, vector<T>& res) {
    if (node) {
        res.push_back(node->val);
        internalPreorder(node->left, res);
        internalPreorder(node->right, res);
    }
}

template <class T>
void AVL<T>::internalInorder(TreeNode<T>* node, vector<T>& res) {
    if (node) {
        internalInorder(node->left, res);
        res.push_back(node->val);
        internalInorder(node->right, res);
    }
}

template <class T>
void AVL<T>::internalPosorder(TreeNode<T>* node, vector<T>& res) {
    if (node) {
        internalPosorder(node->left, res);
        internalPosorder(node->right, res);
        res.push_back(node->val);
    }
}

#endif // AVL_H
