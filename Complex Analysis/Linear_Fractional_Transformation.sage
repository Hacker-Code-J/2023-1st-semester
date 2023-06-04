import numpy as np
import matplotlib.pyplot as plt

# Define the domain of the transformation
r = np.linspace(0, 1, 100)
theta = np.linspace(0, np.pi/2, 100)
R, Theta = np.meshgrid(r, theta)
Z = R * np.exp(1j * Theta)

# Define the transformation
def transform(z):
    z = z**4
    #z = -1j*(z - 1)/(z + 1)
    #z = (z - 1)**2
    #z = z / (1 - z + 1e-12)
    return z

# Apply the transformation
Z_transformed = transform(Z)

# Create the plot
fig, ax = plt.subplots(1, 2, figsize=(12, 6))

# Plot the original region
ax[0].pcolormesh(R*np.cos(Theta), R*np.sin(Theta), np.angle(Z), shading='auto', cmap='hsv')
ax[0].set_title('Original Region')
ax[0].set_xlabel('Real Part')
ax[0].set_ylabel('Imaginary Part')

# Plot the transformed region
ax[1].pcolormesh(np.real(Z_transformed), np.imag(Z_transformed), np.angle(Z_transformed), shading='auto', cmap='hsv')
ax[1].set_title('Transformed Region')
ax[1].set_xlabel('Real Part')
ax[1].set_ylabel('Imaginary Part')

plt.show()
