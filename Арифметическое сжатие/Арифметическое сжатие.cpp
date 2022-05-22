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

int series (double low, double high)
{
    double degtwo = 0;
    unsigned int k=0; int p = 1;
    int i = 31;
    while (degtwo<low)
    {
        
        
        if (degtwo + (float)pow(2, -p) < high)
        {
            degtwo += (float)pow(2, -p); k |= 1 << i;
            cout << '1';
        }
        else cout << '0';
        i--; p++;
    }
    cout << endl;
    cout << degtwo;
    cout << endl;
     /*i = 31;
    while (i >= 0)
    {
        if (k & 1 << i) cout << '1';
        else cout << '0';
        i--;
    }
    cout << endl;*/
    return k;
    
}

void coding(std::map<char, float[2]>& mp)
{
    double h, l, hold, lold;
    fstream in("исходный текст1.txt");
    fstream cod("C:/Users/Дима и Егор/Source/repos/Арифметическое сжатие/код.txt", ios::out);
    char buf;
    map<char, float[2]>::iterator it;
    while (in)
    {
        int k = 0;
        in.get(buf);
        it = mp.find(buf);
        h = mp[it->first][1]; l = mp[it->first][0];
        cout << '[' << l << ' ' << h << ']' << endl;
        cout << buf << endl;
        k++;
        while (in&&k!=5)
        {   in.get(buf); cout << buf << endl;
            it = mp.find(buf);
            hold = h; lold = l;
            h = lold + (hold - lold) * mp[it->first][1];
            l = lold + (hold - lold) * mp[it->first][0];
            cout << '[' << l << ' ' << h << ']' << endl;
            k++;
        }
      unsigned int sim= series(l, h);
      cout << sim << endl;
      cod << sim;
    }
    in.close();
    cod.close();
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
            fd1 << ' ' << (char)i <<asc[i];
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
    cout.precision(16);
    out(mp);
    fc.close();
    coding(mp);
   int p = 1;
   fd1.close();
   fstream cod("C:/Users/Дима и Егор/Source/repos/Арифметическое сжатие/код.txt", ios::binary);
   int num;
   cod >> num; cod >> num; cod >> num;
   cout << endl;
   for (int i = 31; i >= 0; i--)
   {
       if (num & 1 << i) cout << '1';
       else cout << '0';
   }
   
}





