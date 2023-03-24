#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>

void pollard_p_1(mpz_t N, unsigned long k, mpz_t p, mpz_t q) {
    mpz_t a, d, j, one;
    mpz_inits(a, d, j, one, NULL);

    mpz_set_ui(a, 2);
    mpz_set_ui(j, 2);
    mpz_set_ui(one, 1);

    while (mpz_cmp_ui(j, k) < 0) {
        mpz_powm(a, a, j, N);
        mpz_sub_ui(a, a, 1);
        mpz_gcd(d, a, N);

        if (mpz_cmp(d, one) > 0 && mpz_cmp(d, N) < 0) {
            mpz_set(p, d);
            mpz_divexact(q, N, d);
            break;
        }

        mpz_add_ui(a, a, 1);
        mpz_add_ui(j, j, 1);
    }

    mpz_clears(a, d, j, one, NULL);
}

int main() {
    mpz_t N, p, q;
    unsigned long k = 1000;

    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_inits(N, p, q, NULL);
    mpz_rrandomb(N, state, 40); // Generate a 40-bit random number
    mpz_nextprime(N, N);        // Get the next prime larger than N

    pollard_p_1(N, k, p, q);

    gmp_printf("N = %Zd = %Zd * %Zd\n", N, p, q);

    mpz_clears(N, p, q, NULL);
    gmp_randclear(state);

    return 0;
}
