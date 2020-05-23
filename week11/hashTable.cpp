#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int FindPrime(int N);

bool isPrime(int N);
int nextPrime(int n);

struct HashTable
{
    int _sizeTable;
    int _loadNum;
    vector<int> _vecInt;
    HashTable(int N): _sizeTable(N), _loadNum(0)
    {
        _vecInt.resize(N, -1);
    }

    int insert(int i)
    {
        // Table already full
        if (_loadNum >= _sizeTable) {
            cout << "-";
            return false;
        }
        int index = i % _sizeTable;
        if (_vecInt[index] < 0) {
            _vecInt[index] = i;
            _loadNum++;
            cout << index;
            return index;
        }
        // collision
        int terms = 1;
        int offset, probeIndex;
        if (_sizeTable == 2) {
            probeIndex = 1 - index;
            if (_vecInt[probeIndex] < 0) {
                _vecInt[probeIndex] = i;
                _loadNum++;
                cout << probeIndex;
                return probeIndex;
            }
            else {
                cout << "-";
                return -1;
            }
        }

        // only (p-1)/2 different quadratics
        int threshold = (_sizeTable - 1)/2;
        while (terms <= threshold) {
            // offset = terms % 2 ==  1 ? (terms + 1)/2 * (terms + 1)/2 : -(terms/2 * terms/2);
            offset = terms * terms;
            probeIndex = (index + offset) % _sizeTable;
            // while (probeIndex < 0) {
            //     probeIndex += _sizeTable;
            // }
            if (_vecInt[probeIndex] < 0) {
                _vecInt[probeIndex] = i;
                _loadNum++;
                cout << probeIndex;
                return index;
            }
            terms++;
        }
        cout << "-";
        return -1;
    }

    void outPutIndex(int M)
    {
        int value, index;
        while(--M) {
            cin >> value;
            index = insert(value);
            if (index >= 0) {
                cout << index << " ";
            }
            else {
                cout << "- ";
            }
        }
        cin >> value;
        index = insert(value);
        if (index >= 0) {
            cout << index << endl;
        }
        else {
            cout << "-\n";
        }
    }
};


int main()
{
    int N,M;
    cin >> N >> M;
    int prime = FindPrime(N);
    // int prime = nextPrime(N);
    HashTable ht(prime);
    int value;
    while(--M) {
        cin >> value;
        ht.insert(value);
        cout << " ";
    }
    cin >> value;
    ht.insert(value);
    cout << endl;
    // ht.outPutIndex(M);
    // int a = -2, b = 4, c = 13, d = 7;
    // cout << a % d << endl;
    // cout << b % d << endl;
    // cout << c % d << endl;
}

int FindPrime(int N)
{
    if (N == 1 || N == 2) {
        return 2;
    }
    if (isPrime(N)) {
        return N;
    }
    if (N % 2) {
        N += 2;
    }
    else {
        N += 1;
    }
    while (!isPrime(N)) {
        N += 2;
    }
    return N;
}

bool isPrime(int N)
{
    if (N == 2) {
        return true;
    }
    if (N % 2 == 0) {
        return false;
    }
    int test = 3;
    while (test * test <= N) {
        if (N % test == 0) {
            return false;
        }
        test += 2;
    }
    return true;
}

int nextPrime(int n)
{
	if (n <= 2) return 2;
	if (n == 3) return 3;
	int p = (n % 2) ? n : n + 1;
	while (1) {
		int i;
		for (i = (int)sqrt(p); i > 2; i --)
			if (!(p % i))
				break;
		if (i == 2)
			return p;
		else
			p += 2;
	}
}


// #include <iostream>
// using namespace std;
// #include <math.h>

// int nextPrime(int n)
// {
// 	if (n <= 2) return 2;
// 	if (n == 3) return 3;
// 	int p = (n % 2) ? n : n + 1;
// 	while (1) {
// 		int i;
// 		for (i = (int)sqrt(p); i > 2; i --)
// 			if (!(p % i))
// 				break;
// 		if (i == 2)
// 			return p;
// 		else
// 			p += 2;
// 	}
// }


// int main()
// {
// 	int m, n;
// 	cin >> m >> n;
// 	int size = nextPrime(m);
// 	int *hashTable = new int[size];
// 	fill(hashTable, hashTable + size, 0);
// 	for (int i = 0; i < n; i++) {
// 		int key;
// 		cin >> key;
// 		int flag = 0;
// 		for (int increment = 0; increment < size; increment++) {
// 			int pos = key + pow(increment, 2);
// 			pos %= size;
// 			if (hashTable[pos] == 0) {
// 				hashTable[pos] = 1;
// 				if (i != 0) putchar(' ');
// 				cout << pos;
// 				flag = 1;
// 				break;
// 			}
// 		}
// 		if (flag == 0) {
// 			if (i != 0) putchar(' ');
// 			cout << "-";
// 		}
// 	}
// 	return 0;
// }