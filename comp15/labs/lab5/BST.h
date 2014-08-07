//
//  BST.h
// Comp 15 Spring 2012 Lab 5
// 

#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

using namespace std;

struct Node {
    string word;
    Node *left;
    Node *right;
};

class BST
{

/* Class invariants:
 * the data value of each node in the tree is greater than any data value  
 * in its left subtree and less than any data value in its right subtree.
*/

public:
    BST();
      // Constructor: sets root to NULL

    void insert(string word);
      // Postcondition: if word didn't exist in tree, it is added 
    
    void printTree();
      // prints the contents of the tree and their depth
    
    void printPreOrderTraversal();
      // Postcondition: The nodes of the tree are printed in value-left-right order 
    
    void printPostOrderTraversal();
      // Postcondition: The nodes of the tree are printed in left-right-value order 
    
    void printInOrderTraversal();
      // Postcondition: The nodes of the tree are printed in left-value-right order 
    
    int size();
      // Postcondition: returns the number of the nodes in the tree

    int height();
      // Description: computes the longest branch of the tree
      // Postcondition: returns 0 if empty tree, else size of the longest branch of tree

    bool find (string searchTerm);
      // Description: searches for a given word in the tree
      // Postcondition: returns true if word is in found in tree, else false    
      

    /**** MORE COMPLICATED METHODS: DO THESE LAST ****/
      
    bool isPerfect();
      // Description: determines if the tree is "perfect." That is, if every node other 
      //  than the leaves has two children
      // Postcondition: returns true if BST is perfect, else false
      
    bool isComplete();
      // Description: determines whether the tree is "complete." That is, if every level
      //  except possibly the last if full, and all nodes are as far left as possible
      // Postcondition: returns true if tree is complete, else false
      
    void printBreadthFirstTraversal();
      // Description: visits the nodes of the tree one level at a time from left to right,
      //  or right to left, printing values along the way.  In other words, it would print
      //  the root value, then the root's children, then the children of those nodes, and
      //  so on, as opposed to visiting the left subtree of the root before the right.
      // Postcondition: values in the tree's nodes are printed in breadth-first order
      
    ~BST();
      // Description:  Destructor 
      // Postcondition: Any nodes remaining in the tree are deallocated
      
private:
    Node *root;
    
    void insert (string word, Node* root);
      // Description: inserts a word into the tree if not found
      // Precondition: word is or is not in the tree 
      // Postcondition: word is in its proper place in the tree
    
    void print(Node* n, int depth);
     // prints the contents of the tree and their depth
    
    /* PRINTING THE TREE CONTENTS: DO THESE FIRST*/
    void preorderPrint(Node* aNode);
      // Postcondition: The nodes of the tree are printed in root-left-right order 

    void postorderPrint(Node* aNode);
      // Postcondition: The nodes of the tree are printed in left-right-root order 

    void inorderPrint(Node* aNode);
      // Postcondition: The nodes of the tree are printed in left-root-right order 
    
    /*BASIC TREE OPERATIONS: DO THESE SECOND*/
    int size(Node* root);
      // Description: calculates and returns the number of nodes in the tree 
      // Postcondition: size of the tree is returned
    int height(Node* root);
      // Description: calculates and returns the longest branch in the tree 
      // Postcondition: height of the tree is returned
    bool find(string searchTerm, Node* root);
      // Description: searches the tree for a word 
      // Postcondition: returns true if word found, else false 
    void destroyTree(Node *ptr);
      // Description: deletes any allocated Nodes attached to root 
      
};

#endif


