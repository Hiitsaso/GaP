#include "nain4.hh"
#include "g4-mandatory.hh"
#include "GeometryV2.hh"
#include "n4-volumes.hh"
#include "n4-utils.hh"

#include "materials.hh"
#include "GeometryV2.hh"

//~ #include <FTFP_BERT.hh>
//~ #include <G4EmStandardPhysics_option4.hh>
//~ #include <G4LogicalVolume.hh>
//~ #include <G4Material.hh>
//~ #include <G4OpticalPhysics.hh>
//~ #include <G4PVPlacement.hh>
//~ #include <G4RandomDirection.hh>
//~ #include <G4RunManagerFactory.hh>
//~ #include <G4SubtractionSolid.hh>
//~ #include <G4SystemOfUnits.hh>
//~ #include <G4Tubs.hh>
//~ #include <G4UnionSolid.hh>
//~ #include <G4OpticalSurface.hh>
//~ #include <G4LogicalBorderSurface.hh>
//~ #include <G4UserLimits.hh>
//~ #include <G4UserLimits.hh>

//~ #include <G4VSolid.hh>
//~ #include <iostream>
//~ #include <typeinfo>


using vecd = std::vector<G4double>;

const auto world_size = 0.5 * m;

G4Material* vacuum;

G4LogicalVolume* world;

field_cage_parameters help() {
  field_cage_parameters fcp;
   
  //Cathode 
  fcp.cathode_z = 1*mm;
  fcp.cathode_z_new = 1*mm;

  // Cathode Bracket
  fcp.cathBracket_z =  1*mm;
  fcp.cathBracket_z_new =  1*mm;

  //Gas
  fcp.drift_length = 14.8*mm;
  fcp.el_length    = 9.05*mm;

  // Drift
  fcp.drift_z = 14.8*mm;
  fcp.drift_z_new = 14.8*mm;
  fcp.drift_r = 14.8*mm;
  
  fcp.el_z = 14.8*mm;

  return fcp;
}



void ensure_initialized() {
  static bool initialized = false;
  if (initialized) { return; }
  initialized = true;

  vacuum = n4::material("G4_Galactic");   
  world = n4::box("world").cube(world_size).volume(vacuum);
}

G4LogicalVolume* get_world() {
  ensure_initialized();
  return world;
}

G4PVPlacement* GeometryV2() {
  ensure_initialized();
  return n4::place(world).now();
}

