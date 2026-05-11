// include/PrimaryGeneratorAction.hh
//
// Defines the primary particles for each event.
// Minimal version: a particle gun firing one electron at fixed
// energy, position, and direction. We'll swap this for an Am-Be
// G4GeneralParticleSource much later.

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

// Forward declarations
class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    // Called by Geant4 at the start of every event.
    // We use it to fire one particle.
    void GeneratePrimaries(G4Event* event) override;

private:
    G4ParticleGun* fParticleGun;
};

#endif
