#include <iostream>
#include <fstream>
#include <map>
#include <list>

using namespace std;

struct Node
{
    float freq;
    char key;
};

bool comp(const Node* a, const Node* b)
{
    return a->freq > b->freq;
}

void out(std::map<char, float[2]>& mp)
{
    map<char, float[2]>::iterator it = mp.begin();
    while (it != mp.end())
    {
        cout << it->first << '-';
        cout << '[' << mp[it->first][0] << ' ' << mp[it->first][1] << ']' << endl;
        it++;
    }
}

float section()
{
    ifstream dec("C:/Users/Дима и Егор/Source/repos/Арифметическое сжатие/код.txt", ios::binary);
    int i = 31;
    int num;
    dec >> num;
    int p = 1;
    float q=0;
    while (i >= 0)
    {
        if (num & 1 << i) {
            q = q + pow(2, -p); cout << '1';
        }
        else cout << '0';
        p++; i--;
    }
    cout << endl;
    return q;
}

void decod (float code, map<char, float[2]>& q)
{
    float rangeh, rangel;
    map<char, float[2]>::iterator it;
    int i = 0;
    while (i != 6)
    {
        it = q.begin();
        while (code<=q[it->first][0] || code>q[it->first][1])
            it++;
        cout << it->first;
        rangel = q[it->first][0];
        rangeh = q[it->first][1];
        code = (code - rangel) / (rangeh - rangel);
        i++;
    }
}

int main()
{
    fstream fc("C:/Users/Дима и Егор/Source/repos/Арифметическое сжатие/частоты.txt");
    list<Node*> sort;
    char key; int size;
    fc.seekg(1, ios::cur);
    fc.get(key);
    fc >> size;
    int weight1 = size;
    cout << weight1 << endl;
    list<Node*> fsort;
    map <char, float[2]>mp;
    // считываем символы исходного текста и их частоты
    while (fc)
    {
        Node* push = new Node;
        push->key = key; push->freq = size;
        fsort.push_back(push);
        fc.seekg(1, ios::cur);
        fc.get(key);
        fc >> size;
        if (fc) { weight1 += size; };
    }
    cout << weight1 << endl;
    fsort.sort(comp);
    list<Node*>::iterator it1 = fsort.begin();
    float beg = 0, en = 0;
    while (it1 != fsort.end())
    {
        beg = en; en = beg + (*it1)->freq / weight1;
        mp[(*it1)->key][0] = beg; mp[(*it1)->key][1] = en;
        it1++;
    }
    cout << fixed;
    cout.precision(8);
    out(mp);
    float fromint = section();
    cout << fromint << endl;
    decod(fromint, mp);

}