#include "AVLTree.h"

#include <iostream>
#include <ostream>
#include <string>

using KeyType = string;
using ValueType = size_t;

///Constructor for AVLNode
/*
This creates a node with the chosen key and value, with left and right set to null
It also allows for the values of AVLNode to be assigned on creation
*/
AVLTree::AVLNode::AVLNode(const KeyType key, const size_t value) : left(nullptr), right(nullptr)
{
    this->key = key;
    this->value = value;
}

///Constructor for AVLTree
/*
This creates the AVL Tree which is a binary search tree that automatically balances itslef
This initializes the two values stored in the tree to null
*/
AVLTree::AVLTree() : treeSize(0), root(nullptr)
{
}

///insert - inserts a key/value pair into the tree, automatically rebalancing if necessary
/*
This is the public version of the insert method, which calls the private recursive one.
After adding the value to the tree, it runs the balance method to update the heights
and rebalance the tree

Returns: True if a value was inserted, False if the value already exists
*/
bool AVLTree::insert(const KeyType& key, ValueType value)
{
    bool status = insert(key, value, root);
    balance(key, root);
    return status;
}

///insert (helper) - private recursive helper function for the public insert function
/*
This function recursively iterates through the tree until it reaches a null pointer,

returns: true down the chain if node was successfully inserted, or false if the node already exists
*/
bool AVLTree::insert(const KeyType& key, ValueType value, AVLNode*& current)
{
    if (current == nullptr) //add node
    {
        current = new AVLNode(key, value);
        treeSize++;
        current->height = 0;
        return true;
    }
    if (key < current->key)
    {
        bool resize = insert(key, value, current->left);
        current->height = current->nodeHeight();
        return resize;
    }
    if (key > current->key)
    {
        bool resize = insert(key, value, current->right);
        current->height = current->nodeHeight();
        return resize;
    }
    return false;
}

///remove - removes a key/value pair from the tree, automatically rebalancing if necessary
/*
This is the public version of the remove method, which calls the private recursive one.
After removing the value to the tree, it runs the balance method to update the heights
and rebalance the tree

Returns: True if a value was removed, False if the value doesn't exist
*/
bool AVLTree::remove(const KeyType& key)
{
    bool status = remove(key, root);
    balance(key, root);
    return status;
}

///remove (helper) - private recursive helper function for the public remove function
/*
This function recursively iterates through the tree until it reaches a matching key, calling removeNode
once it has been found. It will stop and return false if it reaches a nullpointer
which signifies that the key is not in the tree.

returns: true if the node is found and successfully removed, or false if it reaches a null pointer
*/
bool AVLTree::remove(const KeyType& key, AVLNode*& current)
{
    if (current == nullptr)
    {
        return false;
    }
    if (key < current->key)
    {
        bool resize = remove(key, current->left);
        if (resize) current->height = current->nodeHeight();
        return resize;
    }
    if (key > current->key)
    {
        bool resize = remove(key, current->right);
        if (resize) current->height = current->nodeHeight();
        return resize;
    }
    removeNode(current);
    return true;
}

///getNode (helper) - returns the pointer to the corresponding key for the operator[] overload
/*
This recursive function returns the pointer that corresponds with the provided key
If the key is reached, it will return the found pointer. Otherwise, it will return nullptr.

Returns nullptr if key is not present, or its pointer if it is
*/
AVLTree::AVLNode* AVLTree::getNode(const KeyType& key, AVLNode* current)
{
    if (current == nullptr)
    {
        return nullptr;
    }
    if (key < current->key) return getNode(key, current->left);
    if (key > current->key) return getNode(key, current->right);
    return current;
}

///readNode (helper) - returns a read only pointer to the corresponding key for the get and contains functions
/*
This function returns the pointer to the node that corresponds to the given key, but the returned value is a
constant so as to work with constant functions.

Returns nullptr if key isn't present, or the node's pointer if it is
*/
const AVLTree::AVLNode* AVLTree::readNode(const KeyType& key, const AVLNode* current) const
{
    if (current == nullptr) //add node
    {
        return nullptr;
    }
    if (key < current->key) return readNode(key, current->left);
    if (key > current->key) return readNode(key, current->right);
    return current;
}

///contains - check if AVL tree contains the key
/*
contains checks the tree for the key,

returns true if the key is in the tree, or false if the key is not in the tree.
*/
bool AVLTree::contains(const KeyType& key) const
{
    if (readNode(key, root) != nullptr) return true;
    return false;
}

///get - gets value from the tree associated with the key
/*
If the key is found in the tree, get() will return the value associated with that key. If the key is not
in the tree, get() will return something called std::nullopt

returns: nullopt if key is not in the tree, or its value if it is
*/
optional<ValueType> AVLTree::get(const KeyType& key) const
{
    const AVLNode* node = readNode(key, root);
    if (node == nullptr) return nullopt;
    return node->value;
}

///operator[] overload - return a reference to a key's value
/*
overloads the [] operator so that the values of the tree can be accessed and modified directly

returns the value in the tree corresponding to the key placed between the brackets
*/
ValueType& AVLTree::operator[](const KeyType& key)
{
    AVLNode* node = getNode(key, root);
    return node->value;
}

///findRange - return a vector of all values between two keys
/*
Find range is a method to quickly check the values within parts of the tree
it is handled so that the values are displayed in ascending key order (via a left-right traversal)

returns a vector of values returned from every key between the two input keys
*/
vector<ValueType> AVLTree::findRange(const KeyType& lowKey, const KeyType& highKey) const
{
    vector<ValueType> valueVec;
    findRange(lowKey, highKey, root, valueVec);
    return valueVec;
}

///findRange (helper) - populates a vector with all values between two keys
/*
This helper function recursively attaches every vector within range from left to right

returns void, as the vector was passed in by reference (to be modified)
*/
void AVLTree::findRange(const KeyType& lowKey, const KeyType& highKey, const AVLNode* current,
                        vector<ValueType>& valueVec) const
{
    if (current == nullptr) return;
    if (lowKey < current->key) findRange(lowKey, highKey, current->left, valueVec);
    if (lowKey <= current->key && current->key <= highKey) valueVec.push_back(current->value);
    if (highKey > current->key) findRange(lowKey, highKey, current->right, valueVec);
}

///keys - return a vector of all keys in tree
/*
The keys() method will return a std::vector with all of the keys currently in the tree. The length
of the vector should be the same as the size of the tree
*/
vector<KeyType> AVLTree::keys() const
{
    vector<KeyType> keyVec;
    keys(root, keyVec);
    return keyVec;
}

///keys (helper) - populates a vector with all keys
/*
this recursive function handles populating a vector with keys in order

returns void, as the vector is modified by reference
*/
void AVLTree::keys(AVLNode* current, vector<KeyType>& keyVec) const
{
    if (current == nullptr) return;
    keys(current->left, keyVec);
    keyVec.push_back(current->key);
    keys(current->right, keyVec);
}

///size - return stored value for AVL tree's number of nodes
/*
The size() method returns how many key-value pairs are in the tree
*/
size_t AVLTree::size() const
{
    return treeSize; //make sure insert and delete increments this value properly
}

///getHeight - return stored value for the height of AVL tree's root node
/*
The getHeight() method will return the height of the AVL tree
*/
size_t AVLTree::getHeight() const
{
    return root->height;
}

///nodeHeight (helper) - return height of a node based off of it's children
/*
This function is useful in updating the heights of nodes and allows for much more concise code

returns the greater height between children with an additional +1 for the parent
*/
size_t AVLTree::AVLNode::nodeHeight() const
{
    if (isLeaf()) return 0;
    if (numChildren() == 1)
    {
        if (left) return left->height + 1;
        return right->height + 1;
    }
    return max(left->height, right->height) + 1;
}

///copy constructor - perform a deep copy
/*
perform a deep copy
*/
AVLTree::AVLTree(const AVLTree& other)
{
    root = copyNode(other.root, root);
    treeSize = other.treeSize;
}

///copyNode (helper) - recursively go through a tree and copy its contents over
/*
this function populates a tree with the contents of another through recursion
it doesn't check if the clone was wiped before copying, so that should be done beforehand

returns a pointer to a node to expedite the process
*/
AVLTree::AVLNode* AVLTree::copyNode(const AVLNode* current, AVLNode*& clone)
{
    if (current == nullptr) return nullptr;
    clone = new AVLNode(current->key, current->value);

    clone->left = copyNode(current->left, clone->left);
    clone->right = copyNode(current->right, clone->right);
    clone->height = current->height;
    return clone;
}

///operator= overload - replace object with a deep copy of another
/*
The overload of the = operator allows one to overwrite a tree with another
this will recursively both clear up the memory in the tree and copy over the other tree's contents

returns void
*/
void AVLTree::operator=(const AVLTree& other)
{
    clearNode(root);
    root = copyNode(other.root, root);
    treeSize = other.treeSize;
}

///deconstructor - deallocate allocated memory
/*
calls the clear function to make sure all memory allocated to nodes within are deallocated
*/
AVLTree::~AVLTree()
{
    clearNode(root);
}

///clearNode (helper) - recursively clears out all nodes for the deleting or overwriting of trees
/*
this function recursively goes through a tree, deleting all nodes on the way back
*/
void AVLTree::clearNode(AVLNode*& current)
{
    if (current == nullptr) return;
    clearNode(current->left);
    clearNode(current->right);
    delete current;
}

///operator<< overload - print AVLTree to ostream
/*
The overload of the << operator aims to let the AVLTree be output to the ostream
Since I am used to working on trees through the use of vectors, I figured a neat way
to show the form of a tree would be through nested brackets:
    [B:2 [A:1 [] []], [C:3 [] []]]
I also included the heights of each node to help with testing
*/
ostream& operator<<(ostream& os, const AVLTree& avlTree)
{
    string output;
    AVLTree::ostreamFeed(avlTree.root, output);
    os << output << endl;
    return os;
}

///ostreamFeed (helper) - turn entire AVLTree into a string
/*
This function recursively goes through the entire tree turning it into a string
that somewhat resembles the nested vectors I am familiar with.

There is no need to return the string as it is passed by reference
*/
void AVLTree::ostreamFeed(AVLNode* current, string& output)
{
    //Print empty brackets to signify an null pointer
    if (current == nullptr)
    {
        output += "[]";
        return;
    }

    //building a bunch of nested vectors to print out the tree:
    //[key:value (height) [leftchild], [rightchild]]
    output += "[";
    output += current->key;
    output += ":";
    output += to_string(current->value);
    output += " (";
    output += to_string(current->height);
    output += ") ";
    ostreamFeed(current->left, output);
    output += ", ";
    ostreamFeed(current->right, output);
    output += "]";
}

/// numChildren (helper) - number of non-null children
/*
This function helps determine how many branches of the tree need to be taken into account

returns the number of branches (children)
*/
size_t AVLTree::AVLNode::numChildren() const
{
    size_t num = 0;
    if (left != nullptr) num++;
    if (right != nullptr) num++;
    return num;
}

/// isLeaf (helper) - returns whether or not the node is a leaf node
/*
This function helps with logic regarding nodes without children
*/
bool AVLTree::AVLNode::isLeaf() const
{
    return numChildren() == 0;
}

/// removeNode (helper) - removes a node given by address
/*
This function handles the complex removal logic for when a node is removed from the AVL Tree

it returns true or false whether or not it functioned properly
*/
bool AVLTree::removeNode(AVLNode*& current)
{
    if (!current)
    {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf())
    {
        // case 1 we can delete the node
        current = nullptr;
    }
    else if (current->numChildren() == 1)
    {
        // case 2 - replace current with its only child
        if (current->right)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    else
    {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left)
        {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        size_t newValue = smallestInRight->value;
        cout << newKey << endl;
        remove(smallestInRight->key, root);

        current->key = newKey;
        current->value = newValue;

        current->height = current->nodeHeight();
        //balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;
    treeSize--;

    return true;
}

///balanceNode (helper) - get key and get balanced
/*
This helper function merely grabs the key for use in the primary helper function
*/
void AVLTree::balanceNode(AVLNode* current)
{
    balance(current->key, root);
}

///balance (helper) - balances the tree up to the specified node, updating the node heights in the process
/*
This function handles both updating the node heights as well as performing rotations to rebalance the tree
*/
void AVLTree::balance(const KeyType& key, AVLNode*& current)
{
    //get heights of nodes to determine balance
    long long leftHeight = -1;
    long long rightHeight = -1;

    //traverse the tree and get left & right node heights
    if (current->left)
    {
        if (key < current->key) balance(key, current->left);
        leftHeight = current->left->height;
    }
    if (current->right)
    {
        if (key > current->key) balance(key, current->right);
        rightHeight = current->right->height;
    }
    current->height = current->nodeHeight();

    // bar unneccisarry calculations
    if (current->height < 2) return;

    //check if tree needs rebalancing
    long long balance = leftHeight - rightHeight;

    if (balance >= 2) // hook is to the left
    {
        // check balance of hook node reusing left and right height variables
        leftHeight = -1;
        rightHeight = -1;
        if (current->left->left) leftHeight = current->left->left->height;
        if (current->left->right) rightHeight = current->left->right->height;
        balance = leftHeight - rightHeight;
        if (balance < 0) //left-right
        {
            rotateLeft(current->left);
            rotateRight(current);
        }
        else //left-left
        {
            rotateRight(current);
        }
    }
    if (balance <= -2) // hook is to the right
    {
        leftHeight = -1;
        rightHeight = -1;
        if (current->right->left) leftHeight = current->right->left->height;
        if (current->right->right) rightHeight = current->right->right->height;
        balance = leftHeight - rightHeight;

        if (balance > 0) //right-left
        {
            rotateRight(current->right);
            rotateLeft(current);
        }
        else //right-right
        {
            rotateLeft(current);
        }
    }
}

///rotateRight (helper) - do a right rotation on nodes
/*
This is a helper function for balance that exectutes a right rotation of the nodes
*/
void AVLTree::rotateRight(AVLNode*& current)
{
    //move nodes
    AVLNode* hold = current->left->right;
    current->left->right = current;
    current = current->left;
    current->right->left = hold;

    //update heights
    current->right->height = current->right->nodeHeight();
    current->height = current->nodeHeight();
}

///rotateLeft (helper) - do a left rotation on nodes
/*
This is a helper function for balance that exectutes a left rotation of the nodes
*/
void AVLTree::rotateLeft(AVLNode*& current)
{
    //move nodes
    AVLNode* hold = current->right->left;
    current->right->left = current;
    current = current->right;
    current->left->right = hold;

    //update heights
    current->left->height = current->left->nodeHeight();
    current->height = current->nodeHeight();
}
