#include <vector>
#include <map>
using namespace std;

template<class T>
class TreeNode{
public:
    T val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(): val(0), left(NULL), right(NULL) {}
    TreeNode(T n): val(n), left(NULL), right(NULL) {};
};

template<class T>
class BT{
public:
    TreeNode<T> *root;

    void build(vector<T>&, vector<T>&);
    vector<T> preorder();
    vector<T> inorder();
    vector<T> posorder();
private:
    TreeNode<T>* internalBuild(vector<T>&, int, int, vector<T>&, int, int, map<T, int>);
    void internalPreorder(TreeNode<T>*, vector<T>&);
    void internalInorder(TreeNode<T>*, vector<T>&);
    void internalPosorder(TreeNode<T>*, vector<T>&);
};

// template <class T>
// void BT<T>::build(vector<T>& arr) {
//     root = internalBuild(arr, 0);
// }

template <class T>
void BT<T>::build(vector<T>& preorder, vector<T>& inorder) {
    map<T, int> m;
    for (int i = 0; i < inorder.size(); i++) {
        m[inorder[i]] = i;
    }
    root = internalBuild(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, m);
}

template <class T>
TreeNode<T>* BT<T>::internalBuild(vector<T>& preorder, int pre_start, int pre_end,
                                  vector<T>& inorder, int in_start, int in_end, map<T, int> m) {
        if (pre_start > pre_end)
            return NULL;

        TreeNode<T> *node = new TreeNode<T>(preorder[pre_start]);
        int root_position = m[preorder[pre_start]];
        int size = root_position - in_start;
        node->left = internalBuild(preorder, pre_start + 1, pre_start + size, inorder, in_start, root_position - 1, m);
        node->right = internalBuild(preorder, pre_start + size + 1, pre_end, inorder, root_position + 1, in_end, m);
        return node;
}

// template <class T>
// TreeNode<T>* BT<T>::internalBuild(vector<T>& arr, int idx) {
//     if (idx >= arr.size())
//         return NULL;

//     TreeNode<T> *node = new TreeNode(arr[idx]);
//     if (arr[idx] != 0) {
//         node->left = internalBuild(arr, idx * 2 + 1);
//         node->right = internalBuild(arr, idx * 2 + 2);
//         return node;
//     }
//     return NULL;
// }

template <class T>
vector<T> BT<T>::preorder() {
    vector<T> res;
    internalPreorder(root, res);
    return res;
}

template <class T>
void BT<T>::internalPreorder(TreeNode<T>* node, vector<T>& res) {
    if (node) {
        res.push_back(node->val);
        internalPreorder(node->left, res);
        internalPreorder(node->right, res);
    }
}

template <class T>
vector<T> BT<T>::inorder() {
    vector<T> res;
    internalInorder(root, res);
    return res;
}

template <class T>
void BT<T>::internalInorder(TreeNode<T>* node, vector<T>& res) {
    if (node) {
        internalInorder(node->left, res);
        res.push_back(node->val);
        internalInorder(node->right, res);
    }
}

template <class T>
vector<T> BT<T>::posorder() {
    vector<T> res;
    internalPosorder(root, res);
    return res;
}

template <class T>
void BT<T>::internalPosorder(TreeNode<T>* node, vector<T>& res) {
    if (node) {
        internalPosorder(node->left, res);
        internalPosorder(node->right, res);
        res.push_back(node->val);
    }
}
