#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX_VAL 10000
#define MIN_VAL -10000
typedef struct Edge
{
    int _start,_end,_weight;
    Edge(int st, int en, int weight) : _start(st), _end(en),_weight(weight)
    {

    }
    
    Edge(): _start(-1), _end(-1),_weight(MIN_VAL)
    {

    }

    bool operator<(const Edge & e1) 
    {
        return _weight < e1._weight;
    }

    bool operator==(const Edge & e1)
    {
        return _weight == e1._weight;
    }
    
    bool operator<=(const Edge & e1)
    {
        return _weight <= e1._weight;
    }
}Edge;

typedef struct MyHeap
{
    int sizeMyHeap;
    vector<Edge> vec_edge;
    MyHeap(int _N, int _E)
    {
        sizeMyHeap = 0;
        vec_edge.resize(_E + 1);
        buildMyHeap(_E);
    }

    void insert(Edge & edge)
    {
        int index;
        for(index = ++sizeMyHeap; edge < vec_edge[index/2]; index /= 2) {
            vec_edge[index] = vec_edge[index/2];
        }
        vec_edge[index] = edge;
    }

    void buildMyHeap(int _E)
    {
        int st,end,weight;
        while(_E--) {
            cin >> st >> end >> weight;
            Edge edge(st,end,weight);
            insert(edge);
        }
    }

    Edge deleteMin()
    {
        Edge minEdge = vec_edge[1];
        Edge temp = vec_edge[sizeMyHeap--];
        int parent,child;
        for(parent = 1; parent * 2 <= sizeMyHeap; parent = child) {
            child = parent * 2;
            if(child < sizeMyHeap && vec_edge[child + 1] < vec_edge[child]) {
                child++;
            }
            if(temp <= vec_edge[child]) {
                break;
            }
            vec_edge[parent] = vec_edge[child];
        }
        vec_edge[parent] = temp;
        return minEdge; 
    }

    bool isEmpty() const
    {
        return sizeMyHeap == 0;
    }
}MinMyHeap;

typedef struct UnionFind
{
    int _vecSize;
    vector<int> unionFind;
    UnionFind(int _N)
    {
        // the unionFind has valid index 1 to _N
        _vecSize = _N + 1;
        unionFind.resize(_vecSize);
        for(int i = 1; i <= _N; i++) {
            unionFind[i] = -1;
        }
    }

    void Union(int i, int j) {
        int w1 = numOfNodes(i);
        int w2 = numOfNodes(j);
        if(w1 >= w2) {
            int rootNode_i = root(i);
            unionFind[rootNode_i] -= w2;
            int rootNode_j = root(j);
            unionFind[rootNode_j] = rootNode_i;
        }
        else {
            int rootNode_j = root(j);
            unionFind[rootNode_j] -= w1;
            int rootNode_i = root(i);
            unionFind[rootNode_i] = rootNode_j;
        }
    }

    int root(int vertex)
    {
        int i = vertex;
        int parent = unionFind[i];
        int grandParent;
        while(parent > 0) {
            grandParent = unionFind[parent];
            if(grandParent > 0) {
                unionFind[i] = grandParent;
            }
            
            i = parent;
            parent = grandParent;
        }

        if(vertex != i) {
            unionFind[vertex] = i;
        }
        return i;
    }

    // the number of points in that connected set which contains i
    int numOfNodes(int i)
    {
        int rootNode = root(i);
        return -unionFind[rootNode];
    }

    bool isConnected(int i, int j)
    {
        return root(i) == root(j);
    }
}UnionFind;

typedef struct MyGraph {
    size_t _row;
    size_t _col;
    // int* _array;
    vector<vector<int> > _array;
    MyHeap edgeHeap;
    UnionFind vertexUF;
    MyGraph(int Vertex, int edges) : _row(Vertex),_col(Vertex), edgeHeap(Vertex,edges), vertexUF(Vertex)
    {
        // // _array = new int[row * col];
        // _array.resize(Vertex);
        // while(edges--) {
        //     int i,j;
        //     cin >> i >> j;
        //     // if(i > j) {
        //     //     _array[j].push_back(i);
        //     // }
        //     // else {
        //     //     _array[i].push_back(j);
        //     // }
        //     _array[i].push_back(j);
        //     _array[j].push_back(i);
        // }
        // for(size_t i = 0; i < Vertex; i++) {
        //     sort(_array[i].begin(),_array[i].end());
        // }

        
    }

    ~MyGraph() {
        // delete [] _array;
    }

    int & operator()(size_t i, size_t j) {
        if(i >= _row || i < 0 || j >= _col || j < 0) {
            throw("index invalid\n");
        }
        return _array[i][j];
    }

    void kruskalMinSpanningTree()
    {
        vector<Edge> minSpannTree;
        int distance = 0;
        while(minSpannTree.size() < _row - 1 && !edgeHeap.isEmpty()) {
            Edge eMin = edgeHeap.deleteMin();
            if(!isLoop(eMin._start, eMin._end)) {
                minSpannTree.push_back(eMin);
                vertexUF.Union(eMin._start,eMin._end);
                distance += eMin._weight;
            }
        }
        if(minSpannTree.size() < _row - 1) {
            cout << -1 << endl;
        }
        else {
            cout << distance << endl;
        }
    }

    bool isLoop(int i,int j) {
        return vertexUF.isConnected(i,j);
    }

    void DFSvertex(int i, int* arr)
    {
        if(arr[i]) {
            return;
        }
        cout << i << " ";
        arr[i] = 1;
        for(vector<int>::iterator iter = _array[i].begin(); 
            iter != _array[i].end(); iter++) {
            DFSvertex(*iter,arr);
        }

    }
    void DFS() {
        int visited[_row];
        for(size_t i = 0; i < _row; i++) {
            visited[i] = 0;
        }
        for(size_t i = 0; i < _row; i++) {
            if(!visited[i]) {
                cout << "{ ";
                DFSvertex(i,visited);
                cout << "}\n";
            }   
        }
    }

    void BFS() {
        queue<int> queueVertex;
        
        int visited[_row];
        for(size_t i = 0; i < _row; i++) {
            visited[i] = 0;
        }
        for(size_t i = 0; i < _row; i++) {
            if(!visited[i]){
                cout << "{ ";
                queueVertex.push(i);
                visited[i] = 1;
                while(!queueVertex.empty()) {
                    int neighbor = queueVertex.front();
                    queueVertex.pop();
                    cout << neighbor << " ";
                    visited[neighbor] = 1;
                    for(size_t l = 0; l < _array[neighbor].size(); l++) {
                        int v = _array[neighbor][l];
                        if(!visited[v]) {
                            queueVertex.push(v);
                            visited[v] = 1;
                        }
                    }
                }
                cout << "}" << endl;
            }    
        }
    }
}MyGraph;
void MyGraphTraverse();

int main()
{
    MyGraphTraverse();
}

void MyGraphTraverse()
{
    int Vertex,edges;
    cin >> Vertex >> edges;
    MyGraph gph(Vertex,edges);
    gph.kruskalMinSpanningTree();
}
