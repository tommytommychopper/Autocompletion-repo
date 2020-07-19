#include<iostream>
using namespace std;

#include "tnode.h"
#ifndef BST_H
#define BST_H

class BST{
    public:
    	  BST():  root(NULL) {};
        ~BST(){ clean(root); root = NULL; };    
		    void insert(string akey, string aval){
			  if(root == NULL){
			  root = new Tnode(akey, aval);
						return;
					}
					root = insert(root, akey, aval);
				}
				void print_inorder(){ 
					print_inorder(root);
                    cout << endl;
				}
				void findPrint(string akey){ 
					findPrint(root, akey); 
				}
				void heightPrint(){ 
					heightPrint(root); 
					cout << endl;
				}

				void updateHeight(Tnode *cur);
				int getHeight(Tnode *cur);
				int balanceFactor(Tnode *cur);
				void printBF(){
					if(root!= NULL)
						printBF(root);
					cout << endl;
				}
		private:
				void heightPrint(Tnode *cur);
				Tnode* insert(Tnode *cur, string akey, string aval);
				void print_inorder(Tnode *cur);
				Tnode *root = NULL;
				void clean(Tnode* cur);
				Tnode* copy(Tnode* cur);
				void findPrint(Tnode* cur, string key);
				void printBF(Tnode *cur);
				Tnode* restoreBalance(Tnode *cur);
				Tnode* rightRotation(Tnode *cur);
				Tnode* left_rightRotation(Tnode *cur);
				Tnode* leftRotation(Tnode *cur);
				Tnode* right_leftRotation(Tnode *cur);
};

#endif
