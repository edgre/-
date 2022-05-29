#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <locale.h>

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

double section(int num, int& p)
{
        int i = 7;
        double q = 0;
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

void decod (double code, int &kol, map<char, float[2]>& q, ofstream& out)
{
    
    double rangeh, rangel;
    map<char, float[2]>::iterator it;
    int chank = 5;
    it = q.begin();
    while (code <= q[it->first][0] || code > q[it->first][1])
        it++;
    while (it->first!='^')
    {
        cout << code << '-';
        out << it->first;
        cout << it->first<<endl;
        rangel = q[it->first][0];
        rangeh = q[it->first][1];
        code = (code - rangel) / (rangeh - rangel);
        chank--; kol--;
        it = q.begin();
        while (code<=q[it->first][0] || code>q[it->first][1])
        it++;
    }
    cout << chank << endl;
    
    cout << endl;
    
    
}

bool proof()
{
    fstream fc("результат.txt");
    fstream fs("C:/Users/Дима и Егор/Source/repos/Арифметическое сжатие/Арифметическое сжатие/исходный текст1.txt");
    char sim, sim1;
    fc.get(sim); fs.get(sim1);
    while (fs || fc)
    {   cout << sim << ' ' << sim1 << endl;
        if (sim != sim1) return false;
        fc.get(sim); fs.get(sim1);
        
    }
    return true;
}

void weight(float weight1, float weight2)
{
    cout <<"файл сжат в "<< weight1 / weight2<<" раз";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    fstream fc("C:/Users/Дима и Егор/Source/repos/Арифметическое сжатие/частоты.txt");
    list<Node*> sort;
    char key; float size;
    fc.seekg(1, ios::cur);
    fc.get(key);
    fc >> size;
    float weight1 = size;
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
    cout.precision(16);
    out(mp);
    ifstream dec("C:/Users/Дима и Егор/Source/repos/Арифметическое сжатие/код.txt", ios::binary);
    ofstream out("результат.txt");
    char num;
    int weight2 = weight1;
    float weight3 = 0;
    int kolvo = 4;
    char bu;
    dec.get(num);
    cout << num << endl;
    while (dec) {
        double fromint = 0;
        int p = 1;
        while (kolvo && dec) 
        {
            if ((int)num == 13)
            {
                
                dec.get(bu);
                if ((int)bu == 10) num = bu;
                else dec.seekg(-1, ios::cur);
            }
            cout << (int)num << endl;
            fromint += section(num, p);
            cout << fromint << endl;
            dec.get(num);
            weight3++;
            kolvo--;
        }
       decod(fromint, weight2, mp, out);
       kolvo = 4;

   };
    _fcloseall();
    cout << endl;
    if (proof()) cout << "совпали" << endl;
    else cout << "не совпали";
    cout << endl;
    weight(weight1, weight3);
}