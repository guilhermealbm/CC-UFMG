/* Você deve implementar uma versão usando paralelismo de dados (também
 * chamado decomposição/partição de domínio (domain partition/decomposition)
 * Para simplificar, você pode considerar que seu programa criará oito
 * threads para processar todos os números. Todas as threads devem executar
 * o mesmo código, já que estarão executando as mesmas operações para
 * partes diferentes do conjunto de dados.
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
    long first_n, last_n;
    int ndigits;
} datapar_args;

pthread_mutex_t counters_lock;
pthread_mutex_t update_max_lock;

void *check_num(void *args)
{

    datapar_args *data = (datapar_args *) args;
    long first_n = data->first_n;
    long last_n = data->last_n;
    int ndigits = data->ndigits;

    int all_batch, pal_batch, rep_batch, sum_batch, dou_batch, fou_batch;

    for (long n = first_n; n <= last_n; n++) 
    {
        int all, pal, rep, sum, dou, fou;
        digit_t num;
        long orign = n;

        // Transforma número (n) em vetor de dígitos (num)
        break_into_digits(n, num, ndigits);

        // Aplica os diversos testes a um dado número
        pal = is_palindrome( num, ndigits );
        rep = has_repeated_seq( num, ndigits );
        sum = sum_is_ap( num, ndigits );
        dou = has_tripled_digits( num, ndigits );
        fou = has_four_repetitions( num, ndigits );

        // Para processar número de condições satisfeitas
        all = pal + rep + sum + dou + fou;
        if (all>0) {
            //match_some_test += 1;
            all_batch += 1;
        }

        pthread_mutex_lock(&update_max_lock);
        update_max( orign, all );
        pthread_mutex_unlock(&update_max_lock);

        pal_batch += pal;
        rep_batch += rep;
        sum_batch += sum;
        dou_batch += dou;
        fou_batch += fou;
        
    }

    pthread_mutex_lock(&counters_lock);

    match_some_test += all_batch;

    // Atualiza os contadores por condição
    palindromes += pal_batch;
    repeated_seqs += rep_batch;
    sums_are_ap += sum_batch;
    have_tripled_digits += dou_batch;
    have_four_repetitions += fou_batch;
    pthread_mutex_unlock(&counters_lock);

}

int
main( int argc, char* argv[] )
{
    int  ndigits; // núm. de dígitos para representar até o maior número

    long i, tmp, maxnum, rv;
    long n_threads = 8;

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
    datapar_args args[n_threads];
    pthread_mutex_init(&counters_lock, NULL);
    pthread_mutex_init(&update_max_lock, NULL);

    long interval = maxnum/n_threads;

    gettimeofday(&t1,NULL);
    for (i = 0; i < n_threads; i++) {
        args[i].first_n = i * interval;
        if (i == n_threads -1)
        {
            args[i].last_n = maxnum;
        }
        else
        {
            args[i].last_n = (i * interval) + (interval - 1);
        }
        
        args[i].ndigits = ndigits;
        rv = pthread_create( &threads[i], NULL, check_num, &(args[i]));

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
