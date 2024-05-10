import os
import sys

file = sys.argv[1]

x, y, z = 0, 0, 0
distances = [i for i in range(5, 15)]

for d in distances:

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

    os.system("./G4_LaBr mac/run.mac")