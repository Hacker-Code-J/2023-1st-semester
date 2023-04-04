N = 2^13 - 1 #12-bit
n = floor(sqrt(N))
print("N = {}\nn = floor(sqrt N) = {}\n".format(N,n))

def f(x):
    return (x^2 + 1) % N

# Step 1: Discover k such that x_k = x_{2k}
x0 = ZZ.random_element(N, 2*N) #x0 is the start node
x1, x2 = x0, x0
k = 0
while True :
    k = k + 1
    x1, x2 = f(x1), f(f(x2))
    if x1 == x2 :
        print ("k = {}, 2k = {}".format(k, 2*k))
        break

# Step 2: Find the collision pair
print ("\nx0: {}, x_k: {}\n".format(x0, x2))
x1 , x2 = x0, x2
for i in [0..k]:
    if f(x1) == f(x2):
        print("Collision: ({}-th elt = {}, {}-th elt = {})\n".format(i, x1, k+i, x2))
        print("f({})={}, f({})={}\n".format(x1, f(x1), x2, f(x2)))
        break
    else :
        x1, x2 = f(x1), f(x2)

L = [(0, x0)]
for j in [1..2*k]:
    print("j:{}, L[j-1][1]={}, f(L[j-1][1])={}\n ".format(j, L[j-1][1], f(L[j-1][1])))
    L = L + [(j, f(L[j-1][1]))]

# list_plot(L)
#for pair in L:
#    print(pair)
