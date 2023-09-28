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
#include <G4SubtractionSolid.hh>
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

const auto world_size = 0.6*m;

G4Material* peek;
G4Material* steel;
G4Material* aluminum;
G4Material* Cu;
G4Material* vacuum;
G4Material* mesh_mat;
G4Material* quartz;
G4Material* tpb;
G4Material* gas;
G4Material* air;
G4Material* teflon;
G4LogicalVolume* world;

field_cage_parameters version2_parameters() {
  field_cage_parameters fcp;
  //PROPERTIES
  fcp.photoe_prob       =   0;
  fcp.pressure          =  10 * bar;
  fcp.temperature       = 293 * kelvin;
  //const auto sc_yield        =  22222./MeV; // Wsc = 45 eV, fr
  fcp.sc_yield          =   1/GeV;
  //~ const auto sc_yield        =  1000./MeV;
  fcp.elifetime         = 1e6 * ms;
  // const auto drift_vel         = 1. * mm/microsecond;
  // const auto drift_transv_diff = 1. * mm/sqrt(cm);
  // const auto drift_long_diff   = .3 * mm/sqrt(cm);
  // const auto el_field          = 16.0 * kilovolt/cm;
  // const auto el_vel            = 3. * mm/microsecond;
  // const auto el_transv_diff    = 1. * mm/sqrt(cm);
  // const auto el_long_diff      = .3 * mm/sqrt(cm);
  
  //MEASUREMENTS
  fcp.vessel_out_rad    = 288./2  *mm;
  fcp.vessel_out_length = 466.79  *mm;
  fcp.vessel_rad        = 276./2  *mm;
  fcp.vessel_length     = 386.471 *mm; 

  fcp.mesh_rad          = 104./2  *mm;
  fcp.mesh_thickn       = 0.075   *mm;
  fcp.mesh_transparency = 0.95;

  fcp.meshBracket_rad      = 180./2  *mm;
  fcp.meshBracket_thickn   = 5.      *mm;
  fcp.anodeBracket_rad     = 160./2  *mm;
  fcp.anodeBracket_thickn  = 6.      *mm;

  fcp.pmt_rad = 25.4/2  *mm;

  fcp.enclosure_pmt_rad        = 120./2  *mm;
  fcp.enclosure_pmt_thickn     = 8.5     *mm;
  fcp.enclosure_pmt_length     = 113.5   *mm;
  fcp.enclosurevac_pmt_length  = 110.5   *mm;

  fcp.plate_pmt_rad        = 105./2  *mm;
  fcp.plate_pmt_thickn     = 105./2  *mm;
  fcp.plate_pmt_length     = 20      *mm;
  fcp.plateUp_pmt_length   = 15      *mm;
  fcp.plateUp_pmt_thickn   = 21.5    *mm;
  fcp.plateUp_pmt_rad      = 126./2  *mm;
  fcp.plateBottom_pmt_length   = 22      *mm;
  fcp.plateBottom_pmt_rad      = 105./2  *mm;
  
  fcp.pmtHolder_rad        = 115./2  *mm;
  fcp.pmtHolder_length     = 9       *mm;

  fcp.quartz_window_rad    = 108./2  *mm;
  fcp.quartz_window_thickn = 3       *mm;
  fcp.tpb_coating_thickn   = 3       *micrometer;

  fcp.pmt_length = 43.0  *mm;
  
  fcp.rings_out_rad    = 175./2  *mm;
  fcp.rings_int_rad    = 165./2  *mm;
  fcp.rings_length     = 10.     *mm;
  
	//faltan las medidas de los anillos, 
  
  //S1 AND S2 LENGTHS
  fcp.drift_length = 0*mm;
  fcp.el_length    = 0*mm;
  
  //POSITIONS(faltan por medir)
  fcp.vessel_z = fcp.vessel_length/2 - (163.5*mm + fcp.meshBracket_thickn);
  fcp.cathBracket_z = -fcp.vessel_z; //From the vessel (and at the origin or the world)
  
  fcp.pmt_z    = - (12.*mm + fcp.meshBracket_thickn/2 + fcp.pmt_length/2) + fcp.cathBracket_z; 
  fcp.plateUp_pmt_z = - ( 150.5*mm + fcp.meshBracket_thickn/2 + fcp.plateUp_pmt_length/2) + fcp.cathBracket_z;
  fcp.enclosure_pmt_z = fcp.plateUp_pmt_z + fcp.enclosure_pmt_length/2 + fcp.plateUp_pmt_length/2;
  fcp.plate_pmt_z = fcp.enclosure_pmt_z + fcp.enclosure_pmt_length/2 + fcp.plate_pmt_length/2;
  fcp.PMTplateBottom1_pos_z = fcp.pmt_z;
  
  fcp.cathode_z = 1*mm; 
  fcp.drift_z = 14.8*mm;  
  fcp.el_z = 14.8*mm;

  return fcp;
}

void ensure_initialized(field_cage_parameters const & fcp) {
  static bool initialized = false;
  if (initialized) { return; }
  initialized = true;

  Cu     = n4::material("G4_Cu"); 
  vacuum = n4::material("G4_Galactic");
  steel  = steel_with_properties();
  aluminum = aluminum_with_properties();
  gas      = GAr_with_properties(fcp.pressure, fcp.temperature, fcp.sc_yield, fcp.elifetime);
  mesh_mat = FakeDielectric_with_properties(gas, "mesh_mat",
                                            fcp.pressure, fcp.temperature, fcp.mesh_transparency, fcp.mesh_thickn,
                                            fcp.sc_yield, fcp.elifetime, fcp.photoe_prob);
  peek   = peek_with_properties();
  quartz = quartz_with_properties();
  tpb    = TPB_with_properties();
  teflon = teflon_with_properties();
  world = n4::box("world").cube(world_size).volume(vacuum);
}

G4LogicalVolume* get_world(field_cage_parameters const & fcp) {
  ensure_initialized(fcp);
  return world;
}

void place_pmt_holder_in(G4LogicalVolume* vessel, field_cage_parameters const & fcp) {     
  //Upper steel plate at the pmt clad
  n4::tubs("PMTplateUp").r_inner(fcp.plateUp_pmt_rad).r_delta(fcp.plateUp_pmt_thickn).z(fcp.plateUp_pmt_length).place(steel).in(vessel).at_z(fcp.plateUp_pmt_z).check_overlaps().now();
  
  //PMT clad
  n4::tubs("EnclosurePMT").r_inner(fcp.enclosure_pmt_rad).r_delta(fcp.enclosure_pmt_thickn).z(fcp.enclosure_pmt_length).place(steel).in(vessel).at_z(fcp.enclosure_pmt_z).check_overlaps().now();
  
  // Steel plate attached where the peek holders are attached
  n4::tubs("PMTplateBottom0").r_inner(fcp.plate_pmt_rad).r_delta(fcp.plate_pmt_thickn).z(fcp.plate_pmt_length).place(steel).in(vessel).at_z(fcp.plate_pmt_z).check_overlaps().now();
  
  // Position pairs (x,Y) for PMTs
  std::vector <float> pmt_PsX={-15.573,  20.68 , -36.253, 0, 36.253, -20.68 , 15.573};
  std::vector <float> pmt_PsY={-32.871, -29.922,  -2.949, 0,  2.949,  29.922, 32.871};
  
  //Build PMT and PMTplateBottom1
  auto solid_pmt = n4::tubs("solid_PMT").r(fcp.pmt_rad).z(fcp.pmt_length).solid(); //Hamamatsu pmt length: 43*mm | STEP pmt gap length: 57.5*mm
  G4LogicalVolume* logic_pmt = new G4LogicalVolume(solid_pmt, aluminum, "PMT");
 
  G4ThreeVector pos_pmt = {0, 0, 0};
  std::vector<std::vector<G4ThreeVector>> all_pos_pmt;
  
  for (G4int i = 0; i < G4int(pmt_PsX.size()); i++) {
    pos_pmt = G4ThreeVector(pmt_PsX[i]*mm, pmt_PsY[i]*mm, fcp.pmt_z);
    
    G4ThreeVector temp_pos_pmt;
    std::vector<G4ThreeVector> temp_vector; 
    temp_pos_pmt = {pos_pmt[0], pos_pmt[1], 0.};
    temp_vector.push_back(temp_pos_pmt); 
    all_pos_pmt.push_back(temp_vector);   

    n4::place(logic_pmt).in(vessel).at(pos_pmt).copy_no(i).check_overlaps().now();
  }

  auto PMtplateBottom1 =   
  /*      */n4::tubs("solid_PMTplateBottom1").r(fcp.plateBottom_pmt_rad).z(fcp.plateBottom_pmt_length)
  .subtract(solid_pmt).at(all_pos_pmt[0][0])
  .subtract(solid_pmt).at(all_pos_pmt[1][0])
  .subtract(solid_pmt).at(all_pos_pmt[2][0])
  .subtract(solid_pmt).at(all_pos_pmt[3][0])
  .subtract(solid_pmt).at(all_pos_pmt[4][0])
  .subtract(solid_pmt).at(all_pos_pmt[5][0])
  .subtract(solid_pmt).at(all_pos_pmt[6][0])
  .name("PMTplateBottom1").place(steel).in(vessel).at_z(fcp.PMTplateBottom1_pos_z).check_overlaps().now();;
}

G4PVPlacement* GeometryV2() {
  field_cage_parameters fcp = version2_parameters();
  ensure_initialized(fcp);
      
  auto vessel_steel = n4::tubs("vessel_steel").r_inner(fcp.vessel_rad).r(fcp.vessel_out_rad).z(fcp.vessel_out_length).volume(steel); //esto no me da tapas, que realmente me viene bien, pero es un poco raro
  n4::place(vessel_steel).in(world).at_z(fcp.vessel_z).check_overlaps().now();
  auto vessel       = n4::tubs("GasVessel").r(fcp.vessel_rad).z(fcp.vessel_length).volume(gas);
  n4::place(vessel).in(world).at_z(fcp.vessel_z).check_overlaps().now();
  
  place_pmt_holder_in(vessel, fcp);
  
  return n4::place(world).now();
}

