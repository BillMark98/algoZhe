#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define TABLE_SIZE 1000000
#define STRING_LEN 6
int _prime;
struct QUser
{
    string _loginName;
    string _pwd;
    int _times;

    QUser(): _times(0)
    {

    }

    QUser(string & name, string & pwd): _loginName(name), _pwd(pwd), _times(1)
    {

    }

    bool operator==(const QUser & pc) 
    {
        return _loginName == pc._loginName;
    }
    // friend int HashFunc(QUser & pc)
    // {
    //     string substr = pc._loginName.substr(6,5);
    //     int val = stoi(substr);
    //     return val % _prime;
    // }

    bool operator < (const QUser & pc)
    {
        return _times < pc._times;
    }

    friend ostream & operator<<(ostream & os, const QUser & pc)
    {
        os << pc._loginName;
        return os;
    }
};

struct HashTable
{
    int _sizeTable;
    vector<vector<QUser>> table_vecQUsers;
    HashTable() : _sizeTable(TABLE_SIZE)
    {
        // setPrime(N);
        table_vecQUsers.resize(_sizeTable);
        
    }

    int HashFunc(QUser & pc)
    {

        string substr;
        if(pc._loginName.length() <= STRING_LEN) {
            substr = pc._loginName;
        }
        else {
            substr = pc._loginName.substr(pc._loginName.length()-STRING_LEN-1,STRING_LEN);
        }
        int val = stoi(substr);
        return val % _sizeTable;
    }

    bool insert(QUser & pc)
    {
        int index = HashFunc(pc);
        vector<QUser> & vec = table_vecQUsers[index];
        int _len = vec.size();
        bool signInNew = true;
        for (int i = 0; i < _len; i++) {
            if (vec[i] == pc) {
                signInNew = false;
                cout << "ERROR: Exist\n";
                return false;
                // vec[i]._times++;
                // if (_phoneMania.empty() || _phoneMania[0] < vec[i]) {
                //     _phoneMania.clear();
                //     _phoneMania.push_back(vec[i]);
                // }
                // else if (_phoneMania[0]._times == vec[i]._times) {
                //     _phoneMania.push_back(vec[i]);
                // }
            }
        }
        // if (!quserFound) {
        //     vec.push_back(pc);
        //     if (_phoneMania.empty() || _phoneMania[0] < pc) {
        //         _phoneMania.clear();
        //         _phoneMania.push_back(pc);
        //     }
        //     else if (_phoneMania[0]._times == pc._times) {
        //         _phoneMania.push_back(pc);
        //     }
        // }
        cout << "New: OK\n";
        vec.push_back(pc);
        return signInNew;
    }

    bool query(QUser & pc)
    {
        int index = HashFunc(pc);
        vector<QUser> & vec = table_vecQUsers[index];
        int _len = vec.size();
        bool quserFound = false;
        for (int i = 0; i < _len; i++) {
            if (vec[i] == pc) {
                if (vec[i]._pwd != pc._pwd) {
                    cout << "ERROR: Wrong PW\n";
                    return false;
                }
                else {
                    cout << "Login: OK\n";
                    return true;
                }
                // vec[i]._times++;
                // if (_phoneMania.empty() || _phoneMania[0] < vec[i]) {
                //     _phoneMania.clear();
                //     _phoneMania.push_back(vec[i]);
                // }
                // else if (_phoneMania[0]._times == vec[i]._times) {
                //     _phoneMania.push_back(vec[i]);
                // }
            }
        }
        // if (!quserFound) {
        //     vec.push_back(pc);
        //     if (_phoneMania.empty() || _phoneMania[0] < pc) {
        //         _phoneMania.clear();
        //         _phoneMania.push_back(pc);
        //     }
        //     else if (_phoneMania[0]._times == pc._times) {
        //         _phoneMania.push_back(pc);
        //     }
        // }
        cout << "ERROR: Not Exist\n";
        return quserFound;
    }

    void logIn(QUser & pc)
    {
        query(pc);
    }

    void signIn(QUser & pc)
    {
        insert(pc);
    }

    void setPrime(int N)
    {
        _prime = 10 * N;
    }
};

int main()
{
    int N;
    cin >> N;
    HashTable ht = HashTable();
    string operat, loin,pwd;
    while (N--) {
        cin >>operat >> loin >> pwd;
        QUser pc(loin,pwd);
        if(operat == "L") {
            ht.query(pc);
        }
        else {
            ht.insert(pc);
        }
    }
    // long long num = 13005711862;
    // cout << num;
}