// src/PrimaryGeneratorAction.cc

#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

// ---------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------
PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),
      fParticleGun(nullptr)
{
    constexpr G4int nParticles = 1;
    fParticleGun = new G4ParticleGun(nParticles);

    // Default particle: 10 MeV electron, travelling along +z, starting at z = -30 cm
    auto* particleTable = G4ParticleTable::GetParticleTable();
    auto* electron      = particleTable->FindParticle("e-");

    fParticleGun->SetParticleDefinition(electron);
    fParticleGun->SetParticleEnergy(10.0 * MeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -30.0 * cm));
}

// ---------------------------------------------------------------------
// Destructor — we own fParticleGun, so we delete it
// ---------------------------------------------------------------------
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

// ---------------------------------------------------------------------
// GeneratePrimaries — called once per event
// ---------------------------------------------------------------------
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    fParticleGun->GeneratePrimaryVertex(event);
}