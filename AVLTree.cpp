#include "AVLTree.h"

#include <string>

/* Additional challenges

insert(), remove(), contains(), get(), operator[], findRange(),
keys(), the copy constructor, the assignment operator, and the destructor
!!!must utilize recursion!!!

insert(), remove(), contains(),  get(), operator[],
𝒪︀(log2 𝑛)

size(), getHeight()
𝒪︀(1).
*/

/* Graded functions:

AVLTree::insert() stores key-value pairs in the tree and correctly rejects duplicate
keys. After insert() the tree remains balanced. Time complexity of insert() is
𝒪︀(log2 𝑛)

AVLTree::remove() correctly finds and deletes nodes from the tree without interfering
with subsequent search and insert operations. After remove() tree remains balanced.
Time complexity of remove is 𝒪︀(log2 𝑛).

AVLTree::contains() correctly returns true if the key is in the tree and false
otherwise. Time complexity of contains is 𝒪︀(log2 𝑛).

AVLTree::get() correctly finds, and returns the value associated if the key is found.
Returns nullopt when the key is not in the tree. Time complexity of get is 𝒪︀(log2 𝑛).

AVLTree::operator[] correctly returns a reference to the value associated with the
given key. There is no requirement for your project to handle missing keys in
operator[] Time complexity of operator[] is 𝒪︀(log2 𝑛).

AVLTree::findRange() correctly returns a C++ std::vector<size_t> matching the
keys in the specified range

AVLTree::keys() correctly returns a std::vector<size_t> with all of the keys
currently stored in the tree

AVLTree::size() correctly returns the number of key-value pairs in the tree in 𝒪︀(1).
time

AVLTree::getHeight() correctly returns the height of the tree in 𝒪︀(1). time.

operator<< is correctly overloaded as described above

Copy constructor correctly creates an independent copy of an AVL tree

AVLTree::operator= correctly creates an independent copy of the tree
*/
///insert - bool down the tree to nullptr, add value and rebalance
/*
Insert a new key-value pair into the tree. After a sucessful insert, the tree is rebalanced if necessary.
Duplicate keys are disallowed. The insert() method should return true if the insertion was
successful, false otherwise. If the insertion was unsuccessful, such as when a duplicate is
attempted to be inserted, the method should return false.
*/
bool AVLTree::insert(const std::string& key, size_t value)
{

}
bool AVLTree::insert(const std::string& key, AVLNode*& current)
{

}

///remove - bool down the tree to nullptr, add removeNode
/*
If the key is in the tree, remove() will delete the key-value pair from the tree. The memory allocated
for the node that is removed will be released. After removing the key-value pair, the tree is
rebalanced if necessary. If the key was removed from the tree, remove() returns true, if the key
was not in the tree, remove() returns false.
*/
//bool AVLTree::remove(const std::string& key)

///contains - check if AVL tree contains the value
/*
The contains() method returns true if the key is in the tree and false if the key is not in the tree.
The time complexity for contains() must be 𝒪︀(log2 𝑛).
*/
//bool AVLTree::contains(const std::string& key) const

///get - gets value associated with key value
/*
If the key is found in the tree, get() will return the value associated with that key. If the key is not
in the tree, get() will return something called std::nullopt, which is a special value in C++. The
get() method returns std::optional<size_t>, which is a way to denote a method might not
have a valid value to return. This approach is nicer than designating a special value, like −1, to
signify the return value is invalid. It’s also much better than throwing an exception if the key is
not found.
*/
//std::optional<size_t> AVLTree::get(const std::string& key) const

///operator[] overload - return reference to key's value
/*
The bracket operator, operator[], allows us to use our map the same way various programming
languages such as C++ and Python allow us to use keys to access values. The bracket operator will
work like get() in so that it will return the value stored in the node with the given key. We can
retrieve the value associated with a key by saying:
*/
//size_t& AVLTree::operator[](const std::string& key)

///findRange - return a vector of all values between to keys
/*
The findRange() method should return a C++ std::vector of size_t containing all the values
associated with keys ≥ lowKey and keys ≤ highKey. For each key found in the given range, there
will be one value in the vector. If no matching key-value pairs are found, the function should return
an empty vector.
*/
//vector<std::string> AVLTree::findRange( const std::string& lowKey, const std::string& highKey) const

///keys - return a vector of all keys in tree
/*
The keys() method will return a std::vector with all of the keys currently in the tree. The length
of the vector should be the same as the size of the tree
*/
//std::vector<std::string> AVLTree::keys() const

///size - return stored value for AVL tree's number of nodes
/*
The size() method returns how many key-value pairs are in the tree
*/
//size_t AVLTree::size() const

///getHeight - return stored value for AVL tree's root node
/*
The getHeight() method will return the height of the AVL tree
*/
//size_t AVLTree::getHeight() const

///copy constructor
/*
perform a deep copy
*/
//AVLTree::AVLTree(const AVLTree& other)

///operator= overload - replace object with a deep copy of another
/*
Along with operator[] and operator<<, we can overload operator=, or the assignment operator.
If we do not, the same thing happens if we don’t implement the copy constructor. So, operator=
needs to also create a deep copy of the other tree. The main difference is the tree we want to copy
into may already have had elements inserted, so that memory needs to be released.
*/
//void AVLTree::operator=(const AVLTree& other)

///deconstructor - make sure to deallocate allocated memory
/*
When an object goes out of scope, the memory used by its member variables is released back to the
operating system. This means only the root variable is released, but not the memory root points
to. In order to release the memory occupied by our nodes, we need to implement what C++ calls the
destructor. A better name might be deconstructor, because as the constructor initializes any
memory for the object, the destructor will release that memory. When an object goes out of scope,
if it has a destructor defined, the destructor is called. Thus, we want our destructor to visit all the
nodes in our tree (a postorder traversal?) and use delete to release the memory taken by each
node.
*/
//AVLTree::~AVLTree()

///operator<< overload - print AVLTree to ostream
/*
Similar to other projects, we will store everything associated with a key-value pair in a node. The
BSTNode (or AVLNode) should have, at a minimum, std::string key, size_t value, BSTNode* left,
and BSTNode* right. Additionally, since the height() method needs to be 𝒪︀(1), you will also want to
store a member in each node for the height of the node. The height will then need to be updated on
every call to insert() and remove(). Storing the height in the node allows you to calculate a node’s
height in 𝒪︀(1) by checking the height of it’s left and right children. It also allows you to return the
height of the tree in 𝒪︀(1) as the height of a tree is the height of it’s root node.
You also need to keep track of how many times a key of right is entered into that nodes left subtree.

I recommend having in your BSTNode class methods to perform operations such as finding the current
height of the node, finding the balance of the node, finding how many children the node has, and
possibly whether or not a node is a leaf or not. Another good method would be to return the sum of the values
located in a nodes subtrees.

Keep in mind, these methods contribute to the time complexity of the algorithm they are utilized in, such
as insert() and remove(). Therefore, to keep those operations in 𝒪︀(log2 𝑛), they cannot be any
worse than 𝒪︀(log2 𝑛). If the method to find the height of a node is 𝒪︀(𝑛), that makes any operation
that uses it at least 𝒪︀(𝑛).
*/
//friend std::ostream& operator<<(ostream& os, const AVLTree & avlTree)

/// number of non-null children?
size_t AVLTree::AVLNode::numChildren() const {
    return 0;
}
/// true if no children
bool AVLTree::AVLNode::isLeaf() const {
    return false;
}
/// returns auto-updating value stored as node height
size_t AVLTree::AVLNode::getHeight() const {
    return 0;
}
/// remove node and reorder tree as needed
bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}
///// bool down tree and run removeNode when node is found
//bool AVLTree::remove(AVLNode *&current, KeyType key) {
//    return false;
//}
///// checks every parent node if needs rebalancing and rebalances;
//void AVLTree::balanceNode(AVLNode *&node) {
//}
