import numpy as np

def checkPU( prob ):
    rand = np.random.rand( ) 
    if( rand > prob ):
        return False
    else:
        return True