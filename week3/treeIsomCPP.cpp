#include<iostream>
 
using namespace std;
 
#define ElementType char
#define Tree int
#define Null -1
#define MaxTree 10
 
typedef struct{
 
	ElementType Data;
	Tree Left;
	Tree Right;
}TreeNode;
Tree BuildTree(TreeNode T[]);
int Isomorphic(Tree R1, Tree R2);
TreeNode T1[MaxTree], T2[MaxTree];
int main()
{
	 Tree Root1 = BuildTree(T1);
	 Tree Root2 = BuildTree(T2);
	 int Re = Isomorphic(Root1, Root2);
	 if (Re == 1)
		 cout << "Yes";
	 else
		 cout << "No";
}
 
 
Tree BuildTree(TreeNode T[])
{
	int N,Root;
	int check[MaxTree];
	char cl, cr;
	cin >> N;
	if (N == 0)
		return Null;
	for (int i = 0; i < N; i++) check[i] = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> T[i].Data >> cl >> cr;
		if (cl != '-')
		{
			T[i].Left = cl - '0';
			check[T[i].Left] = 1;
		}
		else T[i].Left = Null;
		if (cr != '-')
		{
			T[i].Right = cr - '0';
			check[T[i].Right] = 1;
		}
		else T[i].Right = Null;
	}
	for (int i = 0; i < N; i++)
	{
		Root = i;
		if (check[i] == 0) break;
		
	}
	return Root;
}
 
int Isomorphic(Tree R1, Tree R2) 
{
	if (R1 == Null&&R2 == Null)
		return 1; /*both roots empty*/
	if (((R1 == Null) && (R2 != Null)) || (R1 != Null&&R2 == Null))
		return 0;/*roots are diffent,one of is empty*/
	if (T1[R1].Data != T2[R2].Data)
		return 0;/*roots are different*/
	if (T1[R1].Left == Null && T2[R2].Left == Null)
		return Isomorphic(T1[R1].Right, T2[R2].Right);
	// if(T1[R1].Right==Null&& T2[R2].Right == Null)
	// 	return Isomorphic(T1[R1].Left, T2[R2].Left);
	if (((T1[R1].Left != Null) && (T2[R2].Left != Null)) && ((T1[T1[R1].Left].Data) == (T2[T2[R2].Left].Data)))
		return (Isomorphic(T1[R1].Right, T2[R2].Right) && Isomorphic(T1[R1].Left,T2[R2].Left));
	else
		return (Isomorphic(T1[R1].Right, T2[R2].Left) && Isomorphic(T1[R1].Left, T2[R2].Right));
 
}