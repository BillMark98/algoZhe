#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
template <typename T>
T square(T a);

using namespace std;
typedef double coordType;
#define EPSILON 1e-5
#define RADIUS 7.5
#define BANK 50
#define MAX_VAL 1000
typedef struct Point {
    
    coordType _xCoord;
    coordType _yCoord;
    bool riverBank;
    Point(coordType x, coordType y, coordType thresholdSquare) : _xCoord(x), _yCoord(y)
    {
        coordType xDist, yDist;
        if(x > 0) {
            xDist = fabs(BANK - x);
        }
        else {
            xDist = fabs(-BANK - x);
        }

        if(y > 0) {
            yDist = fabs(BANK - y);
        }
        else {
            yDist = fabs(-BANK - y);
        }

        if(xDist < yDist) {
            riverBank = xDist < sqrt(thresholdSquare) + EPSILON;
        }
        else {
            riverBank = yDist < sqrt(thresholdSquare) + EPSILON;
        }
    }

    coordType distSquare(const Point & p)
    {
        if(!isOrigin() && !p.isOrigin()) {
            return square<coordType>(_xCoord - p._xCoord) + 
                square<coordType>(_yCoord - p._yCoord);
        }
        else if(isOrigin()) {
            coordType d = square<coordType>(p._xCoord) + square<coordType>(p._yCoord);
            coordType l = sqrt(d) - RADIUS;
            return l * l;
        }
        else {
            coordType d = square<coordType>(_xCoord) + square<coordType>(_yCoord);
            coordType l = sqrt(d) - RADIUS;
            return l * l;
        }
        // return square<coordType>(_xCoord - p._xCoord) + 
        //         square<coordType>(_yCoord - p._yCoord);
    }

    bool jumpAble(const Point & p, coordType thresholdSquare)
    {
        if(p.isOrigin()) {
            coordType d = square<coordType>(_xCoord) + square<coordType>(_yCoord);
            coordType l = sqrt(d) - RADIUS;
            return l < sqrt(thresholdSquare);
        }
        else if(isOrigin()) {
            coordType d = square<coordType>(p._xCoord) + square<coordType>(p._yCoord);
            coordType l = sqrt(d) - RADIUS;
            return l < sqrt(thresholdSquare);
        }
        else {
            return distSquare(p) <= thresholdSquare;
        }
    }

    bool isOrigin() const
    {
        return fabs(_xCoord) < EPSILON && fabs(_yCoord) < EPSILON;
    }

    friend ostream & operator<<(ostream & os, const Point & p) 
    {
        os << p._xCoord << " " << p._yCoord << endl;
        return os;
    }
}Point;

typedef struct MyGraph {
    int * _array;
    vector<vector<int> > vec_array;
    int _N;
    vector<Point> _vpt;
    bool safe;
    MyGraph(int npoints, coordType thresholdSquare) :
    _N(npoints + 1),safe(false)
    {
        _array = new int[_N * _N];
        vec_array.resize(_N);
        int _index = 1;
        Point pt(0,0,thresholdSquare);
        _vpt.push_back(pt);
        while(npoints--) {
            coordType x,y;
            cin >> x >> y;
            Point pt(x,y,thresholdSquare);
            _vpt.push_back(pt);
            for(int i = 0; i < _index; i++) {
                if(_vpt[i].jumpAble(pt,thresholdSquare)) {
                    _array[i * _N + _index] = 1;
                    _array[_index * _N + i] = 1;
                }
            }
            _index++;
        }
        for(int i = 1; i < _N; i++) {
            for(int j = 0; j < i; j++) {
                if((*this)(i,j) == 1) {
                    vec_array[i].push_back(j);
                    vec_array[j].push_back(i);
                }   
            }
        }
    }

    ~MyGraph() 
    {
        delete [] _array;
    }

    bool DFSvertex(int i, int * arr)
    {
        if(arr[i]) {
            return false;
        }
        arr[i] = 1;
        if(_vpt[i].riverBank) {
            return true;
        }
        else {
            bool subVer = false;
            for(int l = 0; l < _N; l++) {
                if((*this)(i,l) && !arr[l]) {
                    subVer = DFSvertex(l, arr);
                    if(subVer) {
                        return true;
                    }
                }
            }
            return subVer;
        }
    }

    void Unweighted(int vertex) 
    {
        queue<int> queueVertex;
        queueVertex.push(vertex);
        vector<int> dist;
        vector<int> path;
        dist.resize(_N);
        path.resize(_N);
        for(int i = 0; i < _N; i++) {
            if(i != vertex) {
                dist[i] = -1;
                path[i] = -1;
            }
            else {
                dist[i] = 0;
                path[i] = i;
            }
        }
        while(!queueVertex.empty()) {
            int nb = queueVertex.front();
            queueVertex.pop();
            int len = vec_array[nb].size();
            for(int index = 0; index < len; index++) {
                int j = vec_array[nb][index];
                if(dist[j] == -1) {
                    dist[j] = dist[nb] + 1;
                    path[j] = nb;
                    queueVertex.push(j);
                }
            }
        }

        // find all bank point
        int minJumps = MAX_VAL;
        int endPoint = -1;
        for(int i = 0; i < _N; i++) {
            if(dist[i] != -1) {
                if(_vpt[i].riverBank && dist[i] <= minJumps) {
                    // if dist equal, need to check in addition the first jump, which is according to the problem
                    // guaranteed to be able to compare. (i.e, there is a unique optimal)
                    if(dist[i] == minJumps) {
                        int root_i = i;
                        // find the next to vertex node on the jump
                        while(path[root_i] != vertex) {
                            root_i = path[root_i];
                        }
                        int root_endPoint = endPoint;
                        while(path[root_endPoint] != vertex) {
                            root_endPoint = path[root_endPoint];
                        }
                        // calculate the first jump distance
                        coordType di = _vpt[vertex].distSquare(_vpt[root_i]);
                        coordType de = _vpt[vertex].distSquare(_vpt[root_endPoint]);
                        if(di < de) {
                            minJumps = dist[i];
                            endPoint = i;
                        }
                    }
                    else {
                        minJumps = dist[i];
                        endPoint = i;
                    }
                }
            }
        }

        // 007 cant jump to the bank
        if(endPoint == -1) {
            cout << "0\n";
        }
        else {
            vector<int> vt;
            int vd = endPoint;
            while(vd != vertex) {
                vt.push_back(vd);
                vd = path[vd];
            }
            cout << ++minJumps << endl;
            for(int i = vt.size() - 1; i >= 0; i--) {
                cout << _vpt[vt[i]]; 
            }
        }
    }

    void save007()
    {
        Unweighted(0);
    }

    void jumpToBank() 
    {
        bool jumpFlag = false;
        int arr[_N];
        for(int i = 0; i < _N; i++) {
            arr[i] = 0;
        }
        jumpFlag = DFSvertex(0,arr);
        if(jumpFlag) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    int operator()(int i, int j) 
    {
        if(i < 0 || i >= _N || j < 0 || j >= _N) {
            cout << "the index in operator() invalid\n";
            return -1;
        }
        return _array[i * _N + j];
    }
}MyGraph;

int main() 
{
    int N;
    coordType dist;
    cin >> N >> dist;
    MyGraph gph(N,square<coordType>(dist));
    gph.save007();
}



template <typename T>
T square(T a) 
{
    return a * a;
}