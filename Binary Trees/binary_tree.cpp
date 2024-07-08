// لَنْ تَنَالُوا الْبِرَّ حَتَّى تُنْفِقُوا مِمَّا تُحِبُّونَ وَمَا تُنْفِقُوا مِنْ شَيْءٍ فَإِنَّ اللَّهَ بِهِ عَلِيمٌ [آل عمران:92].

// © M_Abrazeg

#include <iostream>
#include <string>
#include <queue>
using namespace std;

/**
 * @brief Represents a node in a binary tree.
 * 
 * This struct defines the basic structure of a node in a binary tree. Each node contains a value of type `T` (`info`), and pointers to its left and right child nodes (`left` and `right`).
 * 
 * The default constructor initializes the left and right pointers to `nullptr`. The parameterized constructor takes a value of type `T` and initializes the `info` member with that value, while also setting the left and right pointers to `nullptr`.
 */
template<class T>
struct TreeNode { // Represents a node in a binary tree.
    T info;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : left(nullptr), right(nullptr) {}
    TreeNode(const T&val) : info(val), left(nullptr), right(nullptr) {}
};

/**
 * @brief This class specifies the basic operations to implement a binary tree.
 * @tparam T The type of the elements stored in the BT . The type must support comparison operators.
 */
template<class T>
class BinaryTree {
protected:
    TreeNode<T>* root;
    int nubmer_of_nodes;

    /**
     * @brief Calculates the height of a binary tree rooted at the given node.
     *
     * @param root The root node of the binary tree.
     * @return The height of the binary tree, which is the number of nodes in the longest path from the root to a leaf node.
     */
    int height (TreeNode<T>* root) const {
        if (root == nullptr) return 0;
        return 1 + max(height(root->left),height(root->right));
    };
    
    /**
     * @brief Performs an inorder traversal of the binary tree rooted at the given node.
     * This function recursively traverses the left subtree, then visits the root node, and finally the right subtree.
     *
     * @param root The root node of the binary tree to be traversed.
     */
    void inorder (TreeNode<T>* root) { 
        if (root) {
            inorder(root->left);
            cout << root->info << " | ";
            inorder(root->right);
        }
    }
    
    /**
     * @brief Performs a postorder traversal of the binary tree rooted at the given node.
     * This function recursively traverses the left subtree, then the right subtree, and finally the root node.
     *
     * @param root The root node of the binary tree to be traversed.
     */
    void postorder (TreeNode<T>* root) { 
        if (root) {
            postorder(root->left);
            postorder(root->right);
            cout << root->info << " | ";
        }
    }

    /**
     * @brief Performs a preorder traversal of the binary tree rooted at the given node.
     * This function visits the root node first, then recursively traverses the left subtree, and finally the right subtree.
     *
     * @param root The root node of the binary tree to be traversed.
     */
    void preorder (TreeNode<T>* root) {
        if (root) {
            cout << root->info << " | ";
            inorder(root->left);
            inorder(root->right);
        }
    }
    
    /**
     * @brief Performs a Breadth-First Search (BFS) traversal of the binary tree rooted at the given node.
     * This function traverses the binary tree in a level-order fashion, printing the value of each node as it is visited.
     *
     * @param root The root node of the binary tree to be traversed.
     */
    void bfs (TreeNode<T>*root) { 
        if (root == 0) 
            return;
        queue<TreeNode<T>*> qu;
        qu.push(root);
        while (qu.empty() == 0) { 
            cout << qu.front()->info << " | ";
            if (qu.front()->left) 
                qu.push(qu.front()->left);
            if(qu.front()->right)
                qu.push(qu.front()->right);
            qu.pop();
        }
    }

     /**
     * @brief copie the binary tree rooted at the given node.
     *
     * @param root The reference to the root node of the new binary tree.
     * @param copyRoot The root node of the binary tree to be copied.
     */
    void copy (TreeNode<T>*&root,TreeNode<T>*copyRoot) {
        if (copyRoot == nullptr)
            root = nullptr;
        else {
            root = new TreeNode<T>(copyRoot->info);
            copy(root->left,copyRoot->left);
            copy(root->right,copyRoot->right);
        }
    } 
    
    /**
     * @brief destroy the binary tree rooted at the given node.
     * @param r The root node of the binary tree to be destroyed.
     */
    void destroy (TreeNode<T>*&r) { 
        if (r) { 
            destroy(r->left);
            destroy(r->right);
            delete r;
            r = nullptr;
        }
    }

    /**
     * @brief Counts the number of leaf nodes in the binary tree.
     * @param root The root node of the binary tree.
     * @return The number of leaf nodes in the binary tree.
     */
    int countLeves (TreeNode<T>* root) {
        if (root == 0) { 
            return 0;
        }
        else { 
            int cnt = 0;
            queue<TreeNode<T>*> qu;
            qu.push(root);
            while (qu.empty() == 0) {
                if (qu.front()->left) qu.push(qu.front()->left);
                if(qu.front()->right) qu.push(qu.front()->right);
                cnt += qu.front()->left == 0 && qu.front()->right == 0 ;
                qu.pop();
            }
            return cnt;
        }
    }
    
public:
    // The default constructor initializes the binary tree to an empty state
    BinaryTree<T>() : root(nullptr) , nubmer_of_nodes(0){}

    BinaryTree<T>(const BinaryTree<T>& otherTree) {
        if (otherTree.root == NULL) //otherTree is empty
            root = NULL;
        else copy(root, otherTree.root);
    }

    /**
     * @brief Checks if the binary tree is empty.
     * @return true if the binary tree is empty, false otherwise.
    */
    bool empty() const {
        return this->root == nullptr;
    }
    
    /**
     * @return The height of the binary tree.
    */
    int height() const {
        return height(this->root);
    }

    /**
     * @brief Prints the binary tree using breadth-first search (BFS) traversal.
    */
    void print () { 
        bfs(this->root);
    }

    /**
     * @brief Counts the number of leaf nodes in the binary tree.
     * @return The number of leaf nodes in the binary tree.
     */
    int countLeves () { 
        return countLeves(this->root);
    }

    /**
     * @brief Copies the contents of another binary tree into this binary tree.
     * @param other The binary tree to copy from.
     */
    void copy (const BinaryTree<T>&other) { 
        this->copy(this->root , other.root);
    }
    
    /**
     * @brief Destroys the entire binary tree.
    */
    void destroy () {
        this->destroy(this->root);
    }
 
    /**
     * @brief Assigns the contents of another binary tree to this binary tree.
     * @param otherTree The binary tree to copy from.
     * @return A reference to this binary tree after the assignment.
     * 
     * This overloaded assignment operator copies the contents of the `otherTree` binary
     * tree to this binary tree. If this binary tree is not empty, it is first destroyed
     * before the copy operation. The assignment operator ensures that self-assignment
     * is handled correctly, and returns a reference to the modified binary tree to
     * allow for efficient assignment chaining.
     * handling deep copies and resource management (like memory allocation and deallocation).
     */
    const BinaryTree<T>&operator=(const BinaryTree<T>& otherTree)
    {
        if (this != &otherTree) //avoid self-copy
        {
            if (root != NULL) //if the binary tree is not empty,
            //destroy the binary tree
                destroy(root);
            if (otherTree.root == NULL) //otherTree is empty
                root = NULL;
            else
            this->copy(root, otherTree.root);
        }//end else
        return *this; 
    }

    ~BinaryTree() {
        this->destroy();
    }
};

/**
 * @brief Represents a Binary Search Tree (BST), which is a specialized form of a Binary Tree.
 * A BST maintains the property that for every node, all the values in its left subtree are less than
 * the node's value, and all the values in its right subtree are greater than the node's value.
 * This allows for efficient searching, insertion, and deletion operations.
 
 * @tparam T The type of the elements stored in the BST . The type must support comparison operators.

 */
template<class T>
class BST : public BinaryTree<T> { 
public:
    BST() { this->nubmer_of_nodes = 0;}
    /**
     * @brief Searches the binary tree for the given item.
     * @param item The item to search for in the binary tree.
     * @return true if the item is found in the binary tree, false otherwise.
    */
    bool search (const T& item) { 
        return search(this->root , item);
    }
    /** 
     * @brief Removes the binary search tree for the given item.
     * @param item The item to remove from the binary search tree(BST).
     */
    void remove (const T& item) { 
        this->root = remove(this->root, item);
    }
     /**
     * @brief Inserts the given item into the binary search tree.
     * @param item The item to insert into the binary search tree.
     */
    void insert (const T&item) { 
        insert(this->root,item);
    }
    
     /**
     * @brief Returns the number of nodes in the binary tree.
     * @return The number of nodes in the binary tree.
     */
    int size () { 
        return this->nubmer_of_nodes;
    }
    /**
     * @brief Returns the maximum value in the binary tree.
     * @return The maximum value in the binary tree.
     */
    T getMaxValue() { 
        return this->getMaxValue(this->root);
    }
    /**
     * @brief Returns the minimum value in the binary tree.
     * @return The minimum value in the binary tree.
     */
    T getMinValue() {
        return this->getMinValue(this->root);
    }

    /**
     * @brief Recursively prints all nodes in the binary tree by calling the provided user-level function.
     * @param root The root node of the subtree to print.
     * @param userLevelFunction The function to call for each node in the tree.
     */
    void printBy ( TreeNode<T>*root , void(*userLevelFunction)(T&)) { 
        if (!root) return;
        (*userLevelFunction)(root->info);
        printBy(root->left,userLevelFunction);
        printBy(root->right,userLevelFunction);
    }
    /**
     * @brief Function to print all nodes by another functiono in user level
     * @param f function to print by using it all items in BST.
     */
    void printBy(void(*f)(T&)) { 
        printBy(this->root,f);
    }
protected:

    /**
     * @brief Inserts the given item into the binary search tree.
     * @param root The root of the subtree to insert the item into.
     * @param item The item to insert into the binary search tree.
     */
    void insert (TreeNode<T>*root , const T& item) { 
        if (this->empty())  {
            this->root = new TreeNode<T>(item);
        } else { 
            TreeNode<T> *go = root , *add = nullptr;  
            while (go) { 
                add = go;

                if (go->info >= item) { 
                    go = go->left;
                } else  {
                    go = go->right;
                }
            }

            if (add->info >= item) { 
                add->left = new TreeNode<T>(item);
            }else
                add->right = new TreeNode<T>(item);
        }
        ++this->nubmer_of_nodes;
    }
     /**
     * @brief Searches the binary search tree for the given item.
     * @param root The root of the subtree to search.
     * @param item The item to search for in the binary search tree.
     * @return True if the item is found in the binary search tree, false otherwise.
     */
    bool search(TreeNode<T>*root , const T& item) {
        bool is_found = false;
        TreeNode<T>*go = root;
        while (go) {
            if (go->info == item) return true;
            else if (go->info > item) go = go->left;
            else go = go->right;
        }
        return false ; 
    }
    /**
     * @brief Recursively finds the maximum value in the binary search tree rooted at the given node.
     * @param root The root of the subtree to search for the maximum value.
     * @return The maximum value in the binary search tree rooted at the given node.
     */
    T getMaxValue (TreeNode<T>*root) {   
        return root->right ? getMaxValue(root->right) : root->info;
    }
    /**
     * @brief Recursively finds the minimum value in the binary search tree rooted at the given node.
     * @param root The root of the subtree to search for the minimum value.
     * @return The minimum value in the binary search tree rooted at the given node.
     */
    T getMinValue (TreeNode<T>*root) {   
        return root->left ? getMinValue(root->left) : root->info;
    }
    /**
     * Recursively removes the node containing the specified item from the binary search tree.
     *
     * @param root The root of the subtree to search and remove the item from.
     * @param item The item to remove from the binary search tree.
     * @return The updated root of the subtree after the item has been removed.
     */
    TreeNode<T>* remove (TreeNode<T>*root , const T&item) 
    { 
        if (root == NULL)  
            return NULL;

        // search on data 
        if (root->info > item) // go left 
            root->left = remove(root->left,item);
        else if (root->info < item) // go right 
            root->right = remove(root->right,item);
        else 
        {   // found the node to be deleted
            if (root->left == NULL) { // no left child || no child 
                TreeNode<T>* rightSubTree = root->right;
                delete root;             
                return rightSubTree;   
            } 
            else if (root->right == NULL) { // no right child || no child 
                TreeNode<T>* leftSubTree = root->left;
                delete root;
                return leftSubTree;
            } else { // has to chidldren
                T maxValue = getMaxValue(root->left);
                root->info = maxValue;
                root->left = remove(root->left, maxValue);
            }
        }

    }
} ; 

/**
 * @class AVLTree
 * @brief A class that implements an AVL Tree, a self-balancing binary search tree.
 *
 * @tparam T The type of the elements stored in the AVL Tree. The type must support comparison operators.
 */
template<class T>
class AVL : public BinaryTree<T> {

    /**
     * @brief Calculates the balance factor of the given binary tree node.
     * @param root The root node of the subtree to calculate the balance factor.
     * @return The balance factor of the given binary tree node,which is the difference between the heights of the left and right subtrees.
     */
    int getBalanceFactor(TreeNode<T> *root) {
        if (root == NULL) 
            return -1;
        return this->height(root->left) - this->height(root->right);
    }
    /**
     * Performs a right rotation on the given binary tree node.
     *
     * @param root The root node of the subtree to rotate.
     * @return The new root of the rotated subtree.
     */
    TreeNode<T>*rightRotate(TreeNode<T>*root) { 
        TreeNode<T>*newRoot = root->left;
        TreeNode<T>*rightSubTree = newRoot->right;
        
        // perform rotation
        newRoot->right = root;
        root->left = rightSubTree;
        return newRoot;
    }
    /**
     * Performs a left rotation on the given binary tree node.
     *
     * @param root The root node of the subtree to rotate.
     * @return The new root of the rotated subtree.
     */
    TreeNode<T>*leftRotate(TreeNode<T>*root) { 
        TreeNode<T>*newRoot = root->right;
        TreeNode<T>*leftSubTree = newRoot->left;

        // perform rotation
        newRoot->left = root;
        root->right = leftSubTree;
        return newRoot;
    }
     /**
     * Inserts a new node with the given item value into the binary tree rooted at the given node.
     *
     * @param root The root node of the binary tree to insert the new node into.
     * @param item The value to store in the new node.
     * @return The new root node of the binary tree after the insertion.
     */
    TreeNode<T>* insert(TreeNode<T>*root, const T& item)
    {
        if (NULL == root) 
        { 
            root = new TreeNode<T>(item);
            ++this->nubmer_of_nodes;
            return root;   
        }

        // insert data into the AVL 
        if (item < root->info) // go left  
            root->left = insert(root->left, item);
        else if (item > root->info) 
            root->right = insert(root->right, item);
        else // No duplicate values allowed
            return root;

        // update the balance factor of each node
        int balanceFactor = getBalanceFactor(root);

        bool Is_left_heavy = (balanceFactor > 1);
        bool Is_right_heavy = (balanceFactor < -1);

        bool Is_left_left = (Is_left_heavy &&  item < root->left->info); 
        bool Is_right_right = (Is_right_heavy && item > root->right->info); 
        bool Is_Left_Right = (Is_left_heavy && item > root->left->info);
        bool Is_Right_Left = (Is_right_heavy && item < root->right->info);

        if (Is_left_left) { 
            return rightRotate(root);
        } 
        if (Is_right_right) {
            return leftRotate(root);
        } 
        if (Is_Left_Right) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        } 
        if (Is_Right_Left) { 
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        // no rotation (balance subtree) 
        return root;
        
    }

    /**
     * Returns the minimum value in the binary tree rooted at the given node.
     * @param root The root of the binary tree to search for the minimum value.
     * @return The minimum value in the binary tree rooted at the given node.
     */
    TreeNode<T> *getMinValue(TreeNode<T> *root){
        return root->left ? getMinValue(root->left) : root;
    }
    /**
     * Returns the maximum value in the binary tree rooted at the given node.
     * @param root The root of the binary tree to search for the maximum value.
     * @return The maximum value in the binary tree rooted at the given node.
     */
    TreeNode<T> *getMaxValue(TreeNode<T> *root){
        return root->right ? getMaxValue(root->right) : root;
    }
    
    /**
     * Removes the node with the given item value from the AVL tree.
     * If the item is not found in the tree, the tree is left unchanged.
     * If the node to be removed has two children, the in-order successor
     * (the minimum value in the right subtree) is used to replace the node.
     * The tree is then rebalanced using rotations as necessary.
     * @param root The root of the AVL tree.
     * @param item The value to be removed from the AVL tree.
     * @return The updated root of the AVL tree after the removal.
     */
    TreeNode<T> *remove(TreeNode<T> *root, const T &item)k
    {
        if (root == NULL)
            return root;
        if (item > root->info)
        { // go right
            root->right = remove(root->right, item);
        }
        else if (item < root->info)
        {
            root->left = remove(root->left, item);
        }
        else
        { // found the item to remove
            bool has_one_left_child = (root->right == NULL);
            bool has_one_right_child = (root->left == NULL);

            if (has_one_left_child)
            { // has one child (right) or has no children
                TreeNode<T> *temp = root->left;
                delete root;
                return temp;
            }
            else if (has_one_right_child)
            { // has one child (left) or has no children
                TreeNode<T> *temp = root->right;
                delete root;
                return temp;
            }
            else
            { // has two chidldren
                TreeNode<T> *temp = getMaxValue(root->left);
                root->info = temp->info;
                root->left = remove(root->left, temp->info);
            }
        }

        --this->nubmer_of_nodes; // update the number of nodes in the AVL tree
        // update the balance factor of each node
        int balanceFactor = getBalanceFactor(root);
        bool Is_left_heavy = (balanceFactor == 2);   // deleted from the right subtree
        bool Is_right_heavy = (balanceFactor == -2); // deleted from the left subtree

        if (Is_left_heavy)
        {
            int bf = getBalanceFactor(root->left);
            bool Is_left_left = (bf >= 0); // case1 & case2
            bool Is_left_right = (bf < 0); // case3

            if (Is_left_right)
                root->left = leftRotate(root->left);

            return rightRotate(root);
        }
        else if (Is_right_heavy)
        { // this mean deleted from the left subtree
            int bf = getBalanceFactor(root->right);
            bool Is_Right_Right = (bf <= 0);
            bool Is_Right_Left = (bf > 0);

            if (Is_Right_Left)
                root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        else {
            // no rotation (balance subtree)
            return root;
        }
    }


public:
    AVL(){ 
        this->nubmer_of_nodes = 0 ;
    }
    /**
     * Inserts a new node with the given item value into the AVL tree.
     * @param data The value to be inserted into the AVL tree.
     */
    void insert(const T& item) {
        this->root = insert(this->root, item);
    }
    
    /**
     * Returns the number of nodes in the AVL tree.
     * @return The number of nodes in the AVL tree.
     */
    int size() const { 
        return this->nubmer_of_nodes;
    }

    /**
     * Returns the minimum value in the AVL tree.
     * @return The minimum value in the AVL tree.
     */
    T getMinValue(){
        if (!this->empty())
            return getMinValue(this->root)->info;
    }
    /**
     * Returns the maximum value in the AVL tree.
     * @return The maximum value in the AVL tree.
     */
    T getMaxValue(){
        if (!this->empty())
            return getMaxValue(this->root)->info;
    }
    
    /**
     * Removes the node with the given item value from the AVL tree.
     * @param item The value of the node to be removed.
     */
    void remove(const T &item){
        if (this->empty() == 0)
            this->root = remove(this->root, item);
    }
    
    
    void print2D(TreeNode<T>*r, int space = 5, int SPACE = 10) { 
        if (r == NULL) // Base case  1
            return;
        space += SPACE; // Increase distance between levels   2
        print2D(r->right, space); // Process right child first 3 
        cout << endl;
        for (int i = SPACE; i < space; i++) // 5 
            cout << " "; // 5.1  
        cout << "["<<r->info  << "]\n"; // 6
        print2D(r->left, space); // Process left child  7
    }
    void print2D (){ 
        print2D(this->root);
    }

};

int main() 
{
    return  ;  
}