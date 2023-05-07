#ifndef RADIXTREE_H
#define RADIXTREE_H

#include <iostream>
#include <string>
#include <vector>

// this class is the central idea of the project
// it defines a Radix Tree structure to quickly store, insert and search info
// many objects (maps, sets) that could do a similar task were banned in this projeect


template <typename ValueType>
class RadixTree {
private:
    struct Node {
        std::vector<Node*> children;
        bool isEndOfWord;
        ValueType* value;

        Node() : children(128, nullptr), isEndOfWord(false), value(nullptr) {} // note: project constraint of 128 possible characters
    };

    Node* root;

public:
    RadixTree() {
        root = new Node();
    }

    ~RadixTree() {
        treeDestructor(root);  // deallocates all children, not just root
    }

    void insert(std::string key, const ValueType& value) {
        Node* current = root;
        for (char c : key) { // finds correct part of tree
            int index = static_cast<int>(c);
            if (current->children[index] == nullptr) {
                current->children[index] = new Node();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
        if (current->value != nullptr) { // key exists? replace value
            *(current->value) = value;
        } else { // key does not exist? add new value
            current->value = new ValueType(value);
        }
    }

    // very similar to insert function, but simpler as it does not need to modify the tree
    // returns nullptr if to key found
    ValueType* search(std::string key) const {
        Node* current = root;
        for (char c : key) {
            int index = static_cast<int>(c);
            if (current->children[index] == nullptr) {
                return nullptr;
            }
            current = current->children[index];
        }
        if (current->isEndOfWord) {
            return current->value;
        } else {
            return nullptr;
        }
    }

private:
    // recursive function that deallocates momory of a node and its children
    void treeDestructor(Node* node) {
        if (node == nullptr) {
            return;
        }
        for (Node* child : node->children) {
            treeDestructor(child);
        }
        delete node->value;
        delete node;
    }
};

#endif
