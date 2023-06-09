#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4GenericPolycone.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();
    
    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
    
    virtual G4VPhysicalVolume *Construct();

private:
    G4LogicalVolume *logicDetector;
    virtual void ConstructSDandField();

    G4LogicalVolume *fScoringVolume;
    
};
#endif
