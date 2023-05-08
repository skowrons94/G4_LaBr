import numpy as np

a = { "1" : 18.8,
      "2" : 13
      }

b = { "1" : 0.86,
      "2" : 1.12
      }

FWHMToSigma = 1/2.633

def getReso( energy, key ):
    return np.sqrt( a[key] + b[key]*energy )*FWHMToSigma
