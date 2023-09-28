#ifndef GEOMETRYV2_H
#define GEOMETRYV2_H

struct field_cage_parameters {
  //PROPERTIES
  G4double photoe_prob;
  G4double pressure;
  G4double temperature;
  G4double sc_yield;
  G4double elifetime;
  
  //MEASUREMENTS
  G4double vessel_out_rad;
  G4double vessel_out_length;
  G4double vessel_rad;
  G4double vessel_length;
  
  G4double mesh_rad;
  G4double mesh_thickn;
  G4double mesh_transparency;
  
  G4double meshBracket_rad;
  G4double meshBracket_thickn;
  G4double anodeBracket_rad;
  G4double anodeBracket_thickn;
  
  G4double pmt_rad;
  
  G4double enclosure_pmt_rad;
  G4double enclosure_pmt_thickn;
  G4double enclosure_pmt_length;
  G4double enclosurevac_pmt_length;
  
  G4double plate_pmt_rad;
  G4double plate_pmt_thickn;
  G4double plate_pmt_length;
  G4double plateUp_pmt_length;
  G4double plateUp_pmt_thickn;
  G4double plateUp_pmt_rad;
  G4double plateBottom_pmt_length;
  G4double plateBottom_pmt_rad;
  
  G4double pmtHolder_rad;
  G4double pmtHolder_length;
  
  G4double quartz_window_rad;
  G4double quartz_window_thickn;
  G4double tpb_coating_thickn;
  
  G4double pmt_length;
  
  G4double rings_rad;
  G4double rings_thickn;
  G4double rings_length;
  
  G4double teflon_cage_rad;
  G4double teflon_cage_thickn;
  G4double teflon_cage_lenght;

  //S1 AND S2 LENGTHS
  G4double drift_length;
  G4double el_length;
  
  //POSITIONS
  G4double vessel_z; 
  G4double cathBracket_z;
  G4double gateBracket_z;
  G4double anodeBracket_z;
  
  G4double teflon_cage_z;
  
  G4double pmt_z;
  G4double plateUp_pmt_z;
  G4double enclosure_pmt_z;
  G4double plate_pmt_z;
  G4double PMTplateBottom1_pos_z;
  
  G4double cathode_z; 
  G4double drift_z;  
  G4double el_z;
  
};

field_cage_parameters version2_parameters();

G4LogicalVolume* get_world(field_cage_parameters const & fcp);
G4PVPlacement* GeometryV2();

#endif
