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

		/*
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
	  binsize = 1; // in keV
	  nbins= (int)((xmax-xmin)/binsize);
	  analysisManager->CreateH1("Edep","Edep in Crystal", nbins, xmin*keV, xmax*keV);

      xmin = 0; // in keV
	  xmax = 12e3; // in keV
	  binsize = 2; // in keV
	  nbins= (int)((xmax-xmin)/binsize);
	  analysisManager->CreateH1("Egam","Energy of Primary Particles", nbins, xmin*keV, xmax*keV);

	  // Creating ntuple
	  //
	  analysisManager->CreateNtuple("Data", "Data");
	  analysisManager->CreateNtupleDColumn("Edep");
	  analysisManager->CreateNtupleDColumn("Egam");
	  analysisManager->FinishNtuple();
	  */

}

RunAction::~RunAction()
{
	delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run*)
{
	// Get analysis manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetNtupleMerging(true);

	// Open an output file
	analysisManager->OpenFile(fFileName);

	// Create outputs
	auto* gm = GeometryManager::GetInstance();
    gm->SetupOutputs();
}

void RunAction::EndOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();
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
