#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <G4Types.hh>
#include <G4Material.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>

#include "detector.hh"

G4LogicalVolume* get_world();

void place_mesh_holder_in(G4LogicalVolume* vessel);
void place_quartz_window_holder_in(G4LogicalVolume* vessel);
void place_pmt_holder_in(G4LogicalVolume* vessel);

struct field_cage_parameters {
  G4double cathode_z;
  G4double cathode_z_new;
  G4double cathBracket_z;
  G4double cathBracket_z_new;
  G4double drift_length;
  G4double el_length;
  G4double drift_z;
  G4double drift_z_new;
  G4double drift_r;
  G4double el_z;
};

field_cage_parameters model_something_old();
field_cage_parameters model_new();

void place_rings_in         (G4LogicalVolume* vessel, field_cage_parameters const & fcp);
void place_anode_el_gate_in (G4LogicalVolume* vessel, field_cage_parameters const & fcp);

G4PVPlacement* place_teflon_surface(G4LogicalVolume* vessel);
void place_optical_surface_between(G4PVPlacement* one, G4PVPlacement* two, G4String name, G4double refelctivity);

G4PVPlacement* geometry();
G4PVPlacement* geometry_test();

#endif
