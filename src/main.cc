/////////////////////////////////////////////////////////
//                                                     //
//  Oct/2013  E. Nacher  -->  main.cc                  //
//  Practical work for the SWG2013 Workshop            //
//                                                     //
/////////////////////////////////////////////////////////

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "GeometryManager.hh"

#include "ActionInitialization.hh"

#include "PhysicsList.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

using namespace std;	 

int main(int argc, char** argv)
{
	// construct the default run manager
	G4RunManager* runManager = new G4RunManager;
	
	// set mandatory initialization classes
	runManager->SetUserInitialization(GeometryManager::GetInstance());
	runManager->SetUserInitialization(new PhysicsList);

  // Implementation of G4VUserActionInitialization
  auto actionInitialization = new ActionInitialization();
  runManager->SetUserInitialization(actionInitialization);
	
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc!=1) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode : define UI session
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute mac/init_vis.mac"); 
    ui->SessionStart();
    delete ui;
//#endif
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete UImanager;
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
