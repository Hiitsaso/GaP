#include "nain4.hh"
#include "g4-mandatory.hh"

#include "PositionGenerator.hh"
#include "GeometryV2.hh"

#include <G4SystemOfUnits.hh>
#include <G4RandomDirection.hh>

G4ThreeVector random_generator_inside_S1(std::optional<G4double> fixed_z){
	field_cage_parameters fcp = version2_parameters();
	    
    //~ auto zmin  = fcp.drift_z + fcp.mesh_thickn/2;
    //~ auto zmax  = fcp.teflon_cage_z + fcp.teflon_cage_length/2 - fcp.teflon_cage_thickn - fcp.tpb_coating_thickn;
    //~ auto rmax  = fcp.teflon_cage_rad - fcp.tpb_coating_thickn;
    
    auto zmin  = fcp.S1_z - fcp.S1_lenght/2; 
    auto zmax  = fcp.S1_z + fcp.S1_lenght/2; 
    auto rmax  = fcp.S1_rad;
    
    auto r     = G4RandFlat::shoot(0.,   rmax);
    auto angle = G4RandFlat::shoot(0., 2*M_PI);
    auto z     = fixed_z.has_value()
               ? fixed_z.value()
               : G4RandFlat::shoot(zmin, zmax);

    auto pos_x = r * cos(angle);
    auto pos_y = r * sin(angle);
    auto pos_z = z;
   
   return {pos_x, pos_y, pos_z};
}

G4ThreeVector random_generator_inside_S2(std::optional<G4double> fixed_z){    
	field_cage_parameters fcp = version2_parameters();
	
    //~ auto zmin  = fcp.cathode_z + fcp.mesh_thickn/2;
    //~ auto zmax  = fcp.gate_z    - fcp.mesh_thickn/2;
    //~ auto rmax  = fcp.cathBracket_rad + fcp.cathBracket_thickn;
    
    auto zmin  = fcp.S2_z - fcp.S2_lenght/2; 
    auto zmax  = fcp.S2_z + fcp.S2_lenght/2; 
    auto rmax  = fcp.S2_rad;
    
    auto r     = G4RandFlat::shoot(0.,   rmax);
    auto angle = G4RandFlat::shoot(0., 2*M_PI);
    auto z     = G4RandFlat::shoot(zmin, zmax);

    auto pos_x = r * cos(angle);
    auto pos_y = r * sin(angle);
    auto pos_z = z;
   
   return {pos_x, pos_y, pos_z};
}

G4ThreeVector random_generator_tpb(){  
	auto delta_tpb = 1.4985;
	const auto quartz_window_rad    = 108./2  *mm;
	const auto quartz_window_thickn = 3       *mm;
	const auto tpb_coating_thickn   = 3       *micrometer;  
	auto quartz_window_z = 35.495*mm + quartz_window_thickn/2;
	auto tpb_coating_z = quartz_window_z - quartz_window_thickn/2 - tpb_coating_thickn/2 - delta_tpb;
    
    auto r     = G4RandFlat::shoot(   0., quartz_window_rad);
    auto angle = G4RandFlat::shoot(   0.,           2*M_PI);

    auto pos_x = r * cos(angle);
    auto pos_y = r * sin(angle);
    auto pos_z = -tpb_coating_z;
   
   return {pos_x, pos_y, pos_z};
}
