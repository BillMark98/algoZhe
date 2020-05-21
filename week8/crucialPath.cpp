#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <map>

using namespace std;

#define MAX_VAL 1000000
#define MIN_VAL -1000

typedef size_t IndexType;

typedef pair<int,int> pair_Edge;
typedef map<pair_Edge,int> EdgeIntMap;
class NotConnected 
{

};

struct ProjectNode
{
    int _index;
    int _timeToFinish;
    int _activeTime;
    ProjectNode(int ind, int time) : _index(ind), _timeToFinish(time)
    {

    }

    ProjectNode(int ind) : _index(ind), _timeToFinish(0)
    {

    }

    ProjectNode() : _timeToFinish(0),_activeTime(MAX_VAL)
    {

    }

    void setTimeToFinish(int time)
    {
        _timeToFinish = time;
    }

    void setActiveTime(int time) 
    {
        _activeTime = time;
    }

    void setNode(int ind) 
    {
        _index = ind;
    }
};

struct Edge
{
    int _start,_end;
    Edge(int st, int end): _start(st),_end(end)
    {

    }

    Edge():_start(-1),_end(-1) 
    {

    }
};

struct MyHeap
{
    vector<Edge> _array;
    int sizeHeap;
    int _row;
    vector<int> & sequenceEdge;
    // function<bool(Edge &,Edge &)> compareFunc;

    // MyHeap(int size, bool(*f)(Edge &,Edge &)) : sizeHeap(0),compareFunc(f)
    // {
    //     _array.resize(size + 1);
    // }

    MyHeap(int size,int row, vector<int> & vecEdge) : sizeHeap(0), _row(row), sequenceEdge(vecEdge)
    {
        _array.resize(size + 1);
    }

    bool compareFunc(Edge & e1, Edge & e2) {
        if(e1._start < e2._start) {
            return true;
        }
        else if(e1._start > e2._start) {
            return false;
        }
        else {
            // according to the problem set,
            // if start is the same, the edge that is later inputted is smaller
            return sequenceEdge[e1._start * _row + e1._end] < sequenceEdge[e2._start * _row + e2._end];
        }
    }

    void insert(Edge t1)
    {
        int index;
        for(index = ++sizeHeap; index >= 2 && compareFunc(t1,_array[index/2]); index /= 2) {
            _array[index] = _array[index/2];
        }
        _array[index] = t1;
    }

    Edge deleteMin()
    {
        if(isEmpty()) {
            // cout << "heap empty\n";
            throw "heap empty";
        }
        Edge minElem = _array[1];
        Edge temp = _array[sizeHeap--];
        int parent,child;
        for(parent = 1; parent * 2 <= sizeHeap; parent = child) {
            child = 2 * parent;
            if(child < sizeHeap && compareFunc(_array[child + 1], _array[child])) {
                child++;
            }
            if(compareFunc(temp,_array[child])) {
                break;
            }
            _array[parent] = _array[child];
        }
        _array[parent] = temp;
        return minElem;
    }

    bool isEmpty() {
        return sizeHeap == 0;
    }
};


typedef struct myGraph {
    int _row;
    int _col;
    int _edgeCount;
    vector<int> _array;
    vector<int> _inDegree;
    vector<int> _outDegree;
    // vector of all sinks
    vector<int> _sinkVertex;
    // save all those point points to the index
    vector<vector<int> > ParentVec_Array;
    vector<vector<int> > ChildVec_Array;

    vector<int> _sequenceEdge;
    EdgeIntMap edge_seqMap;
    bool _isDag;
    myGraph(int Vertex, int edges) : _row(Vertex + 1),_col(Vertex + 1),_edgeCount(edges),_isDag(true)
    {
        _array.resize(_row * _col,MAX_VAL);
        _inDegree.resize(_row,0);
        _outDegree.resize(_row,0);
        _sequenceEdge.resize(_row * _col, MAX_VAL);

        ParentVec_Array.resize(_row);
        ChildVec_Array.resize(_row);
        while(edges--) {    
            int i,j,weight;
            cin >> i >> j >> weight;
            // edge_seqMap[pair_Edge(i,j)] = edges;
            _sequenceEdge[i * _row + j] = edges;
            (*this)(i,j) = weight;
            _inDegree[j]++;
            _outDegree[i]++;
            ParentVec_Array[j].push_back(i);
            ChildVec_Array[i].push_back(j);
        }
        for(int i = 1; i < _row; i++) {
            if(ChildVec_Array[i].empty()) {
                _sinkVertex.push_back(i);
            }
        }
        if(_sinkVertex.empty()) {
            cout << "0\n";
            _isDag = false;
        }
    }

    ~myGraph() {

    }

    int & operator()(int i, int j) {
        if(i >= _row || i < 0 || j >= _col || j < 0) {
            throw("index invalid\n");
        }
        return _array[i * _row + j];
    }

    // bool edgeCompare(Edge & e1, Edge & e2) {
    //     if(e1._start < e2._start) {
    //         return true;
    //     }
    //     else if(e1._start > e2._start) {
    //         return false;
    //     }
    //     else {
    //         // according to the problem set,
    //         // if start is the same, the edge that is later inputted is smaller
    //         return edge_seqMap[pair_Edge(e1._start,e1._end)] < edge_seqMap[pair_Edge(e2._start,e2._end)];
    //     }
    // }

    void FindMinWorkTime()
    {
        if(!_isDag) {
            return;
        }
        queue<int> InVertex;
        int countVertex = 0;
        vector<int> visited;
        visited.resize(_row);
        for(int i = 1; i < _row; i++) {
            if(_inDegree[i] == 0) {
                InVertex.push(i);
                visited[i] = 1;
            }
        }

        vector<ProjectNode> vecProjectNode;
        vecProjectNode.resize(_row);

        while(!InVertex.empty()) {
            int vd = InVertex.front();
            InVertex.pop();
            countVertex++;
            vecProjectNode[vd].setNode(vd);

            // necessary?
            // int max = 0;
            // size_t lenParent = ParentVec_Array[vd].size();
            // for(IndexType i = 0; i < lenParent; i++) {
            //     int parent = ParentVec_Array[vd][i];
            //     int timeNew = vecProjectNode[parent]._timeToFinish + (*this)(parent,vd);
            //     if(max < timeNew) {
            //         max = timeNew;
            //     }
            // }
            // vecProjectNode[vd].setTimeToFinish(max);

            // enqueue all neighbors turing to source, and update the child working time
            size_t lenChild = ChildVec_Array[vd].size();
            for(IndexType i = 0; i < lenChild; i++) {
                if(!visited[ChildVec_Array[vd][i]]) {
                    int j = ChildVec_Array[vd][i];
                    _inDegree[j]--;
                    if(vecProjectNode[vd]._timeToFinish + (*this)(vd,j) > vecProjectNode[j]._timeToFinish) {
                        vecProjectNode[j].setTimeToFinish(vecProjectNode[vd]._timeToFinish + (*this)(vd,j));
                    }
                    if(_inDegree[j] == 0) {
                        InVertex.push(j);
                        visited[j] = 1;
                    }
                }
            }
        }

        if(countVertex != _row - 1) {
            _isDag = false;
            cout << "0\n";
        }
        else {
            int maxTime = 0;
            for(vector<int>::iterator it = _sinkVertex.begin(); it != _sinkVertex.end(); it++) {
                if(maxTime < vecProjectNode[*it]._timeToFinish) {
                    maxTime = vecProjectNode[*it]._timeToFinish;
                }
            }
            cout << maxTime << endl;

            // calculate the crucial path
            queue<int> OutVertex;
            for(int i = 1; i < _row; i++) {
                if(_outDegree[i] == 0) {
                    OutVertex.push(i);
                    vecProjectNode[i].setActiveTime(maxTime);
                    visited[i] = 1;
                }
                else {
                    visited[i] = 0;
                }
            }
            while(!OutVertex.empty()) {
                int vd = OutVertex.front();
                OutVertex.pop();
                size_t lenParent = ParentVec_Array[vd].size();
                for(IndexType i = 0; i < lenParent; i++) {
                    if(!visited[ParentVec_Array[vd][i]]) {
                        int parent = ParentVec_Array[vd][i];
                        _outDegree[parent]--;
                        int timeNew = vecProjectNode[vd]._activeTime - (*this)(parent,vd);
                        if(vecProjectNode[parent]._activeTime > timeNew) {
                            vecProjectNode[parent].setActiveTime(timeNew);
                        }
                        if(_outDegree[parent] == 0) {
                            OutVertex.push(parent);
                            visited[parent] = 1;
                        }
                    }
                }
            }
            // MyHeap edgeHeap(_edgeCount,[](Edge & e1, Edge & e2) -> bool {
            //     if(e1._start < e2._start) {
            //         return true;
            //     }
            //     else if(e1._start > e2._start) {
            //         return false;
            //     }
            //     else {
            //         return e1._end < e2._end;
            //     }
            // });
            
            MyHeap edgeHeap(_edgeCount,_row, _sequenceEdge);
            // MyHeap<Edge> edgeHeap(_edgeCount, &edgeCompare);
    //         MyHeap<Edge> edgeHeap(_edgeCount,[](Edge & e1, Edge & e2) -> bool {
    //     if(e1._start < e2._start) {
    //         return true;
    //     }
    //     else if(e1._start > e2._start) {
    //         return false;
    //     }
    //     else {
    //         // according to the problem set,
    //         // if start is the same, the edge that is later inputted is smaller
    //         return edge_seqMap[pair_Edge(e1._start,e1._end)] < edge_seqMap[pair_Edge(e2._start,e2._end)];
    //     }
    // }
            for(int vertex = 1; vertex < _row; vertex++) {
                int lenChild = ChildVec_Array[vertex].size();
                for(int index = 0; index < lenChild; index++) {
                    int child = ChildVec_Array[vertex][index];
                    if(vecProjectNode[child]._activeTime - vecProjectNode[vertex]._timeToFinish - (*this)(vertex,child) == 0) {
                        edgeHeap.insert(Edge(vertex,child));
                    }
                }
            }
            try {
                while(!edgeHeap.isEmpty()) {
                    Edge edgeTemp = edgeHeap.deleteMin();
                    cout << edgeTemp._start << "->" << edgeTemp._end << endl;
                }
            }
            catch (char const * s) {
                cout << "s" << endl;
            }
            catch(...) {
                cout << "unknown error\n";
            }
        }
    }

}myGraph;

int main()
{
    int Vertex,edges;
    cin >> Vertex >> edges;
    myGraph gp(Vertex,edges);
    gp.FindMinWorkTime();
}