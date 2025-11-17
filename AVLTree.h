/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <vector>
#include <optional>

using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;


    };

private:
    AVLNode* root;
    size_t treeSize;

public:
    bool insert(const std::string& key, size_t value);
    bool remove(const std::string& key);
    bool contains(const std::string& key) const;
    std::optional<size_t> get(const std::string& key) const;
    size_t& operator[](const std::string& key);
    vector<std::string> findRange( const std::string& lowKey, const std::string& highKey) const;
    std::vector<std::string> keys() const;
    size_t size() const;
    size_t getHeight() const;
    AVLTree(const AVLTree& other);
    void operator=(const AVLTree& other);
    ~AVLTree();
    friend std::ostream& operator<<(ostream& os, const AVLTree & avlTree);

    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    // bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node); //this is where node height assignments should be done

};

#endif //AVLTREE_H
