FibonacciHeap
=============
<b>Version 0.01</b> <br>

1. A C++ library which offers Fibonacci Heap data structure and corresponding operations.
2. <b>LICENSE</b>: MIT
3. <b>Interfaces</b>: The interfaces of this library are much like the ones of piority queue in STL.
4. <b>Comparison</b>: depends on the operator < .
5. <b>Decrease Key</b>: In order to do so, you have to maintain the pointer of each node by yourself.
6. <b>Creating new node</b>: The <i>push(T key)</i> method will return the pointer and give the new node an integer ID according to the pushing sequence. You can also set the ID for each new node in your own purpose with the <i>push(T key, int id)</i> method.
7. <b>Time complexity</b>: <ul><li><b>push</b> (insert): O(1)</li>  <li><b> top</b> (get min): O(1)</li>  <li><b>pop</b> (delete min): O(log(n)) amortized time</li>  <li><b>decrease key</b>: O(1) amortized time</li> </ul>
8. <b>Usage</b>: 

```cpp
#include <iostream>
#include "fibonacciheap.h"

using namespace std;

#define N 10

int main() {

    FibonacciHeap<int> fh;  
    FibonacciHeap<int>::FibNode * arr[N];  
    for (int i=0; i<N; i++) arr[i] = fh.push(10+i);

    cout << fh.top() << endl;
    fh.pop();
    cout << fh.top() << endl;
    fh.decreaseKey(arr[3], 2);
    cout << fh.top() << endl;
    fh.pop();
    cout << fh.top() << endl;

    FibonacciHeap<int>::FibNode * tmp = fh.topNode();
    cout << tmp->getKey() << ' ' << tmp->getID() << endl;

    fh.push(-100, 77);
    tmp = fh.topNode();
    cout << tmp->getKey() << ' ' << tmp->getID() << endl;

    return 0;
}

```

The output is like:
```cpp
10
11
2
11
11 1
-100 77
```
