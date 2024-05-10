///////////////////////////////////////////////////////////////////
//
// Apr/2015  E. Nacher -> DetectorConstruction.cc
//
///////////////////////////////////////////////////////////////////

#include "geometry/TargetChamber.hh"
#include "Analysis.hh"

#include "CADMesh.hh"

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

G4VPhysicalVolume* TargetChamber::Construct()
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

	//
	// define materials
	//

	G4NistManager* man = G4NistManager::Instance();

	// Polyethylene
	G4Material* pl = man->FindOrBuildMaterial("G4_POLYETHYLENE");

	// Copper
	G4Material* cp = man->FindOrBuildMaterial("G4_Cu");

	//------------------------------------------------------
	// Target Holder geometry
	//------------------------------------------------------
	
	
	//
	// Positions
	//

	auto mesh = CADMesh::TessellatedMesh::FromSTL("/Users/kuba/Desktop/G4_LaBr/build/mesh/chamber.stl");
	G4LogicalVolume* logicHolder = new G4LogicalVolume(mesh->GetSolid(), cp, "TargetChamber", 0, 0, 0);
	G4ThreeVector positionHolder = G4ThreeVector(0,0,0);
	PlaceVolume(logicHolder, GetMotherVolume(), positionHolder, G4RotationMatrix());

	/*
	fParser.Read("mesh/chamber.gdml");

	G4LogicalVolume* logicVol;
	G4ThreeVector positionHolder = G4ThreeVector(0,0,0);

	logicVol = fParser.GetVolume("V-boccola guida bersaglio-15");
	PlaceVolume(logicVol, GetMotherVolume(), positionHolder, G4RotationMatrix());
	logicVol = fParser.GetVolume("V-asta guida portabersaglio-16");
	PlaceVolume(logicVol, GetMotherVolume(), positionHolder, G4RotationMatrix());
	logicVol = fParser.GetVolume("V-KF20-55-2");
	PlaceVolume(logicVol, GetMotherVolume(), positionHolder, G4RotationMatrix());
	logicVol = fParser.GetVolume("V-SOLID-3");
	PlaceVolume(logicVol, GetMotherVolume(), positionHolder, G4RotationMatrix());
	logicVol = fParser.GetVolume("V-KF20xORi-4");
	PlaceVolume(logicVol, GetMotherVolume(), positionHolder, G4RotationMatrix());
	logicVol = fParser.GetVolume("V-flangia collimatore-5");
	PlaceVolume(logicVol, GetMotherVolume(), positionHolder, G4RotationMatrix());
	logicVol = fParser.GetVolume("V-KF20-25_Collare-6");
	PlaceVolume(logicVol, GetMotherVolume(), positionHolder, G4RotationMatrix());
	logicVol = fParser.GetVolume("V-portabersaglio_4-8");
	PlaceVolume(logicVol, GetMotherVolume(), positionHolder, G4RotationMatrix());
	logicVol = fParser.GetVolume("V-tappo portabersaglio_1-9");
	PlaceVolume(logicVol, GetMotherVolume(), positionHolder, G4RotationMatrix());
	*/

	return nullptr;
}

void TargetChamber::ConstructSDandField(){

}

void TargetChamber::SetupOutput(){
	
}

void TargetChamber::FillOutput(const G4Event *event){
	
}