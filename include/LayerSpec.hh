/*THis is a data structure that describes one layer of the graded-z stack. It is the single most important data structure in the
geometry part of the project. 

The whole one binary infinite configuration" promise (Architecture lockdown)"= rests on the geometry being a std::vector<LayerSpec> that the messenger fills 
from a macro file instead of hardcoded G4Box calls

Two kinds of layers are supported:
    1. A puure NIST material e.g "G4_POLYETHYLENE", "G4_Pb", "G4_Al"
    2. A composite material (matrix + metal filler at a mass fraction)

I am keeping both descriptions in thes ame struct and using 'isComposite' to tell them apart. 

Detector construction reads this flag in order to decide whether to call G4NistManager::FindOrBuildMaterial (pure) or to build a custom G4Material 
(composite) See Geometry strategy.md and modelling flexibility.md. 
*/

#ifndef LAYERSPEC_HH+
#define LAYERSPEC_HH

#include "G4String.hh"
#include "G4SystemOfUnits.hh"

struct LayerSpec
{
    G4double thickness = 1.0*mm;  //this is full thickness not half lenghts like im used to when working with G4 primitives. DC will halve it when building G4Box
    
    G4String material = "G4_Galactic"; //this is a NIST material name used when !isComposite is true.

    //----COmposite Description---

    bool isCOmposite = false;
    G4String matrix = "";   //e.g. "G4_POLYETHYLENE" ,"g4_EPOXY"
    G4String filler = ""; // e.g "G4_Pb", "G4_W", "G4_Bi"
    G4double fillerMassFrac = 0.0; // 0...1 the fraction of the total mass that is filler material

    /*the below is a human-readable label, used as the csv column duffix/ scoring name. For pure layers, this is just the material, for composites,
    we synthesize something like "EPOXY+Pb30". DC sets it*/
    G4String label ="layer";
};

#endif