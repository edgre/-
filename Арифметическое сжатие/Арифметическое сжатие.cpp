﻿#include <iostream>
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

void series(float low, float high)
{
    float degtwo = 0;
    double k; int p = 1;
    int mask;
    while (degtwo > low)
    {
        if (degtwo + pow(2, -p) < high)
        {
            degtwo += pow(2, -p);
        }
    }
}

void coding(std::map<char, float[2]>& mp)
{
    float h, l, hold, lold;
    fstream in("исходный текст1.txt");
    char buf;
    in.get(buf);
    map<char, float[2]>::iterator it;
    it = mp.find(buf);
    h = mp[it->first][1]; l = mp[it->first][0];

    cout << '[' << l << ' ' << h << ']' << endl;
    in.get(buf);
    while (in)
    {
        it = mp.find(buf);
        hold = h; lold = l;
        h = lold + (hold - lold) * mp[it->first][1];
        l = lold + (hold - lold) * mp[it->first][0];
        cout << '[' << l << ' ' << h << ']' << endl;
        in.get(buf);
    }

}
int main()
{
    float asc[256];
    int n = 0;
    for (int i = 0; i < 256; i++) asc[i] = 0;
    fstream fc("исходный текст1.txt");
    char sim;
    fc >> sim;
    int quan = 0;
    while (fc)
    {
        asc[(int)sim]++;
        fc.get(sim);
        quan++;
    };
    map <char, float[2]> mp;
    list<Node*>fsort;
    fstream fd1("C:/Users/Дима и Егор/Source/repos/Арифметическое сжатие/частоты.txt", ios::out);
    float beg = 0, en = 0;
    for (int i = 0; i < 256; i++)

    {
        if (asc[i] != 0)
        {
            Node* q = new Node;
            q->key = (char)i;
            q->freq = asc[i];
            fsort.push_back(q);
        }
    }
    fsort.sort(comp);

    list<Node*>::iterator it1 = fsort.begin();

    while (it1 != fsort.end())
    {
        beg = en; en = beg + (*it1)->freq / quan;
        mp[(*it1)->key][0] = beg; mp[(*it1)->key][1] = en;
        it1++;
    }
    cout << fixed;
    cout.precision(8);
    out(mp);
    fc.close();
    coding(mp);
}





