#include "Animal.h"


struct Node
{
    Animal* animal; 
    Node* left;
    Node* right;
    Node* parent;

    Node(Animal* a){
	parent=NULL;
	left=NULL;
	right=NULL;
	animal=a;
    }
};

class BST
{

public:

    BST();
    void load(vector<Animal>& a);
    void add(Animal* b);
    void add(Animal* b, Node*& location, Node*& parent);
    void inorderPrint();

private:

    void inorderPrint(Node* a, int depth);
    Node* root;

    void insert(Node* toAdd, Node*& location, Node* parent);
   
};
