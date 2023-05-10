#include <iostream>
#include <vector>
#include <algorithm>
#include "RandomNumberGenerator.h"
#include <list>
#include <climits>
#include <cmath>
#include <sys/resource.h>
#include <unistd.h>

using namespace std;

struct Data
{
    vector<int> p;
    vector<int> w;
    vector<int> d;
    int number;

    Data() { number = 0; }
};

int Cmax(vector<Data> pi, int liczba_maszyn, int elem)
{
    int C_max;
    int *p_i;
    p_i = new int[liczba_maszyn];
    for (int i = 0; i < liczba_maszyn; i++)
    {
        p_i[i] = 0;
    }

    for (int i = 0; i < elem; i++)
    {
        p_i[0] = p_i[0] + pi[i].p[0];
        for (int j = 1; j < liczba_maszyn; j++)
        {
            p_i[j] = max(p_i[j - 1], p_i[j]) + pi[i].p[j];
        }
    }
    C_max = p_i[liczba_maszyn - 1];

    return C_max;
}

struct Result
{
    int penalty;
    vector<int> order;
};

Result dynamic_programing(vector<Data> new_data)
{
    vector<Data> J = new_data;
    int n = J.size();
    int mask = (1 << n);

    vector<Result> memory(mask, {INT_MAX, {}}); // parę (minimalna kara, kolejność zadań)

    memory[0] = {0, {}}; // dla pustego podzbioru zadań minimalna kara wynosi zero

    for (int D = 1; D < mask; D++)
    {
        int time_sum = 0;
        for (int i = 0; i < n; i++)
        {
            if (D & (1 << i))
            {
                time_sum += J[i].p[0];
            }
        }
        Result MinResult = {INT_MAX, {}}; //(minimalna kara, kolejność zadań) dla danego podzbioru zadań
        for (int i = 0; i < n; i++)
        {
            if (D & (1 << i))
            {
                Result r = memory[D ^ (1 << i)];
                int pen = max(time_sum - J[i].d[0], 0) * J[i].w[0] + r.penalty;
                if (pen < MinResult.penalty)
                {
                    MinResult.penalty = pen;
                    MinResult.order = r.order;
                    MinResult.order.push_back(i + 1);
                }
            }
        }
        memory[D] = MinResult;
    }
    return memory[mask - 1];
}

int main()
{
    rusage usage;
    int elem = 25;
    RandomNumberGenerator rdy(1);
    vector<Data> new_data;
    Data pi[elem];
    int A = 0;
    int C_max;
    Data tmp;
    int liczba_maszyn = 1;
    int pomoc;
    cout << "number\t";
    for (int i = 0; i < liczba_maszyn; i++)
    {
        cout << "p_" << i + 1 << "\t";
    }

    for (int i = 0; i < liczba_maszyn; i++)
    {
        cout << "w_" << i + 1 << "\t";
    }

    for (int i = 0; i < liczba_maszyn; i++)
    {
        cout << "d_" << i + 1 << "\t";
    }
    cout << endl;

    for (int i = 0; i < elem; i++)
    {
        for (int j = 0; j < liczba_maszyn; j++)
        {
            pomoc = rdy.nextInt(1, 29);
            tmp.p.push_back(pomoc);
            A += pomoc;
        }
        for (int j = 0; j < liczba_maszyn; j++)
        {
            pomoc = rdy.nextInt(1, 9);
            tmp.w.push_back(pomoc);
        }
        for (int j = 0; j < liczba_maszyn; j++)
        {
            // pomoc = rdy.nextInt(1, A);
            pomoc = rdy.nextInt(1, 29);
            tmp.d.push_back(pomoc);
        }
        tmp.number = i + 1;
        new_data.push_back(tmp);
        cout << tmp.number << "\t";
        for (int i = 0; i < liczba_maszyn; i++)
        {
            cout << tmp.p[i] << "\t";
        }
        for (int i = 0; i < liczba_maszyn; i++)
        {
            cout << tmp.w[i] << "\t";
        }
        for (int i = 0; i < liczba_maszyn; i++)
        {
            cout << tmp.d[i] << "\t";
        }
        cout << endl;
        tmp.p.clear();
        tmp.w.clear();
        tmp.d.clear();
    }

    Result result = dynamic_programing(new_data);

    cout << "Minimalna kara: " << result.penalty << endl;
    cout << "Kolejnosc zadan: ";
    for (int i = 0; i < result.order.size(); i++)
    {
        cout << result.order[i] << " ";
    }
    cout << endl;

    vector<Data> PI_Cmax;

    for (int i = 0; i < elem; i++)
    {
        PI_Cmax.push_back(new_data[result.order[i]-1]);
    }
    int end_cmax = Cmax(PI_Cmax, 1, elem);
    cout << "Cmax: " << end_cmax << endl;
    getrusage(RUSAGE_SELF, &usage);
    long memory_used = usage.ru_maxrss;
    cout << "Ilość zużytej pamięci: " << memory_used << " KB" << endl;
    return 0;
}
