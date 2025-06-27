import pandas as pd
import matplotlib.pyplot as plt
import os

# Ensure plots/ directory exists
os.makedirs("plots", exist_ok=True)

# Load simulation params from environment
start = os.environ.get("START")
end = os.environ.get("END")
experiments = os.environ.get("EXPERIMENTS")
step = os.environ.get("STEP")

# Load CSV
df = pd.read_csv("output.csv")

# Plotting
plt.figure(figsize=(8, 5))
plt.plot(df["num_particles"], df["average_iterations"], marker='o')
plt.xlabel("Number of Particles")
plt.ylabel("Average Iterations")

# Title and filename with params
title = f"Particles: {start} to {end}, Step: {step}, Experiments: {experiments}"
plt.title(f"Particle Collision Simulation\n{title}")
plt.grid(True)
plt.tight_layout()

filename = f"particle_sim_{start}_{end}_{step}_{experiments}.png"
plot_path = os.path.join("plots", filename)
plt.savefig(plot_path)
print(f"Plot saved to {plot_path}")

plt.show()
