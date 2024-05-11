import os
import sys
import subprocess

file = sys.argv[1]

x, y, z = 0, 0, 0
distances = [i for i in range(5, 15)]

for d in distances:

    # Wait for 2 seconds
    subprocess.run(["sleep", "2"])

    with open(file, 'r') as f:
        lines = f.readlines()
        for i, line in enumerate(lines):
            if "xxx" in line:
                lines[i] = lines[i].replace("xxx", str(x))
            if "yyy" in line:
                lines[i] = lines[i].replace("yyy", str(y))
            if "zzz" in line:
                lines[i] = lines[i].replace("zzz", str(z))
            if "ddd" in line:
                lines[i] = lines[i].replace("ddd", str(d))
    
    with open("mac/run.mac", 'w') as f:
        f.writelines(lines)

    subprocess.run(["./G4_LaBr", "mac/run.mac"])