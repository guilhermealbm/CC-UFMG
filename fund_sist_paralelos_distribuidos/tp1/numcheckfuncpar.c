/* Você deve implementar uma versão usando paralelismo de funções (também
 * chamado decomposição por funções (function decomposition)
 * Para simplificar, você pode considerar que seu programa criará as
 * threads que você julgar necessárias para processar todos os números,
 * onde cada thread executará uma função diferente, com parte das ações
 * esperadas do programa final.
 * 
 * O programa deve aceitar o mesmo parâmetro de linha de comando da versão
 * sequencial - e nenhum outro. 
 * A saída deve sequir exatamente o mesmo formato da versão sequencial.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "timediff.h"   // calcula tempo decorrido
#include "numchecks.h"  // conta números com mais condições válidas
#include "conditions.h" // verifica cada condição

// Contadores para cada uma das condições testadas
long match_some_test = 0,
     palindromes = 0,
     repeated_seqs = 0,
     sums_are_ap = 0,
     have_tripled_digits = 0,
     have_four_repetitions = 0;

/* check_num: concentra todos os testes a serem aplicados a cada número.
 */

typedef struct {
    long maxnum;
    int ndigits, func_num;
} funcpar_args;

pthread_mutex_t counters_lock;

unsigned char *cond_array;

void *check_func_par(void *args) {

    funcpar_args *data = (funcpar_args *) args;
    long maxnum = data->maxnum;
    int ndigits = data->ndigits;
    int func_num = data->func_num;

    for (long n=0;n<=maxnum;++n) {
        int pal, rep, sum, dou, fou;
        digit_t num;
        long orign = n;

        break_into_digits(n, num, ndigits);

        switch (func_num)
        {
        case 0:
            pal = is_palindrome( num, ndigits );
            if (pal) {
                pthread_mutex_lock(&counters_lock);

                palindromes += pal;
                if (!cond_array[orign])
                    match_some_test += 1;

                cond_array[orign] += 1;

                update_max(orign, cond_array[orign]);
                pthread_mutex_unlock(&counters_lock);
            }
            break;
        case 1:
            rep = has_repeated_seq( num, ndigits );
            if (rep) {
                pthread_mutex_lock(&counters_lock);

                repeated_seqs += rep;
                if (!cond_array[orign])
                    match_some_test += 1;

                cond_array[orign] += 1;

                update_max(orign, cond_array[orign]);
                pthread_mutex_unlock(&counters_lock);
            }
            break;
        case 2:
            sum = sum_is_ap( num, ndigits );
            if (sum) {
                pthread_mutex_lock(&counters_lock);

                sums_are_ap += sum;
                if (!cond_array[orign])
                    match_some_test += 1;

                cond_array[orign] += 1;

                update_max(orign, cond_array[orign]);
                pthread_mutex_unlock(&counters_lock);
            }
            break;
        case 3:
            dou = has_tripled_digits( num, ndigits );
            if (dou) {
                pthread_mutex_lock(&counters_lock);

                have_tripled_digits += dou;
                if (!cond_array[orign])
                    match_some_test += 1;

                cond_array[orign] += 1;

                update_max(orign, cond_array[orign]);
                pthread_mutex_unlock(&counters_lock);
            }
            break;
        case 4:
            fou = has_four_repetitions( num, ndigits );
            if (fou) {
                pthread_mutex_lock(&counters_lock);

                have_four_repetitions += fou;
                if (!cond_array[orign])
                    match_some_test += 1;

                cond_array[orign] += 1;

                update_max(orign, cond_array[orign]);
                pthread_mutex_unlock(&counters_lock);
            }
            break;
        }

    }

}

int
main( int argc, char* argv[] )
{
    int  ndigits; // núm. de dígitos para representar até o maior número

    long i, tmp, maxnum, rv;
    long n_threads = 5;

    struct timeval t1, t2; // marcação do tempo de execução

    // tratamento da linha de comando
    if (argc!=2) {
        fprintf(stderr,"usage: %s maxnum\n",argv[0]);
        exit(1);
    }
    maxnum = atol(argv[1]);

    // determinação de ndigits em função do maxnum
    tmp = maxnum;
    ndigits=0;
    do {
        ndigits++;
        tmp=tmp/10;
    } while (tmp>0);

    pthread_t threads[n_threads];
    funcpar_args args[n_threads];
    pthread_mutex_init(&counters_lock, NULL);

    cond_array = (unsigned char *) calloc(maxnum + 1, sizeof(unsigned char));
    if (cond_array == NULL) {
        printf("Can't alocate memory\n");
        exit(1);
    }    

    gettimeofday(&t1,NULL);
    for (i = 0; i < n_threads; i++) {
        args[i].maxnum = maxnum;
        args[i].ndigits = ndigits;
        args[i].func_num = i;
        rv = pthread_create(&(threads[i]), NULL, check_func_par, &(args[i]));
        if (rv != 0) {
            printf("ERR: create\n"); exit(-1);
        }
    }

    for (i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&t2,NULL);

    // Escrita das estatísticas ao final da execução
    printf("%ld match_some_test (%d%%)\n", match_some_test, (int)((100.0*match_some_test)/maxnum));
    printf("%ld palindromes\n", palindromes);
    printf("%ld repeated_seqs\n", repeated_seqs);
    printf("%ld sums_are_ap\n", sums_are_ap);
    printf("%ld have_tripled_digits\n", have_tripled_digits);
    printf("%ld have_four_repetitions\n", have_four_repetitions);
    print_max( ndigits );
    printf("\ntempo: %lf\n",timediff(&t2,&t1));
}
