#include <iostream>
#include <algorithm>
#include <iomanip>
#include "RandomNumberGenerator.h"
#include <queue>
#include <list>
#include <vector>
#include <functional>
#include <bits/stdc++.h>

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
		S = 0;
        C = 0;
        Cq = 0;
    }
    Data(int r, int p, int q) : r(r), p(p), q(q) {}
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




int Schrage_pmtn(vector<Data> dane)
{
    int size = 12;
    Data tmp[size];
    priority_queue<Data, vector<Data>, Compare_r> N;
    priority_queue<Data, vector<Data>, Compare_q> G;
    int t = 0;
    Data next_job;
    Data current_job;
    int Cmax = 0;
 
    for (int i = 0; i < size; i++){
        tmp[i] = dane[i];
    }

    for (int i = 0; i < size; i++){
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

    return Cmax;
}




int Schrage(vector<Data> dane)
{
	int Cmax_schrage = 0;
    int k = 1;
    int size = 12;
    Data tmp[size];
    list <Data> N;
    list <Data> G;
    list <Data> Pi;
    int t;
    Data tmp_q; // do znajdowania max q w G
    list<Data>::iterator wsk_G;
    list<Data>::iterator help;
    for (int i = 0; i < size; i++){
        tmp[i] = dane[i];
    }

    sort(tmp, tmp + size);

    for (int i = 0; i < size; i++) {
        N.push_back(tmp[i]);
    }
  
    t = N.front().r;

    while (G.empty() != true || N.empty() != true)
    {
        while (N.empty() != true && N.front().r <= t)
        {
            G.push_back(N.front()); //2. wersja będzie na kolejkę priorytetowa
            N.pop_front();
        }
        if (G.empty() != true)
        {
            tmp_q = G.front();
            wsk_G = G.begin();
            help = wsk_G;
            tmp_q = *wsk_G;
            while (wsk_G != G.end())
            {
                if (tmp_q.q < wsk_G->q){
                    tmp_q = *wsk_G;
                    help = wsk_G;
                }
                wsk_G = next(wsk_G);
            }
            G.erase(help);
            tmp_q.S = t;
            tmp_q.C = t + tmp_q.p;
            tmp_q.Cq = tmp_q.C + tmp_q.q;
            Pi.push_back(tmp_q);
			if(Cmax_schrage < tmp_q.Cq)
			{
				Cmax_schrage = tmp_q.Cq;
			}
            t += tmp_q.p;
            k += 1;
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

    return Cmax_schrage;
}





int carlier(vector<Data> &to_do)
{
    int n = to_do.size();
    int Cmax = Schrage(to_do);

    // krok 1
    int UB = Cmax;
    int LB = Schrage_pmtn(to_do);

    // krok 2
    // while (UB < LB)
    while (UB > LB)
    {
        int b = -1, c = -1, s = 0;
        int t = 0;

        for (int i = 0; i < n; i++)
        {
            t += to_do[i].p;
            s = max(s, t + to_do[i].q - UB);
            if (s == t + to_do[i].q - UB)
            {
                b = i;
            }
        }

        t = 0;

        for (int i = 0; i <= b; i++)
        {
            t += to_do[i].p;
            s = max(s, t + to_do[b].q + to_do[b].p - UB);
            if (s == t + to_do[b].q + to_do[b].p - UB)
            {
                c = i;
            }
        }

        // krok 3
        if (c == -1)
        {
            to_do[b].r = max(to_do[b].r, UB - to_do[b].p - to_do[b].q);
        }
        else
        {
            int r_c = to_do[c].r;
            for (int i = c + 1; i <= b; i++)
            {
                r_c = min(r_c, to_do[i].r - to_do[c].p);
            }

            to_do[c].r = max(to_do[c].r, UB - s - to_do[c].q - r_c);
            to_do[c].r = max(to_do[c].r, to_do[b].r - to_do[b].p);
            for (int i = c + 1; i <= b; i++)
            {
                to_do[i].r = min(to_do[i].r, to_do[i - 1].r + to_do[i - 1].p);
            }
        }

        // krok 4
        int new_LB = Schrage_pmtn(to_do);
        if (new_LB < LB)
        {
            LB = new_LB;
        }
        else
        {
            // krok 5
            int r_b = to_do[b].r;
            for (int i = b - 1; i >= c; i--)
            {
                r_b = min(r_b, to_do[i].r + to_do[i].p);
            }

            to_do[b].r = min(to_do[b].r, UB - s - to_do[c].q - r_b);
            to_do[b].r = max(to_do[b].r, to_do[c].r + to_do[c].p);
            for (int i = c + 1; i <= b; i++)
            {
                to_do[i].r = min(to_do[i].r, to_do[i - 1].r + to_do[i - 1].p);
            }
        }

        // krok 6
        // Cmax = Schrage(to_do);
        Cmax = Schrage_pmtn(to_do);
        UB = min(UB, Cmax);
    }

    return UB;
}

int main()
{
    RandomNumberGenerator rdy(1);
    int size = 12;
    Data new_data[size];
    vector<Data> to_do;
    int A = 0;

    for (int i = 0; i < size; i++)
    {
        new_data[i].p = rdy.nextInt(1, 29);
        A += new_data[i].p;
    }

    for (int i = 0; i < size; i++)
    {
        new_data[i].r = rdy.nextInt(1, A);
    }
    // int X = 29;
    int X = A;

    for (int i = 0; i < size; i++)
    {
        new_data[i].q = rdy.nextInt(1, X);
    }

    // Wyswietlanie nieposortowanych zadan
    cout << endl;
    cout << "r\t";
    for (int i = 0; i < size; i++)
    {
        cout << new_data[i].r << " ";
    }
    cout << endl;
    cout << "p\t";
    for (int i = 0; i < size; i++)
    {
        cout << new_data[i].p << " ";
    }
    cout << endl;
    cout << "q\t";
    for (int i = 0; i < size; i++)
    {
        cout << new_data[i].q << " ";
    }
    cout << endl;
    //

    for (int i = 0; i < size; i++)
    {
        to_do.push_back(new_data[i]);
    }
    

    int Cmax = carlier(to_do);

    cout << "Cmax: " << Cmax << endl;

    return 0;
}
