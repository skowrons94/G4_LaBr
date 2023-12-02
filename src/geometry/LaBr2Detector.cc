///////////////////////////////////////////////////////////////////
//
// Apr/2015  E. Nacher -> DetectorConstruction.cc
//
///////////////////////////////////////////////////////////////////

#include "geometry/LaBr2Detector.hh"
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

G4VPhysicalVolume* LaBr2Detector::Construct()
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

	// Aluminum
	G4Material* Al = man->FindOrBuildMaterial("G4_Al");

	// Teflon
	G4Material* Teflon = man->FindOrBuildMaterial("G4_TEFLON");	
	
	// LaBr3
	density = 5.26*g/cm3;
	G4Material* LaBr3 = new G4Material(name="LaBr3", density, ncomponents=2);
	LaBr3->AddElement(Br, natoms=3);
	LaBr3->AddElement(La, natoms=1);
	
	// Quartz
	density = 2.2*g/cm3;
	G4Material* Quartz = new G4Material(name="Quartz", density, ncomponents=2);
	Quartz->AddElement(Si, natoms=1);
	Quartz->AddElement(O, natoms=2);

	//------------------------------------------------------
	// Detector geometry
	//------------------------------------------------------
	
	
	//
	// Positions
	//

	G4double ScintLength = 15.24*cm;


	G4double ReflectorStart = 3.3368* mm;
	G4double ScintStart = 6.3368 * mm;
	G4double PMTStart = ScintStart + ScintLength;
	G4double CrystalFin = ScintStart + ScintLength;

	G4double StartPhi = 0.*deg;
	G4double DeltaPhi = 360.*deg;	
	
	//Crystal

	G4double ScintRadius = 4.2616*cm;

	const  G4int  crystalNZPlanes = 2;
	const  G4double crystalZPlanes[] =
	{
		0,
		ScintLength
	};

	const G4double crystalRInner[] =
	{
		0,
		0
	};

	const G4double crystalROuter[] =
	{
		ScintRadius,
		ScintRadius
	};
	
	G4Polycone* solidCrystal = new G4Polycone("LaBr2Crystal",StartPhi,DeltaPhi,crystalNZPlanes,
										      crystalZPlanes,crystalRInner,crystalROuter);
	
	G4LogicalVolume* logicCrystal = new G4LogicalVolume(solidCrystal,LaBr3,
														"LaBr2Crystal");
	
	G4ThreeVector positionCrystal = G4ThreeVector(0.*cm,0.*cm,ScintStart);
	
	//G4VPhysicalVolume* physiCrystal = new G4PVPlacement(0,positionCrystal,
	//													logicCrystal, "LaBr2Crystal",
	//													GetMotherVolume(),false,0);
	
	
	// PMT

	G4double PMTLength = 15.8 * cm;
	G4double PMTRadiusLarge = 6.6 * cm;
	G4double PMTRadiusLow = 2.6 * cm;

	const  G4int  pmtNZPlanes = 6;
	const  G4double pmtZPlanes[] =
	{
		0,
		5.6 * cm,
		7.15 * cm,
		8.26 * cm,
		10.03 * cm,
		PMTLength
	};

	const G4double pmtRInner[] =
	{
		0,
		0,
		0,
		0,
		0,
		0
	};

	const G4double pmtROuter[] =
	{
		PMTRadiusLarge,
		PMTRadiusLarge,
		5.15 * cm,
		3.6 * cm,
		PMTRadiusLow,
		PMTRadiusLow
	};

	G4Polycone* solidPMT = new G4Polycone("LaBr2PMT",StartPhi,DeltaPhi,pmtNZPlanes,
									      pmtZPlanes,pmtRInner,pmtROuter);
	
	G4LogicalVolume* logicPMT = new G4LogicalVolume(solidPMT,
													Quartz,"LaBr2PMT");
	
	G4ThreeVector positionPMT = G4ThreeVector(0.*cm,0.*cm,PMTStart);
	
	//G4VPhysicalVolume* physiPMT = new G4PVPlacement(0,positionPMT,
	//												logicPMT,"LaBr2PMT",
	//												GetMotherVolume(),false,0);

	// Reflector

	G4double ReflectorRadiusOuter = 4.5616 *cm;

	const  G4int  reflectorNZPlanes = 4;
	const  G4double reflectorZPlanes[] =
	{
		ReflectorStart,
		ScintStart,
		ScintStart,
		CrystalFin
	};

	const G4double reflectorRInner[] =
	{
		0,
		0,
		ScintRadius,
		ScintRadius
	};

	const G4double reflectorROuter[] =
	{
		ReflectorRadiusOuter,
		ReflectorRadiusOuter,
		ReflectorRadiusOuter,
		ReflectorRadiusOuter
	};

	G4Polycone* solidReflector = new G4Polycone("LaBr2Reflector",StartPhi,DeltaPhi,reflectorNZPlanes,
											    reflectorZPlanes,reflectorRInner,reflectorROuter);

	G4LogicalVolume* logicReflector = new G4LogicalVolume(solidReflector,Teflon,
														  "LaBr2Reflector");
	
	G4ThreeVector positionReflector = G4ThreeVector(0.*cm,0.*cm,0);
	
	//G4VPhysicalVolume* physiReflector = new G4PVPlacement(0,positionReflector,
	//													  logicReflector,"LaBr2Reflector",
	//													  GetMotherVolume(),false,0);

	// Housing

	G4double HousingLengthLow = 14.46 * cm;
	G4double HousingLengthHigh = 18.4 * cm;

	G4double HousingRadiusLow = 4.9 * cm;
	G4double HousingRadiusMid = 7.23 * cm;
	G4double HousingRadiusHigh = 3.0 * cm;

	const  G4int  housingNZPlanes = 13;
	const  G4double housingZPlanes[] =
	{
		/*1*/ 0,
		0.8*mm,
		/*2*/ ReflectorStart,
		/*3*/ ReflectorStart,
		/*4*/ HousingLengthLow,
		/*5*/ 14.9 * cm,
		/*6*/ 14.9 * cm,
		/*7*/ PMTStart,
		/*8*/ PMTStart,
		/*9*/ HousingLengthLow + 7.23 * cm,
		/*10*/ HousingLengthLow + 11.51 * cm,
		/*11*/ PMTStart + PMTLength,
		/*12*/ HousingLengthLow + 17.56 * cm
	};

	const G4double housingRInner[] =
	{
		/*1*/ 4.53*cm,
		4.45*cm,
		/*2*/ 0,
		/*3*/ ReflectorRadiusOuter,
		/*4*/ ReflectorRadiusOuter,
		/*5*/ ReflectorRadiusOuter,
		/*6*/ ReflectorRadiusOuter,
		/*7*/ ReflectorRadiusOuter,
		/*8*/ PMTRadiusLarge,
		/*9*/ PMTRadiusLarge,
		/*10*/ PMTRadiusLow,
		/*11*/ PMTRadiusLow,
		/*12*/ 0

	};

	const G4double housingROuter[] =
	{
		/*1*/ HousingRadiusLow,
		HousingRadiusLow,
		/*2*/ HousingRadiusLow,
		/*3*/ HousingRadiusLow,
		/*4*/ HousingRadiusLow,
		/*5*/ HousingRadiusLow + 0.4 * cm,
		/*6*/ HousingRadiusMid,
		/*7*/ HousingRadiusMid,
		/*8*/ HousingRadiusMid,
		/*9*/ HousingRadiusMid,
		/*10*/ HousingRadiusHigh,
		/*11*/ HousingRadiusHigh,
		/*12*/ HousingRadiusHigh
	};

	G4Polycone* solidHousing = new G4Polycone("LaBr2Housing",StartPhi,DeltaPhi,housingNZPlanes,
											  housingZPlanes,housingRInner,housingROuter);

	G4LogicalVolume* logicHousing = new G4LogicalVolume(solidHousing,Al,
														"LaBr2Housing");
	
	G4ThreeVector positionHousing = G4ThreeVector(0.*cm,0.*cm,0);
	
	//G4VPhysicalVolume* physiHousing = new G4PVPlacement(0,positionHousing,
	//													logicHousing,"LaBr2Housing",
	//													GetMotherVolume(),false,0);
	
	//------------------------------------------------------
	// visualization attributes
	//------------------------------------------------------
	
	//Green color for crystal
	G4VisAttributes* red= new G4VisAttributes(G4Colour(1.5,1.0,1.0));
	logicCrystal->SetVisAttributes(red);
	
	//Blue color for PMT
	G4VisAttributes* blue= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
	logicPMT->SetVisAttributes(blue);

	//Grey color for housing
	G4VisAttributes* grey= new G4VisAttributes(G4Colour(0.2,0.2,0.2));
	logicHousing->SetVisAttributes(grey);

	//White color for the reflector
	G4VisAttributes* white= new G4VisAttributes(G4Colour(0.8,0.8,0.8));
	logicReflector->SetVisAttributes(white);
    
	// Place the logic volumes
	PlaceVolume(logicCrystal, GetMotherVolume(),positionCrystal, G4RotationMatrix());
	PlaceVolume(logicReflector, GetMotherVolume(),positionReflector, G4RotationMatrix());
	PlaceVolume(logicPMT, GetMotherVolume(),positionPMT, G4RotationMatrix());
	PlaceVolume(logicHousing, GetMotherVolume(),positionHousing, G4RotationMatrix());

	return nullptr;
}

void LaBr2Detector::ConstructSDandField()
{
    // Energy deposition in the LaBr crystals is tracked with a primitive scorer

    // attempts to delete this pointer in the destructor result in error,
    // apparently detectors are cleaned up by Geant4
    auto *det = new G4MultiFunctionalDetector("LaBr2Crystal");
    G4SDManager::GetSDMpointer()->AddNewDetector(det);

    auto *psEdep = new G4PSEnergyDeposit("Edep",1);
    det->RegisterPrimitive(psEdep);

    SetSensitiveDetector( "LaBr2Crystal", det);
}

void LaBr2Detector::SetupOutput()
{
    auto *am = G4AnalysisManager::Instance();

    fTupleID = am->CreateNtuple("EdepLaBr2", "Energy Deposition in La2Br detector");

    G4cout << "LaBr2Detector::SetupOutput - " << fTupleID << G4endl;

    am->CreateNtupleDColumn("LaBr2");
 
    am->FinishNtuple();
}

void LaBr2Detector::FillOutput(const G4Event *event)
{
    // Get hit collection ID
    if (fHCID == -1 )
    {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID("LaBr2Crystal/Edep");
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