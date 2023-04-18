import itertools
from sage.all import *

def lcm(iterable):
    return reduce(lambda x, y: x*y // gcd(x, y), iterable, 1)

def pollard_p_minus_1(n, a=59384740):
    print(f"Factoring {n} using Pollard's p-1 method:")
    for B in itertools.count(start=2):
        print(f"Trying bound B = {B}")
        lcm_of_1_to_B = lcm(range(1, B+1))
        a_to_lcm_mod_n = pow(a, lcm_of_1_to_B, n)
        gcd_result = gcd(a_to_lcm_mod_n - 1, n)
        print(f"GCD({a_to_lcm_mod_n} - 1, {n}) = {gcd_result}")
        if 1 < gcd_result < n:
            return gcd_result
        print("Increasing bound")

n = 87010111
factor = pollard_p_minus_1(n)
print(f"Found nontrivial factor: {factor}")
print(f"Other factor: {n // factor}")
