#include "AVLTree.h"

#include <string>

using KeyType = string;
using ValueType = size_t;

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

AVLTree::AVLNode::AVLNode(const KeyType key, const size_t value) : left(nullptr), right(nullptr)
{
    this->key = key;
    this->value = value;
}

///insert - bool down the tree to nullptr, add value and rebalance
/*
Insert a new key-value pair into the tree. After a sucessful insert, the tree is rebalanced if necessary.
Duplicate keys are disallowed. The insert() method should return true if the insertion was
successful, false otherwise. If the insertion was unsuccessful, such as when a duplicate is
attempted to be inserted, the method should return false.
*/
bool AVLTree::insert(const KeyType& key, ValueType value)
{
    insert(key, value, root);
}

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
        current->height = current->getHeight();
        return resize;
    }
    if (key > current->key)
    {
        bool resize = insert(key, value, current->left);
        current->height = current->getHeight();
        return resize;
    }
    return false;
}

///remove - bool down the tree to nullptr, add removeNode
/*
If the key is in the tree, remove() will delete the key-value pair from the tree. The memory allocated
for the node that is removed will be released. After removing the key-value pair, the tree is
rebalanced if necessary. If the key was removed from the tree, remove() returns true, if the key
was not in the tree, remove() returns false.
*/
bool AVLTree::remove(const KeyType& key)
{
    return remove(key, root);
}
bool AVLTree::remove(const KeyType& key, AVLNode*& current)
{
    if (current == nullptr)
    {
        return false;
    }
    if (key < current->key)
    {
        bool resize = remove(key, current->left);
        if (resize) current->height = current->getHeight();
        return resize;
    }
    if (key > current->key)
    {
        bool resize = remove(key, current->left);
        if (resize) current->height = current->getHeight();
        return resize;
    }
    removeNode(current);
    return true;
}

AVLTree::AVLNode* AVLTree::getNode(const KeyType& key, AVLNode* current)
{
    if (current == nullptr)
    {
        return nullptr;
    }
    if (key < current->key) return getNode(key, current->left);
    if (key > current->key) return getNode(key, current->left);
    return current;
}

const AVLTree::AVLNode* AVLTree::readNode(const KeyType& key, const AVLNode* current) const
{
    if (current == nullptr) //add node
    {
        return nullptr;
    }
    if (key < current->key) return readNode(key, current->left);
    if (key > current->key) return readNode(key, current->left);
    return current;
}

///contains - check if AVL tree contains the value
/*
The contains() method returns true if the key is in the tree and false if the key is not in the tree.
The time complexity for contains() must be 𝒪︀(log2 𝑛).
*/
bool AVLTree::contains(const KeyType& key) const
{
    if (readNode(key, root) != nullptr) return true;
    return false;
}

///get - gets value associated with key value
/*
If the key is found in the tree, get() will return the value associated with that key. If the key is not
in the tree, get() will return something called std::nullopt, which is a special value in C++. The
get() method returns std::optional<size_t>, which is a way to denote a method might not
have a valid value to return. This approach is nicer than designating a special value, like −1, to
signify the return value is invalid. It’s also much better than throwing an exception if the key is
not found.
*/
optional<ValueType> AVLTree::get(const KeyType& key) const
{
    const AVLNode* node = readNode(key, root);
    if (node == nullptr) return nullopt;
    return node->value;
}

///operator[] overload - return a reference to a key's value
/*
The bracket operator, operator[], allows us to use our map the same way various programming
languages such as C++ and Python allow us to use keys to access values. The bracket operator will
work like get() in so that it will return the value stored in the node with the given key. We can
retrieve the value associated with a key by saying:
*/
ValueType& AVLTree::operator[](const KeyType& key)
{
    AVLNode* node = getNode(key, root);
    return node->value;
}

///findRange - return a vector of all values between two keys
/*
The findRange() method should return a C++ std::vector of size_t containing all the values
associated with keys ≥ lowKey and keys ≤ highKey. For each key found in the given range, there
will be one value in the vector. If no matching key-value pairs are found, the function should return
an empty vector.
*/
vector<ValueType> AVLTree::findRange(const KeyType& lowKey, const KeyType& highKey) const
{
    vector<ValueType> valueVec;
    findRange(lowKey, highKey, root, valueVec);
    return valueVec;
}

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
size_t AVLTree::AVLNode::getHeight() const
{
    if (isLeaf()) return 0;
    if (numChildren()==1)
    {
        if (left) return left->height + 1;
        return right->height + 1;
    }
    return max(left->height,right->height) + 1;
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

AVLTree::AVLNode* AVLTree::copyNode(const AVLNode* current, AVLNode*& clone)
{
    if (current == nullptr) return nullptr;
    clone = new AVLNode(current->key, current->value);

    clone->left = copyNode(current->left, clone->left);
    clone->right = copyNode(current->right, clone->right);
    clone->height = current->height;
}

///operator= overload - replace object with a deep copy of another
/*
Along with operator[] and operator<<, we can overload operator=, or the assignment operator.
If we do not, the same thing happens if we don’t implement the copy constructor. So, operator=
needs to also create a deep copy of the other tree. The main difference is the tree we want to copy
into may already have had elements inserted, so that memory needs to be released.
*/
void AVLTree::operator=(const AVLTree& other)
{
    clearNode(root);
    root = copyNode(other.root, root);
    treeSize = other.treeSize;
}

///deconstructor - deallocate allocated memory
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
AVLTree::~AVLTree()
{
    clearNode(root);
}

void AVLTree::clearNode(AVLNode*& current)
{
    if (current == nullptr) return;
    clearNode(current->left);
    clearNode(current->right);
    delete current;
}

///operator<< overload - print AVLTree to ostream
/*
In addition to these methods of AVLTree, you will also implement an operator to easily print out
the tree. The stream insertion operator, operator<<, is not a method of the AVLTree class, and as
such does not have access to the private data of AVLTree. To get around this, you can declare
operator<< as a friend function inside of the AVLTree class (put the keyword friend before the
declaration, but not the definition), which will give it access to the private member data and
functions.

operator<< is another example of operator overloading in C++, similar to the bracket operator.
This operator will allow us to print the contents of our tree using the normal syntax:
cout << myAvlTree << endl;

You should output the key-value pairs in the tree in a way that represents the structure of the tree.
One approach would be to print the tree “sideways” using indentation to show the structure. For
example, the tree in Figure 1 could be printed like Code Fig. 1 If you turn your head sideways, you
can see how this represents the tree with {S: 83} as the root with no indentation, the root’s
children {G: 71} and {Z: 90} indented a certain amount, and their children {C: 67}, {J: 74} and
{X: 88} indented by twice as much.

This style of printout can be achieved by doing a right-child-first in-order traversal of the tree,
with each call passing in the current depth + 1 to use as an indentation factor
*/
//friend std::ostream& operator<<(ostream& os, const AVLTree & avlTree)

/// number of non-null children?
size_t AVLTree::AVLNode::numChildren() const
{
    size_t num = 0;
    if (left != nullptr) num++;
    if (right != nullptr) num++;
    return num;
}

/// true if no children
bool AVLTree::AVLNode::isLeaf() const
{
    return numChildren() == 0;
}

/// remove node and reorder tree as needed
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
        remove(smallestInRight->key, root);

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;
    treeSize--;

    return true;
}

///// bool down tree and run removeNode when node is found
//bool AVLTree::remove(AVLNode *&current, KeyType key) {
//    return false;
//}
/// checks every parent node if needs rebalancing and rebalances;
void AVLTree::balanceNode(AVLNode* current)
{
    balance(current->key, root);
}

//needs to return
void AVLTree::balance(const KeyType& key, AVLNode*& current)
{
    //get heights of nodes to determine balance
    long long leftHeight = -1;
    long long rightHeight = -1;

    //traverse the tree and get balance
    if (current->left)
    {
        leftHeight = current->left->height;
        if (key < current->key ) balance(key, current->left);
    }
    if (current->right)
    {
        rightHeight = current->right->height;
        if (key > current->key) balance(key, current->right);
    }
    current->height = current->getHeight();
    // bar unneccisarry calculations
    if (current->height < 2) return;

    //check if tree needs rebalancing
    size_t balance = leftHeight - rightHeight;
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


        }
        else //right-right
        {
            AVLNode* hold = current->left->right;
            current->left->right = current;
            current = current->left;
            current->right->left = hold;

            current->height = max(current->left->height,current->right->height) + 1;
            current->height = max(hold->height,current->right->height + 1);
        }
    }
    if (balance <= -2) // hook is to the right
    {
    }
}
