#include <iostream>
#include <vector>
#include <cmath>
template <typename T>
T square(T a);

using namespace std;
typedef double coordType;
#define EPSILON 1e-5
#define RADIUS 7.5
#define BANK 50
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
        return square<coordType>(_xCoord - p._xCoord) + 
                square<coordType>(_yCoord - p._yCoord);
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
}Point;

typedef struct Graph {
    int * _array;
    int _N;
    vector<Point> _vpt;
    bool safe;
    Graph(int npoints, coordType thresholdSquare) :
    _N(npoints + 1),safe(false)
    {
        _array = new int[_N * _N];
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
    }

    ~Graph() 
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
}Graph;

int main() 
{
    int N;
    coordType dist;
    cin >> N >> dist;
    Graph gph(N,square<coordType>(dist));
    gph.jumpToBank();
}



template <typename T>
T square(T a) 
{
    return a * a;
}