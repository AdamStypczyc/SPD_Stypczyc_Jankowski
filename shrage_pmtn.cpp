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
    bool operator<(const Data &n) const
    {
        return r < n.r;
    }
    Data()
    {
        p = 0;
        r = 0;
        q = 0;
    }
};

struct Compare_q
{
    bool operator()(const Data &dana1, const Data &dana2)
    {
        // kolejność - malejaco
        if (dana1.q > dana2.q)
            return false;

        if (dana1.q < dana2.q)
            return true;

        return false;
    }
};

struct Compare_r
{
    bool operator()(const Data &dana1, const Data &dana2)
    {
        // kolejność - rosnąco
        if (dana1.r < dana2.r)
            return false;

        if (dana1.r < dana2.r)
            return true;

        return true;
    }
};


void Schrage_1(Data *dane)
{
    Data tmp[10];
    priority_queue<Data, vector<Data>, Compare_r> N;
    priority_queue<Data, vector<Data>, Compare_q> G;
    int t = 0;
    Data next_job;
    Data current_job;
    int Cmax = 0;
 
    for (int i = 0; i < 10; i++){
        tmp[i] = dane[i];
    }

    for (int i = 0; i < 10; i++){
        N.push(tmp[i]);
    }
    
    current_job.q = 9999;

    while (G.empty() != true || N.empty() != true)
    {
        while (N.empty() != true && (N.top().r <= t))
        {
            next_job = N.top();
            G.push(next_job);
            N.pop();
            if(next_job.q > current_job.q)
            {
                current_job.p = t - next_job.r;
                t = next_job.r;
                if(current_job.p > 0)
                {
                    G.push(current_job);
                }
            }
        }
        if (G.empty())
        {
            t = N.top().r; 
        }
        else
        {
            next_job = G.top();
            G.pop();
            current_job = next_job;
            t = t + next_job.p;
            Cmax = max(Cmax, t+next_job.q);
        }
    }
    cout << "Cmax\t" << Cmax << endl;
}

int main()
{
    RandomNumberGenerator rdy(7523);
    Data new_data[10];
    int A = 0;

    for (int i = 0; i < 10; i++)
    {
        new_data[i].p = rdy.nextInt(1, 29);
        A += new_data[i].p;
    }

    for (int i = 0; i < 10; i++)
    {
        new_data[i].r = rdy.nextInt(1, A);
    }
    // int X = 29;
    int X = A;

    for (int i = 0; i < 10; i++)
    {
        new_data[i].q = rdy.nextInt(1, X);
    }

    // Wyswietlanie nieposortowanych zadan
    cout << endl;
    cout << "r\t";
    for (int i = 0; i < 10; i++)
    {
        cout << new_data[i].r << " ";
    }
    cout << endl;
    cout << "p\t";
    for (int i = 0; i < 10; i++)
    {
        cout << new_data[i].p << " ";
    }
    cout << endl;
    cout << "q\t";
    for (int i = 0; i < 10; i++)
    {
        cout << new_data[i].q << " ";
    }
    cout << endl;
    //
    

    Schrage_1(new_data);

}  