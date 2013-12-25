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

	int getID() { return id; }
	void setID(int i) { id = i; }

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

	FibNode (T k, int i) {
		key = k;
		parent = NULL;
		leftSib = NULL;
		rightSib = NULL;
		child = NULL;
		flag = false;
		rank = 0;
		id = i;
	}

private:
	T key;
	FibNode<T> * parent;
	FibNode<T> * leftSib;
	FibNode<T> * rightSib;
	FibNode<T> * child;
	bool flag;
	int rank;
	int id;

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
		delete minNode;
		heapSize -= 1;


		FibNode<T> * ranks[MAX_RANK];
		for (i = 0; i<MAX_RANK; i++) ranks[i] = NULL;
		cur = rootEntry;
		next = NULL;
		while (cur != NULL) {
			next = cur->getRightSib();
			int curRank = cur->getRank();
			if (ranks[curRank] != NULL) cur = merge(cur, ranks[curRank]);
			ranks[cur->getRank()] = cur;
			cur = next;
		}
	}


	//.........................................................................
	FibNode<T> * push(T k, int id) {
		if (rootEntry == NULL) {
			rootEntry = new FibNode<T>(k, totalNum++);
			minNode = rootEntry;
			heapSize = 1;
		}
		else {
			addToRootList(new FibNode<T>(k, totalNum++));
			heapSize += 1;
		}
	}


	//.........................................................................
	int size() {
		return heapSize;
	}


	//.........................................................................
	void decreaseKey(FibNode<T> * nd, T k) {
		if (empty()) return;
		/*
		//Judge if the new key is actually larger than the previous one
		FibNode<T> tmp(k, -1);
		if (nd->compare(&tmp)) { //If yes, cancel the decreaseKey operation
			return;
		}
		*/

		//keep doing the decreaseKey operation
		nd->setKey(k);
		if (nd->compare(minNode)) minNode = nd;
		if (nd->getParent() != NULL) {
			FibNode<T> * par = nd->getParent();
			if (nd->compare(par)) { //If nd is smaller than the parent
				deleteFromParent(nd, par);
			}
		}
	}


	//.........................................................................
	FibonacciHeap() {
		rootEntry = NULL;
		minNode = NULL
		heapSize = 0;
		totalNum = 0;
	}

	~FibonacciHeap() {
	}

	int static const MAX_RANK = 32;

private:
	FibNode<T> * rootEntry;
	FibNode<T> * minNode;
	int heapSize;
	int totalNum;

	void addToRootList(FibNode<T> * nd) {
		nd->setLeftSib(NULL);
		nd->setRightSib(rootEntry);
		rootEntry->setLeftSib(nd);
		rootEntry = nd;
		if ( rootEntry->compare(minNode) ) minNode = rootEntry;
	}

	void deleteFromRootList(FibNode<T> * nd) {
		left = nd->getLeftSib();
		right = nd->getRightSib();
		if (rootEntry == nd) rootEntry = right;
		if (left != NULL) left->setRightSib(right);
		if (right != NULL) right->setLeftSib(left);
	}

	void deleteFromParent(FibNode<T> * nd, FibNode<T> * par) {
		nd->setParent(NULL);
		par->decRank();
		FibNode<T> * left = nd->getLeftSib();
		FibNode<T> * right = nd->getRightSib();

		if (par->getChild == nd) par->setChild(right); //nd is the first child
		if (left != NULL) left->setRightSib(right);
		if (right != NULL) right->setLeftSib(left);

		addToRootList(nd);

		if (par->isMark()) {
			grandPar = par->getParent();
			par->unmark();
			if (grandPar != NULL) deleteFromParent(par, grandPar);
		}
		else par->mark();
	}

	FibNode<T> * merge(FibNode<T> * a, FibNode<T> * b) {
		FibNode<T> * big = a->compare(b) ? b : a;
		FibNode<T> * sma = a->compare(b) ? a : b;
		deleteFromRootList(sma);
		FibNode<T> * child = big->getChild();
		big->setChild(sma);
		big->incRank();
		sma->setParent(big);
		sma->setRightSib(child);
		if (child != NULL) child->setLeftSib(sma);
		return big;
	}

};
