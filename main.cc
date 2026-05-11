// main.cc
// Entry point for graded-z-shielding simulation.
//
// Two modes:
//   ./graded-z                  → interactive mode (UI window, vis.mac auto-loaded)
//   ./graded-z some_macro.mac   → batch mode (run macro, exit)

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "FTFP_BERT.hh"   // Placeholder physics list — we'll customize later

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv)
{
    // ------------------------------------------------------------------
    // 1. Detect mode: interactive (no args) vs batch (macro file as arg)
    // ------------------------------------------------------------------
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // ------------------------------------------------------------------
    // 2. Run manager — start in SerialOnly mode for clarity during dev
    //    We'll switch to MT (multithreaded) much later, when we have a
    //    Python orchestrator running many independent simulations.
    // ------------------------------------------------------------------
    auto* runManager =
        G4RunManagerFactory::CreateRunManager(G4RunManagerType::SerialOnly);

    // ------------------------------------------------------------------
    // 3. Mandatory user initializations:
    //    a) Detector geometry
    //    b) Physics list
    //    c) User actions (primary generator, run/event hooks, etc.)
    // ------------------------------------------------------------------
    runManager->SetUserInitialization(new DetectorConstruction);
    runManager->SetUserInitialization(new FTFP_BERT);
    runManager->SetUserInitialization(new ActionInitialization);

    runManager->Initialize();

    // ------------------------------------------------------------------
    // 4. Visualization
    // ------------------------------------------------------------------
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // ------------------------------------------------------------------
    // 5. UI manager — used to apply commands (interactive or from macro)
    // ------------------------------------------------------------------
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (ui) {
        // Interactive mode: load vis.mac, then drop into the UI session
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } else {
        // Batch mode: run the specified macro and exit
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // ------------------------------------------------------------------
    // 6. Cleanup — delete in reverse order of construction
    // ------------------------------------------------------------------
    delete visManager;
    delete runManager;
    return 0;
}
