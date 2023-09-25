#include "nain4.hh"
#include "g4-mandatory.hh"

#include "PositionGenerator.hh"
#include "GeometryV1.hh"

#include <G4SystemOfUnits.hh>
#include <G4RandomDirection.hh>

G4ThreeVector random_generator_inside_drift(std::optional<G4double> fixed_z){
	field_cage_parameters fcp = model_something_old();
	auto meshBracket_rad_     = 180./2 *mm;
    
    auto zmin  = fcp.drift_z_new - fcp.drift_length/2;
    auto zmax  = fcp.drift_z_new + fcp.drift_length/2;
    
    auto r     = G4RandFlat::shoot(   0., meshBracket_rad_);
    auto angle = G4RandFlat::shoot(   0.,           2*M_PI);
    auto z     = fixed_z.has_value()
               ? fixed_z.value()
               : G4RandFlat::shoot( zmin,             zmax);

    auto pos_x = r * cos(angle);
    auto pos_y = r * sin(angle);
    auto pos_z = z;
   
   return {pos_x, pos_y, pos_z};
}

G4ThreeVector random_generator_inside_el(std::optional<G4double> fixed_z){    
	field_cage_parameters fcp = model_something_old();
	auto meshBracket_rad_     = 180./2 *mm;
	
    auto zmin  = fcp.el_z - fcp.el_length/2;
    auto zmax  = fcp.el_z + fcp.el_length/2;
    
    auto r     = G4RandFlat::shoot(   0., meshBracket_rad_);
    auto angle = G4RandFlat::shoot(   0.,           2*M_PI);
    auto z     = G4RandFlat::shoot( zmin,             zmax);

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
