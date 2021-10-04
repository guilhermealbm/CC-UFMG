import copy
import numpy as np


def read_input():
    n, m = [int(x) for x in input().split()]
    c = [int(x) for x in input().split()]

    A = []
    b = []

    for _ in range(n):
        raw_input = [int(x) for x in input().split()]
        A.append(raw_input[:-1])
        b.append(raw_input[-1])

    A = np.array(A, dtype=float)
    b = np.array(b, dtype=float)
    c = np.array(c, dtype=float)

    return n, m, A, b, c


def create_tableau(n, m, A, b, c):
    identity = np.identity(n)

    header = np.zeros(n)
    step = np.vstack([header, identity])

    A = np.concatenate((identity, A), axis=1)
    c = np.concatenate((c, np.zeros(n)))

    std_tableau = np.zeros((n + 1, n + m + 1))

    for i in range(n):
        for j in range(n + m):
            std_tableau[i + 1][j] = A[i][j]

    for i in range(m):
        std_tableau[0][i + n] = (c[i] * (-1))

    tableau = np.concatenate((std_tableau[:, :-1], step, np.atleast_2d(std_tableau[:, -1]).T), axis=1)

    for i in range(n):
        tableau[i + 1][-1] = b[i]

        if b[i] < 0:
            tableau[i + 1][:] *= -1

    return tableau


def create_aux(tableau, n, rows):
    identity = np.identity(n)
    header = np.zeros(n)
    step1 = np.vstack([header, identity])

    aux = np.concatenate((tableau[:, :-1], step1, np.atleast_2d(tableau[:, -1]).T), axis=1)
    aux[0, :] = 0

    aux[0, -n - 1:-1] = 1

    for i in range(1, rows):
        aux[0, :] -= aux[i, :]

    return aux


def convert_to_fpi(tableau, pos):
    for elem in pos:
        row, column = elem
        if tableau[row, column] != 1:
            tableau[row, :] /= tableau[row, column]

        if tableau[0, column] != 0:
            tableau[0, :] -= tableau[0, column] * tableau[row, :]

    return tableau


def choose_column(tableau, n, columns):
    pivot_column = -1
    for i in range(n, columns - 1):
        if tableau[0][i] < 0:
            pivot_column = i
            break

    return pivot_column


def choose_row(tableau, n, pivot_column):
    lowest_ratio = np.inf

    pivot_row = -1
    for i in range(1, n + 1):
        if tableau[i][pivot_column] <= 0:
            continue

        ratio = tableau[i][-1] / tableau[i][pivot_column]
        if ratio < lowest_ratio:
            lowest_ratio = ratio
            pivot_row = i

    return pivot_row


def pivot_matrix(tableau, n, pivot_row, pivot_column):
    if tableau[pivot_row][pivot_column] != 1:
        tableau[pivot_row][:] = tableau[pivot_row][:] * (1 / tableau[pivot_row][pivot_column])

    pivot = tableau[pivot_row][pivot_column]

    for i in range(n + 1):
        if i == pivot_row:
            continue
        tableau[i][:] = tableau[i][:] + (-1 * tableau[i][pivot_column] / pivot) * tableau[pivot_row][:]

    return tableau


def print_solution(tableau, n, m, rows, columns):
    solution = np.zeros(m)
    for i in range(1, rows):
        for j in range(n, columns - 1):
            if tableau[i][j] == 1 and np.sum(tableau[:, j]) == 1:
                if j - n < m:
                    solution[j - n] = tableau[i][-1]
                break

    for i in range(m):
        print(round(solution[i], 7), end=" ")

    print()


def main():
    n, m, A, b, c = read_input()

    tableau = create_tableau(n, m, A, b, c)
    rows, columns = tableau.shape

    pivots_pos = []
    for i in range(rows, columns):
        positive_values = np.where(tableau[1:, i - 1] > 0)[0]
        if positive_values.shape[0] == 1:
            pivots_pos.append([positive_values[0] + 1, i - 1])

    tableau = convert_to_fpi(tableau, pivots_pos)

    vero = [[]]
    if len(pivots_pos) < n:
        vero = copy.deepcopy(tableau)
        tableau = create_aux(tableau, n, rows)

    while True:

        if len(pivots_pos) >= n:

            pivot_column = choose_column(tableau, n, columns)

            if pivot_column == -1:
                print("otima")
                print(round(tableau[0][-1], 7))
                print_solution(tableau, n, m, rows, columns)

                for i in range(n):
                    print(round(tableau[0][i], 7), end=" ")

                print()
                break

            pivot_row = choose_row(tableau, n, pivot_column)

            if pivot_row == -1:
                print("ilimitada")
                print_solution(tableau, n, m, rows, columns)

                certificate = np.zeros(m + n)
                certificate[pivot_column - n] = 1
                for i in range(rows, columns):
                    positive_values = np.where(tableau[1:, i - 1] > 0)[0]
                    if positive_values.shape[0] == 1:
                        pivots_pos.append([positive_values[0] + 1, i - 1])

                    for elem in pivots_pos[:min(n, m)]:
                        row, column = elem
                        certificate[column - n] = (tableau[row][pivot_column] * -1)

                for i in range(m):
                    print(round(certificate[i], 7), end=" ")

                print()
                break

            tableau = pivot_matrix(tableau, n, pivot_row, pivot_column)

        else:
            pivot_column = choose_column(tableau, n, columns)

            if pivot_column == -1:
                if np.isclose(tableau[0][-1], 0):

                    orig = tableau[:rows, :columns]
                    orig[:, -1] = tableau[:, -1]
                    orig[0, :] = vero[0, :]

                    tableau = orig

                    for i in range(rows, columns):
                        positive_values = np.where(tableau[1:, i - 1] > 0)[0]
                        if positive_values.shape[0] == 1:
                            pivots_pos.append([positive_values[0] + 1, i - 1])

                else:
                    print("inviavel")
                    for i in range(n):
                        print(round(tableau[0][i], 7), end=" ")

                    print()
                    break

            pivot_row = choose_row(tableau, n, pivot_column)

            if pivot_row == -1:
                print("ilimitada")
                print_solution(tableau, n, m, rows, columns)

                certificate = np.zeros(m + n)
                certificate[pivot_column - n] = 1
                for i in range(rows, columns):
                    positive_values = np.where(tableau[1:, i - 1] > 0)[0]
                    if positive_values.shape[0] == 1:
                        pivots_pos.append([positive_values[0] + 1, i - 1])

                    for elem in pivots_pos[:min(n, m)]:
                        row, column = elem
                        certificate[column - n] = (tableau[row][pivot_column] * -1)

                for i in range(m):
                    print(round(certificate[i], 7), end=" ")

                print()
                break

            tableau = pivot_matrix(tableau, n, pivot_row, pivot_column)


if __name__ == '__main__':
    main()
