import sys
import time

from suffix_tree import SuffixTree


def main():
    initial_time = time.time()
    file = open(sys.argv[1], 'r')
    s = file.read()
    index = s.find("\n")
    genome = s[index:].replace("\n", "") + "$"
    file.close()
    print("Tempo gasto para ler o arquivo da memória secundária: " + str(time.time() - initial_time) + " s")
    SuffixTree(genome, initial_time)


if __name__ == '__main__':
    main()
