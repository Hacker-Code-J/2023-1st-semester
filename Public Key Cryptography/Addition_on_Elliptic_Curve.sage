# Import the necessary modules
from sage.all import *

# Define the field
F = GF(5)

# Define the projective space
P = ProjectiveSpace(F, 2)

# Define the elliptic curve
E = P.subscheme([P.coordinate_ring().gen(1)^2*P.coordinate_ring().gen(2) - P.coordinate_ring().gen(0)^3 - 3*P.coordinate_ring().gen(0)*P.coordinate_ring().gen(2)^2 - 3*P.coordinate_ring().gen(2)^3])

# Define the points
P1 = E((1,1,2))
P2 = E((4,1,3))
P3 = E((3,3,1))
P4 = E((4,4,3))
P5 = E((1,4,2))
P6 = E((2,4,3))

# Perform the additions
R1 = P1 + P2
R2 = P3 + P4
R3 = P5 + P6

print(f"(1:1:2) + (4:1:3) = {R1}")
print(f"(3:3:1) + (4:4:3) = {R2}")
print(f"(1:4:2) + (2:4:3) = {R3}")
