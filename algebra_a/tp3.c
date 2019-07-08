#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>

void codifica(mpz_t r, const char *str){
	int tamanho, indice, ascii_number;

	mpz_t GMP_ascii_number, GMP_indice_char, aux;
	mpz_inits(GMP_ascii_number, GMP_indice_char, aux, NULL);
	mpz_set_ui(GMP_indice_char, 1);
	mpz_set_ui(r, 0);

	tamanho = strlen(str);

	for(indice = 0; indice < tamanho+1; indice++){
		
		ascii_number = *(str + indice);

		mpz_set_ui(GMP_ascii_number, ascii_number);
		mpz_mul(aux, GMP_ascii_number, GMP_indice_char);

		mpz_set(GMP_ascii_number, r);
		mpz_add(r, GMP_ascii_number, aux);

		mpz_set(aux, GMP_indice_char);
		mpz_mul_ui(GMP_indice_char, aux, 256);
	}

}

char *decodifica(const mpz_t n){
	mpz_t str, c;
	char *string;
	int i;

	string = (char *) calloc(501, sizeof(char));

	mpz_inits(str, c, NULL);
	mpz_set(str, n);
	for(i = 0; mpz_cmp_ui(str, 0) != 0; i++){

		mpz_mod_ui(c, str, 256);
		string[i] = (char)mpz_get_ui(c);
		mpz_fdiv_q_ui(str, str, 256);

	}

	string[i] = '\0';
	mpz_clears(str, c, NULL);
	
	return string;
}

void criptografa(mpz_t C, const mpz_t M, const mpz_t n, const mpz_t e){
	mpz_powm(C, M, e, n);
}

void descriptografa(mpz_t M, const mpz_t C, const mpz_t n, const mpz_t d){
	mpz_powm(M, C, d, n);
}