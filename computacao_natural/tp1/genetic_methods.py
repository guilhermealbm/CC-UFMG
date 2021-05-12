import copy
import random
from operator import attrgetter

import numpy as np


def tournament_selection(original_pop, k, ind):
    pop = copy.deepcopy(original_pop)
    np.random.shuffle(pop)

    if ind == 2:
        return max(pop[:k], key=attrgetter("fitness")), max(pop[-k:], key=attrgetter("fitness"))
    else:
        return max(pop[:k], key=attrgetter("fitness"))


def get_node_and_path(node, path, depth):
    prob = 0.3
    if random.random() < prob and (node.get_depth() < depth):
        return node, path
    else:
        if random.random() < 0.5:
            if node.left is not None:
                path.append("L")
                return get_node_and_path(node.left, path, depth)
            elif node.right is not None:
                path.append("R")
                return get_node_and_path(node.right, path, depth)
            else:
                return node, path

        else:
            if node.right is not None:
                path.append("R")
                return get_node_and_path(node.right, path, depth)
            elif node.left is not None:
                path.append("L")
                return get_node_and_path(node.left, path, depth)
            else:
                return node, path


def change_node_at_crossover(cur, new, path):
    if not path:
        cur = new
    elif path[0] == "L":
        cur.left = change_node_at_crossover(cur.left, new, path[1:])
    else:
        cur.right = change_node_at_crossover(cur.right, new, path[1:])

    cur.fitness = None
    return cur


def crossover(n1, n2, depth):
    node1 = n1
    node2 = n2

    new_node1, path_n1 = get_node_and_path(node1, [], depth)
    new_node2, path_n2 = get_node_and_path(node2, [], depth - len(path_n1))

    return change_node_at_crossover(node1, new_node2, path_n1), change_node_at_crossover(node2, new_node1, path_n2)


def change_node_at_mutation(cur, new, path):
    if not path:
        cur.data = new
    elif path[0] == "L":
        cur.left = change_node_at_mutation(cur.left, new, path[1:])
    else:
        cur.right = change_node_at_mutation(cur.right, new, path[1:])

    cur.fitness = None
    return cur


def mutation(n, operators, operands, depth):
    node = n

    m_node, path = get_node_and_path(node, [], depth)

    if m_node.data in operators:
        operators_removed = operators.copy()
        operators_removed.remove(m_node.data)
        data = random.choice(operators_removed)
    else:
        operands_removed = operands.copy()
        operands_removed.remove(m_node.data)
        data = random.choice(operands_removed)

    return change_node_at_mutation(node, data, path)
