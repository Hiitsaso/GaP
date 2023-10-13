#include "nain4.hh"
#include "g4-mandatory.hh"

//#include <G4SystemOfUnits.hh>

#include "detector.hh"

bool process_hits_anode(G4Step *step){			
	const std::string& filename_map = "Test_anode_vessel_2.txt";
	//~ const std::string& filename_map_primaries = "nan.txt";
	G4Track* track = step -> GetTrack();
	G4String particleType = track->GetDefinition()->GetParticleName();			
	G4int hits_check = 0;
	
	G4ThreeVector position     = track -> GetVertexPosition();
	G4ThreeVector position_hit = step  -> GetPostStepPoint() -> GetPosition();
	int colWidth = 20;
	
	//G4cout << "*************************************  :)  " << particleType << "  (:  *************************************"  << G4endl;   
	
	if (particleType == "opticalphoton"){ 
	track -> SetTrackStatus(fStopAndKill);
	
	hits_check = 1;
	//G4cout << "*************************************  :)  OUCH  (:  *************************************"  << G4endl; 
				
	}
	
	std::ofstream file1(filename_map, std::ios::app);
	file1 << std::left << std::setw(colWidth) << position.x();
	file1 << std::left << std::setw(colWidth) << position.y();
	file1 << std::left << std::setw(colWidth) << position.z();
	file1 << std::left << std::setw(colWidth) << position_hit.x();
	file1 << std::left << std::setw(colWidth) << position_hit.y();
	file1 << std::left << std::setw(colWidth) << position_hit.z();
	file1 << std::left << std::setw(colWidth) << hits_check;
	file1 << std::endl;
	file1.close();
	
	return true;
}

bool process_hits(G4Step *step){			
	//~ const std::string& filename_map = "files_OneSiPM/OpticalPhoton_420nm_S1_1000000.txt";
	const std::string& filename_map = "files_OneSiPM/nan.txt";
	G4Track* track = step -> GetTrack();
	G4String particleType = track->GetDefinition()->GetParticleName();			
	G4int hits_check = 0;
	
	G4ThreeVector position     = track -> GetVertexPosition();
	G4ThreeVector position_hit = step  -> GetPreStepPoint() -> GetPosition();
	
	G4String volume = step -> GetPreStepPoint() -> GetTouchableHandle() -> GetVolume() -> GetLogicalVolume() -> GetName();
	int colWidth = 20;
	
	if (position == position_hit && volume == "CathodeRing0"){ //That means that it has been generated inside the CathodeRing0¿?
	track -> SetTrackStatus(fStopAndKill);
	G4cout << "*************************************  :)  I'M DEAD  (:  *************************************"  << G4endl; 

    }
	
	if (particleType == "opticalphoton"){ 
	track -> SetTrackStatus(fStopAndKill);
	
	hits_check = 1;
	G4cout << "*************************************  :)  OUCH  (:  *************************************"  << G4endl; 
				
	}
	
	std::ofstream file1(filename_map, std::ios::app);
	file1 << std::left << std::setw(colWidth) << position.x();
	file1 << std::left << std::setw(colWidth) << position.y();
	file1 << std::left << std::setw(colWidth) << position.z();
	file1 << std::left << std::setw(colWidth) << position_hit.x();
	file1 << std::left << std::setw(colWidth) << position_hit.y();
	file1 << std::left << std::setw(colWidth) << position_hit.z();
	file1 << std::left << std::setw(colWidth) << hits_check;
	file1 << std::endl;
	file1.close();
	
	return true;
}
