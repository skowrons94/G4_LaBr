#include "EventAction.hh"
#include "Analysis.hh"
//#include "Randomize.hh" // do we really need this?
#include <iomanip>

#include "GeometryManager.hh"

#include "RunAction.hh"
#include "G4GeneralParticleSource.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4RunManager.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4UnitsTable.hh"

#include "globals.hh"

//#include "iomanip"

using namespace std;
using namespace CLHEP;

EventAction::EventAction(RunAction*)
:G4UserEventAction()//, EdepInCrystal(0.), nAbsPhotons(0.), absTime(0.)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{

}

void EventAction::EndOfEventAction(const G4Event* evt)
{
	// Accumulate statistics
	auto *gm = GeometryManager::GetInstance();
    gm->FillOutputs(evt);

  	// Print per event (modulo n)
  	G4int eventID = 1 + evt->GetEventID();
  	G4int printModulo = 100;
  	if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) )
  	{
    	G4cout << "---> End of event: " << eventID << G4endl;
  	}
}
