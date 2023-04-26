#include <iostream>
#include <vector>
#include <algorithm>
#include "RandomNumberGenerator.h"
#include <list>
#include <climits>

using namespace std;

struct Data {
    vector<int> p;
    int number;

    Data() { number = 0; }
};


int Cmax(vector<Data> pi, int liczba_maszyn, int elem)
{
    int C_max;
    int* p_i;
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

void make_tree(vector<Data>& job_to_do, int current_id, vector<int>& permutation, vector<bool>& used, vector<vector<Data>>& tree) 
{
    if (current_id == job_to_do.size()) 
    {
        vector<Data> current_tasks(job_to_do.size());
        for (int i = 0; i < job_to_do.size(); i++) 
        {
            current_tasks[i] = job_to_do[permutation[i]];
        }
        tree.push_back(current_tasks);
    }
    else 
    {
        for (int i = 0; i < job_to_do.size(); i++) 
        {
            if (!used[i]) 
            {
                permutation[current_id] = i;
                used[i] = true;
                make_tree(job_to_do, current_id + 1, permutation, used, tree);
                used[i] = false;
            }
        }
    }
}


int brute_force(vector<Data>& job_to_do, vector<Data>& best_order, int elem) 
{
    vector<vector<Data>> tree;
    vector<int> permutation(job_to_do.size());
    vector<bool> used(job_to_do.size());

    make_tree(job_to_do, 0, permutation, used, tree);

    int Best_C_max = INT_MAX;
    for (int i = 0; i < tree.size(); i++) 
    {
        int current_C_max = Cmax(tree[i],2, elem);
        if (current_C_max < Best_C_max) 
        {
            Best_C_max = current_C_max;
            best_order = tree[i];
        }
    }

    return Best_C_max;
}

int main() 
{
    int elem = 10;
    RandomNumberGenerator rdy(1);
    vector<Data> new_data;
    vector<Data> best_order;
    Data pi[elem];
    int A = 0;
    int C_max;
    Data tmp;
    int liczba_maszyn;
    cout << "Podaj liczbe maszyn: ";
    cin >> liczba_maszyn;
    int pomoc;
    cout << "number\t";
    for (int i = 0; i < liczba_maszyn; i++)
    {
        cout << "p_" << i + 1 << "\t";
    }
    cout << endl;

    for (int i = 0; i < elem; i++)
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

    int result = brute_force(new_data, best_order, elem);

    cout << "Kolejnosc wykonywanych zadan: ";
    for (int i = 0; i < best_order.size(); i++) 
    {
        cout << best_order[i].number << " ";
    }
    cout << endl;
    cout << "C_max = " << result << endl;

    return 0;
}