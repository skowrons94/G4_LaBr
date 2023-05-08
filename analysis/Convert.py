import ROOT

from Reso import *
from Dgtz import checkTRG
from PileUp import checkPU

inFileName = "data/sim.root"
outFileName = "data/137cs.root"

MevToKev = 1e3

# Trigger settings
a = 10
energyCut = 110

# Pile-Up settings 
probPU   = 0.014
energyPU = 0 

energyLaBr1PU = 0
energyLaBr2PU = 0

inFile = ROOT.TFile( inFileName )

tree1 = inFile.Get( "EdepLaBr1" )
tree2 = inFile.Get( "EdepLaBr2" )

h1 = ROOT.TH1D( "LaBr1","LaBr1", 10000, 0, 10000 )
h2 = ROOT.TH1D( "LaBr2","LaBr2", 10000, 0, 10000 )

rand = ROOT.TRandom3( )

for entryNum in range( 0, tree1.GetEntries( ) ):

    tree1.GetEntry( entryNum )
    tree2.GetEntry( entryNum )

    energyLaBr1 = getattr( tree1, "LaBr1" )*MevToKev 
    energyLaBr2 = getattr( tree2, "LaBr2" )*MevToKev 

    if( energyLaBr1 > 0 ):
        energyLaBr1 = rand.Gaus( energyLaBr1, getReso( energyLaBr1, "1" ) )
    if( energyLaBr2 > 0 ):
        energyLaBr2 = rand.Gaus( energyLaBr2, getReso( energyLaBr2, "2" ) )

    if( checkTRG( energyLaBr1, energyCut, a ) ):
        energyLaBr1 = 0

    if( checkTRG( energyLaBr2, energyCut, a ) ):
        energyLaBr2 = 0

    if( energyLaBr1 == 0 ):
        h1.Fill( energyLaBr1 )
    elif( not checkPU( probPU ) ):
        h1.Fill( energyLaBr1 + energyLaBr1PU )
        energyLaBr1PU = 0
    else:
        energyLaBr1PU = energyLaBr1

    if( energyLaBr2 == 0 ):
        h2.Fill( energyLaBr2 )
    elif( not checkPU( probPU ) ):  
        h2.Fill( energyLaBr2 + energyLaBr2PU )
        energyLaBr2PU = 0
    else:
        energyLaBr2PU = energyLaBr2

outFile = ROOT.TFile.Open( outFileName, "RECREATE" )

outFile.cd( )

h1.Write( )
h2.Write( )

outFile.Close( )

inFile.Close( )