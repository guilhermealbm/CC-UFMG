#include <stdio.h>
#include <gmp.h>

void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b){
	mpz_t q, r;
	mpz_inits(q, r, g, x, y, NULL);
	mpz_fdiv_qr(q, r, a, b);
	if (mpz_cmp_ui(r, 0) == 0){
		mpz_set_ui(x, 0);
		mpz_set_ui(y, 1);
		mpz_set(g, b);
		mpz_clears(q, r, NULL);
	}else{
		mdc_estendido(g, x, y, b, r);
		mpz_t xr1;
		mpz_init(xr1);
		mpz_set(xr1, x);
		mpz_set(x,y);
		mpz_mul(y, q, y);
		mpz_sub(y, xr1, y);
		mpz_clears(xr1, q, r, NULL);
	}
}

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n){
	mpz_t g, x, y;
	mpz_inits(g, x, y, NULL);
	mdc_estendido(g, x, y, a, n);

	if (mpz_cmp_ui(g, 1) == 0){
		mpz_set(r, x);

		if(mpz_cmp_ui(r, 0) < 0)
			mpz_add(r, r, n);

		mpz_clears(g, x, y, NULL);
		return 1;
	}

	mpz_clears(g, x, y, NULL);
	return 0;
}

void exp_binaria(mpz_t r, const mpz_t b, const mpz_t e, const mpz_t n){
	mpz_set_ui(r, 1);
	mpz_t mod_result, b_mut, e_mut;
	mpz_inits(mod_result, b_mut, e_mut, NULL);
	mpz_set(b_mut, b);
	mpz_set(e_mut, e);
	while(mpz_cmp_ui(e_mut, 0) > 0){
		mpz_mod_ui(mod_result, e_mut, 2);
		if(mpz_cmp_ui(mod_result, 1) == 0){
			mpz_mul(r, r, b_mut);
			mpz_mod(r, r, n);
		}
		mpz_fdiv_q_ui(e_mut, e_mut, 2);
		mpz_mul(b_mut, b_mut, b_mut);
		mpz_mod(b_mut, b_mut, n);
	}
}