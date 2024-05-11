import os
import sys
import subprocess

import numpy as np

file = sys.argv[1]

x, y, z, d = 0, 0, 0, 7

# Create a histo for x and y
xbins = np.linspace(-3, 3, 10)
ybins = np.linspace(-3, 3, 10)

for x in xbins:
    
    for y in ybins:

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