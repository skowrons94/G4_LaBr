
#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <fstream>

#include "G4UImessenger.hh"
class G4UIcmdWithAString;

#include <memory>
using std::shared_ptr;

using namespace std;

class G4Run;

class RunAction : public G4UserRunAction, public G4UImessenger
{
  public:
    RunAction();
    ~RunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    void SetNewValue(G4UIcommand*, G4String);

	G4double xmin;
	G4double xmax;
	G4int binsize;
	G4int nbins;

  private:
    G4String fFileName = "";
    shared_ptr<G4UIcmdWithAString> m_setFileNameCmd;
		
};

#endif

