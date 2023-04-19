import sage.all as sg

def f(xab, g, h, p):
    x, a, b = xab
    if x % 3 == 0:
        return (g * x) % p, a + 1, b
    elif x % 3 == 1:
        return (x * x) % p, 2 * a, 2 * b
    else:
        return (h * x) % p, a, b + 1

def pollards_rho_dlp(g, h, p):
    xab = (1, 0, 0)
    xab2 = f(xab, g, h, p)

    print("Step by step process:")
    print(f"Tortoise: {xab}, Hare: {xab2}")

    while xab[0] != xab2[0]:
        xab = f(xab, g, h, p)
        xab2 = f(f(xab2, g, h, p), g, h, p)

        print(f"Tortoise: {xab}, Hare: {xab2}")

    if xab[2] == xab2[2]:
        return None

    return (xab2[1] - xab[1]) * sg.inverse_mod(xab[2] - xab2[2], p - 1) % (p - 1)

p = 23
g = sg.FiniteField(p)(2)
h = sg.FiniteField(p)(3)

x = pollards_rho_dlp(g, h, p)
print(f"\nx = {x}")
