#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

void pollard_p_1(uint64_t N, uint64_t k, uint64_t *p, uint64_t *q) {
    uint64_t a = 2;
    uint64_t j = 2;

    while (j < k) {
        a = mod_exp(a, j, N);
        uint64_t d = gcd(a - 1, N);

        if (d > 1 && d < N) {
            *p = d;
            *q = N / d;
            break;
        }

        a = (a + 1) % N;
        j++;
    }
}

int main() {
    uint64_t N = 96940019531; // This is just an example value for N
    uint64_t k = 1000;
    uint64_t p, q;

    pollard_p_1(N, k, &p, &q);

    printf("N = %" PRIu64 " = %" PRIu64 " * %" PRIu64 "\n", N, p, q);

    return 0;
}
