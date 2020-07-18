#include<iostream>
using namespace std;

#include "bst.h"
void BST::updateHeight(Tnode *cur){
	if(!cur)
		return;
	int lh = getHeight(cur->left);
	int rh = getHeight(cur->right);
	int myh = (lh > rh) ? lh+1 : rh+1;
	cur->height = myh;
}//updateHeight

int BST::getHeight(Tnode *cur){
	if(!cur)
		return -1;
	return cur->height;
}//getHeight

int BST::balanceFactor(Tnode *cur){
	if(!cur)
		return 0;
	int bf = getHeight(cur->left) - getHeight(cur->right);
	return bf;
}//balanceFactor

void BST::printBF(Tnode *cur){
	if(cur != NULL){
		printBF(cur->left);
		cout<< balanceFactor(cur) << " ";
		printBF(cur->right);
	}
}//printBF

void BST::heightPrint(Tnode *cur){
	if(cur != NULL){
		heightPrint(cur->left);
		cout << cur->height << " ";
		heightPrint(cur->right);
	}
}//heightPrint

void BST::findPrint(Tnode *cur, string akey){
	if(cur != NULL){
		if(cur->key == akey){
			int asize = (int)(cur->value).size();
			for(int i = 0; i < asize ; i++)
				cout << (cur->value)[i] << " ";
			cout << endl;
			return;
		}else if(akey < cur->key)
			findPrint(cur->left, akey);
		else
			findPrint(cur->right, akey);
	}
}//findPrint()

void BST::print_inorder(Tnode *cur){
	if(cur == NULL)
		return;
	print_inorder(cur->left);
	cout << "(" << cur->key << "){";
	int asize = (int)(cur->value).size();
	for(int i = 0; i < asize; i++)
		cout << (cur->value)[i] << " " ;
	cout << "} ";
	print_inorder(cur->right);
}//print_inorder

void BST::clean(Tnode *cur){
	if(cur == NULL)
		return;
	clean(cur->left);
	clean(cur->right);
	delete cur;
}//clean()

Tnode* BST::rightRotation(Tnode* cur){
	Tnode* leftChild = cur->left;
	cur->left = cur->left->right;
	updateHeight(cur);
	leftChild->right = cur;
	updateHeight(leftChild);
	return leftChild;
}//rightRotation

Tnode* BST::left_rightRotation(Tnode* cur){
	Tnode* leftChild = cur->left;
	Tnode* lrChild = cur->left->right;
	leftChild->right = lrChild->left;
	lrChild->left = leftChild;
	updateHeight(leftChild);
	updateHeight(lrChild);
	cur->left = lrChild->right;
	lrChild->right = cur;
	updateHeight(cur);
	updateHeight(lrChild);
	return lrChild;
}//left_rightRotation

Tnode* BST::leftRotation(Tnode* cur){
	Tnode* rightChild = cur->right;
	cur->right = rightChild->left;
	updateHeight(cur);
	rightChild->left = cur;
	updateHeight(rightChild);
	return rightChild;
}//leftRotation

Tnode* BST::right_leftRotation(Tnode* cur){
	Tnode* rightChild = cur->right;
	Tnode* rlChild = cur->right->left;
	rightChild->left = rlChild->right;
	rlChild->right = rightChild;
	updateHeight(rightChild);
	updateHeight(rlChild);
	cur->right = rlChild->left;
	rlChild->left = cur;
	updateHeight(cur);
	updateHeight(rlChild);
	return rlChild;
}//restoreBalance

Tnode* BST::restoreBalance(Tnode *cur){
	if(!cur){ return cur; }
	if(balanceFactor(cur) == 2){
		if(balanceFactor(cur->left) >= 0){
			cur = rightRotation(cur);
		}
		else if(balanceFactor(cur->left) < 0){
			cur = left_rightRotation(cur);	
		}
	}
	else if(balanceFactor(cur) == -2){
		if(balanceFactor(cur->right) <= 0){
			cur = leftRotation(cur);
		}
		else if(balanceFactor(cur->right) > 0 ){
			cur = right_leftRotation(cur);
		}
	}
	return cur;
}

Tnode* BST::insert(Tnode *cur, string akey, string aval){
	if(akey < cur->key){
		if(cur->left == NULL){
			cur->left = new Tnode(akey, aval);
			updateHeight(cur);
			return cur;
		}
		else{
			cur->left = insert(cur->left, akey, aval);
			int bf = balanceFactor(cur);
			if(bf < -1 || bf > 1)
				cur = restoreBalance(cur);
			updateHeight(cur);
		}//else
	}//if
	else if(akey > cur->key){
		if(cur->right == NULL){
			cur->right = new Tnode(akey, aval);
			updateHeight(cur);
			return cur;
		}
		else{
			cur->right = insert(cur->right, akey, aval);
			int bf = balanceFactor(cur);
			if(bf < -1 || bf > 1)
				cur = restoreBalance(cur);
			updateHeight(cur);
		}
	}//else if
	else if(akey == cur->key){
		cur->value.push_back(aval);
		return cur;
	}
	return cur;
}//insert
