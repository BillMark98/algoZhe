#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define MAX_LEN 10000
#define MAX_COST 10000
typedef struct NodeLengthCost
{
    int _node,_length,_cost;
    NodeLengthCost(int nd, int len, int co) : _node(nd),_length(len),_cost(co)
    {

    }
    NodeLengthCost() : _length(MAX_LEN),_cost(MAX_COST)
    {

    }

    // void operator=(const NodeLengthCost & n1)
    void setParam(int nd, int len, int co)
    {
        _node = nd;
        _length = len;
        _cost = co;
    }

    bool operator<(const NodeLengthCost & n1) 
    {
        if(_length < n1._length) {
            return true;
        }
        else if(_length == n1._length) {
            return _cost < n1._cost;
        }
        else {
            return false;
        }
    }

    bool operator == (const NodeLengthCost & n1) 
    {
        return (_length == n1._length) && (_cost == n1._cost);
    }

    bool operator <= (const NodeLengthCost & n1) 
    {
        bool smaller = (*this) < n1;
        if(smaller) {
            return true;
        }
        return (*this) == n1;
    }

    NodeLengthCost operator+(const NodeLengthCost & n1) 
    {
        NodeLengthCost nd(n1._node,_length + n1._length, _cost + n1._cost);
        return nd;
    }
}NodeLengthCost;

typedef struct MinHeap 
{
    vector<NodeLengthCost *> ptr_vecNLC;
    int sizeHeap;
    MinHeap(int n, vector<NodeLengthCost> & vec)
    {
        ptr_vecNLC.resize(n + 1);
        for(int i = 1; i < n + 1; i++) {
            ptr_vecNLC[i] = &(vec[i - 1]);
        }
        sizeHeap = n;
    }

    void BuildHeap()
    {
        for(int i = sizeHeap / 2; i >= 1; i--) {
            int c1,c2;
            c1 = i * 2;
            int child = c1;
            if(c1 < sizeHeap) {
                c2 = c1 + 1;
                if((*ptr_vecNLC[c2]) < (*ptr_vecNLC[c1])) {
                    child = c2;
                }
            }
            if((*ptr_vecNLC[child]) < (*ptr_vecNLC[i])) {
                NodeLengthCost * temp = ptr_vecNLC[i];
                ptr_vecNLC[i] = ptr_vecNLC[child];
                ptr_vecNLC[child] = temp;
            }
        }
    }

    NodeLengthCost* deleteMin()
    {
        NodeLengthCost * minItem = ptr_vecNLC[1];
        int parent,child;
        NodeLengthCost * temp = ptr_vecNLC[sizeHeap--];
        for(parent = 1; parent * 2 <= sizeHeap; parent = child) {
            child = parent * 2;
            if(child != sizeHeap && (*ptr_vecNLC[child + 1]) < (*ptr_vecNLC[child])) {
                child += 1;
            }
            if(*temp <= (*ptr_vecNLC[child])) {
                break;
            }
            else {
                ptr_vecNLC[parent] = ptr_vecNLC[child];
            }
        }
        ptr_vecNLC[parent] = temp;
        return minItem;
    }

}MinHeap;

typedef struct MyGraph {
    int _row;
    int _col;
    // int* _array;
    vector<vector<NodeLengthCost> > _array;
    MyGraph(int Vertex, int edges) : _row(Vertex),_col(Vertex)
    {
        // _array = new int[row * col];
        _array.resize(Vertex);
        while(edges--) {
            int i,j,len,cost;
            cin >> i >> j >> len >> cost;
            // if(i > j) {
            //     _array[j].push_back(i);
            // }
            // else {
            //     _array[i].push_back(j);
            // }
            _array[i].push_back(NodeLengthCost(j,len,cost));
            _array[j].push_back(NodeLengthCost(i,len,cost));
        }
        // for(int i = 0; i < Vertex; i++) {
        //     sort(_array[i].begin(),_array[i].end());
        // }
    }

    ~MyGraph() {
        // delete [] _array;
    }

    // int & operator()(int i, int j) {
    //     if(i >= _row || i < 0 || j >= _col || j < 0) {
    //         throw("index invalid\n");
    //     }
    //     return _array[i][j];
    // }

    
    void dijkstra(int i,int dest) 
    {
        vector<bool> collected;
        collected.resize(_row,false);
        collected[i] = true;
        int count = 1;
        vector<NodeLengthCost> dist;
        dist.resize(_row);
        int ilen = _array[i].size();
        for(int j = 0; j < ilen; j++) {
            dist[_array[i][j]._node] = _array[i][j];
        }
        dist[i].setParam(i,0,0);

        // for those not set yet, just update the node;
        for(int j = 0; j < _row; j++) {
            if(dist[j]._length >= MAX_LEN) {
                dist[j]._node = j;
            }
        }

        MinHeap mp(_row,dist);
        while(count < _row) {
            NodeLengthCost& n1 = *(mp.deleteMin());

            collected[n1._node] = true;
            count++;
            int index = n1._node;
            int len = _array[index].size();
            for(int j = 0; j < len; j++) {
                if(!collected[_array[index][j]._node]) {
                    NodeLengthCost & v2 = _array[index][j];
                    NodeLengthCost newDist = dist[n1._node] + v2;
                    if(newDist < dist[v2._node]) {
                        dist[v2._node].setParam(v2._node,newDist._length,newDist._cost);
                    }
                }
            }
            // update the Heap
            mp.BuildHeap();
        }
        cout << dist[dest]._length << " " << dist[dest]._cost << endl;
    }
    // void DFSvertex(int i, int* arr)
    // {
    //     if(arr[i]) {
    //         return;
    //     }
    //     cout << i << " ";
    //     arr[i] = 1;
    //     for(vector<int>::iterator iter = _array[i].begin(); 
    //         iter != _array[i].end(); iter++) {
    //         DFSvertex(*iter,arr);
    //     }

    // }
    // void DFS() {
    //     int visited[_row];
    //     for(int i = 0; i < _row; i++) {
    //         visited[i] = 0;
    //     }
    //     for(int i = 0; i < _row; i++) {
    //         if(!visited[i]) {
    //             cout << "{ ";
    //             DFSvertex(i,visited);
    //             cout << "}\n";
    //         }   
    //     }
    // }

    // void BFS() {
    //     queue<int> queueVertex;
        
    //     int visited[_row];
    //     for(int i = 0; i < _row; i++) {
    //         visited[i] = 0;
    //     }
    //     for(int i = 0; i < _row; i++) {
    //         if(!visited[i]){
    //             cout << "{ ";
    //             queueVertex.push(i);
    //             visited[i] = 1;
    //             while(!queueVertex.empty()) {
    //                 int neighbor = queueVertex.front();
    //                 queueVertex.pop();
    //                 cout << neighbor << " ";
    //                 visited[neighbor] = 1;
    //                 for(size_t l = 0; l < _array[neighbor].size(); l++) {
    //                     int v = _array[neighbor][l];
    //                     if(!visited[v]) {
    //                         queueVertex.push(v);
    //                         visited[v] = 1;
    //                     }
    //                 }
    //             }
    //             cout << "}" << endl;
    //         }    
    //     }
    // }
}MyGraph;

int main()
{
    int Vertex,edges,start,dest;
    cin >> Vertex >> edges >> start >> dest;
    MyGraph mp(Vertex,edges);
    mp.dijkstra(start,dest);
}