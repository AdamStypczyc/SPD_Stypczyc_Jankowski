#include <iostream>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include "RandomNumberGenerator.h"
#include <queue>
#include <list>

using namespace std;

struct Data
{
    vector<int> p;
    int lower_p;
    int number;

    Data()
    {
        number = 0;
        lower_p = 999999999;
    }
};

int return_lower_p(Data dane)
{
    int lower = 9999999;
    // vector<int>::const_iterator tmp = dane.p.begin();

    // for (int i = 0; i < dane.p.size(); i++)
    // {
        cout << "dupa " << dane.p[0] << " " << dane.p[1] << endl;
        // if (*tmp < lower)
        // {
        //     lower = *tmp;
            
        // }
        
    // }
    // return lower;
}

list<Data> Johnson(list<Data> dane)
{
    Data pi[10];
    int l = 0; // indeksy tablicy
    int k = 9;
    int tmp_min_indeks;
    Data *wsk;
    list<Data> N = dane;
    while (!N.empty())
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                //     wsk = N.front();
            }
        }
    }
}

int main()
{
    RandomNumberGenerator rdy(1);
    list<Data> new_data;
    list<Data> wynik;
    int A = 0;
    Data tmp;
    int liczba_maszyn = 2;
    int pomoc;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < liczba_maszyn; j++)
        {
            pomoc = rdy.nextInt(1, 29);
            tmp.p.push_back(pomoc);
            cout << pomoc << " " << tmp.p[j] << " ";
        }
        cout << endl;
        return_lower_p(tmp);
        //cout << i << ": " << return_lower_p(tmp) << endl;
        new_data.push_back(tmp);
        tmp.p.clear();
        
    }

    // wynik = Johnson(new_data);
}