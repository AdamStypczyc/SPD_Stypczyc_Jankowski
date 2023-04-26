#include <iostream>
#include <vector>
#include <algorithm>
#include "RandomNumberGenerator.h"
#include <list>
#include <climits>
#include <unistd.h>

using namespace std;

struct Data {
    vector<int> p;
    int number;

    Data() { number = 0; }
};

int lower_bound(vector<Data>& job_to_do, vector<int> permutation,  int liczba_maszyn, int liczba_zadan)
{
    int LB = 0;
    vector<Data> current_tasks(job_to_do.size());
    for (int i = 0; i < liczba_zadan; i++) 
    {
        current_tasks[i] = job_to_do[permutation[i]];
    }
    for (int i = 0; i < liczba_zadan; i++)
    {
        LB += current_tasks[i].p[liczba_maszyn - 1];
    }
    return LB;
}

int Cmax(vector<Data> pi, int liczba_maszyn, int liczba_zadan)
{
    int C_max;
    int* p_i;
    p_i = new int[liczba_maszyn];
    for (int i = 0; i < liczba_maszyn; i++)
    {
        p_i[i] = 0;
    }

    for (int i = 0; i < liczba_zadan; i++)
    {
        p_i[0] = p_i[0] + pi[i].p[0];
        for (int j = 1; j < liczba_maszyn; j++)
        {
            p_i[j] = max(p_i[j - 1], p_i[j]) + pi[i].p[j];
        }
    }
    C_max = p_i[liczba_maszyn - 1];

    delete p_i;
    return C_max;
}

int Cmax_LB(vector<Data> job_to_do, vector<int> permutation,int liczba_maszyn, int liczba_zadan)
{
    int C_max;
    int* p_i;
    
    p_i = new int[liczba_maszyn];
    for (int i = 0; i < liczba_maszyn; i++)
    {
        p_i[i] = 0;
    }

    for (int i = 0; i < liczba_zadan; i++)
    {
        p_i[0] = p_i[0] + job_to_do[permutation[i]].p[0];
        for (int j = 1; j < liczba_maszyn; j++)
        {
            p_i[j] = max(p_i[j - 1], p_i[j]) + job_to_do[permutation[i]].p[j];
        }
    }
    C_max = p_i[liczba_maszyn - 1];

    // for (int i = 0; i < liczba_zadan; i++)
    // {
    //     cout << job_to_do[permutation[i]].number << " ";
    // }
    
    // cout << "| " << liczba_zadan << "| " << C_max<< endl;
    // usleep(100000);

    // if(liczba_zadan == 10)
    // {
    //     for (int i = 0; i < liczba_zadan; i++)
    //     {
    //         cout << job_to_do[permutation[i]].number << " ";
    //     }
        
    //     cout << "| " << liczba_zadan << "| " << C_max<< endl;
    //     usleep(10000);
    // }
    delete p_i;
    return C_max;
}

void make_tree(vector<Data>& job_to_do, int current_id, vector<int>& permutation, vector<bool>& used, vector<vector<Data>>& tree, int LB, int& UB, int liczba_maszyn, int liczba_zadan) 
{
    if (current_id == job_to_do.size() and (permutation[job_to_do.size() -1] != 0)) 
    {
        vector<Data> current_tasks(job_to_do.size());
        for (int i = 0; i < job_to_do.size(); i++) 
        {
            current_tasks[i] = job_to_do[permutation[i]];
        }
        int current_C_max = Cmax(current_tasks,liczba_maszyn,liczba_zadan);
        if(current_C_max < UB)
        {
            UB = current_C_max;
            if(!tree.empty())
            {
                tree.clear();
            }
            tree.push_back(current_tasks);
        }
    }
    else 
    {
        for (int i = 0; i < job_to_do.size(); i++) 
        {
            if (!used[i]) 
            {
                permutation[current_id] = i;
                used[i] = true;
                LB = Cmax_LB(job_to_do, permutation,liczba_maszyn, current_id+1);
                // LB = 0;
                if(LB<UB)
                {
                    make_tree(job_to_do, current_id + 1, permutation, used, tree, LB, UB, liczba_maszyn,liczba_zadan);
                    // make_tree(job_to_do, current_id +1, permutation, used, tree, LB, UB, liczba_maszyn,liczba_zadan);
                    used[i] = false;
                }
            }
        }
    }
}



int BranchandBound(vector<Data>& job_to_do, vector<Data>& best_order, int liczba_maszyn, int liczba_zadan) 
{
    vector<vector<Data>> tree;
    vector<int> permutation(job_to_do.size());
    vector<bool> used(job_to_do.size());

    int LB = lower_bound(job_to_do, permutation, liczba_maszyn, liczba_zadan);
    int UB = 10000;

    make_tree(job_to_do, 0, permutation, used, tree, LB, UB, liczba_maszyn,liczba_zadan);
    best_order = tree[0];
   
    return UB;
}

int main() 
{
    RandomNumberGenerator rdy(1);
    vector<Data> new_data;
    vector<Data> best_order;
    Data pi[10];
    int A = 0;
    int C_max;
    Data tmp;
    int liczba_maszyn;
    int liczba_zadan = 10;
    cout << "Podaj liczbe maszyn: ";
    cin >> liczba_maszyn;
    int pomoc;
    cout << "number\t";
    for (int i = 0; i < liczba_maszyn; i++)
    {
        cout << "p_" << i + 1 << "\t";
    }
    cout << endl;

    for (int i = 0; i < liczba_zadan; i++)
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

    int result = BranchandBound(new_data, best_order, liczba_maszyn, liczba_zadan);

    cout << "Kolejnosc wykonywanych zadan: ";
    for (int i = 0; i < best_order.size(); i++) 
    {
        cout << best_order[i].number << " ";
    }
    cout << endl;
    cout << "C_max = " << result << endl; //164 dobre 10 zadan 3 maszyny

    return 0;
}