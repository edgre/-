#include <iostream>
#include <fstream>
#include <map>

using namespace std;

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
    float degtwo=0;
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
    map<float, char> sort;
    map <char, float[2]> mp;

    fstream fd1("C:/Users/Дима и Егор/Source/repos/Арифметическое сжатие/частоты.txt", ios::out);
    float beg = 0, en = 0;
    for (int i = 0; i < 256; i++)

    {
        if (asc[i] != 0)
        {
            sort[asc[i]] = char(i);
            cout <<asc[i]<<' '<< sort[asc[i]] << endl;
        }
    }

    map<float, char>::iterator it1=sort.begin();

    while (it1!=sort.end())
    {
        beg = en; en = beg + it1->first / quan;;
        cout << en << endl;
        mp[it1->second][0] = beg; mp[it1->second][1] = en;
        it1++;
    }
    cout << fixed;
    cout.precision(8);
    out(mp);
    fc.close();
    coding(mp);
}





