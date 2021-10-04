import numpy as np


def read_input():
    n, m = [int(x) for x in input().split()]
    c = [int(x) for x in input().split()]

    A = []

    for _ in range(n):
        raw_input = [int(x) for x in input().split()]
        A.append(raw_input)

    A = np.array(A, dtype=float)
    c = np.array(c, dtype=float)

    return n, m, A, c


def tpB():
    n, m, A, c = read_input()
    x = np.zeros(n)
    C = []
    y = np.zeros(m)
    covered_elem = []
    while len(covered_elem) != n:
        i = 0
        for i in range(0, n):
            if i not in covered_elem:
                break

        sets = []
        for j in range(m):
            if A[i][j]:
                sets.append(j)

        matrix = c - A.transpose().dot(x)

        index = np.nonzero(matrix == matrix[sets].min())[0][0]
        x[i] = matrix[index]

        matrix[sets] -= matrix[index]
        equals = np.nonzero(matrix == 0)[0]

        choose_element = None
        for elem in sets:
            if elem in equals:
                choose_element = elem
                break

        C.append(choose_element)

        for k, elem in enumerate(A[:, choose_element]):
            if elem == 1 and k not in covered_elem:
                covered_elem.append(k)

    y[C] = 1
    for out in y:
        print(int(out), end=" ")

    print("")

    for out in x:
        print(int(out), end=" ")

    print("")


if __name__ == '__main__':
    tpB()
