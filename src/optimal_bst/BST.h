#ifndef BST_H
#define BST_H

#endif // BST_H
#include <vector>
using std::vector;

template <class T>
class TreeNode {
public:
    T val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(T n): val(n), left(nullptr), right(nullptr) {}
};

template <class T>
class BST {
public:
    TreeNode<T> *root;
    BST(): root(nullptr) {}
    void insert(T);
    vector<T> preorder();
    vector<T> inorder();

private:
    TreeNode<T>* internalInsert(TreeNode<T>*, T);
    void internalPreorder(TreeNode<T>*, vector<T>&);
    void internalInorder(TreeNode<T>*, vector<T>&);
};

template <class T>
void BST<T>::insert(T n) {
    root = internalInsert(root, n);
}

template <class T>
TreeNode<T>* BST<T>::internalInsert(TreeNode<T>* node, T n) {
    if (node == nullptr) {
        return new TreeNode(n);
    }

    if (n <= node->val) {
        node->left = internalInsert(node->left, n);
    }
    else if (n > node->val) {
        node->right = internalInsert(node->right, n);
    }

    return node;
}

template <class T>
vector<T> BST<T>::preorder() {
    vector<T> res;
    internalPreorder(root, res);
    return res;
}

template <class T>
void BST<T>::internalPreorder(TreeNode<T>* node, vector<T>& res) {
    if (node) {
        res.push_back(node->val);
        internalPreorder(node->left, res);
        internalPreorder(node->right, res);
    }
}

template <class T>
vector<T> BST<T>::inorder() {
    vector<T> res;
    internalInorder(root, res);
    return res;
}

template <class T>
void BST<T>::internalInorder(TreeNode<T>* node, vector<T>& res) {
    if (node) {
        internalInorder(node->left, res);
        res.push_back(node->val);
        internalInorder(node->right, res);
    }
}
