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

int policz_p1_wirtualne(list<Data>::iterator wsk)
{
    int suma = 0;
    for (int i = 0; i < (int)wsk->p.size()-1; i++)
    {
        suma += wsk->p[i];
    }
    return suma;
}
int policz_p2_wirtualne(list<Data>::iterator wsk)
{
    int suma = 0;
    for (int i = 1; i < (int)wsk->p.size(); i++)
    {
        suma += wsk->p[i];
    }
    return suma;
}
void Johnson(list<Data> dane, Data *pi)
{
    int l = 0; // indeksy tablicy
    int k = 9;
    int min = INT_MAX;
    list<Data>::iterator help;
    list<Data>::iterator to_erase;
    list<Data> N = dane;
    int p1 = 0, p2 =0;
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
        // p1 = policz_p1_wirtualne(to_erase);
        // p2 = policz_p2_wirtualne(to_erase);
        p1 = to_erase->p.front();
        p2 = to_erase->p.back();

        if (p1 < p2)
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

int Cmax(Data *pi,int liczba_maszyn)
{
    int C_max;
    int *p_i;
    p_i = new int[liczba_maszyn];
    for (int i = 0; i < sizeof(p_i); i++)
    {
        p_i[i] = 0;
    }
    
    for (int i = 0; i<10; i++)
    {
        p_i[0] = p_i[0] + pi[i].p[0];
        for(int j = 1; j < liczba_maszyn; j++)
        {
            p_i[j] = max(p_i[j-1], p_i[j]) + pi[i].p[j];
        }
    }
    C_max = p_i[liczba_maszyn-1];

    delete p_i;
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
    int liczba_maszyn;
    cout << "Podaj liczbę maszyn: ";
    cin >> liczba_maszyn;
    int pomoc;
    cout << "number\t";
    for (int i = 0; i < liczba_maszyn; i++)
    {
        cout << "p_"<< i+1 << "\t";
    }
    cout << endl;
    
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < liczba_maszyn; j++)
        {
            pomoc = rdy.nextInt(1, 29);
            tmp.p.push_back(pomoc);
        }
        tmp.number = i + 1;
        new_data.push_back(tmp);
        cout << tmp.number << "\t";
        for (int i = 0; i < liczba_maszyn; i++)
        {
            cout << tmp.p[i] << "\t";
        }
        cout << endl;
        tmp.p.clear();
    }

    Johnson(new_data, pi);
    cout << "Order\t";
    for (int i = 0; i < 10; i++)
    {
        cout << pi[i].number << "\t";
    }
    cout << endl;

    C_max = Cmax(pi,liczba_maszyn);
    cout << "C_max\t" << C_max << endl;

}
