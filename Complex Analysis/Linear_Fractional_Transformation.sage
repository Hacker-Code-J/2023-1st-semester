import numpy as np
import matplotlib.pyplot as plt

# Define the domain of the transformation
r = np.linspace(1e-5, 1, 100)  # start from a small positive number
theta = np.linspace(0, np.pi/2, 100)
R, Theta = np.meshgrid(r, theta)
Z = R * np.exp(1j * Theta)

# Define the transformation
def transform(z):
    z = z**2
    z = 1 / z
    z = z**2
    #z = np.exp(1j * z)
    return z

# Apply the transformation
Z_transformed = transform(Z)

# Check for any NaNs or Infs in the array
if np.any(np.isnan(Z_transformed)) or np.any(np.isinf(Z_transformed)):
    print("Warning: Z_transformed contains NaNs or Infs.")

# Replace any NaNs or Infs with a large finite number
Z_transformed = np.nan_to_num(Z_transformed, nan=1e6, posinf=1e6, neginf=1e6)

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
