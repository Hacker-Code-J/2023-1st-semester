#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void pollard_p_1(mpz_t N, mpz_t k, mpz_t p, mpz_t q) {
    mpz_t a, j, d, one;

    mpz_inits(a, j, d, one, NULL);
    mpz_set_ui(a, 2);
    mpz_set_ui(j, 2);
    mpz_set_ui(one, 1);

    while (mpz_cmp(j, k) < 0) {
        mpz_powm(a, a, j, N);
        mpz_sub_ui(d, a, 1);
        mpz_gcd(d, d, N);

        if (mpz_cmp(d, one) > 0 && mpz_cmp(d, N) < 0) {
            mpz_divexact(q, N, d);
            mpz_set(p, d);
            break;
        }

        mpz_add_ui(j, j, 1);
    }

    mpz_clears(a, j, d, one, NULL);
}

int main() {
    mpz_t N, k, p, q;

    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_inits(N, k, p, q, NULL);

    mpz_urandomb(N, state, 20); // Generate a 20-bit random number
    mpz_nextprime(N, N); // Find the next prime
    mpz_urandomb(k, state, 20); // Generate another 20-bit random number
    mpz_nextprime(k, k); // Find the next prime
    mpz_mul(N, N, k); // Multiply the two primes to get N

    mpz_set_ui(k, 1000);

    pollard_p_1(N, k, p, q);

    if (mpz_cmp_ui(p, 0) != 0) {
        gmp_printf("N = %Zd\n", N);
        gmp_printf("p = %Zd, q = %Zd\n", p, q);
    } else {
        printf("Failure\n");
    }

    mpz_clears(N, k, p, q, NULL);
    gmp_randclear(state);

    return 0;
}
