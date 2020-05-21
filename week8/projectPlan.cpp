#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX_VAL 1000000
#define MIN_VAL -1000

typedef size_t IndexType;

class NotConnected 
{

};

struct ProjectNode
{
    int _index;
    int _timeToFinish;
    ProjectNode(int ind, int time) : _index(ind), _timeToFinish(time)
    {

    }

    ProjectNode(int ind) : _index(ind), _timeToFinish(0)
    {

    }

    ProjectNode() : _timeToFinish(0)
    {

    }

    void setTimeToFinish(int time)
    {
        _timeToFinish = time;
    }

    void setNode(int ind) 
    {
        _index = ind;
    }
};

typedef struct myGraph {
    int _row;
    int _col;
    vector<int> _array;
    vector<int> _inDegree;

    // vector of all sinks
    vector<int> _sinkVertex;
    // save all those point points to the index
    vector<vector<int> > ParentVec_Array;
    vector<vector<int> > ChildVec_Array;

    bool _isDag;
    myGraph(int Vertex, int edges) : _row(Vertex),_col(Vertex),_isDag(true)
    {
        _array.resize(_row * _col,MAX_VAL);
        _inDegree.resize(_row,0);
        ParentVec_Array.resize(_row);
        ChildVec_Array.resize(_row);
        while(edges--) {    
            int i,j,weight;
            cin >> i >> j >> weight;
            (*this)(i,j) = weight;
            _inDegree[j]++;
            ParentVec_Array[j].push_back(i);
            ChildVec_Array[i].push_back(j);
        }
        for(int i = 0; i < Vertex; i++) {
            if(ChildVec_Array[i].empty()) {
                _sinkVertex.push_back(i);
            }
        }
        if(_sinkVertex.empty()) {
            cout << "Impossible\n";
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

    void FindMinWorkTime()
    {
        if(!_isDag) {
            return;
        }
        queue<int> InVertex;
        int countVertex = 0;
        vector<int> visited;
        visited.resize(_row);
        for(int i = 0; i < _row; i++) {
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

        if(countVertex != _row) {
            _isDag = false;
            cout << "Impossible\n";
        }
        else {
            int maxTime = 0;
            for(vector<int>::iterator it = _sinkVertex.begin(); it != _sinkVertex.end(); it++) {
                if(maxTime < vecProjectNode[*it]._timeToFinish) {
                    maxTime = vecProjectNode[*it]._timeToFinish;
                }
            }
            cout << maxTime << endl;
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