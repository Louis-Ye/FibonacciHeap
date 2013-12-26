FibonacciHeap
=============
<b>Version 0.01</b> <br>

1. A C++ library which offers Fibonacci Heap data structure and corresponding operations.
2. The interfaces of this library are much like the ones of piority queue in STL.
3. Comparison depending on the operator < .
4. <b>LICENSE</b>: MIT
5. Usage:

````cpp
#include "fibonacciheap.h"
#include <iostream>

using namespace std;

#define N 10

int main() {

	FibonacciHeap<int> fh;	
	FibNode<int> * arr[N];	
	for (int i=0; i<N; i++) arr[i] = fh.push(10+i);

	cout << fh.top() << endl;
	fh.pop();
	cout << fh.top() << endl;
	fh.decreaseKey(arr[3], 2);
	cout << fh.top() << endl;
	fh.pop();
	cout << fh.top() << endl;

	return 0;
}

````

The output is like:
```cpp
10
11
2
11
```
