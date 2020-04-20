## sameTree.cpp
* note that when running, it's better to redirect the output to a file, or else what in the console stands, might look like this :
```
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0Yes
No
No
```  
In particular we see that at the last input line 
> 0Yes  
The program does not finish reading the last line before it began to output, so in particular the last input line is ignored. (because it does not has a newline at the end, I guess.)  
If instead, make sure that the last line has a `newline` at the end, then the output would be correct, like:
```
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
Yes
No
No
```


### myAvl.cpp
* dont forget to update the subtree's info (height, balance) after rotating

* do not do the update simply after insertion, like
```
    else if(_data > (*root) -> data) {
        insert(&((*root) -> rightNode), _data);
        (*root) -> balance--;
    }
    else {
        insert(&((*root) -> leftNode), _data);
        (*root) -> balance++;
    }
    (*root) -> height++;
```  

because it's possible that after insertion, the subtree structure varies, 
so the balance could not be calculated simply by increment or decrement by 1, so is height.  
e.g 
```
    70
  /   \
61    88
        \
        96
```  
and insert 120

```
    70
  /   \
61    96
    /   \
   88    120
```    
Now look at 70, it has balance -1, height 3  
now after modifying, the balance is -2 and height 4, which is incorrect

### myCBP
the idea is that first read in the data into an array.   
Sort the array in ascending order, then arrange the item in such an order  
that corresponds to a complete binary search tree (CBSP).  
(The CBSP is unique because the structure of a CBP given a certain number of vertices
is unique. Then if each vertex abides by the binary search tree property(left < root < right),   
then we know that the CBSP is unique)  

given for example 10 integers.
``` 
                      7(1)
                 /          \
               4(2)         10(3)
            /       \       /   \
          2(4)      6(5)  8(6)  9(7)
         /   \      /  
      1(8)  3(9)   5(10)
```  
where for example `1(8)` means that the smallest element(dataVec[1]) should  
be at the 8-th position of the array respresenting the CBSP  

we start from the bottom left and follow up the path on the most left side (8 -> 4 -> 2 -> 1)  
the function  `setTree` make sure that the subtree at given pivot is all set.