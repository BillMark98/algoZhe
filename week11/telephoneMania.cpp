#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int _prime;
struct PhoneCall
{
    string _phoneNum;
    int _times;

    PhoneCall(): _times(0)
    {

    }

    PhoneCall(string & name): _phoneNum(name),_times(1)
    {

    }

    bool operator==(const PhoneCall & pc) 
    {
        return _phoneNum == pc._phoneNum;
    }
    // friend int HashFunc(PhoneCall & pc)
    // {
    //     string substr = pc._phoneNum.substr(6,5);
    //     int val = stoi(substr);
    //     return val % _prime;
    // }

    bool operator < (const PhoneCall & pc)
    {
        return _times < pc._times;
    }

    friend ostream & operator<<(ostream & os, const PhoneCall & pc)
    {
        os << pc._phoneNum;
        return os;
    }
};

struct HashTable
{
    int _sizeTable;
    vector<vector<PhoneCall>> table_vecPhoneCalls;
    vector<PhoneCall> _phoneMania;
    HashTable(int N) : _sizeTable(N), _phoneMania()
    {
        setPrime(N);
        table_vecPhoneCalls.resize(_prime);
        
    }

    int HashFunc(PhoneCall & pc)
    {
        string substr = pc._phoneNum.substr(6,5);
        int val = stoi(substr);
        return val % _prime;
    }

    void insert(PhoneCall & pc)
    {
        int index = HashFunc(pc);
        vector<PhoneCall> & vec = table_vecPhoneCalls[index];
        int _len = vec.size();
        bool phoneCallFound = false;
        for (int i = 0; i < _len; i++) {
            if (vec[i] == pc) {
                phoneCallFound = true;
                vec[i]._times++;
                if (_phoneMania.empty() || _phoneMania[0] < vec[i]) {
                    _phoneMania.clear();
                    _phoneMania.push_back(vec[i]);
                }
                else if (_phoneMania[0]._times == vec[i]._times) {
                    _phoneMania.push_back(vec[i]);
                }
            }
        }
        if (!phoneCallFound) {
            vec.push_back(pc);
            if (_phoneMania.empty() || _phoneMania[0] < pc) {
                _phoneMania.clear();
                _phoneMania.push_back(pc);
            }
            else if (_phoneMania[0]._times == pc._times) {
                _phoneMania.push_back(pc);
            }
        }
        
    }

    void setPrime(int N)
    {
        _prime = 10 * N;
    }

    void getMania()
    {
        sort(_phoneMania.begin(), _phoneMania.end(), [](PhoneCall & p1, PhoneCall & p2) -> bool {
            long long l1 = stoll(p1._phoneNum);
            long long l2 = stoll(p2._phoneNum);
            return l1 < l2;
        });
        cout << _phoneMania[0] << " " << _phoneMania[0]._times;
        int _len = _phoneMania.size();
        if (_len > 1) {
            cout << " " << _len;
        }
        cout << endl;
    }
};

int main()
{
    int N;
    cin >> N;
    HashTable ht(N);
    string erCallPhone;
    string eeCallPhone;
    while (N--) {
        cin >> erCallPhone >> eeCallPhone;
        PhoneCall p1(erCallPhone);
        PhoneCall p2(eeCallPhone);
        ht.insert(p1);
        ht.insert(p2);
    }
    ht.getMania();
    // long long num = 13005711862;
    // cout << num;
}