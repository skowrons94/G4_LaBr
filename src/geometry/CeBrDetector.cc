///////////////////////////////////////////////////////////////////
//
// Apr/2015  E. Nacher -> DetectorConstruction.cc
//
///////////////////////////////////////////////////////////////////

#include "geometry/CeBrDetector.hh"
#include "Analysis.hh"

#include "G4NistManager.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"

#include "G4LogicalBorderSurface.hh"
#include "G4OpticalSurface.hh"

#include "G4SDManager.hh"
#include "G4Event.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4SDParticleFilter.hh"

using namespace CLHEP;

#include <memory>
using std::make_shared;

G4VPhysicalVolume* CeBrDetector::Construct()
{
	
	//----------------------------------------------------
	// Material definitions
	//----------------------------------------------------
	
	G4String name, symbol;             //a=mass of a mole;
	G4double a, z, density;            //z=mean number of protons;  
	
	G4int ncomponents, natoms;         
	
	G4double pressure    = 3.e-18*pascal;
	G4double temperature = 2.73*kelvin;
	density     = 1.e-25*g/cm3;
	
	G4Material* Vacuum = new G4Material(name="Galactic", z=1., a=1.01*g/mole, 
										density,kStateGas,temperature,pressure);

	//
	// define elements
	//
	
	// O
	a = 15.999*g/mole;
	G4Element* O  = new G4Element(name="Oxygen" ,symbol="O" , z= 8., a);
		
	// Mg
	a = 24.305*g/mole;
	G4Element* Mg  = new G4Element(name="Magnesium"  ,symbol="Mg" , z= 12., a);
	
	// Si
	a = 28.0855*g/mole;
	G4Element* Si  = new G4Element(name="Silicon"  ,symbol="Si" , z= 14., a);
	
	// Cl
	a = 35.453*g/mole;
	G4Element* Cl  = new G4Element(name="Chlorine"  ,symbol="Cl" , z= 17., a);
	
	// K
	a = 39.0983*g/mole;
	G4Element* K  = new G4Element(name="Potassium"  ,symbol="K" , z= 19., a);
	
	// Br
	a = 79.904*g/mole;
	G4Element* Br  = new G4Element(name="Bromine"  ,symbol="Br" , z= 35., a);
	
	// Sb
	a = 121.76*g/mole;
	G4Element* Sb = new G4Element(name="Antimony",symbol="Sb" , z= 51., a);
	
	// Cs
	a = 132.905*g/mole;
	G4Element* Cs = new G4Element(name="Cesium",symbol="Cs" , z= 55., a);
	
	// La
	a = 138.905*g/mole;
	G4Element* La = new G4Element(name="Lanthanum",symbol="La" , z= 57., a);

	// Ce
	a = 140.116*g/mole;
	G4Element* Ce = new G4Element(name="Cerium",symbol="Ce" , z= 58., a);

	// Al
	a = 26.982*g/mole;
	G4Element* Al = new G4Element(name="Aluminum",symbol="Al" , z= 13., a);

	//
	// define materials
	//

	G4NistManager* man = G4NistManager::Instance();

	// Aluminum
	G4Material* AlMat = man->FindOrBuildMaterial("G4_Al");

	// Teflon
	G4Material* Teflon = man->FindOrBuildMaterial("G4_TEFLON");	
	
	// LaBr3
	density = 5.08*g/cm3;
	G4Material* LaBr3 = new G4Material(name="LaBr3", density, ncomponents=2);
	LaBr3->AddElement(Br, natoms=3);
	LaBr3->AddElement(La, natoms=1);
	
	// Quartz
	density = 2.20*g/cm3;
	G4Material* Quartz = new G4Material(name="Quartz", density, ncomponents=2);
	Quartz->AddElement(Si, natoms=1);
	Quartz->AddElement(O, natoms=2);

	// CeBr3
	density = 5.1*g/cm3;
  	G4Material* CeBr3 = new G4Material(name="CeBr3", density, ncomponents=2);
  	CeBr3->AddElement(Ce, natoms=1);
  	CeBr3->AddElement(Br, natoms=3);

	density = 3.987*g/cm3;
  	G4Material* Al2O3 = new G4Material(name="Al2O3", density, ncomponents=2);
  	Al2O3->AddElement(Al, natoms=2);
  	Al2O3->AddElement(O, natoms=3);

	//------------------------------------------------------
	// Detector geometry
	//------------------------------------------------------
	
	
	// G4VisAttributes *colorMotherCylinder = new G4VisAttributes(G4Colour(1.,1.,0.0));
  	G4VisAttributes *colorAlCylinder = new G4VisAttributes(G4Colour(0.5,0.5,0.0));
  	G4VisAttributes *colorReflectorCylinder = new G4VisAttributes(G4Colour(1.,0.,0.0));
  	G4VisAttributes *colorCeBrCylinder = new G4VisAttributes(G4Colour(0.0,1.,0.0));

  	//Solid Volume
  	//Mother Cylinder
  	// G4Tubs* MotherCylinderSol = new G4Tubs("MotherCylinderSolid", 0, 120*mm/2, 120*mm/2, 0.0, 360.0*deg);

  	//Al Cylinder
  	G4Tubs* AlCylinderSol = new G4Tubs("AlCylinderSolid", 56.2*mm/2, 57*mm/2, 60*mm/2, 0.0, 360.0*deg);

  	//Reflector Cylinder
  	G4Tubs* ReflectorCylinderSol = new G4Tubs("ReflectorCylinderSolid", 51.2*mm/2, 56.2*mm/2, 60*mm/2, 0.0, 360.0*deg);

  	//CeBr Cylinder
  	G4Tubs* CeBrCylinderSol = new G4Tubs("CeBrCrystal", 0, 51*mm/2, 51*mm/2, 0.0, 360.0*deg);


  	//Al Cylinder
  	G4LogicalVolume *AlCylinderLog = new G4LogicalVolume(AlCylinderSol, AlMat, "AlCylinderLogical");

  	//Reflector Cylinder
  	G4LogicalVolume *ReflectorCylinderLog = new G4LogicalVolume(ReflectorCylinderSol, Al2O3, "ReflectorCylinderLogical");

  	//CeBr Cylinder 
  	G4LogicalVolume *CeBrCylinderLog = new G4LogicalVolume(CeBrCylinderSol, CeBr3, "CeBrCrystal");
 
  	AlCylinderLog->SetVisAttributes(colorAlCylinder);
  	ReflectorCylinderLog->SetVisAttributes(colorReflectorCylinder);
  	CeBrCylinderLog->SetVisAttributes(colorCeBrCylinder);
    
	// Place the logic volumes
	PlaceVolume(AlCylinderLog, GetMotherVolume(),G4ThreeVector( ), G4RotationMatrix());
	PlaceVolume(ReflectorCylinderLog, GetMotherVolume(),G4ThreeVector( ), G4RotationMatrix());
	PlaceVolume(CeBrCylinderLog, GetMotherVolume(),G4ThreeVector( ), G4RotationMatrix());

	return nullptr;
}

void CeBrDetector::ConstructSDandField()
{
    // Energy deposition in the BGO crystals is tracked with a primitive scorer

    // attempts to delete this pointer in the destructor result in error,
    // apparently detectors are cleaned up by Geant4
    auto *det = new G4MultiFunctionalDetector("CeBrCrystal");
    G4SDManager::GetSDMpointer()->AddNewDetector(det);

    auto *psEdep = new G4PSEnergyDeposit("Edep",1);
    det->RegisterPrimitive(psEdep);

    SetSensitiveDetector( "CeBrCrystal", det);
}

void CeBrDetector::SetupOutput()
{
    auto *am = G4AnalysisManager::Instance();

    fTupleID = am->CreateNtuple("EdepCeBr", "Energy Deposition in CeBr detector");

    G4cout << "CeBrDetector::SetupOutput - " << fTupleID << G4endl;

    am->CreateNtupleDColumn("CeBr");
 
    am->FinishNtuple();
}

void CeBrDetector::FillOutput(const G4Event *event)
{
    // Get hit collection ID
    if (fHCID == -1 )
    {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID("CeBrCrystal/Edep");
    }

    // Get sum values from hits collections
    //
    G4double Edep = 0;

    auto hitsCollection
        = static_cast<G4THitsMap<G4double>*>(
              event->GetHCofThisEvent()->GetHC(fHCID));

    for (auto it : *hitsCollection->GetMap())
    {
        Edep = *(it.second);
    }

    // Fill ntuple
    auto *am = G4AnalysisManager::Instance();

    am->FillNtupleDColumn(fTupleID, 0, Edep / CLHEP::MeV);
    am->AddNtupleRow(fTupleID);
}