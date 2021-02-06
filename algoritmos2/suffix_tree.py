import os
import psutil
import time
import copy


def get_memory_usage():
    process = psutil.Process(os.getpid())
    return float(process.memory_info().rss) / 1048576  # in Mbytes


class SuffixTree:
    class Node:
        def __init__(self, first_index, last_index):
            self.first_index = first_index
            self.last_index = last_index
            self.out = {}  # mapeia caracteres para outros nós

    def __init__(self, s, initial_time):
        print("Uso de memória após a leitura do arquivo: " + str(get_memory_usage()) + " MB")
        print("------------------------------")

        build_tree_initial_time = time.time()
        self.s = s
        self.s_len = len(self.s)
        self.root = self.Node(None, None)
        self.root.out[s[0]] = self.Node(0, self.s_len)  # árvore para o sufixo mais longo
        self.add_suffixes()

        print("Tempo gasto para construir a árvore de sufixos: " + str(time.time() - build_tree_initial_time) + " s")
        print("Uso de memória após construir a árvore de sufixos: " + str(get_memory_usage()) + " MB")
        print("------------------------------")

        find_biggest_repeated_substring_initial_time = time.time()
        result = self.find_biggest_repeated_substring()

        print("Tempo gasto para construir a árvore de sufixos: " +
              str(time.time() - find_biggest_repeated_substring_initial_time) + " s")
        print("Uso de memória após construir a árvore de sufixos: " + str(get_memory_usage()) + " MB")
        print("------------------------------")
        print("Tempo total gasto pelo algoritmo " + str(time.time() - initial_time) + " s")
        print("------------------------------")
        print("Maior substring que se repete no texto: " + result[0])
        print("Localização da substring (índice no texto): " + str(result[1]))
        print("Número de vezes que a substring se repete no texto: " + str(result[2]))

    def add_suffixes(self):
        for i in range(1, self.s_len):
            cur = self.root
            j = i
            is_prefix = True

            # repete até não encontrar o prefixo ou chegar a um nó folha
            while is_prefix and len(cur.out) > 0:
                is_prefix = False
                for node in cur.out:
                    node = cur.out[node]

                    # encontra o maior prefixo entre a substring e o texto
                    prefix_size = min(self.s_len - j, node.last_index - node.first_index)
                    for k in range(prefix_size):
                        if self.s[j + k] != self.s[node.first_index + k]:
                            prefix_size = k
                            break

                    if prefix_size > 0:

                        # caso pelo menos um caractere da substring já estiver na árvore, cria-se um novo nó para
                        # armazena-lo
                        if node.last_index > node.first_index + prefix_size:
                            prefix_child = self.Node(node.first_index + prefix_size, node.last_index)
                            prefix_child.out = copy.copy(node.out)

                            node.first_index = node.first_index
                            node.last_index = node.first_index + prefix_size
                            node.out = {self.s[node.first_index + prefix_size]: copy.copy(prefix_child)}

                        j += prefix_size
                        cur = node
                        is_prefix = True
                        break

            # se, após a execução do while, ainda existem caracteres não inseridos na árvore
            if j != self.s_len:
                cur.out[self.s[j]] = self.Node(j, self.s_len)

    def find_biggest_repeated_substring(self):
        start, end, node = self.follow_nodes(self.root)
        return self.s[start: end], start, len(node.out)

    def follow_nodes(self, node):

        start, end = node.first_index, node.last_index

        if start is None:  # se for o nó raíz
            start, end = 0, 0

        if len(node.out) == 0:  # se for nó folha
            return start, start, node

        length = end - start
        sub_strings = {}

        # recursivamente, percorre a árvore e procura pela maior substring
        for child in node.out.keys():
            start_index, end_index, node_t = self.follow_nodes(node.out[child])
            sub_strings[end_index - start_index] = end_index, node_t

        biggest_substring = max(sub_strings.keys())
        if biggest_substring > 0:
            sec, node_t = sub_strings[biggest_substring]
            first = sec - biggest_substring - length
        else:
            first = start
            sec = end
            node_t = node

        return first, sec, node_t
