## vetor.begin()
[why const_iterator](https://stackoverflow.com/questions/42580761/why-does-stdbegin-always-return-const-iterator-in-such-a-case)

## swapZeroCount
the basic idea is that to count the distinct non-trivial cycle of the cyclic representation of the permutation of the array.

e.g `0 3 2 1 5 4`, cycle (1 3 2)(4 5), two cycles so need, basically, a cycle of length l, need (l-1) Swap(0,*), if 0 is in that cycle, take for example (0,1,2). If 0 not in that cycle, need to conjugate (0,x) where x is an element of that cycle, e.g
(0,1)(1,3,2)(0,1)^(-1).  So two additional cycles needed. 
In the algorithm, count the total length of the nontrivial cycles (for each cycle, len - 1) and the cyclenum, then swaps = totalLen + 2 * (cycle - 1)  (the two stands for the conjugation of the (0,x)). But if the 0 is fixed, then initially, cycle = 1.

Need to pay special attention if the 0 is fixed. 
