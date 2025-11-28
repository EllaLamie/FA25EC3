//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
   TEMPLATE TREE CLASS
   Multiple parents may point to the same child.
   Students must manage storage, pointers, and dynamic allocation.

   Requirements:
   1. Templated Tree class.
   2. Nodes stored dynamically.
   3. Each node has:
      - id
      - data
      - vector of children pointers
   4. Students must prevent memory leaks.
   5. Students must create createRoot, addNode, findNode, print functions, etc.

   DO NOT IMPLEMENT ANYTHING HERE.
   Only placeholders and TODO comments.
*/


template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;

    // TODO: Write constructor
    Node(const string &nodeID, const U &value) {
        id = nodeID;
        data = value;
    };
};

template <typename T>
class Tree {
private:
    Node<T>* root;

public:
    Tree() {
        root = nullptr;
    };
    // TODO: Initialize root pointer to nullptr

    void createRoot(const string &id, const T &value) {
        Node<T>* createdRoot = new Node<T>(id, value);
        root = createdRoot;

    };
    // TODO: Allocate memory, assign id, assign data, set as root

    void addNode(const string &parentID, const string &childID, const T &value) {
        Node<T>* parent = findNode(parentID);
        if (!parent) {
            cout << "No parent found" << endl;
        }
        Node<T>* child = new Node<T>(childID, value);
        parent->children.push_back(child);

    };
    // TODO: Find parent, create child, link parent to child
    // TODO: Support repeated children under multiple parents

    Node<T>* findNode(const string &id) {
        if (!root) {
            return nullptr;
        }
        vector<Node<T>*> stack;
        vector<Node<T>*> visited;
        stack.push_back(root);

        while (!stack.empty()) {
            Node<T>* cur = stack.back();
            stack.pop_back();

            if (cur->id == id) {
                return cur;
            }
            for (Node<T>* child : cur-> children) {
                stack.push_back(child);
            }
        }
        return nullptr;
    };
    // TODO: Use DFS or BFS to search tree

    void printAll() {
        if (!root) {
            return;
        }
        vector<Node<T>*> stack;
        vector<Node<T>*> alreadyVisitedList;
        stack.push_back(root);

        while (!stack.empty()) {
            Node<T>* cur = stack.back();
            stack.pop_back();

            bool wasVisited = false;
            for (Node<T>* v : alreadyVisitedList) {
                if (v == cur) {
                    wasVisited = true;
                    break;
                }
            }
            if (wasVisited) continue;

            alreadyVisitedList.push_back(cur);
            cout << cur << endl;
            for (Node<T>* child : cur->children) {
                stack.push_back(child);
            }
        }
    };
    // TODO: Print entire structure in readable form

    ~Tree() {
        if (!root) {
            return;
        }

        vector<Node<T>*> stack;
        vector<Node<T>*> visited;
        stack.push_back(root);
        while (!stack.empty()) {
            Node<T>* cur = stack.back();
            stack.pop_back();
            bool wasVisited = false;
            for (Node<T>* v : visited) {
                if (v == cur) {
                    wasVisited = true;
                    break;
                }
            }
            if (wasVisited) continue;
            visited.push_back(cur);
            for (Node<T>* child : cur->children) {
                stack.push_back(child);
            }
        }
        for (Node<T>* n : visited) {
            delete n;
        }
        root = nullptr;
    };
    // TODO: Free all allocated memory
};

#endif //FA25EC3_TREE_H
