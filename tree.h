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
    // Each node will have an ID, data, and a vector of children
    string id;
    U data;
    vector<Node<U>*> children;

    // TODO: Write constructor
    // Comtructor that sets the ID and value of the node
    Node(const string &nodeID, const U &value) {
        id = nodeID;
        data = value;
    };
};

template <typename T>
class Tree {
private:
    // Root is a private member
    Node<T>* root;

public:
    // Tree constructor that sets the root to nullptr
    Tree() {
        root = nullptr;
    };
    // TODO: Initialize root pointer to nullptr

    // Create root allocates memory, assigns ID and data, and then sets the node as
    // the root
    void createRoot(const string &id, const T &value) {
        // First make sure the root is not nullptr
        if (root != nullptr) {
            // If so, return
            return;
        }
        // Now create the root by creating a new node and setting it with ID and value
        root = new Node<T>(id, value);

    };
    // TODO: Allocate memory, assign id, assign data, set as root

    // Adds a node based on a location of the parent using parentID
    void addNode(const string &parentID, const string &childID, const T &value)
    {
        // Vector that keeps track of the nodes that have been created by addNode
        static vector<Node<T>*> created;
        // Find the parent using the given parentID and the findNode method
        Node<T>* parent = findNode(parentID);
        // If the parent does not exist, simply return
        if (!parent) {
            return;
        }
        // Initialize the child pointer to nullptr
        Node<T>* child = nullptr;
        // For all nodes n in the vector created, if the node ID and the childID are equal,
        // the child now equals that node in created. Makes sure we are not adding two nodes
        // with the same ID
        for (Node<T>* n : created) {
            if (n->id == childID) {
                child = n;
                break;
            }
        }
        // If we did not find the child, then try to search the tree for a matching childID
        if (!child) {
            child = findNode(childID);
        }

        // If the previous did not work, we know the child does not exist yet
        if (!child) {
            // Create a new node with childID and value
            child = new Node<T>(childID, value);
            // Make sure to add this to the created vector
            created.push_back(child);
        }
        // However, if the previous if statement did work, now make sure there is a value in it.
        // If so, we will not change it
        else {
            // If the value is empty, we can add our value
            if (!value.empty()) {
                child->data = value;
            }
        }
        // Now add to this parent's children vector
        parent->children.push_back(child);
    };
    // TODO: Find parent, create child, link parent to child
    // TODO: Support repeated children under multiple parents

    // This method uses DFS to search the tree
    Node<T>* findNode(const string &id) {
        // First make sure the tree has a root, and if it doesn't return nullptr
        if (!root) {
            return nullptr;
        }

        // Create a vector called stack (since we are going to be using it like a stack)
        vector<Node<T>*> stack;

        // First push the root in (push_back adds to the end)
        stack.push_back(root);

        // While the stack is not empty
        while (!stack.empty()) {
            // The current pointer is the back of the vector
            Node<T>* cur = stack.back();
            // Pop the back
            stack.pop_back();

            // If the current (back) equals the ID we are looking for, return that
            if (cur->id == id) {
                return cur;
            }
            // Now, using this current pointer, find all its children and push them into the stack
            // to examine to see if any of them are matching the ID
            for (Node<T>* child : cur->children) {
                stack.push_back(child);
            }
        }
        // Final case: if none of this worked, return nullptr (the ID was not found)
        return nullptr;
    };
    // TODO: Use DFS or BFS to search tree

    // This method will print all of the nodes of the tree
    void printAll() {
        // First make sure the tree has a root, if not return nullptr
        if (!root) {
            return;
        }
        // Create two vectors, one will be used like a stack to traverse, and the other
        // will be used to store the nodes that have already been visited
        vector<Node<T>*> stack;
        vector<Node<T>*> alreadyVisitedList;
        // Now push the root into the stack
        stack.push_back(root);

        // While the stack is not empty
        while (!stack.empty()) {
            // Use a current pointer to the current back of the stack
            Node<T>* cur = stack.back();
            // Now pop the back of the stack
            stack.pop_back();

            // Automatically assign wasVisited to false
            bool wasVisited = false;
            // Traverse through the alreadyVisitedList to see if we have already seen
            // this node
            for (Node<T>* v : alreadyVisitedList) {
                // If we have, assign wasVisited to true
                if (v == cur) {
                    wasVisited = true;
                }
            }
            // If wasVisited is true, move on to the next node
            if (wasVisited) continue;

            // Push the current pointer into the already visited list because we have already
            // visited it
            alreadyVisitedList.push_back(cur);
            // Print out the node with the ID and data
            cout << "Node " << cur->id << ": " << cur->data << endl;

            // If the children vector for this node is empty
            if (cur->children.empty()) {
                // Print "No children" underneath
                cout << "No children" << endl;
            }
            // If the children vector for this node is not empty
            else {
                // For all children, print each of them out
                for (Node<T> *child : cur->children) {
                    cout << "  Child " << child->id << ": " << child->data << endl;
                    // Add each of the children to the stack
                    stack.push_back(child);
                }
            }
            cout << endl;
        }
    };
    // TODO: Print entire structure in readable form
    // This will control how the user interacts with the program
    void playGame() {
        // If no root, return
        if (!root) {
            return;
        }
        // Print a "Begin Adventure" to indicate the adventure has begun
        cout << "===== Begin Adventure =====\n" << endl;
        // Use a current pointer which will not point to the root
        Node<T>* cur = root;
        // Create a vector visited to keep track of visited nodes
        vector<string> visited;

        // Use a while(true) loop because the conditions that make the loop false
        // will simply break out of the loop
        while (true) {
            // Print out the current node's data
            cout << cur->data << endl;
            // Add the current node to the visited vector
            visited.push_back(cur->id);

            // Create a new vector called validChildren (this is for each node)
            vector<Node<T>*> validChildren;
            // Iterate through all the children in the current nodes children vector
            for (Node<T>* child : cur->children) {
                // Create a boolean variable that indicates whether a current node has been
                // visited and immediately set it to false
                bool visitedNode = false;
                // Use a for loop to iterate through all the nodes in the visited vector
                for (const string& id : visited) {
                    // If any of the ID's match with the child ID, assign visitedNode to true
                    if (id == child->id) {
                        visitedNode = true;
                        break;
                    }
                }
                // If we have not visited the node, and the data of the particular child is not empty,
                // then push the node into validChildren
                if (!visitedNode && !child->data.empty()) {
                    validChildren.push_back(child);
                }
            }

            // However, if valid children is empty, this means we have finished
            // the choose your adventure game
            if (validChildren.empty()) {
                cout << "There are no further paths." << endl;
                cout << "Your journey ends here.\n" << endl;
                break;
            }

            // This is what the user will use to put in what node they would like to go
            // to next
            cout << "Choose your next action:" << endl;
            // Iterates through all the valid children nodes, and prints the choices
            for (int i = 0; i < validChildren.size(); i++) {
                cout << i + 1 << ". " << validChildren[i]->data << endl;
            }

            // Create a variable to store the user's choice
            int choice;
            // Use a while loop to find the selection and make sure it is valid
            while (true) {
                // Print and get in the user input
                cout << "Selection: ";
                cin >> choice;
                // Make sure the choice is greater than or equal to 1 and less than the
                // size of validChildren
                if (choice >= 1 && choice <= validChildren.size())
                    break;
                // Print "Invalid choice. Try again."
                cout << "Invalid choice. Try again." << endl;
            }
            cout << endl;

            // Now move the current pointer to the validChildren of the next node
            cur = validChildren[choice - 1];
        }

        // Let the user know that the adventure is complete
        cout << "===== Adventure Complete =====" << endl;
    }



    // Tree destructor
    ~Tree() {
        // Make sure there is a root
        if (!root) {
            return;
        }

        // Create two vectors, one used as a stack and one used to track the
        // visited nodes
        vector<Node<T>*> stack;
        vector<Node<T>*> visited;
        // Push back the root into the stack
        stack.push_back(root);

        // While the stack is not empty
        while (!stack.empty()) {
            // Use a current pointer to the back of the stack
            Node<T>* cur = stack.back();
            // Pop the back of the stack
            stack.pop_back();
            // Set a boolean variable tracking whether the node was already visited to false
            bool wasVisited = false;
            // For all the nodes in the visited vector
            for (Node<T>* v : visited) {
                // If the node equals one of the nodes in the visited vector
                if (v == cur) {
                    // Then set wasVisited to true
                    wasVisited = true;
                }
            }
            // If the current node was already visited, then move on to the next node
            if (wasVisited) continue;
            // Push the current node to the visited vector
            visited.push_back(cur);
            // Now iterate through all the children nodes for this node
            for (Node<T>* child : cur->children) {
                // Push all the children into the stack
                stack.push_back(child);
            }
        }
        // After this, we have basically transferred all the nodes to the visited
        // vector, so now we just go through and delete all of them
        for (Node<T>* n : visited) {
            delete n;
        }
        // Finally, set the root to nullptr
        root = nullptr;
    };
    // TODO: Free all allocated memory
};

#endif //FA25EC3_TREE_H