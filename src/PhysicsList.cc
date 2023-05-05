/////////////////////////////////////////////////////////
//
// Apr/2015  E. Nacher -> PhysicsList.cc
//
// Physics List is a simplification of the LXePhysicsList 
// ($G4INSTALL/examples/extended/optical/LXe). EM physics 
// just registering G4EmStandardPhysics and no Decay Physics.
//
////////////////////////////////////////////////////////

#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
//#include "G4OpticalProcessIndex.hh"

#include "G4ParticleTypes.hh"

#include "G4SystemOfUnits.hh"


PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
	// default cut value  (0.1 mm)
	defaultCutValue = 0.1*mm;
	
	// EM Physics
	RegisterPhysics(new G4EmStandardPhysics());
	
}


PhysicsList::~PhysicsList() {}

void PhysicsList::SetCuts(){
	
	SetCutsWithDefault();
}
