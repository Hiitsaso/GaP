#ifndef WLS_H
#define WLS_H

#include "g4-mandatory.hh"
#include "nain4.hh"
#include "Physics.hh"

#include <G4OpticalPhoton.hh>
#include <Randomize.hh>


class WLS : public G4VProcess {
public:
    WLS(const G4String& name = "WLS") : G4VProcess(name) {}
    
    G4VParticleChange* PostStepDoIt(const G4Track& track, const G4Step& step) {
        G4VParticleChange* particleChange = new G4ParticleChange();
        
		G4String particleType = track.GetDefinition()->GetParticleName();	
		if (step.GetPreStepPoint() -> GetTouchableHandle() -> GetVolume() -> GetLogicalVolume() -> GetName() == "CoatingTPB"){
			if (particleType == "opticalphoton"){
			
				G4DynamicParticle* secondaryParticle = new G4DynamicParticle(
					n4::find_particle("opticalphoton"),
					track.GetMomentumDirection(),
					1*eV);
				G4Track* secondaryTrack = new G4Track( 
					secondaryParticle,
					track.GetGlobalTime(),
					step.GetPostStepPoint() -> GetPosition());
			
				particleChange->SetNumberOfSecondaries(1);
				particleChange->AddSecondary(secondaryTrack);
				particleChange->ProposeTrackStatus(fStopAndKill);
			}
		}
		
		return particleChange;
	}
    
    G4double GetMeanFreePath(const G4Track& aTrack, G4double, G4ForceCondition*) {
        return DBL_MAX;
    }
};

#endif
