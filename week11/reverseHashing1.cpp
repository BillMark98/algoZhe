#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int A[1001];

struct compare
{
    bool operator() (int i, int j) 
    {
        return A[i] > A[j];
    }

};

int HashFunc(int i, int N)
{
    return i % N;
}

int dependLen(int index, int aughtIndex, int N)
{
    return (index + N - aughtIndex%N) % N;
}

int main()
{
    int N;
    cin >> N;

    vector<vector<int>> childVec;
    vector<int> InDegree;
    InDegree.resize(N);
    childVec.resize(N);
    priority_queue<int, vector<int>, compare> myQueue;
    int value;
    int flag = 1;
    for (int i = 0; i < N; i++) {
        cin >> value;
        A[i] = value;
        if (value > 0) {
            
            int len = dependLen(i, value, N);
            int aughtIndex = HashFunc(value,N);
            for (int j = 0; j < len; j++) {
                childVec[HashFunc(aughtIndex + j,N)].push_back(i);
                InDegree[i]++;
            }
            if (len == 0) {
                myQueue.push(i);
            }
        }
    }
    while (!myQueue.empty()) {
        int index = myQueue.top();
        myQueue.pop();
        if (!flag) {
            cout << " ";
        }
        flag = 0;
        cout << A[index];
        for (int i = 0; i < childVec[index].size(); i++) {
            int temp = childVec[index][i];
            if(--InDegree[temp] == 0) {
                myQueue.push(temp);
            }
        }
    }
    cout << endl;
}