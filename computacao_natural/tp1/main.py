from node import Node
from genetic_methods import tournament_selection, crossover, mutation

from collections import Counter

import random
import copy

import pandas as pd
import numpy as np

from sklearn.metrics.cluster import v_measure_score
from pyclustering.cluster.kmeans import kmeans
from pyclustering.cluster.center_initializer import kmeans_plusplus_initializer
from pyclustering.utils.metric import distance_metric, type_metric

file1 = "data/breast_cancer_coimbra_train.csv"
file2 = "data/glass_train.csv"


def get_repeats(pop):
    expression_list = []
    for ind in pop:
        expression_list.append(ind.get_expression([]))

    return sum(y for y in Counter(tuple(x) for x in expression_list).values() if y > 1)


def pop_initialization(pop_size, max_depth, operators, operands):
    pop = []
    ind_by_depth = int(pop_size / (max_depth - 1))

    for i in range(2, max_depth + 1):
        for j in range(int(ind_by_depth / 2)):
            # Ramped half-and-half
            grow = Node("")
            grow.generate_expression(i, operators, operands, 0)
            pop.append(grow)

            full = Node("")
            full.generate_expression(i, operators, operands, 1)
            pop.append(full)

    return np.array(pop)


def evaluate(point1, point2, operators, original_expression):
    expression = []
    for elem in original_expression[::-1]:
        if elem not in operators:
            value = ""
            if elem[1] == "1":
                value = point1[int(elem[-1]) - 1]
            else:
                value = point2[int(elem[-1]) - 1]
            expression.append(value)
        else:
            v1 = expression.pop()
            v2 = expression.pop()

            if elem == '+':
                expression.append(v1 + v2)
            elif elem == '-':
                expression.append(v1 - v2)
            elif elem == '*':
                expression.append(v1 * v2)
            else:
                if v2 == 0:  # div by zero
                    expression.append(1)
                else:
                    expression.append(float(v1) / v2)
    return expression[0]  # final value


def calc_fitness(individual, df, X, target, operators, clusters_n):
    expression = individual.get_expression([])

    def distance_calc(data1, data2):
        result = evaluate(data1, data2, operators, expression)
        return result

    metric = distance_metric(type_metric.USER_DEFINED, func=distance_calc)

    k_means = kmeans(X, kmeans_plusplus_initializer(X, clusters_n).initialize(), metric=metric)
    k_means.process()

    for i, cluster in enumerate(k_means.get_clusters()):
        df.loc[cluster, 'y'] = i

    return v_measure_score(target, df.y)


def check_test_file(file, operators, ind, label, clusters_n):
    df = pd.read_csv(file)
    X = df.drop([label], axis=1)

    ind.fitness = calc_fitness(ind, df, X, df[label], operators, clusters_n)

    print("\nFitness do melhor indivíduo contra os dados de teste: {}".format(ind.fitness))


def run_gp(file, pop_size, prob_cros, prob_mut, n_gen, tour):
    operators = ["+", "-", "*", "/"]
    operands = ["P1_1", "P1_2", "P1_3", "P1_4", "P1_5", "P1_6", "P1_7", "P1_8", "P1_9",
                "P2_1", "P2_2", "P2_3", "P2_4", "P2_5", "P2_6", "P2_7", "P2_8", "P2_9"]
    max_depth = 7

    if file == file1:
        clusters_n = 2
        label = "Classification"
    else:
        clusters_n = 7
        label = "glass_type"

    df = pd.read_csv(file)
    X = df.drop([label], axis=1)

    print("Iniciando execução. Parâmetros: \n"
          "Dataset: {} \n"
          "Tamanhho da população: {} \n"
          "Probabilidade do crossover: {} \n"
          "Probabilidade de mutação: {} \n"
          "Número de gerações: {} \n"
          "Número de turnos no torneio: {}".format(file, pop_size, prob_cros, prob_mut, n_gen, tour))
    print("-----------------------------------")
    pop = pop_initialization(pop_size, max_depth, operators, operands)

    max_fitness = 0
    max_ind = None
    min_fitness = 1
    fitness_sum = 0
    for ind in pop:
        ind.fitness = calc_fitness(ind, df, X, df[label], operators, clusters_n)
        fitness_sum += ind.fitness
        if ind.fitness > max_fitness:
            max_fitness = ind.fitness
            max_ind = ind

        if ind.fitness < min_fitness:
            min_fitness = ind.fitness

    print("Fitness Inicial: \n"
          "    Melhor: {} \n"
          "    Média: {} \n"
          "    Pior: {} \n"
          "    Repetidos: {}".format(max_fitness, fitness_sum / pop.shape[0], min_fitness, get_repeats(pop)))

    for i in range(n_gen):
        print("-----------------------------------")
        print("Iniciando geração {}".format(i + 1))

        better, worse = 0, 0
        gen = np.array([max_ind])

        while gen.shape[0] < pop.shape[0]:
            prob = random.random()
            if prob < prob_cros:
                p1, p2 = tournament_selection(pop, tour, 2)
                p1_p2_fitness = p1.fitness + p2.fitness
                n1, n2 = crossover(p1, p2, max_depth)

                n1.fitness = calc_fitness(n1, df, X, df[label], operators, clusters_n)
                n2.fitness = calc_fitness(n2, df, X, df[label], operators, clusters_n)

                if (2 * n1.fitness) < p1_p2_fitness:
                    worse += 1
                elif (2 * n1.fitness) > p1_p2_fitness:
                    better += 1

                if (2 * n2.fitness) < p1_p2_fitness:
                    worse += 1
                elif (2 * n2.fitness) > p1_p2_fitness:
                    better += 1

                gen = np.append(gen, [n1, n2])

            elif prob < prob_cros + prob_mut:
                p = tournament_selection(pop, tour, 1)
                n = mutation(p, operators, operands, max_depth)
                gen = np.append(gen, n)

            else:
                p = tournament_selection(pop, tour, 1)
                gen = np.append(gen, copy.deepcopy(p))

        for ind in gen:
            if ind.fitness is None:
                ind.fitness = calc_fitness(ind, df, X, df[label], operators, clusters_n)

        pop = np.copy(gen[:pop_size])

        max_fitness = 0
        max_ind = None
        min_fitness = 1
        fitness_sum = 0
        for ind in pop:
            fitness_sum += ind.fitness
            if ind.fitness > max_fitness:
                max_fitness = ind.fitness
                max_ind = ind

            if ind.fitness < min_fitness:
                min_fitness = ind.fitness

        print("Dados da geração {}: \n"
              "    Melhor: {} \n"
              "    Média: {} \n"
              "    Pior: {} \n"
              "    Repetidos: {} \n"
              "    Melhores que os pais: {} \n"
              "    Piores que os pais: {}".format((i + 1), max_fitness, fitness_sum / pop.shape[0],
                                                  min_fitness, get_repeats(pop), better, worse))

    check_test_file(file.replace("train", "test"), operators, max_ind, label, clusters_n)


if __name__ == '__main__':

    for i in range(0, 5):
        run_gp(file=file1, pop_size=24, prob_cros=0.6, prob_mut=0.3, n_gen=24, tour=5)
