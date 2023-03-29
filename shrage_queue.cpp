#include <iostream>
#include <algorithm>
#include <iomanip>
#include "RandomNumberGenerator.h"
#include <queue>
#include <list>


using namespace std;

struct Data
{
    int p;
    int r;
    int q;
    int S;
    int C;
    int Cq;
    bool operator<(const Data& n) const
    {
        return r < n.r;
    }
    Data()
    {
        p = 0;
        r = 0;
        q = 0;
        S = 0;
        C = 0;
        Cq = 0;
    }
};

struct Compare_q
{
    bool operator ()( const Data & dana1, const Data & dana2 )
    {
        //kolejność - rosnąco
        if( dana1.q > dana2.q ) return false;
       
        if( dana1.q < dana2.q ) return true;
       
        return false;
    }
}; 

list <Data> Schrage_2(Data* dane)
{
    int k = 1;
    Data tmp[10];
    list <Data> N;
    //list <Data> G;
    list <Data> Pi;
    priority_queue <Data, vector<Data>, Compare_q> G; 
    int t;
    Data tmp_q; // do znajdowania max q w G
    list<Data>::iterator wsk_G;
    list<Data>::iterator help;
    for (int i = 0; i < 10; i++){
        tmp[i] = dane[i];
    }

    sort(tmp, tmp + 10);

    for (int i = 0; i < 10; i++) {
        N.push_back(tmp[i]);
    }
  
    t = N.front().r;

    while (G.empty() != true || N.empty() != true)
    {
        while (N.empty() != true && N.front().r <= t)
        {
            G.push(N.front()); //2. wersja będzie na kolejkę priorytetowa
            N.pop_front();
        }
        if (G.empty() != true)
        {
            tmp_q = G.top();
            
            tmp_q.S = t;
            tmp_q.C = t + tmp_q.p;
            tmp_q.Cq = tmp_q.C + tmp_q.q;
            t += tmp_q.p;
            k += 1;
            G.pop();
            
            Pi.push_back(tmp_q);
            
        }
        else {
            Data tmp_t = N.front();
            list<Data>::iterator wsk_N = N.begin();
            while (wsk_N != N.end())
            {
                wsk_N = next(wsk_N);
                if (tmp_t.r < wsk_N->r){
                    tmp_t = *wsk_N;
                }
            }
            t = tmp_t.r;
        }
    }

    return Pi;
}


int main()
{
    RandomNumberGenerator rdy(1);
    Data new_data[10];
    int A = 0;

    for (int i = 0; i < 10; i++){
        new_data[i].p = rdy.nextInt(1, 29);
        A += new_data[i].p;
    }

    for (int i = 0; i < 10; i++){
        new_data[i].r = rdy.nextInt(1, A);
    }
    //int X = 29;
    int X = A;

    for (int i = 0; i < 10; i++){
        new_data[i].q = rdy.nextInt(1, X);
    }

    // Wyswietlanie nieposortowanych zadan
    cout << endl;
    cout << "r\t";
    for (int i = 0; i < 10; i++){
        cout << new_data[i].r << " ";
    }
    cout << endl;
    cout << "p\t";
    for (int i = 0; i < 10; i++){
        cout << new_data[i].p << " ";
    }
    cout << endl;
    cout << "q\t";
    for (int i = 0; i < 10; i++){
        cout << new_data[i].q << " ";
    }
    cout << endl;
    //

    list <Data> PI = Schrage_2(new_data);

    // Wyswietlanie posortowanych zadan
    cout << endl;
    list<Data>::iterator wsk;
    wsk = PI.begin();
    cout << "S\t";
    for (wsk = PI.begin(); wsk != PI.end(); wsk++) {
        cout << wsk->S << " ";
    }
    cout << endl;
    wsk = PI.begin();
    cout << "C\t";
    for (wsk = PI.begin(); wsk != PI.end(); wsk++) {
        cout << wsk->C << " ";
    }
    cout << endl;
    wsk = PI.begin();
    cout << "Cq\t";
    for (wsk = PI.begin(); wsk != PI.end(); wsk++) {
        cout << wsk->Cq << " ";
    }
    cout << endl;
    
}

