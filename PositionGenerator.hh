#ifndef POSITIONGENERATOR_H
#define POSITIONGENERATOR_H

G4ThreeVector random_generator_inside_drift(std::optional<G4double> fixed_z);
G4ThreeVector random_generator_inside_el(std::optional<G4double> fixed_z);
G4ThreeVector random_generator_tpb();

#endif
