import numpy as np
import matplotlib.pyplot as plt

# Define the domain
r = np.linspace(0, 1, 400)
theta = np.linspace(0, np.pi/2, 400)
R, Theta = np.meshgrid(r, theta)
Z = R * np.exp(1j*Theta)

# Define the four transformations
f1 = lambda z: z**2
f2 = lambda z: 1j*np.log(z)
f3 = lambda z: z**2
f4 = lambda z: (z + 1j) / (z - 1j)

# Apply the transformations
Z1 = f1(Z)
Z2 = f2(Z1)
Z3 = f3(Z2)
Z4 = f4(Z3)

# Create the plots
fig, axs = plt.subplots(2, 3, figsize=(12, 8))

axs[0, 0].scatter(Z.real, Z.imag, s=1)
axs[0, 0].set_title('Domain')
axs[0, 1].scatter(Z1.real, Z1.imag, s=1)
axs[0, 1].set_title('After $f_1$')
axs[0, 2].scatter(Z2.real, Z2.imag, s=1)
axs[0, 2].set_title('After $f_2$')
axs[1, 0].scatter(Z3.real, Z3.imag, s=1)
axs[1, 0].set_title('After $f_3$')
axs[1, 1].scatter(Z4.real, Z4.imag, s=1)
axs[1, 1].set_title('After $f_4$')

# Show the plots
for ax in axs.flat:
    ax.label_outer()
plt.show()
