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

        AVLNode(KeyType key, ValueType value);

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;


    };

public:

    AVLTree();
    bool insert(const KeyType& key, size_t value);
    bool remove(const KeyType& key);
    bool contains(const KeyType& key);// const;
    optional<ValueType> get(const KeyType& key);// const;
    ValueType& operator[](const KeyType& key);
    vector<ValueType> findRange( const KeyType& lowKey, const KeyType& highKey) const;
    std::vector<KeyType> keys() const;
    size_t size() const;
    size_t getHeight() const;
    AVLTree(const AVLTree& other);
    void operator=(const AVLTree& other);
    ~AVLTree();
    friend std::ostream& operator<<(ostream& os, const AVLTree & avlTree);

private:
    size_t treeSize;
    AVLNode* root;

    /* Helper methods for recursion */

    bool insert(const KeyType& key, size_t value, AVLNode*& pointer); //insert the thing
    AVLNode*& getNode(const KeyType& key, AVLNode*& pointer); //gets the node in the key or returns nullptr
    bool remove(const KeyType& key, AVLNode*& current); //return thing to delete
    bool contains(const KeyType& key, AVLNode*& current); //return thing to check
    std::optional<ValueType> get(const KeyType& key, AVLNode*& current);
    ValueType& opget(const KeyType& key, AVLNode*& current);
    vector<ValueType> findRange( const std::string& lowKey, AVLNode*& current, vector<ValueType>& vec);
    vector<ValueType> findRange( AVLNode*& current, const std::string& highKey, vector<ValueType>& vec);
    std::vector<KeyType> keys(AVLNode*& current) const;
    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    // bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the number of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node); //this is where node height assignments should be done

};

#endif //AVLTREE_H
