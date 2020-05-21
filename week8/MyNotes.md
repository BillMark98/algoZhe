## initialization of vector of class 
see [here](https://stackoverflow.com/questions/6142830/how-do-i-initialize-a-stl-vector-of-objects-who-themselves-have-non-trivial-cons)

I just add a default constructor for simplicity.....

## crucialPath
at first, for the comparison of the edges, I try to use the map to save the sequence of the edges received as input.   
The problem is the key, which is `pair<int,int>` could not simply be kept as a key by calling the constructor, e.g:
`mapEdge[pair(start,end)] = 10`  
since the constructed instance is a temporary object and will be deleted once the function in which the statement stands exits.   
So when running the code, segmentation fault emerged. Besides, such usage of key-value is a bit time-consuming (hard to guarantee O(1)), which should be the performance of the comparison of two objects.  

So as solution just use another vector `_sequenceEdge`  to save the order at the cost of massive space waste. (O(N^2) extra space)  

* dealing with `segmentation fault`
<ins>The golden rule: </ins>
**Don't forget to resize the vector before indexing it**

Every time the place where `segmentation fault` appears can imply possibly where the error may lie.  
For example, when input is given 
```
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2
```  
And segmentation fault emerged directly after the first line and 
we can see the following line will be treated by the system as command, so will lead to 
`1 2 4 command not found ` or something like that. That indicates probably u forgot to resize the array. Because that means that we have not even successfully scanned all input.

The idea of the function is based on the topological sort.  
To determine the minimum work hour. From source to sink, and update the time of each node dynamically.  
To find the crucial path, just turn around the direction, from sink to source and update the active time of each node dynamically.  
To find the crucial Path just check if there is a surplus of time at each edge connecting two points.