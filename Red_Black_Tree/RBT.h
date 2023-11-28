#ifndef RBT_H
#define RBT_H

#include <vector>
using std::vector;
using std::pair;
using std::swap;


enum Color {RED, BLACK};

template <class T>
class TreeNode {
public:
    T val;
    bool color;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

    TreeNode(): val(0), color(RED), left(NULL), right(NULL), parent(NULL) {}
    TreeNode(T n): val(n), color(RED), left(NULL), right(NULL), parent(NULL) {}
};

template <class T>
class RBT {
public:
    TreeNode<T> *root;

    RBT(): root(NULL) {}
    void insert(T);
    vector<pair<int, int>> preorder();
    vector<pair<int, int>> inorder();

public:
    TreeNode<T>* internalInsert(TreeNode<T>*, TreeNode<T>*);
    void insertFix(TreeNode<T>*);
    void internalPreorder(TreeNode<T>*, vector<pair<int, int>>&);
    void internalInorder(TreeNode<T>*, vector<pair<int, int>>&);
    void rightRotation(TreeNode<T>*);
    void leftRotation(TreeNode<T>*);
};

template <class T>
void RBT<T>::insert(T n) {
    TreeNode<T> *insertNode = new TreeNode<T>(n);

    root = internalInsert(root, insertNode);
    insertFix(insertNode);
}

template <class T>
void RBT<T>::insertFix(TreeNode<T>* node) {
    while (node != root && node->color == RED && node->parent->color == RED) {
        TreeNode<T> *parent = node->parent;
        TreeNode<T> *grandparent = node->parent->parent;

        /*
        Case:
                g
               / \
              p   u
             / \
            n   n
        */
        if (parent == grandparent->left) {
            TreeNode<T> *uncle = grandparent->right;

            // Case 1
            /*
                g              G
               / \            / \
              P   U          p   u
             / \            / \
            N   N          N   N
            */
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;

                // update current node
                node = grandparent;
            }
            // Case 2 & 3
            else {
                // Case 2
                /*
                    g            g
                   / \          / \
                  P   u        N   u
                   \          /
                    N        P
                */
                if (node == parent->right) {
                    leftRotation(parent);

                    swap(node, parent);
                }
                // Case 3
                /*
                    g            p
                   / \          / \
                  P   u        N   G
                 /                  \
                N                    u
                */
                parent->color = BLACK;
                grandparent->color = RED;
                rightRotation(grandparent);

                node = parent;
            }
        }
        /*
        Case:
                g
               / \
              u   p
                 / \
                n   n
        */
        else {
            TreeNode<T> *uncle = grandparent->left;

            // Case 1
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;

                // update current node
                node = grandparent;
            }
            // Case 2 & 3
            else {
                // Case 2
                if (node == parent->left) {
                    rightRotation(parent);

                    swap(node, parent);
                    // node = parent;
                    // parent = node->parent;
                }
                // Case 3
                parent->color = BLACK;
                grandparent->color = RED;
                leftRotation(grandparent);

                node = parent;
            }
        }
    }

    root->color = BLACK;
}

template <class T>
void RBT<T>::rightRotation(TreeNode<T>* a) {
/*
    r         r
    |         |
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

    // update parent
    b->parent = a->parent;
    a->parent = b;
    if (br != NULL) br->parent = a;

    // update r point to
    if (b->parent == NULL)
        root = b;
    else if (a == b->parent->left)
        b->parent->left = b;
    else if (a == b->parent->right)
        b->parent->right = b;
}

template <class T>
void RBT<T>::leftRotation(TreeNode<T>* a) {
/*
    r           r
    |           |
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

    // update parent
    b->parent = a->parent;
    a->parent = b;
    if (bl != NULL) bl->parent = a;

    // update r point to
    if (b->parent == NULL)
        root = b;
    else if (a == b->parent->left)
        b->parent->left = b;
    else if (a == b->parent->right)
        b->parent->right = b;
}

template <class T>
TreeNode<T>* RBT<T>::internalInsert(TreeNode<T>* node, TreeNode<T>* insertNode) {
    // similar to BST insert
    if (node == NULL) {
        return insertNode;
    }

    if (insertNode->val <= node->val) {
        node->left = internalInsert(node->left, insertNode);
        node->left->parent = node; // update parent
    }
    else if (insertNode->val > node->val) {
        node->right = internalInsert(node->right, insertNode);
        node->right->parent = node; // update parent
    }

    return node;
}

template <class T>
vector<pair<int, int>> RBT<T>::preorder() {
    vector<pair<int, int>> res;
    internalPreorder(root, res);
    return res;
}

template <class T>
void RBT<T>::internalPreorder(TreeNode<T>* node, vector<pair<int, int>>& res) {
    if (node) {
        res.push_back({node->val, node->color});
        internalPreorder(node->left, res);
        internalPreorder(node->right, res);
    }
}

template <class T>
vector<pair<int, int>> RBT<T>::inorder() {
    vector<pair<int, int>> res;
    internalInorder(root, res);
    return res;
}

template <class T>
void RBT<T>::internalInorder(TreeNode<T>* node, vector<pair<int, int>>& res) {
    if (node) {
        internalInorder(node->left, res);
        res.push_back({node->val, node->color});
        internalInorder(node->right, res);
    }
}

#endif // RBT_H
