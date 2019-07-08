#include <stdio.h>
#include <gmp.h>

int talvez_primo(const mpz_t a, const mpz_t n, const mpz_t n1, unsigned int t, const mpz_t q){
	mpz_t mod_resultado, r1, multiplo;
	mpz_inits(mod_resultado, r1, multiplo, NULL);
	mpz_mod(multiplo, a, n);
	if(mpz_cmp_ui(a, 2) == 0 || mpz_cmp_ui(multiplo, 0) == 0){
		return 1;
	} else {
			int i = 0;
			mpz_powm(r1, a, q, n);
			while(i < t){
				if ((i == 0) && (mpz_cmp_ui(r1, 1) == 0) || (i >=0) && (mpz_cmp(r1, n1) == 0)){
					return 1;
				}
				i++;
				mpz_powm_ui(r1, r1, 2, n);
			}
			return 0;

		}
}

void numero_aleatorio(mpz_t r, const mpz_t n, gmp_randstate_t rnd) {
	mp_bitcnt_t num_bits = mpz_sizeinbase(n, 2);
	do {
		mpz_urandomb(r, rnd, num_bits);
	} while (!(mpz_cmp_ui(r, 1) >= 0 && mpz_cmp(r, n) <= 0));
}

int fatoracao2(mpz_t q, const mpz_t n){
	mpz_t r, n_aux;
	mpz_inits(r, n_aux, NULL);
	mpz_set_ui(r, 0);
	mpz_set(n_aux,n);
	int exp;

	for(exp=0; 1; exp++){
		mpz_tdiv_qr_ui(q, r, n_aux, 2);
		if((mpz_cmp_ui(r, 0))){
			mpz_set(q, n_aux);
			break;
		}
		mpz_set(n_aux, q);
	}

	return exp;
}

int provavelmente_primo(const mpz_t n, unsigned int iter, gmp_randstate_t rnd){
	mpz_t n1, base, q;
	mpz_inits(n1, base, q, NULL);

	mpz_sub_ui(n1, n, 1);

	int t = fatoracao2(q, n1);

	int i, ePrimo;

	ePrimo= 1; //true por default.

	for(i = 0; i < iter; i++){
		numero_aleatorio(base, n1, rnd);
		ePrimo = talvez_primo(base, n, n1, t, q);
			if(!ePrimo)
				return ePrimo;
	}

	return ePrimo;

}

void primo_aleatorio(mpz_t r, unsigned int b, gmp_randstate_t rnd){
	int ePrimo;
	ePrimo = 0;
	while(!ePrimo){
		mpz_urandomb(r, rnd, b);
		ePrimo = provavelmente_primo(r, 10, rnd);
	}
}