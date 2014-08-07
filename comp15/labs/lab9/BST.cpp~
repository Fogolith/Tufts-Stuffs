#include "BST.h"

BST::BST()
{
   
}

void BST::load(vector<Animal>& a, int num)
{  
	root=new Node(&a[0]);
	for(unsigned int i=1; i<a.size(); i++)
	{
	    //   cout << "in loop\n";
	    add(&a[i], root, root);
	}
}

void BST::inorderPrint()
{
    if(root!=NULL);
    inorderPrint(root, 0);
}

void BST::inorderPrint(Node* a, int depth)
{
    if(a->left!=NULL)
	inorderPrint(a->left, depth+1);

    for (int i = 0; i < depth; i++)
	cout << "-";
    cout << a->animal->getName() << endl;

    if(a->right!=NULL)
	inorderPrint(a->right, depth + 1);

}

void BST::add(Animal* b)
{
    cout << " in add" << endl;

    Node* temp=root;
    while(1)
    {
	if(b==temp->animal){
	    return;
        }
	else if(b<temp->animal)
	{
	    if(temp->left==NULL){
	         temp->left=new Node(b);
                 return;
            }
	     else
		 temp=temp->left;
	}
	else if(b>temp->animal)
	{
	    if(temp->right==NULL){
		temp->right=new Node(b);
		return;
	    }
	    else
		temp=temp->right;
	} 
	
    }
}

void BST::insert(Node* toAdd, Node*& location, Node* parent)
{
        if(location==NULL)
	{
	    location=toAdd;
	    toAdd->parent=parent;
	}
	if(location->animal->getName()==toAdd->animal->getName())
	{
	    cout << "duplicate!" << endl;
	    return;
	}
	if(toAdd->animal->getName() > location->animal->getName())
	{
	    insert(toAdd, location->right, location);
	}
	if(toAdd->animal->getName() < location->animal->getName())
	{
	    insert(toAdd, location->left, location);
	}
}



	   
void BST::add(Animal* b, Node*& location, Node*& parent){
    if(location == NULL){
	location = new Node(b);
	location->parent=parent;
    return;
    }

    if (location->animal->getName() == b->getName())
	return;
    if(location->animal->getName() > b->getName()){
	add(b, location->left, location);
    }
    else if (location->animal->getName() < b->getName()){
	add(b, location->right, location);
    }
    else
	cout <<"trouble\n";

}





