import math
from RandomNumberGenerator import RandomNumberGenerator

def find_index_2d(array, current_task_index, value):
    indexes = []
    
    max_array = 0 
    for i in range(current_task_index):
        for j in range(len(array[i])):
            if array[i][j] == value:
                if array[i][j] > max_array:
                    max_array = array[i][j]

    for i in range(current_task_index):
        for j in range(len(array[i])):
            if array[i][j] == max_array:
                indexes = []
                indexes.append((i, j))
 
    if not indexes:
        return None
    else:
        # return [indexes[len(indexes)-1]]
        return indexes

def count_values_2d(array):
    count = 0

    for row in array:
        count += len(row)

    return count

def calculate_Cmax(p, mu):
    n = len(p)  # liczba zadań

    # Obliczenie maksymalnej liczby maszyn dla zadania
    m = max(max(mu[i]) for i in range(n))

    # Inicjalizacja tablicy czasy zakończenia
    C = [[0] * len(p[i]) for i in range(n)]
    C_machine = [[(0, 0)] * len(p[i]) for i in range(n)]  # Tablica pomocnicza z elementami (C, numer maszyny)

    # Obliczanie czasów zakończenia dla pierwszego zadania
    C[0][0] = p[0][0]
    C_machine[0][0] = (C[0][0], mu[0][0])
    for j in range(1, len(p[0])):
        C[0][j] = C[0][j-1] + p[0][j]
        C_machine[0][j] = (C[0][j], mu[0][j])

    # Obliczanie czasów zakończenia dla pozostałych zadań
    for i in range(1, n):
        for j in range(len(p[i])):
            if j == 0:
                values = find_index_2d(mu, i, mu[i][j])
                if values is not None:
                    row, col = values[-1]
                    C[i][j] = max(C[row][col], C[i][j-1])+ p[i][j]
                else:    
                    C[i][j] = p[i][j]

                C_machine[i][j] = (C[i][j], mu[i][j])

            else:
                C[i][j] = C[i][j-1] + p[i][j]
                C_machine[i][j] = (C[i][j], mu[i][j])

    # Obliczanie wartości Cmax
    Cmax = max(max(row) for row in C)

    return C, C_machine, Cmax

def NEH_algorithm(p, mu):
    total_values = count_values_2d(p)

    pi = []

    for i in range(total_values):
        min_Cmax = float('inf')
        min_index = 0

        for j in range(i+1):
            pi.insert(j, i+1)
            _, _, temp_Cmax = calculate_Cmax(p, mu)

            if temp_Cmax < min_Cmax:
                min_Cmax = temp_Cmax
                min_index = j

            pi.remove(i+1)

        pi.insert(min_index, i+1)

    return pi

rng = RandomNumberGenerator(2451)

m = 4
j = 5
o = []
p = []
u = []
p_tmp = []
u_tmp = []

for i in range(j):
    pomoc_o = rng.nextInt(1, math.floor(m * 1.2)) + 1
    o.append(pomoc_o)
    for k in range(o[i]):
        pomoc = rng.nextInt(1, 29)
        p_tmp.append(pomoc)

    p.append(p_tmp.copy())
    p_tmp.clear()

for i in range(j):
    for k in range(o[i]):
        pomoc = rng.nextInt(1, m)
        u_tmp.append(pomoc)
    u.append(u_tmp.copy())
    u_tmp.clear()

# print(p)
# print(u)

C, C_machine, Cmax = calculate_Cmax(p, u)

print("size: ", len(p), "x", max(max(u[i]) for i in range(len(p))))
print(p)
print(u)
print("Permutacja NEH")
pi = NEH_algorithm(p, u)
print(pi)
print(C)
print("C_max jest równy:", Cmax)
