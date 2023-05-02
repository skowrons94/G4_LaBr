///////////////////////////////////////////
//
// Oct/2015  Fabio -> RunAction.cc
//
///////////////////////////////////////////

#include "RunAction.hh"
#include "Analysis.hh"
#include "GeometryManager.hh"

#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4Run.hh"
#include "G4ios.hh"

#include "G4UIcmdWithAString.hh"

#include <memory>
using std::shared_ptr;

#include <iomanip>

RunAction::RunAction() : G4UserRunAction()
{

	  m_setFileNameCmd = make_shared<G4UIcmdWithAString>("/run/setFileName", this);
      m_setFileNameCmd->SetGuidance("Set output file name.");
      m_setFileNameCmd->SetParameterName("file name", false);

	  // Create analysis manager
	  // The choice of analysis technology is done via selecting of a namespace
	  // in B4Analysis.hh
	  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	  G4cout << "Using " << analysisManager->GetType() << G4endl;

	  // Create directories
	  //analysisManager->SetHistoDirectoryName("histograms");
	  //analysisManager->SetNtupleDirectoryName("ntuple");
	  analysisManager->SetVerboseLevel(1);
	  analysisManager->SetFirstHistoId(0); // default is 0
	  analysisManager->SetFirstNtupleId(0); // default is 0

	  // Book histograms, ntuple
	  //

	  // Creating histograms

	  //  G4int CreateH1(const G4String& name, const G4String& title,
	  //                 G4int nbins, G4double xmin, G4double xmax,
	  //                 const G4String& unitName = "none",
	  //                 const G4String& fcnName = "none",
	  //                 const G4String& binSchemeName = "linear");

	  xmin = 0; // in keV
	  xmax = 12e3; // in keV
	  binsize = 2; // in keV
	  nbins= (int)((xmax-xmin)/binsize);
	  analysisManager->CreateH1("Edep","Edep in Crystal", nbins, xmin*keV, xmax*keV);

	  xmin = 0; //
	  xmax = 2e3; //
	  binsize = 2; //
	  nbins= (int)(xmax-xmin)/binsize;
          analysisManager->CreateH1("Npho","Absorbed Photons", nbins, xmin, xmax);

      // Here we need some units!
      xmin = 0; // in ns
	  xmax = 500; // in ns
	  binsize = 2; // in ns
	  nbins= (int)(xmax-xmin)/binsize;
          analysisManager->CreateH1("Tabs","Time of Absorption", nbins, xmin, xmax*ns);

      xmin = 0; // in keV
	  xmax = 12e3; // in keV
	  binsize = 2; // in keV
	  nbins= (int)((xmax-xmin)/binsize);
	  analysisManager->CreateH1("Egam","Energy of Primary Particles", nbins, xmin*keV, xmax*keV);

	  // Creating ntuple
	  //
	  analysisManager->CreateNtuple("Data", "Data");
	  analysisManager->CreateNtupleDColumn("Edep");
	  analysisManager->CreateNtupleDColumn("Npho");
	  analysisManager->CreateNtupleDColumn("Tabs");
	  analysisManager->CreateNtupleDColumn("Egam");
	  analysisManager->FinishNtuple();

}

RunAction::~RunAction()
{
	delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run*)
{
	  //inform the runManager to save random number seed
	  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

	  // Get analysis manager
	  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	  // Open an output file
	  //
	  analysisManager->OpenFile(fFileName);
}

void RunAction::EndOfRunAction(const G4Run*)
{
	  // print histogram statistics
	  //
	  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	  if ( analysisManager->GetH1(1) ) {
	    G4cout << G4endl << " ----> print histograms statistic ";
	    if(isMaster) {
	      G4cout << "for the entire run " << G4endl << G4endl;
	    }
	    else {
	      G4cout << "for the local thread " << G4endl << G4endl;
	    }

	    G4cout << G4endl << " EAbs : mean = "
	       << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy")
	       << " rms = "
	       << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Energy") << G4endl;

	  }

	  // save histograms & ntuple
	  //
	  analysisManager->Write();
	  analysisManager->CloseFile();

}

void RunAction::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if (command == m_setFileNameCmd.get())
    {
        fFileName = newValue;
    }
    else
    {
        G4cerr << "Unknown command in RunAction!" << G4endl;
    }
}
