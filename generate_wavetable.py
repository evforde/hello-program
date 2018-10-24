import json
import math


def generate_wavetable(num_samples):
    increment = math.pi * 2 / num_samples
    samples = []
    for i in range(num_samples):
        samples.append(math.sin(i * increment))
    with open("wavetable.json", "w") as f:
        f.write(json.dumps(samples))

generate_wavetable(100)
