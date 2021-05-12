#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "list.h"

#define MIN_PARAM 5
#define N_BITS 32

#define LRU "lru"
#define SECOND "2a"
#define FIFO "fifo"
#define CUSTOM "personalizado"

#define INVALID -1

unsigned get_offset(unsigned page_size) {
    unsigned s, tmp;
    /* Derivar o valor de s: */
    tmp = page_size;
    s = 0;
    while (tmp>1) {
        tmp = tmp>>1;
        s++;
    }
    return s;
}

unsigned get_number_of_pages(unsigned bits_addr) {
    return pow(2, bits_addr);
}

int check_pos_integer(char *arg) {
    int len = strlen(arg);
    for (int i = 0; i < len; i++) {
        if(!isdigit(arg[i])) {
            return 0;
        }
    }
    return 1;
}

int valid_alg(char *alg) {
    if(strcmp(alg, LRU) != 0 && strcmp(alg, SECOND) != 0 && strcmp(alg, FIFO) != 0 && strcmp(alg, CUSTOM)) {
        return 0;
    }
    return 1;
}

void read_and_exec(char *alg, char *log_file, int page_size, int mem_size) {
    FILE *file;
    unsigned addr;
    char rw;

    unsigned page_offset = get_offset(page_size * 1024);
    unsigned number_of_pages = get_number_of_pages(N_BITS - page_offset);
    unsigned number_of_frames = mem_size / page_size;
    
    unsigned frames_occupied = 0;
    unsigned dirty_written = 0;
    unsigned page_faults = 0;
    unsigned memory_access = 0;
    unsigned total_reads = 0;
    unsigned total_writes = 0;
    
    long lru_count = 0;

    page_table_cell* page_table = (page_table_cell*) malloc(number_of_pages * sizeof(page_table_cell));
    for(int i = 0; i < number_of_pages; i++) {
        page_table[i].frame_addr = INVALID;
        page_table[i].dirty_page = 0;
        page_table[i].reference_bit = 0;
        page_table[i].last_accessed = INVALID;
    }

    unsigned *memory = (unsigned *) malloc(number_of_frames * sizeof(unsigned));
    unsigned victim_addr = 0;

    list fifo_queue;
    make_empty_list(&fifo_queue);

    file = fopen(log_file, "r");
    srand(time(NULL));
    
    while(fscanf(file, "%x %c", &addr, &rw) != EOF) {
        if(rw != 'R' && rw != 'W') {
            printf("ERRO: Comando inválido ou sem comando\n");
            break;
        }

        memory_access++;

        unsigned page_addr = addr >> page_offset;

        if (rw == 'W') {
            total_writes++;
            page_table[page_addr].dirty_page = 1;
        } else {
            total_reads++;
        }
        
        page_table[page_addr].last_accessed = lru_count;

        if (page_table[page_addr].frame_addr != INVALID) {
            page_table[page_addr].reference_bit = 1;
        } else {
            page_table[page_addr].reference_bit = 0;
            page_faults++;

            if (frames_occupied < number_of_frames) {
                memory[frames_occupied] = page_addr;
                page_table[page_addr].frame_addr = frames_occupied;
                

                if (strcmp(alg, FIFO) == 0) {
                    add_item_end(&fifo_queue, frames_occupied);
                }
                frames_occupied++;
            } else {
                unsigned page_removed;
                if (strcmp(alg, LRU) == 0) {
                    long lru = page_table[memory[0]].last_accessed;
                    unsigned lru_page = memory[0];
                    unsigned page_index = 0;

                    for (int i = 0; i < number_of_frames; i++) {
                        if (page_table[memory[i]].last_accessed < lru) {
                            lru = page_table[memory[i]].last_accessed;
                            lru_page = memory[i];
                            page_index = i;
                        }
                    }

                    memory[page_index] = page_addr;
                    page_table[page_addr].frame_addr = page_index;

                    page_removed = lru_page;

                } else if (strcmp(alg, FIFO) == 0) {
                    unsigned memory_addr = get_first_item(&fifo_queue)->item;
                    page_removed = memory[memory_addr];
                    remove_item_start(&fifo_queue);
                    
                    memory[memory_addr] = page_addr;
                    page_table[page_addr].frame_addr = memory_addr;

                    add_item_end(&fifo_queue, memory_addr);
                } else if (strcmp(alg, SECOND) == 0) {
                    while(1) {
                        unsigned victim_page_addr = memory[victim_addr];
                        if (page_table[victim_page_addr].reference_bit == 0) {
                            page_removed = victim_page_addr;
                            
                            memory[victim_addr] = page_addr;
                            page_table[page_addr].frame_addr = victim_addr;
                            
                            victim_addr = (victim_addr + 1) % number_of_frames;
                            break;
                        } else {
                            page_table[victim_page_addr].reference_bit = 0;
                            victim_addr = (victim_addr + 1) % number_of_frames;
                        }
                    }
                } else if (strcmp(alg, CUSTOM) == 0) {
                    while(1) {
                        unsigned page_to_remove = rand() % (number_of_frames);

                        if (page_table[memory[page_to_remove]].reference_bit == 0){                    
                            page_removed = memory[page_to_remove];
                            memory[page_to_remove] = page_addr;
                            page_table[page_addr].frame_addr = page_to_remove;
                            break;
                        } else {
                            page_table[memory[page_to_remove]].reference_bit = 0;
                        }
                    }
                    
                }

                page_table[page_removed].frame_addr = INVALID;
                
                if(page_table[page_removed].dirty_page) {
                    page_table[page_removed].dirty_page = 0;
                    dirty_written++;
                }
            }
        }
        lru_count++;
    }

    printf("Acessos à memória: %d\n", memory_access);
    printf("Total de leituras: %d\n", total_reads);
    printf("Total de escritas: %d\n", total_writes);
    printf("Paginas lidas: %d\n", page_faults);
    printf("Paginas escritas: %d\n", dirty_written);

    printf("endereço físico | página alocada | página suja | second chance\n");
    for (int i = 0; i < number_of_frames; i++) {
        page_table_cell page = page_table[memory[i]];
        
        printf("%15d |       %08x | %11d | %13d\n", i, memory[i], page.dirty_page, page.reference_bit);
    }

    free(page_table);
    free_list(&fifo_queue);
    fclose(file);
}

int main(int argc, char **argv) {
    if (argc != MIN_PARAM) {
        printf("Número de argumentos inválido.\n");
        return EXIT_FAILURE;
    }

    if(!check_pos_integer(argv[3]) || !check_pos_integer(argv[4])) {
        printf("Os parâmetros de tamanho de página e tamanho da memória precisam ser inteiros positivos.\n");
        return EXIT_FAILURE;
    }
    
    char *alg = argv[1];
    char *log_file = argv[2];
    int page_size = atoi(argv[3]);
    int mem_size = atoi(argv[4]);

    if(!valid_alg(alg)) {
        printf("Técnica de reposição inválida\n");
        printf("Técnicas válidas: lru, 2a, fifo e personalizado\n");
        return EXIT_FAILURE;
    }

    printf("Executando o simulador...\n");
    printf("Arquivo de entrada: %s\n", log_file);
    printf("Tamanho da memória: %d KB\n", mem_size);
    printf("Tamanho das páginas: %d KB\n", page_size);
    printf("Técnica de reposição: %s\n", alg);
    clock_t begin = clock();
    read_and_exec(alg, log_file, page_size, mem_size);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("tempo de execução: %fs\n", time_spent);

    return EXIT_SUCCESS;
}
