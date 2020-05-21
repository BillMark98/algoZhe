#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

#define MAX_VAL 1000000
#define MIN_VAL -1000

class NotConnected 
{

};

typedef struct myGraph {
    int _row;
    int _col;
    vector<int> _array;
    
    myGraph(int Vertex, int edges) : _row(Vertex),_col(Vertex)
    {
        _array.resize(_row * _col,MAX_VAL);
       
        while(edges--) {
            int i,j,weight;
            cin >> i >> j >> weight;
            i--;
            j--;
            (*this)(i,j) = weight;
            (*this)(j,i) = weight;
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

    void Floyd()
    {
        for(int k = 0; k < _row; k++) {
            for(int i = 0; i < _row; i++) {
                for(int j = 0; j < _row; j++) {
                    int dist = (*this)(i,k) + (*this)(k,j);
                    if(dist < (*this)(i,j)) {
                        (*this)(i,j) = dist;
                    }
                }
            }
        }
    }

    // find node, to which the cost from node i to that is the largest
    int findMaxWeight(int i)
    {
        int max = 0;
        int maxIndex = i;
        for(int j = 0; j < _row; j++) {
            if(j != i) {
                if((*this)(i,j) > max) {
                    maxIndex = j;
                    max = (*this)(i,j);
                    if(max >= MAX_VAL) {
                        throw NotConnected();
                    }
                }
            }
        }
        return max;
    }

    void FindAnimal() 
    {
        Floyd();
        vector<int> maxIndex;
        maxIndex.resize(_row);
        try {
            int Min = MAX_VAL;
            int tempDist, chosenPoint;
            for(int i = 0; i < _row; i++) {
                // maxIndex[i] = findMaxWeight(i);
                tempDist = findMaxWeight(i);
                if(tempDist < Min) {
                    chosenPoint = i + 1;
                    Min = tempDist;
                }
            }
            cout << chosenPoint << " " << Min << endl;
        }
        catch(NotConnected & nc) {
            cout << "0\n";
        }
    }
}myGraph;

int main()
{
    int Vertex,edges;
    cin >> Vertex >> edges;
    myGraph gp(Vertex,edges);
    gp.FindAnimal();
}