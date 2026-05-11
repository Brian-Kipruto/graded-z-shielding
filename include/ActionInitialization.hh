// include/ActionInitialization.hh
//
// Factory class that creates user actions for each (worker) thread.
// For now: only PrimaryGeneratorAction. RunAction and EventAction
// will be added when we start writing simulation output.

#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization();
    ~ActionInitialization() override;

    // Called once per worker thread (or once total in serial mode).
    // Registers per-thread user actions with Geant4.
    void Build() const override;

    // Called once on the master thread in MT mode.
    // No-op for now — we have no RunAction yet.
    void BuildForMaster() const override;
};

#endif
