#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <math.h>
#include <vector>

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

void series1(double low, double high, int& r, vector <bool>& vec)
{
    double degtwo = 0;
    int k = 0; int p = 1;
    int i = 7;
    while (degtwo < low)
    {
        if (degtwo + (float)pow(2, -p) < high)
        {
            degtwo += (float)pow(2, -p); vec.push_back(1);
            cout << '1';
        }
        else {
            cout << '0'; vec.push_back(0);
             }
        i--; p++;
        if (i < 0 || degtwo >= low) {i = 7; r++;}

    }
    cout << "r= " << r << endl;
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
}


void vector1(ofstream& cod, vector<bool> vec)
{
    int i = 7;
    char k = 0;
    int r = 0;
    cout<<vec[3]<<endl;
    for (int j=0; j<vec.size(); j++)
    {
        
        k = k | vec[j] << i;
        i--;
        if (i < 0 || j == vec.size() - 1) { i = 7; r++; cod << k; cout<< "k="<< (int)k<<endl; k = 0; }
    }
    cout << endl << "r=" << r;
    while (r < 4) { k = 0; cod << k; r++;}
    
}

void coding(std::map<char, float[2]>& mp)
{
    double h, l, hold, lold;
    double h1, l1, hold1, lold1;
    double degtwo = 0;
    fstream in("исходный текст1.txt");
    ofstream cod("C:/Users/Дима и Егор/Source/repos/Арифметическое сжатие/код.txt");
    char buf;
    map<char, float[2]>::iterator it;

    in.get(buf);
     vector <bool> vec;
     vector <bool> vec1;
    while (in)
    {
        int r = 0;
        it = mp.find(buf);
        h = mp[it->first][1]; l = mp[it->first][0];
        cout << '[' << l << ' ' << h << ']' << endl;
        cout << buf << endl;
        it = mp.find('^');
        hold1 = h; lold1 = l;
        h1 = lold1 + (hold1 - lold1) * mp[it->first][1];
        l1 = lold1 + (hold1 - lold1) * mp[it->first][0];
        series1(l1, h1, r, vec);
         in.get(buf);
        while (in && r<4)
        {       r = 0;
                vec1.clear();
                cout << buf << endl;
                it = mp.find(buf);
                hold = h; lold = l;
                h = lold + (hold - lold) * mp[it->first][1];
                l = lold + (hold - lold) * mp[it->first][0];
                it = mp.find('^');
                hold1 = h; lold1 = l;
                h1 = lold1 + (hold1 - lold1) * mp[it->first][1];
                l1 = lold1 + (hold1 - lold1) * mp[it->first][0];
                cout << '[' << l1 << ' ' << h1 << ']' << endl;
                series1(l1, h1, r, vec1);
                if (r <= 4) { vec = vec1; in.get(buf);}
               
        }
        int i = 7;
        char k = 0;
        r = 0;
        
        for (int j = 0; j < vec.size(); j++)
        {

            k = k | vec[j] << i;
            i--;
            if (i < 0 || j == vec.size() - 1) {
                i = 7; r++; cout << "k=";
                while (i >= 0) {
                    if (k & 1 << i) cout << '1';
                    else cout << '0'; i--;
                }
                cout << endl;
                cod << k;
                i = 7; k = 0;
            }
        }
        
        while (r < 4) { k = 0; cod << k;  r++; }
        
    }
    in.close();
    cod.close();
    ifstream fd("C:/Users/Дима и Егор/Source/repos/Арифметическое сжатие/код.txt", ios::binary);
    char k1; fd >> k1;
    int i = 7;
    while (i >= 0)
    {
        if (k1 & 1 << i) cout << '1';
        else cout << '0'; i--;
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
    cout << fixed;
    cout.precision(16);
    cout << quan << endl;
    float kos = ceil(quan / (float)2);
    cout <<"kos="<< kos << endl;
    quan = quan + kos;
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
    Node* q = new Node;
    q->key = '^';
    q->freq = kos;
    fd1 << ' ' << '^' << kos;
    fsort.push_back(q);
    fsort.sort(comp);
    int k=0;
    list<Node*>::iterator it1 = fsort.begin();
    while (it1 != fsort.end())
    {
        beg = en; en = beg + (*it1)->freq / quan;
        mp[(*it1)->key][0] = beg; mp[(*it1)->key][1] = en;
        it1++;
    }
    
    out(mp);
    fc.close();
    coding(mp);
   int p = 1;
   fd1.close(); 
}





