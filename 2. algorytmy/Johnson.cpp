#include <iostream>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include "RandomNumberGenerator.h"
#include <queue>
#include <list>
#include <climits>

using namespace std;

struct Data
{
    vector<int> p;
    int number;

    Data(){number = 0;}
};

int lower_p(Data dane)
{
    int lower = INT_MAX;
    int i = 0;
    for(int i=0; i<dane.p.size(); i++)
    {
        if (dane.p[i] < lower)
        {
            lower = dane.p[i];
        }
    }
    return lower;
}

void Johnson(list<Data> dane, Data *pi)
{
    int l = 0; // indeksy tablicy
    int k = 9;
    int min = INT_MAX;
    list<Data>::iterator help;
    list<Data>::iterator to_erase;
    list<Data> N = dane;

    while (!N.empty())
    {
        help = N.begin();
        for (int i = 0; i < N.size(); i++)
        {
            if (lower_p(*help) < min)
            {
                min = lower_p(*help);
                to_erase = help;
            }
            help++;
        }
        if (to_erase->p[0] < to_erase->p[1])
        {
            pi[l] = *to_erase;
            l++;
        }
        else
        {
            pi[k] = *to_erase;
            k--;
        }
        N.erase(to_erase);
        min = INT_MAX;
    }  
}

int Cmax(Data *pi)
{
    int C_max;
    int p_1 = 0;
    int p_2 = 0;
    
    for (int i = 0; i<10; i++)
    {
        p_1 = p_1 + pi[i].p[0];
        p_2 = max(p_1, p_2) + pi[i].p[1];
    }
    C_max = p_2;

    return C_max;
}

int main()
{
    RandomNumberGenerator rdy(1);
    list<Data> new_data;
    Data pi[10];
    int A = 0;
    int C_max;
    Data tmp;
    int liczba_maszyn = 2;
    int pomoc;
    cout << "number\t" << "p_1\t" << "p_2\t" << endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < liczba_maszyn; j++)
        {
            pomoc = rdy.nextInt(1, 29);
            tmp.p.push_back(pomoc);
        }
        tmp.number = i + 1;
        new_data.push_back(tmp);
        cout << tmp.number << "\t" << tmp.p[0] << "\t" << tmp.p[1] << endl;
        tmp.p.clear();
    }

    Johnson(new_data, pi);
    cout << "Order\t";
    for (int i = 0; i < 10; i++)
    {
        cout << pi[i].number << "\t";
    }

    C_max = Cmax(pi);
    cout << endl << "C_max\t" << C_max << endl;

}
