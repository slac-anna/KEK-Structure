// add vacuum part

#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
   
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *logicMat = nist->FindOrBuildMaterial("G4_Cu");
    G4Material *logicMatCellIn = nist->FindOrBuildMaterial("G4_Galactic");

    G4double tot_l      = 2*175.96*mm;  //total structure length
    G4double out_body_r = 50.00*mm;    //cell body outer radius 
    G4double out_body_l = 2*139.96*mm; //cell body outer length
    G4double out_bp_r   = 12.00*mm;    //beampipe outer radius  
    G4double bp_l = 36.00*mm;          //thin beampipe length

    G4double cc_l = 34.100*mm;    //coupler cell length
    G4double cc_h = 39.585*mm;    //cpupler cell radius

    G4double cr_l = 29.99*mm;     //regular cell length not including disk 
    G4double cr_h = 41.38*mm;    //regular cell radius

    G4double bp_r = 10.00*mm;    //beampipe inner radius
    G4double bp_disk_r = 2.40*mm; //beampipe disk radius

    G4double cell_disk_a = 4.60*mm; //disk radius_a 
    G4double cell_disk_b = 2.30*mm; //disk radius_b
    G4double cell_disk_t = 5.00*mm; //disk tiickness
      
    G4double side_wall_t = 15.885*mm;

    G4double dz1 = bp_disk_r/6;       //points space on beampipe disk
    G4double dz2 = cell_disk_t/10;       //points space on regular disk

    //simulation domain: 200mm*200mm*500mm 
    G4double xWorld = 100.000*mm;  
    G4double yWorld = 100.000*mm;
    G4double zWorld = 250.000*mm;

    G4Box *solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    //Upstream
    //beampipe 
    G4Tubs *solidBeampipe1 = new G4Tubs("solidBeampipe1", bp_r, out_bp_r, bp_l/2, 0., 360.*deg);
    G4LogicalVolume *logicBeampipe1 = new G4LogicalVolume(solidBeampipe1, logicMat, "logicalBeampipe1");
    G4VPhysicalVolume *physBeampipe1 = new G4PVPlacement(0, G4ThreeVector(0., 0., (-out_body_l/2-bp_l/2)), logicBeampipe1, "physBeampipe1", logicWorld, false, 0, true);
 
    //side wall
    G4int numRZ1 = 11;
    G4double z00 = out_body_l/2;
    G4double z01 = z00-side_wall_t+bp_disk_r;
    G4double z02 = z01 - bp_disk_r;

    G4double r1[] = {bp_r, bp_r, 10.033568*mm, 10.137258*mm, 10.321539*mm, 10.611146*mm, 11.07335*mm, 12.4*mm, out_body_r, out_body_r, out_bp_r};
    G4double z1[] = {-z00, -z01, (-z01+dz1), (-z01+2*dz1), (-z01+3*dz1), (-z01+4*dz1), (-z01+5*dz1), (-z01+6*dz1), (-z01+6*dz1), -z00, -z00};
    G4VSolid* solidSideWall1 = new G4GenericPolycone("aPloycone1", 0.*deg, 360.*deg, numRZ1, r1, z1);
    G4LogicalVolume *logicSideWall1 = new G4LogicalVolume(solidSideWall1, logicMat, "logicalSideWall1");
    G4VPhysicalVolume *phySideWall1 = new G4PVPlacement(0, G4ThreeVector(0., 0., 0), logicSideWall1, "physSideWall1", logicWorld, false, 0, true);

    //coupler cell
    G4Tubs *solidCoupler1 = new G4Tubs("solidCoupler1", cc_h, out_body_r, cc_l/2, 0., 360.*deg);
    G4LogicalVolume *logicCoupler1 = new G4LogicalVolume(solidCoupler1, logicMat, "logicalCoupler1");
    G4VPhysicalVolume *physCoupler1 = new G4PVPlacement(0, G4ThreeVector(0.,0, (cc_l/2-z02)), logicCoupler1, "physCoupler1", logicWorld, false, 0, true);

    //downstream
    //beampipe 
    G4Tubs *solidBeampipe2 = new G4Tubs("solidBeampipe2", bp_r, out_bp_r, bp_l/2, 0., 360.*deg);
    G4LogicalVolume *logicBeampipe2 = new G4LogicalVolume(solidBeampipe2, logicMat, "logicalBeampipe2");
    G4VPhysicalVolume *physBeampipe2 = new G4PVPlacement(0, G4ThreeVector(0., 0., (out_body_l/2+bp_l/2)), logicBeampipe2, "physBeampipe2", logicWorld, false, 0, true);

    //side wall
    G4double z2[] = {z00, z01, (z01-dz1), (z01-2*dz1), (z01-3*dz1), (z01-4*dz1), (z01-5*dz1), (z01-6*dz1), (z01-6*dz1), z00, z00};
    G4VSolid* solidSideWall2 = new G4GenericPolycone("aPloycone2", 0.*deg, 360.*deg, numRZ1, r1, z2);
    G4LogicalVolume *logicSideWall2 = new G4LogicalVolume(solidSideWall2, logicMat, "logicalSideWall2");
    G4VPhysicalVolume *phySideWall2 = new G4PVPlacement(0, G4ThreeVector(0., 0., 0), logicSideWall2, "physSideWall2", logicWorld, false, 0, true);

    //coupler cell
    G4Tubs *solidCoupler2 = new G4Tubs("solidCoupler2", cc_h, out_body_r, cc_l/2, 0., 360.*deg);
    G4LogicalVolume *logicCoupler2 = new G4LogicalVolume(solidCoupler2, logicMat, "logicalCoupler2");
    G4VPhysicalVolume *physCoupler2 = new G4PVPlacement(0, G4ThreeVector(0.,0, (-cc_l/2+z02)), logicCoupler2, "physCoupler2", logicWorld, false, 0, true);

    //cavity regular cell disk
    G4int numRZ2 = 13;
    G4double z03 = 2.5*cr_l + 3*cell_disk_t;
    G4double z04 = z03-cell_disk_t;

    G4double r2[] = {out_body_r, 16.27*mm, 13.406436*mm, 12.475267*mm, 11.957228*mm, 11.709298*mm, 11.67*mm, 11.709298*mm, 11.957228*mm, 12.475267*mm, 13.406436*mm, 16.27*mm, out_body_r };
    G4double z3[] = {-z03, -z03, (-z03+dz2), (-z03+2*dz2), (-z03+3*dz2), (-z03+4*dz2), (-z03+5*dz2), (-z03+6*dz2), (-z03+7*dz2), (-z03+8*dz2), (-z03+9*dz2), (-z03+10*dz2), -z04, -z04};
    G4VSolid* solidRegCellDisk = new G4GenericPolycone("aPloycone3", 0.*deg, 360.*deg, numRZ2, r2, z3);
    G4LogicalVolume *logicRegCellDisk = new G4LogicalVolume(solidRegCellDisk, logicMat, "logicRegCellDisk");

    for(G4int j=0; j<6; j++)
     { 
       G4VPhysicalVolume *phyRegCellDisk = new G4PVPlacement(0, G4ThreeVector(0., 0., j*(cr_l+cell_disk_t)), logicRegCellDisk, "physRegCellDisk", logicWorld, false, j, true);
     }

    //cavity regular cell wall
    G4Tubs *solidRegCell = new G4Tubs("solidRegCell", cr_h, 0.05*m, cr_l/2, 0., 360.*deg);
    G4LogicalVolume *logicRegCell = new G4LogicalVolume(solidRegCell, logicMat, "logicRegCell");

    for(G4int j=0; j<5; j++)
     { 
       G4VPhysicalVolume *phyRegCell = new G4PVPlacement(0, G4ThreeVector(0., 0., -(2-j)*(cr_l+cell_disk_t)), logicRegCell, "physRegCell", logicWorld, false, j+6, true);
     }

    fScoringVolume = logicRegCell;


//unite group??

    //sensitive detector
    G4Tubs *solidDetector = new G4Tubs("solidDetector", 50*mm, 100*mm, 250*mm, 0., 360.*deg);

    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicDetector, "physDetector", logicWorld, false, 0, true);

//****************************************************************************************************************
   //vacuum
   //Upstream
    //beampipe
    G4Tubs *solidBeampipe1v = new G4Tubs("solidBeampipe1v", 0, bp_r, (175.965-126.475)/2*mm, 0., 360.*deg);
    G4LogicalVolume *logicBeampipe1v = new G4LogicalVolume(solidBeampipe1v, logicMatCellIn, "logicalBeampipe1v");
    G4VPhysicalVolume *physBeampipe1v = new G4PVPlacement(0, G4ThreeVector(0., 0., (-out_body_l/2-(175.965-126.475)/4)), logicBeampipe1v, "physBeampipe1v", logicWorld, false, 0, true);

    //end disk
    G4double r1v[] = {0, bp_r, 10.033568*mm, 10.137258*mm, 10.321539*mm, 10.611146*mm, 11.07335*mm, 12.4*mm, 0};
    G4double z1v[] = {-z01, -z01, (-z01+dz1), (-z01+2*dz1), (-z01+3*dz1), (-z01+4*dz1), (-z01+5*dz1), (-z01+6*dz1), (-z01+6*dz1)};
    G4VSolid* solidSideWall1v = new G4GenericPolycone("aPloycone4", 0.*deg, 360.*deg, 9, r1v, z1v);
    G4LogicalVolume *logicSideWall1v = new G4LogicalVolume(solidSideWall1v, logicMatCellIn, "logicalSideWall1v");
    G4VPhysicalVolume *phySideWall1v = new G4PVPlacement(0, G4ThreeVector(0., 0., 0), logicSideWall1v, "physSideWall1v", logicWorld, false, 0, true);


    //end disk
    G4double z2v[] = {z01, z01, (z01-dz1), (z01-2*dz1), (z01-3*dz1), (z01-4*dz1), (z01-5*dz1), (z01-6*dz1), (z01-6*dz1)};
    G4VSolid* solidSideWall2v = new G4GenericPolycone("aPloycone5", 0.*deg, 360.*deg, 9, r1v, z2v);
    G4LogicalVolume *logicSideWall2v = new G4LogicalVolume(solidSideWall2v, logicMatCellIn, "logicalSideWall2v");
    G4VPhysicalVolume *phySideWall2v = new G4PVPlacement(0, G4ThreeVector(0., 0., 0), logicSideWall2v, "physSideWall2v", logicWorld, false, 0, true);

    //coupler cell
    G4Tubs *solidCoupler1v = new G4Tubs("solidCoupler1v", 0, cc_h, cc_l/2, 0., 360.*deg);
    G4LogicalVolume *logicCoupler1v = new G4LogicalVolume(solidCoupler1, logicMatCellIn, "logicalCoupler1v");
    G4VPhysicalVolume *physCoupler1v = new G4PVPlacement(0, G4ThreeVector(0.,0, (cc_l/2-z02)), logicCoupler1v, "physCoupler1v", logicWorld, false, 0, true);

    //downstream
    //beampipe
    G4Tubs *solidBeampipe2v = new G4Tubs("solidBeampipe2v", 0, bp_r, (175.965-126.475)/2*mm, 0., 360.*deg);
    G4LogicalVolume *logicBeampipe2v = new G4LogicalVolume(solidBeampipe2v, logicMatCellIn, "logicalBeampipe2v");
    G4VPhysicalVolume *physBeampipe2v = new G4PVPlacement(0, G4ThreeVector(0., 0., (out_body_l/2+(175.965-126.475)/4)), logicBeampipe2v, "physBeampipe2v", logicWorld, false, 0, true);

    //coupler cell
    G4Tubs *solidCoupler2v = new G4Tubs("solidCoupler2v", 0, cc_h, cc_l/2, 0., 360.*deg);
    G4LogicalVolume *logicCoupler2v = new G4LogicalVolume(solidCoupler2v, logicMatCellIn, "logicalCoupler2v");
    G4VPhysicalVolume *physCoupler2v = new G4PVPlacement(0, G4ThreeVector(0.,0, (-cc_l/2+z02)), logicCoupler2v, "physCoupler2v", logicWorld, false, 0, true);

    //cavity regular cell disk
    G4double r2v[] = {0, 16.27*mm, 13.406436*mm, 12.475267*mm, 11.957228*mm, 11.709298*mm, 11.67*mm, 11.709298*mm, 11.957228*mm, 12.475267*mm, 13.406436*mm, 16.27*mm, 0 };
    G4double z3v[] = {-z03, -z03, (-z03+dz2), (-z03+2*dz2), (-z03+3*dz2), (-z03+4*dz2), (-z03+5*dz2), (-z03+6*dz2), (-z03+7*dz2), (-z03+8*dz2), (-z03+9*dz2), (-z03+10*dz2), -z04, -z04};
    G4VSolid* solidRegCellDiskv = new G4GenericPolycone("aPloycone4", 0.*deg, 360.*deg, numRZ2, r2v, z3v);
    G4LogicalVolume *logicRegCellDiskv = new G4LogicalVolume(solidRegCellDiskv, logicMatCellIn, "logicRegCellDiskv");

    for(G4int j=0; j<6; j++)
     {
       G4VPhysicalVolume *phyRegCellDiskv = new G4PVPlacement(0, G4ThreeVector(0., 0., j*(cr_l+cell_disk_t)), logicRegCellDiskv, "physRegCellDiskv", logicWorld, false, j, true);
     }

    //cavity regular cell
    G4Tubs *solidRegCellv = new G4Tubs("solidRegCellv", 0, cr_h, cr_l/2, 0., 360.*deg);
    G4LogicalVolume *logicRegCellv = new G4LogicalVolume(solidRegCellv, logicMatCellIn, "logicRegCellv");

    for(G4int j=0; j<5; j++)
     {
       G4VPhysicalVolume *phyRegCellv = new G4PVPlacement(0, G4ThreeVector(0., 0., -(2-j)*(cr_l+cell_disk_t)), logicRegCellv, "physRegCellv", logicWorld, false, j+6, true);
     }

    return physWorld;

}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new
    MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}
