// include/DetectorConstruction.hh
//
// Minimal detector geometry: world volume of air, one polyethylene box.
// This is intentionally bare-bones. Graded-Z layers, materials, and
// scoring come in later steps.

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

// Forward declarations — we only use these as pointers in the header,
// so we don't need the full headers here. Speeds up compilation.
class G4LogicalVolume;
class G4VPhysicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    // Geant4 calls this once at initialization. We build geometry and
    // return a pointer to the world physical volume.
    G4VPhysicalVolume* Construct() override;

private:
    // The logical volume for our test box. We hold onto it as a member
    // so later (when we add scoring) we can attach a sensitive detector
    // to it from another method without rebuilding geometry.
    G4LogicalVolume* fBoxLV;
};

#endif