// src/ActionInitialization.cc

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"

ActionInitialization::ActionInitialization()
    : G4VUserActionInitialization()
{}

ActionInitialization::~ActionInitialization() = default;

// ---------------------------------------------------------------------
// Build — register per-thread (or per-run, in serial mode) user actions
// ---------------------------------------------------------------------
void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction);
    // SetUserAction(new RunAction);    // will add later
    // SetUserAction(new EventAction);  // will add later
}

// ---------------------------------------------------------------------
// BuildForMaster — master thread in MT mode. No-op for now.
// ---------------------------------------------------------------------
void ActionInitialization::BuildForMaster() const
{
    // When we add a RunAction that needs to merge thread-local files
    // (e.g. one CSV per thread → one combined output), we register it
    // here too. For now: nothing.
}
