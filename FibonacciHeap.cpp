/*

Author: Louis Ye

ATTENTION:
In order to decrease the key, you needs to maintain an array of FibNode<T> * yourself.
For instance, you may record every FibNode<T> * returned by FibonacciHeap.push()

*/


#include <iostream>


//------------------------------------ NODE ------------------------------------
template<class T>
class FibNode {
public:
	T getKey() { return key; }
	void setKey(T k) { key = k; }
	bool compare(FibNode<T> * other) {
		return key < other->getKey();
	}

	FibNode<T> * getParent() { return parent; }
	void setParent(FibNode<T> * p) { parent = p; }

	FibNode<T> * getLeftSib() { return leftSib; }
	void setLeftSib(FibNode<T> * p) { leftSib = p; }

	FibNode<T> * getRightSib() { return rightSib; }
	void setRightSib(FibNode<T> * p) { rightSib = p; }

	FibNode<T> * getChild() { return child; }
	void setChild(FibNode<T> * p) { child = p; }

	void mark() { flag = true; }
	void unmark() { flag = false; }
	bool isMark() { return flag; }

	int getRank() { return rank; }
	void incRank() { rank += 1; }
	void decRank() { rank -= 1; }

	FibNode (T k) {
		key = k;
		parent = NULL;
		leftSib = NULL;
		rightSib = NULL;
		child = NULL;
		flag = false;
		rank = 0;
	}

private:
	T key;
	FibNode<T> * parent;
	FibNode<T> * leftSib;
	FibNode<T> * rightSib;
	FibNode<T> * child;
	bool flag;
	int rank;
};


//------------------------------------ HEAP ------------------------------------
template<class T>
class FibonacciHeap {
public:
	bool empty() {
		return rootEntry == NULL;
	}


	//.........................................................................
	FibNode<T> * topNode() {
		return minNode;
	}


	//.........................................................................
	T top() {
		if (empty()) return;
		return minNode->getKey();
	}


	//.........................................................................
	void pop() {
		if (empty()) return;

		FibNode<T> * cur = minNode->getChild();
		FibNode<T> * next = NULL;
		while (cur != NULL) {
			next = cur->getRightSib();
			addToRootList(cur);
			cur = next;
		}

		deleteFromRootList(minNode);
		heapSize -= 1;

		
	}


	//.........................................................................
	FibNode<T> * push(T k) {
		if (rootEntry == NULL) {
			rootEntry = new FibNode<T>(k);
			minNode = rootEntry;
			heapSize = 1;
		}
		else {
			addToRootList(new FibNode<T>(k));
			if ( rootEntry->compare(minNode) ) minNode = rootEntry;
			heapSize += 1;
		}
	}


	//.........................................................................
	int size() {
		return heapSize;
	}


	//.........................................................................
	void decreaseKey(FibNode<T> * nd, T ky) {
		if (empty()) return;
		/*
		//Judge if the new key is actually larger than the previous one
		FibNode<T> tmp(ky);
		if (nd->compare(&tmp)) { //If yes, cancel the decreaseKey operation
			return;
		}
		*/

		//keep doing the decreaseKey operation
		nd->setKey(ky);
		if (nd->compare(minNode)) minNode = nd;
		if (nd->getParent != NULL) {
			FibNode<T> * par = nd->getParent();
			if (nd->compare(par)) { //If nd is smaller than the parent

				nd->setParent(NULL);
				par->decRank();
				FibNode<T> * left = nd->getLeftSib();
				FibNode<T> * right = nd->getRightSib();

				if (par->getChild == nd) par->setChild(right); //nd is the first child
				if (left != NULL) left->setRightSib(right);
				if (right != NULL) right->setLeftSib(left);

				addToRootList(nd);
			}
		}
	}


	//.........................................................................
	FibonacciHeap() {
		heapSize = 0;
		rootEntry = NULL;
		minNode = NULL
	}

	~FibonacciHeap() {
	}

	int static const MAX_RANK = 128;

private:
	FibNode<T> * rootEntry;
	FibNode<T> * minNode;
	int heapSize;

	void addToRootList(FibNode<T> * nd) {
		nd->setLeftSib(NULL);
		nd->setRightSib(rootEntry);
		rootEntry->setLeftSib(nd);
		rootEntry = nd;
	}

	void deleteFromRootList(FibNode<T> * nd) {
		left = nd->getLeftSib();
		right = nd->getRightSib();
		if (rootEntry == nd) rootEntry = right;
		if (left != NULL) left->setRightSib(right);
		if (right != NULL) right->setLeftSib(left);
		delete nd;
	}
};
