/*

Author: Louis Ye

ATTENTION:
In order to decrease the key, you needs to maintain an array of FibNode<T> * yourself.
For instance, you may record every FibNode<T> * returned by FibonacciHeap.push()
For user's convenience,
there is a integer field of getID() and setID() in each FinNode<T> object

*/

#include <iostream>

//------------------------------------ NODE ------------------------------------
template<class T>
class FibNode {
public:
	T getKey() { return key; }
	void setKey(T k);
	bool compare(FibNode<T> * other);

	int getID();
	void setID(int i);

	FibNode<T> * getParent();
	void setParent(FibNode<T> * p);

	FibNode<T> * getLeftSib();
	void setLeftSib(FibNode<T> * p);

	FibNode<T> * getRightSib();
	void setRightSib(FibNode<T> * p);

	FibNode<T> * getChild();
	void setChild(FibNode<T> * p);

	void mark();
	void unmark();
	bool isMark();

	int getRank();
	void incRank();
	void decRank();

	FibNode (T k, int i);

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
	bool empty();

	FibNode<T> * topNode();

	T top();

	void pop();

	FibNode<T> * push(T k);

	int size();

	void decreaseKey(FibNode<T> * nd, T k);

	void printHeap();

	FibonacciHeap();

	~FibonacciHeap();

	int static const MAX_RANK = 32;

private:
	FibNode<T> * rootEntry;
	FibNode<T> * minNode;
	int heapSize;
	int totalNum;

	void addToRootList(FibNode<T> * nd);

	void deleteFromRootList(FibNode<T> * nd);

	void deleteFromParent(FibNode<T> * nd, FibNode<T> * par);

	FibNode<T> * merge(FibNode<T> * a, FibNode<T> * b);

};