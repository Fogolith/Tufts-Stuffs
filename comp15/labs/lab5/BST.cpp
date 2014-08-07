//
//  BST.cpp
// Comp 15 Spring 2012 Lab 5
//

#include "BST.h"

/**** CONSTRUCTOR ****/

//BST()
// args: none
// returns: none 
// calls: none 
// does: initializes root to NULL
//
BST::BST(){
	root = NULL;
}

/**** PUBLIC INSERT METHOD CALLS... ****/

//insert(string word)
// args: 
//		1. string (word to be added to the list)
// returns: none 
// calls: insert(string, Node*)
// does: if given word isn't already in the list, it is added
//
void BST::insert(string entry){
	
	if(root == NULL){
		root = new Node;
		root->word = entry;
		root->left = NULL;
		root->right = NULL;
	}
	else
		insert(entry, root);
}

//printTree()
// args: none
// returns: none 
// calls: print()
// does: calls print() with root and 0 as arguments
//
void BST::printTree(){
  print(root, 0); 
}

//print()
// args: none
// returns: none 
// calls: print()
// does: prints the contents of the tree with their depth
//
void BST::print(Node * n, int depth){

  if (n == 0) {
    return;
  }

  for (int i = 0; i < depth; i++) {
    cout << ". ";
  }
  cout << n->word << endl;

  print(n->left, depth+1);
  print(n->right, depth+1);
}

/**** ...PRIVATE INSERT METHOD ****/

//insert(string entry, Node *ptr)
// args: 
//		1. string (value to enter into the BST)
//		2. Node* (root of the tree)
// returns: none
// calls: insert(string, Node*)
// does: adds a entry value in proper place on the BST if it's not already there
//      
void BST::insert(string entry, Node *ptr){
	if(ptr->word == entry)
		return;
	else if(entry < ptr->word){
		if(ptr->left == NULL){
			ptr->left = new Node;
			ptr = ptr->left;
			ptr->word = entry;
			ptr->left = NULL;
			ptr->right = NULL;
			return;
		}
		else
			insert(entry, ptr->left);
	}
	else{
		if(ptr->right == NULL){
			ptr->right = new Node;
			ptr = ptr->right;
			ptr->word = entry;
			ptr->left = NULL;
			ptr->right = NULL;
			return;
		}
		else
			insert(entry, ptr->right);	
	}
}






/*****************************************************/
/*************** IMPLEMENT THESE FIRST ***************/
/*****************************************************/

/**** PUBLIC TRAVERSAL METHODS CALL... ****/

//printPreOrderTraversal()
// args: none
// returns: none 
// calls: preorderPrint(Node* root)
// does: prints tree in value-left-right order
//
void BST::printPreOrderTraversal(){
  if(root != NULL)
    preorderPrint(root);
}

//printPostOrderTraversal()
// args: none
// returns: none 
// calls: postorderPrint()
// does: prints tree in left-right-value order
//
void BST::printPostOrderTraversal(){
  if(root != NULL)
    postorderPrint(root);
}

//printInOrderTraversal()
// args: none
// returns: none 
// calls: inorderPrint()
// does: prints tree in left-value-right order
//
void BST::printInOrderTraversal(){
  if(root != NULL)
    inorderPrint(root);
}

/**** ...PRIVATE TRAVERSAL METHODS ****/

// comment?
void BST::preorderPrint(Node* theNode){

    cout << theNode->word << endl;
    if(theNode->left!=NULL)
    preorderPrint(theNode->left);
    if(theNode->right!=NULL)
    preorderPrint(theNode->right);

}

// comment?
void BST::postorderPrint(Node* theNode){

    if(theNode->left!=NULL)
	postorderPrint(theNode->left);
    if(theNode->right!=NULL)
	postorderPrint(theNode->right);

    cout << theNode->word << endl;

}

// comment?
void BST::inorderPrint(Node* theNode){

    if(theNode->left!=NULL)
	inorderPrint(theNode->left);

    cout << theNode->word << endl;

    if(theNode->right!=NULL)
	inorderPrint(theNode->right);
}







/*****************************************************/
/*************** IMPLEMENT THESE SECOND **************/
/*****************************************************/

/**** PUBLIC SIZE METHODS CALLS... ****/

//size()
// args: none
// returns: number of nodes in the tree
// calls: size(Node*)
// does: returns the number of the nodes in the tree (i.e., words)
//
int BST::size(){
	return size(root);
}

/**** PRIVATE SIZE METHOD ****/

// comment?  
int BST::size(Node *ptr){

    int LS=0;
    int RS=0;
    int node=1;
    if((ptr->left==NULL)&&(ptr->right==NULL))
    {
	return 1;
    }

    if(ptr->left!=NULL)
    {
	LS=size(ptr->left);
    }

    if(ptr->right!=NULL){
        RS=size(ptr->right);
     }

node+=RS;
node+=LS;

return node;
	
}




/**** PUBLIC HEIGHT METHOD CALLS... ****/

//height()
// args: none 
// returns: maximum height of the tree 
// calls: height(Node*)
// does: computes the maximum height of the tree
//
int BST::height(){
	return height(root);
}

/**** ...PRIVATE HEIGHT METHOD ****/

// comment?   
int BST::height(Node* ptr){

    int LH=0;
    int RH=0;
    
    if((ptr->left==NULL)&&(ptr->right==NULL))
    {
	return 1;
    }

    if(ptr->left!=NULL)
	LH=height(ptr->left);

    if(ptr->right!=NULL)
	RH=height(ptr->right);

    if(LH>RH)
	return LH+1;

    if(RH>LH)
	return RH+1;


}


/**** PUBLIC FIND METHOD CALLS... ****/

//find(string needle)
// args: 
//		1. string (value to search the tree for)
// returns: true if needle is found, else false
// calls: find(string, Node*)
// does: searches for a given word in the tree, *** case insensitive ***
//
bool BST::find(string searchTerm){
	return find(searchTerm, root);
}

/**** ...PRIVATE FIND METHOD ****/

// comment?  
bool BST::find(string searchTerm, Node* subtree){

    if(subtree->word==searchTerm)
	return true;

    if(subtree->left!=NULL)
    	find(searchTerm, subtree->left);
       
    if(subtree->right!=NULL)
    	find(searchTerm, subtree->right);

    return false;
}

/**** DESTRUCTOR CALLS****/

//~BST()
// args: none 
// returns: none
// calls: destroyTree()
// does: deletes all nodes 
//        
BST::~BST(){
	destroyTree(root);
}

/**** PRIVATE METHOD THAT DELETES ANY NODES ****/

// comment?   
void BST::destroyTree(Node* ptr){

}







/*****************************************************/
/*************** IMPLEMENT THESE LAST ***************/
/*****************************************************/

/**** PUBLIC METHOD ***/

// comment?
bool BST::isPerfect(){


}


/**** PUBLIC METHOD ***/

// comment?
bool BST::isComplete(){
 
 
}


/**** PUBLIC METHOD ***/

// comment?
void BST::printBreadthFirstTraversal(){


}


