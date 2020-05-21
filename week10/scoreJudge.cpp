#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct User 
{
    int _id;
    vector<int> _scores;
    int _perfectScores;
    int _scoreTotal;
    bool _validSolution;
    bool _scoreSet;
    User(int id, int numOfTests) : _id(id), _perfectScores(0), _scoreTotal(0), _validSolution(false),
        _scoreSet(false)
    {
        _scores.resize(numOfTests, -1);
        _scoreTotal = 0;
    }

    User(): _id(-1), _perfectScores(0), _scoreTotal(0), _validSolution(false),
        _scoreSet(false)
    {

    }

    void setIDSize(int id, int numOfTests)
    {
        _id = id;
        _scores.resize(numOfTests, -1);
        _scoreTotal = 0;
    }

    void setScore(int ithProblem, int mark, int fullMark) 
    {
        int & original = _scores[ithProblem - 1];
        if (mark > original) {
            original = mark;
            _validSolution = true;

            // if (original > -1) {
            //     _scoreTotal = _scoreTotal - original + mark;
            // }
            // else {
            //     _scoreTotal = _scoreTotal + mark;
            // }
            // original = mark;
            // if (mark == fullMark) {
            //     _perfectScores++;
            // }
            // if (mark >= 0) {
            //     _validSolution = true;
            // }
        }
        else if (original == -1) {
            original = 0;
        }
        // else if (mark == original && original == -1) {
        //     original = 0;
        // }
    }

    // bool operator<=(const User & u1) const
    // {
    //     return scores() >= u1.scores();
    // }

    // according to the problem setting equal not possible
    void setTotalPerfect(int perfectScores[])
    {
        int len = _scores.size();
        _scoreTotal = 0;
        _perfectScores = 0;
        for (int i = 0; i < len; i++) {
            _scoreTotal += _scores[i] >= 0 ? _scores[i] : 0;
            if (_scores[i] == perfectScores[i]) {
                _perfectScores++;
            }
        }
    }

    bool operator > (const User & u1) const
    {
        return u1 < (*this);
    }

    bool operator<(const User & u1) const
    {
        bool smallerRank = scores() > u1.scores();
        if (smallerRank) {
            return true;
        }
        else if ( scores() < u1.scores()) {
            return false;
        }
        else {
            bool greaterPerfect = perfectScores() > u1.perfectScores();
            if (greaterPerfect) {
                return true;
            }
            else if (perfectScores() < u1.perfectScores()) {
                return false;
            }
            else {
                return _id < u1._id;
            }
        }
    }

    int scores() const
    {
        return _scoreTotal;
    }

    int perfectScores() const 
    {
        return _perfectScores;
    }

    bool userNeedOutput() const
    {
        return _validSolution;
    }

    friend ostream & operator<<(ostream & os, const User & u1) 
    {
        if (!u1._validSolution) {
            return os;
        }
        cout << setfill('0') << setw(5) << u1._id + 1 << " ";
        // for_each(u1._scores.begin(), u1._scores.end(), [](int i) {
        //     if (i) {
        //         cout << i 
        //     }
        // })
        cout << u1._scoreTotal << " ";
        int _len = u1._scores.size();
        int i;
        for (i = 0; i < _len - 1; i++) {
            if (u1._scores[i] > -1) {
                cout << u1._scores[i] << " ";
            }
            else {
                cout << "- ";
            }
        }
        if (u1._scores[i] > -1) {
                cout << u1._scores[i] << endl;
            }
            else {
                cout << "-\n";
        }
        return os;
    }
};

void insertionSort(int Index[], User[], int N);

void quickSort(int Index[], User[], int N);

void HeapSort(int Index[], User[], int N);

void ShellSort(int Index[],User useArr[], int N);

void Merge_Pass(int Index[], int tmpArray[], User useArr[],int N, int length);
void Merge1(int Index[], int tmpArray[], User useArr[],int L, int R, int RightEnd);

void MergeSort(int Index[], User useArr[],int N);
void MergeSort_Iterative(int Index[], User useArr[], int N);

void Swap(int & i, int & j);

void permuteArr(int Index[], User[], int N);

void outPut(User useArr[], int N);
void outPut(vector<User> & useArr);
int main()
{
    int N,K,M;
    cin >> N >> K >> M;
    int noteArr[K];
    for (int i = 0; i < K; i++) {
        cin >> noteArr[i];
    }
    // User useArr[N];
    vector<User> useArr;
    useArr.resize(N);
    while (M--) {
        int id, problemNum, score;
        cin >> id >> problemNum >> score;
        id--;
        if (useArr[id]._id != id) {
            useArr[id].setIDSize(id, K);
        }
        useArr[id].setScore(problemNum, score, noteArr[problemNum - 1]);
    }
    int Index[N];
    for (int i = 0; i < N; i++) {
        Index[i] = i;
        useArr[i].setTotalPerfect(noteArr);
    }

    // insertionSort(Index, useArr, N);

    // ShellSort(Index,useArr,N);
    sort(useArr.begin(), useArr.end());
    outPut(useArr);
}

void insertionSort(int Index[], User useArr[], int N)
{
    for (int p = 1; p < N; p++) {
        int pivot = Index[p];
        int i;
        for (i = p; i > 0 && useArr[Index[i - 1]] > useArr[pivot]; i--) {
            Index[i] = Index[i - 1];
        }
        Index[i] = pivot;
    }
    permuteArr(Index, useArr, N);
}

void quickSort(int Index[], User[], int N)
{

}

void HeapSort(int Index[], User useArr[], int N)
{

}


void ShellSort(int Index[],User useArr[], int N)
{
    int Sedgewick[] = { 1 ,5 ,19 ,41 ,109 ,209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305 };
	int D;
	int pivot;
	int i,j,P;
	for (j = 14; j >= 0; j--) {
		D = Sedgewick[j];
		for (P = D; P < N;P++) {
			pivot = Index[P];
			for (i = P; i >= D && useArr[Index[i - D]] > useArr[pivot];i-=D) {
				Index[i] = Index[i-D];
			}
			Index[i] = pivot;
        }
    }
    permuteArr(Index, useArr, N);
}

void Merge_Pass(int Index[], int tmpArray[], User useArr[],int N, int length)
{

}

void Merge1(int Index[], int tmpArray[], User useArr[],int L, int R, int RightEnd)
{

}

void MergeSort(int Index[], User useArr[],int N)
{

}

void MergeSort_Iterative(int Index[], User useArr[], int N)
{

}

void Swap(int & i, int & j)
{
    int temp = j;
    j = i;
    i = temp;
}

void permuteArr(int Index[], User useArr[], int N)
{
    int index = 0, nextInd;
    while (index < N) {
        if (index == Index[index]) {
            index++;
            continue;
        }
        int origTemp = index;
        nextInd = Index[index];
        Index[index] = index;
        User Temp = useArr[index];
        while (Index[nextInd] != nextInd) {
            useArr[index] = useArr[nextInd];
            Index[index] = index;
            index = nextInd;
            nextInd = Index[nextInd];
        }
        useArr[index] = Temp;
        Index[index] = index;
        index = origTemp + 1;
    }
}

void outPut(User useArr[], int N)
{
    int rank = 1;
    cout << rank << " " << useArr[0];
    int scoreTemp = useArr[0]._scoreTotal;
    for (int i = 1; i < N; i++) {
        if (!useArr[i].userNeedOutput()) {
            break;
        }
        if (useArr[i]._scoreTotal < scoreTemp) {
            rank = i + 1;
            scoreTemp = useArr[i]._scoreTotal;
        }
        cout << rank << " ";
        cout << useArr[i];
    }
    // cout << endl;
}

void outPut(vector<User> & useArr)
{
    int rank = 1;
    cout << rank << " " << useArr[0];
    int scoreTemp = useArr[0]._scoreTotal;
    int N = useArr.size();
    for (int i = 1; i < N; i++) {
        if (!useArr[i].userNeedOutput()) {
            break;
        }
        if (useArr[i]._scoreTotal < scoreTemp) {
            rank = i + 1;
            scoreTemp = useArr[i]._scoreTotal;
        }
        cout << rank << " ";
        cout << useArr[i];
    }
}



#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
bool rule(const vector<int>& vec1, const vector<int>& vec2)
{
	// return vec1[1] == vec2[1] ? vec1[vec1.size() - 1] == vec2[vec2.size() - 1] ? vec1[0] < vec2[0] : vec1[vec1.size() - 1] > vec2[vec2.size() - 1] : vec1[1] > vec2[1];
    // if (vec1[1] == vec2[1]) {
    //     if (vec1[vec1.size() - 1] == vec2[vec2.size() - 1]) {
    //         return vec1[0] < vec2[0];
    //     }
    //     else {
    //         return vec1[vec1.size() - 1] > vec2[vec2.size() - 1];
    //     }
    // }
    // else {
    //     return vec1[1] > vec2[1];
    // }

    bool smallerRank = vec1[1] > vec2[1];
    if (smallerRank) {
        return true;
    }
    else if ( vec1[1] < vec2[1]) {
        return false;
    }
    else {
        bool greaterPerfect = vec1[vec1.size() - 1] > vec2[vec2.size() - 1];
        if (greaterPerfect) {
            return true;
        }
        else if (vec1[vec1.size() - 1] < vec2[vec2.size() - 1]) {
            return false;
        }
        else {
            return vec1[0] < vec2[0];
        }
    }
}
int main()
{
	int id, totalquestion, numOfJudegs, problemNum, score;
	map<int,vector<int>>map_idScores;
	vector<vector<int>>vec_idScores;
	scanf("%d %d %d", &id, &totalquestion, &numOfJudegs);
	vector<int>fullscore(totalquestion + 1);
	for (int i = 0; i < totalquestion; i++)
		scanf("%d", &fullscore[i + 1]);
	for (int i = 0; i < numOfJudegs; i++)
	{
		scanf("%d %d %d", &id, &problemNum, &score);
        // vector 1,...,totalquestion, ?, submitPassCompiler, perfectScoreNumber
		if (!map_idScores[id].size())
			map_idScores[id].resize(totalquestion + 3, -1);//Reserved three locations, which are used to store the ID, whether the flag can be output, and the number of questions that get the full score.
		if (score > map_idScores[id][problemNum])
		{
			map_idScores[id][map_idScores[id].size() - 2] = 1;
			map_idScores[id][problemNum] = score;
		}
		else if (map_idScores[id][problemNum] == -1)
			map_idScores[id][problemNum] = 0;
	}
	for (auto it : map_idScores)
	{
		vector<int>tmp;
		for (int i = 0; i < it.second.size() - 2; i++)
		{
			if (i > 0 && it.second[i] == fullscore[i])
				it.second[it.second.size() - 1]++;
			i == 0 ? it.second[0] = 0 : it.second[0] += it.second[i] >= 0 ? it.second[i] : 0;
            // equivalent if-else branch of the above expression
            // if (i == 0) {
            //     // initialize the sumOfScores
            //     it.second[0] = 0;
            // }
            // else {
            //     if (it.second[i] >= 0) {
            //         it.second[0] += it.second[i];
            //     }
            // }
        
            // push_back the scores
			if (i)
				tmp.push_back(it.second[i]);
		}
        // insert the total scores
		tmp.insert(tmp.begin(), it.second[0]);
        // insert the id
		tmp.insert(tmp.begin(), it.first);
        // push back the submitPassCompiler flag
		tmp.push_back(it.second[it.second.size() - 2]);
        // push back the perfectScoreNum
		tmp.push_back(it.second[it.second.size() - 1]);

        // vec structure: id, totalScores,score_for_1, ... , score_for_last, submitPassCompiler, perfectScoreNum
		vec_idScores.push_back(tmp);
	}
	sort(vec_idScores.begin(), vec_idScores.end(), rule);
	for (int i = 0, k = 0, last = 0; i < vec_idScores.size() && vec_idScores[i][vec_idScores[i].size() - 2] == 1; i++)
	{
		if (vec_idScores[i][1] != last)
		{
			cout << i + 1;
			last = vec_idScores[i][1];
			k = i + 1;
		}
		else
			printf("%d", k);
		for (int j = 0; j < vec_idScores[i].size() - 2; j++)
			if (j == 0)
				printf(" %05d", vec_idScores[i][j]);
			else if (vec_idScores[i][j] >= 0)
				printf(" %d", vec_idScores[i][j]);
			else
				printf(" -");
		printf("\n");
	}
	return 0;
}
