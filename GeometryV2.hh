#ifndef GEOMETRYV2_H
#define GEOMETRYV2_H

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

field_cage_parameters help();

G4LogicalVolume* get_world();
G4PVPlacement* GeometryV2();

#endif
