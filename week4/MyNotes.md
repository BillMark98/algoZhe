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