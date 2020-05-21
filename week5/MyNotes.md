### path in a heap
* note that when inserting an element, the crucial loop: 
```
for(index = ++HeapSize;H[index/2] > elem; index /= 2) {
        H[index] = H[index/2];
}
```  
the condition is `H[index/2] > elem` not `H[index] > elem`  


### huffcode.cpp

[cin char](http://www.fredosaurus.com/notes-cpp/io/reading-chars.html)


note that `shared_ptr<>x.reset(new TreeNode(nullptr))`  
the new pointer `x` is not a nullptr