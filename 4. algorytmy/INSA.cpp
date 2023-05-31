#include <iostream>
#include <vector>
#include <algorithm>
#include "RandomNumberGenerator.h"
#include <list>
#include <climits>
#include <cmath>
#include <unistd.h>

using namespace std;

struct Data
{
    vector<int> p; // czas wykonywania
    vector<int> u; // rodzaj maszyny
    int number;    // numer operacji

    Data() { number = 0; }
};

int Cmax(const vector<Data> &schedule)
{
    int liczba_maszyn = 0;
    for (int i = 0; i < schedule.size(); i++)
    {
        const Data &data = schedule[i];
        int maxMachine = *max_element(data.u.begin(), data.u.end());
        liczba_maszyn = max(liczba_maszyn, maxMachine);
    }

    vector<int> machineEndTime(liczba_maszyn, 0);

    for (int i = 0; i < schedule.size(); i++)
    {
        const Data &data = schedule[i];
        for (int j = 0; j < data.p.size(); j++)
        {
            int machine = data.u[j] - 1;
            int processingTime = data.p[j];

            if (j == 0)
            {
                if (machine == 0)
                {
                    machineEndTime[machine] += processingTime;
                }
                else
                {
                    machineEndTime[machine] = max(machineEndTime[machine], machineEndTime[machine - 1]) + processingTime;
                }
            }
            else
            {
                machineEndTime[machine] = max(machineEndTime[machine], machineEndTime[machine - 1]) + processingTime;
            }
        }
    }

    int maxEndTime = *max_element(machineEndTime.begin(), machineEndTime.end());

    return maxEndTime;
}

vector<Data> INSA(int elem, int liczba_maszyn, int iterations, vector<Data> new_data)
{
    vector<Data> bestSchedule;
    int bestCmax = INT_MAX;

    for (int i = 0; i < iterations; i++)
    {
        int currentCmax = Cmax(new_data);

        // Lokalne przeszukiwanie sąsiedztwa
        bool improved;
        do
        {
            improved = false;
            for (int j = 0; j < elem; j++)
            {
                for (int k = 1; k < new_data[j].p.size(); k++)
                {
                    swap(new_data[j].p[k - 1], new_data[j].p[k]);
                    int newCmax = Cmax(new_data);
                    if (newCmax < currentCmax)
                    {
                        currentCmax = newCmax;
                        improved = true;
                    }
                    else
                    {
                        swap(new_data[j].p[k - 1], new_data[j].p[k]);
                    }
                }
            }
        } while (improved);

        // Aktualizacja najlepszego harmonogramu
        if (currentCmax < bestCmax)
        {
            bestCmax = currentCmax;
            bestSchedule = new_data;
        }
    }

    return bestSchedule;
}

int main()
{
    RandomNumberGenerator rdy(2451);
    vector<Data> new_data;
    Data tmp;
    vector<int> o;
    int elem = 5;
    int liczba_maszyn = 4;
    int iterations = 1000;

    for (int i = 0; i < elem; i++)
    {
        int pomoc_o = rdy.nextInt(1, (int)(liczba_maszyn * 1.2)) + 1;
        o.push_back(pomoc_o);
        for (int j = 0; j < o[i]; j++)
        {
            int pomoc = rdy.nextInt(1, 29);
            tmp.p.push_back(pomoc);
        }
        tmp.number = i + 1;
        new_data.push_back(tmp);
        tmp.p.clear();
    }
    for (int i = 0; i < elem; i++)
    {

        for (int j = 0; j < o[i]; j++)
        {
            int pomoc = rdy.nextInt(1, liczba_maszyn);
            tmp.u.push_back(pomoc);
        }
        new_data[i].u = tmp.u;
        tmp.u.clear();
    }

    // Wyświetlenie wygenerowanego harmonogramu
    for (int i = 0; i < elem; i++)
    {
        cout << new_data[i].number << "." << endl;
        cout << "p: [";
        for (int j = 0; j < new_data[i].p.size(); j++)
        {
            if (j == new_data[i].p.size() - 1)
                cout << new_data[i].p[j];
            else
                cout << new_data[i].p[j] << ", ";
        }
        cout << "]" << endl;
        cout << "u: [";
        for (int j = 0; j < new_data[i].u.size(); j++)
        {
            if (j == new_data[i].u.size() - 1)
                cout << new_data[i].u[j];
            else
                cout << new_data[i].u[j] << ", ";
        }
        cout << "]" << endl;
    }

    vector<Data> bestSchedule = INSA(elem, liczba_maszyn, iterations, new_data);

    vector<int> machineEndTimes(liczba_maszyn, 0);

    for (int i = 0; i < bestSchedule.size(); i++)
    {
        for (int j = 0; j < bestSchedule[i].p.size(); j++)
        {
            int machine = bestSchedule[i].u[j] - 1;
            int processingTime = bestSchedule[i].p[j];

            if (j == 0)
            {
                if (machine == 0)
                {
                    machineEndTimes[machine] += processingTime;
                }
                else
                {
                    machineEndTimes[machine] = max(machineEndTimes[machine], machineEndTimes[machine - 1]) + processingTime;
                }
            }
            else
            {
                machineEndTimes[machine] = max(machineEndTimes[machine], machineEndTimes[machine - 1]) + processingTime;
            }
        }
    }

    // Wyświetlenie czasów zakończenia zadań na każdej z maszyn
    cout << "Czasy zakończenia zadań na maszynach:" << endl;
    for (int m = 1; m <= liczba_maszyn; m++)
    {
        cout << "Maszyna " << m << ": " << machineEndTimes[m - 1] << endl;
    }
    // Obliczenie Cmax dla najlepszego harmonogramu
    int bestCmax = Cmax(bestSchedule);
    cout << "Wartość Cmax: " << bestCmax << endl;
    return 0;
}