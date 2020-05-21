#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;


typedef struct Graph {
    int _row;
    int _col;
    // int* _array;
    vector<vector<int> > _array;
    Graph(int Vertex, int edges) : _row(Vertex + 1),_col(Vertex + 1)
    {
        // _array = new int[row * col];
        _array.resize(Vertex + 1);
        while(edges--) {
            int i,j;
            cin >> i >> j;
            // if(i > j) {
            //     _array[j].push_back(i);
            // }
            // else {
            //     _array[i].push_back(j);
            // }
            _array[i].push_back(j);
            _array[j].push_back(i);
        }
        for(int i = 0; i < Vertex; i++) {
            sort(_array[i].begin(),_array[i].end());
        }
    }

    ~Graph() {
        // delete [] _array;
    }

    int & operator()(int i, int j) {
        if(i >= _row || i < 0 || j >= _col || j < 0) {
            throw("index invalid\n");
        }
        return _array[i][j];
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
        for(int i = 0; i < _row; i++) {
            visited[i] = 0;
        }
        for(int i = 0; i < _row; i++) {
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
        for(int i = 0; i < _row; i++) {
            visited[i] = 0;
        }
        for(int i = 0; i < _row; i++) {
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

    int BFSvertex(int _v)
    {
        queue<int> queueVertex;
        
        int visited[_row];
        for(int i = 0; i < _row; i++) {
            visited[i] = 0;
        }
        queueVertex.push(_v);
        int level = 0;
        int last = _v;
        int tail;
        int count = 1;
        visited[_v] = 1;
        while(!queueVertex.empty() && level <= 5) {
            int neighbor = queueVertex.front();
            queueVertex.pop();
            for(size_t l = 0; l < _array[neighbor].size(); l++) {
                int v = _array[neighbor][l];
                if(!visited[v]) {
                    queueVertex.push(v);
                    visited[v] = 1;
                    tail = v;
                    count++;
                }
            }
            if(neighbor == last) {
                level++;
                last = tail;
            }
        }
        return count;
    }

    void sixDeg() 
    {
        cout.precision(2);
        cout << fixed;
        for(int v = 1; v < _row; v++) {
            int count = BFSvertex(v);
            // _row - 1 is the total number of points
            double percent = (double) count / (_row - 1) * 100.;
            cout << v <<": " << percent << "%\n";
        }
    }
}Graph;
void graphTraverse();

int main()
{
    graphTraverse();
}

void graphTraverse()
{
    int Vertex,edges;
    cin >> Vertex >> edges;
    Graph gph(Vertex,edges);
    gph.sixDeg();
}