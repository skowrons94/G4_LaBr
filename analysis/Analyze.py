import ROOT

import numpy as np

dataDir = "data/"
resultDir = "results/"

nameSim = "137cs"
nameRun = "run222"

activity = 5.79029860485284*pow( 10, 3 ) # Bq
deltaT   = 1 # s

histoNames = ["LaBr1","LaBr2"]

def Analyze( name, sim ):

    intMin = 500
    intMax = 800

    backRange = 50

    fOut = open( resultDir + name + ".dat", 'w' )
    f1 = ROOT.TFile(  dataDir + name + ".root" )
    
    if( sim ):
        nEvents = 1000000
    else:
        nEvents  = activity*deltaT

    for name in histoNames:

        h1 = f1.Get( name )

        backMin = h1.Integral( intMin - backRange, intMin )/backRange
        backMax = h1.Integral( intMax, intMax + backRange )/backRange

        intRange = intMax - intMin
        
        counts = h1.Integral( intMin, intMax )

        realCounts = counts - intRange*( backMin + backMax )/2

        eff = realCounts/( nEvents )
        effErr = np.sqrt( realCounts )/( nEvents )

        effTot = h1.Integral( 1, 100000 )/( nEvents )
        effTotErr = np.sqrt( h1.Integral( 1, 100000 ) )/( nEvents )
    
        fOut.write( name + "\t" + str( eff ) + "\t" + str( effErr ) +
                    "\t" + str( effTot ) + "\t" + str( effTotErr ) + "\n" )

    fOut.close( )
    f1.Close( )

Analyze( nameSim, True )
Analyze( nameRun, False )