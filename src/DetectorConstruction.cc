// src/DetectorConstruction.cc
//
// Minimal geometry: a world volume of air with a single small box
// of polyethylene in the middle. Just enough that primaries have
// something to interact with so we can see tracks during visualization.

#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

// ---------------------------------------------------------------------
// Constructor / destructor
// ---------------------------------------------------------------------
DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction(),
      fBoxLV(nullptr)
{}

DetectorConstruction::~DetectorConstruction() = default;

// ---------------------------------------------------------------------
// Construct() — called by Geant4 once at initialization.
// Returns the world physical volume.
// ---------------------------------------------------------------------
G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // -----------------------------------------------------------------
    // Materials
    // -----------------------------------------------------------------
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air          = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* polyethylene = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

    // -----------------------------------------------------------------
    // World volume: 2 m × 2 m × 2 m cube of air
    // -----------------------------------------------------------------
    G4double worldHalfSize = 1.0 * m;

    auto* solidWorld = new G4Box("World",
                                 worldHalfSize, worldHalfSize, worldHalfSize);
    auto* logicWorld = new G4LogicalVolume(solidWorld, air, "World");
    auto* physWorld  = new G4PVPlacement(
        nullptr,              // no rotation
        G4ThreeVector(),      // at origin
        logicWorld,           // its logical volume
        "World",              // its name
        nullptr,              // no mother (this IS the mother)
        false,                // no boolean ops
        0,                    // copy number
        true);                // check for overlaps

    // -----------------------------------------------------------------
    // Test box: 20 cm × 20 cm × 5 cm slab of polyethylene at the origin
    // -----------------------------------------------------------------
    G4double boxHalfX = 10.0 * cm;
    G4double boxHalfY = 10.0 * cm;
    G4double boxHalfZ = 2.5  * cm;

    auto* solidBox = new G4Box("TestBox", boxHalfX, boxHalfY, boxHalfZ);
    fBoxLV         = new G4LogicalVolume(solidBox, polyethylene, "TestBox");
    new G4PVPlacement(
        nullptr,              // no rotation
        G4ThreeVector(),      // at origin
        fBoxLV,               // its logical volume
        "TestBox",            // its name
        logicWorld,           // mother: the world
        false,                // no boolean ops
        0,                    // copy number
        true);                // check for overlaps

    // -----------------------------------------------------------------
    // Visualization attributes
    // -----------------------------------------------------------------
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    auto* boxVis = new G4VisAttributes(G4Colour(0.9, 0.9, 0.9, 0.4));  // light grey, semi-transparent
    boxVis->SetForceSolid(true);
    fBoxLV->SetVisAttributes(boxVis);

    return physWorld;
}